import socket

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("0.0.0.0", 5000))
    s.listen(1)
    print("TCP Server running on port 5000")

    while True:
        conn, addr = s.accept()
        data = conn.recv(1024)
        conn.sendall(data)


if __name__ == "__main__":
    main()