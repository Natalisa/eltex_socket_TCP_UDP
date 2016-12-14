#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define PORT 22222

struct msg{
    int len;
    char buf[80];
};

int main(){
    int s =-1;
    struct sockaddr_in serv_addr,clnt_addr;
    char buf[80] = "";
    if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("Невозможно создать сокет\n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    if(bind(s,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Ошибка вызова bind()");
        return -1;
    }
    int length = sizeof(serv_addr);
    if (getsockname(s, (struct sockaddr*)&serv_addr, &length)) {
        perror("Вызов getsockname неудачен.");
        return -1;
    }
    int clilen = sizeof(struct sockaddr);
    struct msg obj;
    if(recvfrom(s, &obj, sizeof(struct msg), 0, (struct sockaddr*)&clnt_addr, &clilen) < 0){
        perror("Ошибка при получении данных\n");
        return -1;
    }
    printf("Получено: %s Длина: %d\n", obj.buf,obj.len);
    strcpy(obj.buf,"Hello");
    obj.len = strlen(obj.buf);
    sendto(s, &obj, sizeof(struct msg), 0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));

    close(s);
    return 0;
}
