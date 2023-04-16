#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[256] = "thông tin sinh viên:\n";
    char mssv[100];
    char hoTen[100];
    char ngaySinh[100];
    char diemTrungBinh[100];

    printf("nhập MSSV: ");
    fgets(mssv, sizeof(mssv), stdin);
    strcat(buf, "mã số sinh viên: ");
    strcat(buf, mssv);
    fflush(stdin);

    printf("nhập họ tên: ");
    fgets(hoTen, sizeof(hoTen), stdin);
    strcat(buf, "họ tên: ");
    strcat(buf, hoTen);
    fflush(stdin);

    printf("nhập ngày sinh: ");
    fgets(ngaySinh, sizeof(ngaySinh), stdin);
    strcat(buf, "ngày sinh: ");
    strcat(buf, ngaySinh);
    fflush(stdin);

    printf("nhập điểm trung bình: ");
    fgets(diemTrungBinh, sizeof(diemTrungBinh), stdin);
    strcat(buf, "điểm trung bình: ");
    strcat(buf, diemTrungBinh);
    fflush(stdin);

    send(client, buf, strlen(buf), 0);
    close(client);
}
