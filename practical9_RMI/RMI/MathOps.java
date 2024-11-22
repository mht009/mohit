import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MathOps extends Remote {
    double add(double a, double b) throws RemoteException;
    double subtract(double a, double b) throws RemoteException;
    double multiply(double a, double b) throws RemoteException;
    double divide(double a, double b) throws RemoteException;
    double sin(double angle) throws RemoteException;
    double cos(double angle) throws RemoteException;
    double tan(double angle) throws RemoteException;
    double cot(double angle) throws RemoteException;
}

