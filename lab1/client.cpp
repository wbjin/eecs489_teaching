#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    // Make a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == -1)  {
        perror("error making socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    struct hostent *host = gethostbyname("127.0.0.1");
    if (host == NULL) {
        perror("error gethostbyname");
        exit(1);
    }
    memcpy(&addr.sin_addr, host->h_addr, host->h_length);
    addr.sin_port = htons(8080);  // server port

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("error connecting");
        exit(1);
    }

    // Send a message
    char message[] = "Hi server!";
    if (send(sockfd, message, sizeof(message), 0) == -1) {
        perror("send");
        exit(1);
    }

    close(sockfd);
    shutdown(sockfd, SHUT_RDWR);
}
