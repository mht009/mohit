import socket
import threading
import argparse

HOST = '127.0.0.1'
PORT = 1234
CLIENTS = {}


def broadcast_clients():
    clients_list = list(CLIENTS.keys())
    print(clients_list)

    data = ', '.join(clients_list)
    data = "Clients Online: " + data

    for client_socket in list(CLIENTS.values()):
        client_socket.send(data.encode('utf-8'))


def handle_client(client_socket):
    while True:
        data = client_socket.recv(1024)
        if not data:
            print("Recieved empty message")
            continue
        message = data.decode('utf-8')
        if message == 'quit':
            break
        # print(f"Received message: {message}")
        reciever, message = message.split('<-')
        reciever = reciever.strip()
        if reciever in list(CLIENTS.keys()):
            sender = [key for key, val in CLIENTS.items() if val ==
                      client_socket]
            message = sender[0] + ':' + message
            CLIENTS[reciever].send(message.encode('utf-8'))
            response = "Message sent to " + reciever
            client_socket.sendall(response.encode('utf-8'))
        else:
            response = "No client named " + reciever + " online."
            client_socket.sendall(response.encode('utf-8'))
            broadcast_clients()

    client_socket.close()
    broadcast_clients()


def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(5)
    print(f"Server listening on {HOST}:{PORT}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Accepted connection from {client_address}")
        data = client_socket.recv(1024)
        name = data.decode('utf-8')
        # socket_info = {
        #     "fd": client_socket.fileno(),
        #     "family": client_socket.family,
        #     "type": client_socket.type,
        #     "proto": client_socket.proto,
        #     "laddr": client_socket.getsockname(),  # Local address
        #     "raddr": client_socket.getpeername()   # Remote address
        # }
        CLIENTS[name] = client_socket

        print(CLIENTS)
        broadcast_clients()

        thread = threading.Thread(target=handle_client, args=(client_socket,))
        thread.start()


if __name__ == "__main__":
    main()
