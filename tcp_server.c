//bài tập 2
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

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

    char *filename = argv[2];
    FILE *f = fopen(filename, "rb");
    char buf[2048];
    int ret;
    while (!feof(f))
    {
        ret = fread(buf, 1, sizeof(buf), f);
        if (ret <= 0)
            break;
        send(client, buf, ret, 0);
    }

    fclose(f);
    filename = argv[3];
    f = fopen(filename, "wb");

    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;
        fwrite(buf, 1, ret, f);
    }
    fclose(f);

    close(client);
}
