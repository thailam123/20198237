#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

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

    int client;

    // int client = accept(listener,
    //                     (struct sockaddr *)&client_addr,
    //                     &client_addr_len);

    // printf("Accepted socket %d from IP: %s:%d\n",
    //        client,
    //        inet_ntoa(client_addr.sin_addr),
    //        ntohs(client_addr.sin_port));
    // char *dia_chi_client = inet_ntoa(client_addr.sin_addr);

    char buf[256];
    char *dia_chi_client;
    // được truyền từ client sang
    char buf_nhan_duoc[256];

    FILE *fptr;
    char fname[20] = "sv_log.txt";

    while (1)
    {
        client = accept(listener,
                        (struct sockaddr *)&client_addr,
                        &client_addr_len);

        char *dia_chi_client = inet_ntoa(client_addr.sin_addr);

                int ret = recv(client, buf_nhan_duoc, sizeof(buf_nhan_duoc), 0);

        // if (ret <= 0)
        // {
        //     break;
        // }
        strcpy(buf, "");
        strcat(buf, dia_chi_client);
        strcat(buf, " ");
        if (ret < sizeof(buf_nhan_duoc))
            buf_nhan_duoc[ret] = 0;
        strcat(buf, buf_nhan_duoc);
        printf("%s\n", buf);

        fptr = fopen(fname, "a");
        fputs("\n", fptr);
        fputs(buf, fptr);
        fclose(fptr);
    }

    close(client);
    close(listener);
    fclose(fptr);
}
