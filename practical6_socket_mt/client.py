import socket
import threading
import argparse

HOST = '127.0.0.1'
PORT = 1234
NAME = ""


def handle_server(client_socket):
    while True:
        data = client_socket.recv(1024)
        if not data:
            print("Recieved empty message")
            continue
        message = data.decode('utf-8')

        print(f"{message}")
    client_socket.close()


def main():
    parser = argparse.ArgumentParser(
        description="A simple argparse example")
    parser.add_argument("-un", "--username", type=str,
                        required=True, help="client\'s username")

    args = parser.parse_args()

    NAME = args.username
    NAME = NAME.strip()
    print(NAME)

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))

    client_socket.send(NAME.encode('utf-8'))

    server_handler = threading.Thread(
        target=handle_server, args=(client_socket,))
    server_handler.start()

    print("Enter your message(client_username <- message): ")
    while True:
        message = input()
        if len(message.split('<-')) == 2:
            client_socket.sendall(message.encode('utf-8'))
            data = client_socket.recv(1024)
            response = data.decode('utf-8')
            print(f"Server response: {response}")
        else:
            print("Format incorrect\tclient_username<-message")


if __name__ == "__main__":
    main()
