import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MathClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 5100);
            MathOps mathOps = (MathOps) registry.lookup("MathOps");

            // Arithmetic Operations
            System.out.println("Addition: " + mathOps.add(5, 3));
            System.out.println("Subtraction: " + mathOps.subtract(5, 3));
            System.out.println("Multiplication: " + mathOps.multiply(5, 3));
            System.out.println("Division: " + mathOps.divide(5, 3));

            // Trigonometric Operations
            System.out.println("Sine of 30 degrees: " + mathOps.sin(30));
            System.out.println("Cosine of 60 degrees: " + mathOps.cos(60));
            System.out.println("Tangent of 45 degrees: " + mathOps.tan(45));
            System.out.println("Cotangent of 90 degrees: " + mathOps.cot(90));
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

