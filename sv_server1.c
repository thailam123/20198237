#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client = accept(listener,
                        (struct sockaddr *)&client_addr,
                        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n",
           client,
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    char buf[256];
    printf("đang chờ: \n");
    int ret = recv(client, buf, sizeof(buf), 0);
    if (ret < sizeof(buf))
        buf[ret] = 0;
    printf("đã nhận: ");
    printf("%s\n", buf);

    close(client);
    close(listener);
}
