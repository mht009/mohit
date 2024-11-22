import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class MathClient {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int a = scan.nextInt();
        int b = scan.nextInt();

        int angle = scan.nextInt();
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 5100);
            MathOps mathOps = (MathOps) registry.lookup("MathOps");

            // Arithmetic Operations
            System.out.println("Addition: " + mathOps.add(a, b));
            System.out.println("Subtraction: " + mathOps.subtract(a, b));
            System.out.println("Multiplication: " + mathOps.multiply(a, b));
            System.out.println("Division: " + mathOps.divide(a, b));

            // Trigonometric Operations
            System.out.println("Sine of "+ angle+" degrees: " + mathOps.sin(angle));
            System.out.println("Cosine of "+ angle+" degrees: " + mathOps.cos(angle));
            System.out.println("Tangent of "+ angle+" degrees: " + mathOps.tan(angle));
            System.out.println("Cotangent of "+ angle+" degrees: " + mathOps.cot(angle));
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

