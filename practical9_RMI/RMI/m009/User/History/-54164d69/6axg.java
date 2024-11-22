import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MathServer {
    public static void main(String[] args) {
        try {
            MathOps mathOps = new MathOpsImpl();
            Registry registry = LocateRegistry.createRegistry(5100);
            registry.rebind("MathOps", mathOps);
            System.out.println("Math Server is ready.");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

