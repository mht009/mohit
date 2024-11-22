import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class DataApplet extends Applet {
    private String data = "Fetching data...";

    @Override
    public void init() {
        setSize(300, 200);
        fetchData();
    }

    @Override
    public void paint(Graphics g) {
        g.drawString(data, 10, 20);
    }

    private void fetchData() {
        new Thread(() -> {
            try {
                URL url = new URL("http://your-server-address/data");
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setRequestMethod("GET");
                BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
                data = reader.readLine();
                reader.close();
                repaint();
                callJavaScriptFunction(data);
            } catch (Exception e) {
                e.printStackTrace();
                data = "Error fetching data.";
                repaint();
            }
        }).start();
    }

    private void callJavaScriptFunction(String data) {
        getAppletContext().showDocument(getDocumentBase(), "JavaScriptCallback", data);
    }
}
