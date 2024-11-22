import java.io.*;
import java.net.*;
import java.util.Scanner;
import org.json.JSONObject;

public class Client {

    private String host;
    private int port;
    private Socket clientSocket;
    private String clientIp;
    private int clientPort;

    public Client(String host, int port) throws IOException {
        this.host = host;
        this.port = port;
        this.clientSocket = new Socket(this.host, this.port);
        this.clientIp = clientSocket.getLocalAddress().getHostAddress();
        this.clientPort = clientSocket.getLocalPort();
    }

    public void sendMessage() {
        try (PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)) {
            Scanner scanner = new Scanner(System.in);
            while (true) {
                System.out.println(
                        "Enter message (format: ip:port:message or 'server:port:message' to send to server): ");
                String messageInput = scanner.nextLine();
                String[] parts = messageInput.split(":", 3);
                String recipientIp = parts[0].trim();
                int recipientPort = Integer.parseInt(parts[1].trim());
                String message = parts[2].trim();

                if (recipientIp.equalsIgnoreCase("server")) {
                    recipientIp = host;
                    recipientPort = port;
                }

                JSONObject data = new JSONObject();
                data.put("type", "message");
                data.put("message", message);
                data.put("sender_ip", clientIp + ":" + clientPort);
                data.put("recipient_ip", recipientIp + ":" + recipientPort);

                out.println(data.toString());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void receiveMessage() {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))) {
            String message;
            while ((message = in.readLine()) != null) {
                JSONObject data = new JSONObject(message);
                if (data.getString("type").equals("message")) {
                    System.out.println("\nReceived message from " + data.getString("sender_ip") + ": "
                            + data.getString("message"));
                } else if (data.getString("type").equals("client_list")) {
                    System.out.println("\nClient list: " + data.getJSONArray("client_list").toString() + "\n");
                }
                System.out
                        .print("Enter message (format: ip:port:message or 'server:port:message' to send to server): ");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        System.out.println("Your IP: " + clientIp + ":" + clientPort);
        new Thread(this::receiveMessage).start();
        new Thread(this::sendMessage).start();
    }

    public static void main(String[] args) {
        try {
            Client client = new Client("10.70.33.162", 8000);
            client.run();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
