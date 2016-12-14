#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#define PORT 22222

struct msg{
    int len;
    char buf[80];
} obj;
int main(int n,char **arg){
    int s =-1;
    int i,j;
    struct sockaddr_in serv_addr,serv_addr2;
    strcpy(obj.buf,"Hi");
    obj.len=strlen(obj.buf);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("Невозможно создать сокет\n");
        return -1;
    }

    sendto(s, &obj, sizeof(struct msg), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    int serv_len = sizeof(serv_addr2);
    if(recvfrom(s, &obj, sizeof(struct msg), 0, (struct sockaddr*)&serv_addr2, &serv_len) < 0){
        return -1;
    }
    printf("Получено: %s Длина: %d\n", obj.buf,obj.len);

    close(s);
    return 0;
}
