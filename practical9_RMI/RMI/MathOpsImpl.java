import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class MathOpsImpl extends UnicastRemoteObject implements MathOps {
    protected MathOpsImpl() throws RemoteException {
        super();
    }

    public double add(double a, double b) throws RemoteException {
        return a + b;
    }

    public double subtract(double a, double b) throws RemoteException {
        return a - b;
    }

    public double multiply(double a, double b) throws RemoteException {
        return a * b;
    }

    public double divide(double a, double b) throws RemoteException {
        if (b == 0) throw new RemoteException("Division by zero");
        return a / b;
    }

    public double sin(double angle) throws RemoteException {
        return Math.sin(Math.toRadians(angle));
    }

    public double cos(double angle) throws RemoteException {
        return Math.cos(Math.toRadians(angle));
    }

    public double tan(double angle) throws RemoteException {
        return Math.tan(Math.toRadians(angle));
    }

    public double cot(double angle) throws RemoteException {   
        return 1/Math.tan(Math.toRadians(angle));
    }
}
