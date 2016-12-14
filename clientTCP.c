#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define MY_PORT 3490

int main(){
    int s =-1;
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(MY_PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
/*создадим сокет*/
    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("Невозможно создать сокет\n");
        return -1;
    }
    if(connect(s, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        perror("Ошибка создания виртуального канала");
        return -1;
    }

    char buf[100]="Hello";
    send(s, buf, strlen(buf), 0);
    memset(buf,0,sizeof(buf));
    recv(s, buf, sizeof(buf), 0);
    printf("%s\n",buf);
    close(s);
    return 0;
}
