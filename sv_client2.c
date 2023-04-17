#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <time.h>

int main(int argc,char * argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[256]="";
    char mssv[100];
    char hoTen[100];
    char ngaySinh[100];
    char diemTrungBinh[100];


    printf("nhập MSSV: ");
    fgets(mssv, sizeof(mssv), stdin);
    mssv[strcspn(mssv, "\n")] = '\0';
    strcat(buf, " ");
    strcat(buf, mssv);
    fflush(stdin);

    printf("nhập họ tên: ");
    fgets(hoTen, sizeof(hoTen), stdin);
    hoTen[strcspn(hoTen, "\n")] = '\0';
    strcat(buf, " ");
    strcat(buf, hoTen);
    fflush(stdin);

    printf("nhập ngày sinh: ");
    fgets(ngaySinh, sizeof(ngaySinh), stdin);
    ngaySinh[strcspn(ngaySinh, "\n")] = '\0';
    strcat(buf, " ");
    strcat(buf, ngaySinh);
    fflush(stdin);

    printf("nhập điểm trung bình: ");
    fgets(diemTrungBinh, sizeof(diemTrungBinh), stdin);
    diemTrungBinh[strcspn(diemTrungBinh, "\n")] = '\0';
    strcat(buf, " ");
    strcat(buf, diemTrungBinh);
    fflush(stdin);

    //thời gian
    char buf1[256];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buf1, "%d-%02d-%02d %02d:%02d:%02d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    
    strcat(buf1,buf);

    send(client, buf1, strlen(buf1), 0);
    close(client);
}
