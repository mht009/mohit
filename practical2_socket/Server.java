import java.io.*;
import java.net.*;
import java.util.*;
import org.json.JSONObject;

public class Server {
    private static final String SERVER_IP = "10.70.33.162";
    private static final int SERVER_PORT = 8000;
    private static final Map<Socket, String> clients = new HashMap<>();

    public static void main(String[] args) {
        System.out.println("Server started on " + SERVER_IP + ":" + SERVER_PORT);
        try (ServerSocket serverSocket = new ServerSocket(SERVER_PORT, 50, InetAddress.getByName(SERVER_IP))) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println(
                        "New client connected: " + clientSocket.getInetAddress() + ":" + clientSocket.getPort());

                synchronized (clients) {
                    clients.put(clientSocket,
                            clientSocket.getInetAddress().getHostAddress() + ":" + clientSocket.getPort());
                    updateClientList();
                }

                new Thread(() -> handleClient(clientSocket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {

            String message;
            while ((message = in.readLine()) != null) {
                JSONObject data = new JSONObject(message);

                if ("message".equals(data.getString("type"))) {
                    String[] recipient = data.getString("recipient_ip").split(":", 2);
                    String recipientIp = recipient[0].trim();
                    int recipientPort = Integer.parseInt(recipient[1].trim());

                    Socket recipientSocket = findClientSocket(recipientIp, recipientPort);
                    if (recipientSocket != null) {
                        PrintWriter recipientOut = new PrintWriter(recipientSocket.getOutputStream(), true);
                        JSONObject response = new JSONObject();
                        response.put("type", "message");
                        response.put("message", data.getString("message"));
                        response.put("sender_ip", data.getString("sender_ip"));
                        recipientOut.println(response.toString());
                    }
                } else if ("disconnect".equals(data.getString("type"))) {
                    synchronized (clients) {
                        clients.remove(clientSocket);
                        updateClientList();
                    }
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static Socket findClientSocket(String ip, int port) {
        synchronized (clients) {
            for (Map.Entry<Socket, String> entry : clients.entrySet()) {
                String[] clientInfo = entry.getValue().split(":", 2);
                String clientIp = clientInfo[0].trim();
                int clientPort = Integer.parseInt(clientInfo[1].trim());
                if (ip.equals(clientIp) && port == clientPort) {
                    return entry.getKey();
                }
            }
        }
        return null;
    }

    private static void updateClientList() {
        List<String> clientList = new ArrayList<>();
        synchronized (clients) {
            for (String clientInfo : clients.values()) {
                clientList.add(clientInfo);
            }
            clientList.add(SERVER_IP + ":" + SERVER_PORT);
        }
        JSONObject update = new JSONObject();
        update.put("type", "client_list");
        update.put("client_list", clientList);

        for (Socket clientSocket : clients.keySet()) {
            try {
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                out.println(update.toString());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
