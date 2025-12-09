import socket

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("SERVER_IP", 5000))
    s.sendall(b"hello")
    print(s.recv(1024))


if __name__ == "__main__":
    main()