import socket
import os

HOST = "0.0.0.0"
PORT = int(os.environ.get("PORT", 5000))

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen()
    print(f"TCP server listening on {HOST}:{PORT}")
    while True:
        conn, addr = s.accept()
        with conn:
            print(f"Connection from {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received: {data!r}")
                conn.sendall(data)
