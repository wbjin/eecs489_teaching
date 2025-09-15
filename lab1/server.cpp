#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 7123

int main() {
    // Make a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1)  {
        perror("error making socket");
        exit(1);
    }

    // Option for allowing you to reuse socket
    int yes {1};
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("error setsockopt");
        exit(1);
    }

    // Bind socket to a port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if (bind(sockfd, (sockaddr*)&addr, (socklen_t) sizeof(addr)) == -1) {
        perror("error binding socket");
        exit(1);
    }

    // Listen for incoming connections
    printf("Listening on port %d\n", PORT);
    if (listen(sockfd, 10) == -1) {
        perror("error listening");
        exit(1);
    }

    while (true) {
        // Accept new connection
        struct sockaddr_in connection;
        socklen_t size = sizeof(connection);
        int connectionfd = accept(sockfd, (struct sockaddr*)&connection, &size);

        // Print what IP address connection is from
        char s[INET6_ADDRSTRLEN];
        printf("connetion from %s\n", inet_ntoa(connection.sin_addr));

        // Receive message
        char buf[1024];
        int ret {};
        if ((ret = recv(connectionfd, buf, sizeof(buf), 0)) == -1) {
            perror("recv");
            close(connectionfd);
            continue;
        }
        buf[ret] = '\0';

        printf("message: %s\n", buf);
        close(connectionfd);
    }

    close(sockfd);
}
