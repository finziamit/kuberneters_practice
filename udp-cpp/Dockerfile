FROM ubuntu:24.04
RUN apt-get update && apt-get install -y build-essential
WORKDIR /app
COPY server.cpp .
COPY client.cpp .
RUN g++ -o udp-server server.cpp
RUN g++ -o udp-client client.cpp
EXPOSE 6000/udp
CMD ["./udp-server"]