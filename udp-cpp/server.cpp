#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
    const int PORT = std::getenv("PORT") ? std::stoi(std::getenv("PORT")) : 6000;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); return 1; }

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    if (bind(sockfd, (sockaddr*)&serv, sizeof(serv)) < 0) { perror("bind"); return 1; }

    std::cout << "UDP server listening on 0.0.0.0:" << PORT << std::endl;

    char buf[2048];
    sockaddr_in cli{};
    socklen_t cli_len = sizeof(cli);
    while (true) {
        ssize_t n = recvfrom(sockfd, buf, sizeof(buf), 0, (sockaddr*)&cli, &cli_len);
        if (n < 0) { perror("recvfrom"); break; }
        std::cout << "Received " << n << " bytes from "
                  << inet_ntoa(cli.sin_addr) << ":" << ntohs(cli.sin_port) << std::endl;
        ssize_t s = sendto(sockfd, buf, n, 0, (sockaddr*)&cli, cli_len);
        if (s < 0) { perror("sendto"); break; }
    }
    close(sockfd);
    return 0;
}
