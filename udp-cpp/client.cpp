#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
    const char* host = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? std::stoi(argv[2]) : 6000;
    const char* msg = (argc > 3) ? argv[3] : "hello from udp client";

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); return 1; }

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    inet_pton(AF_INET, host, &serv.sin_addr);

    ssize_t sent = sendto(sockfd, msg, strlen(msg), 0, (sockaddr*)&serv, sizeof(serv));
    if (sent < 0) { perror("sendto"); return 1; }

    char buf[2048];
    sockaddr_in from{};
    socklen_t fromlen = sizeof(from);
    ssize_t n = recvfrom(sockfd, buf, sizeof(buf)-1, 0, (sockaddr*)&from, &fromlen);
    if (n < 0) { perror("recvfrom"); return 1; }
    buf[n] = '\0';
    std::cout << "Echo: " << buf << std::endl;
    close(sockfd);
    return 0;
}
