#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>

#define MY_PORT 3490

int main(){
    int s, ns;
    struct sockaddr_in serv_addr, clnt_addr;
    char buf[100];
    if((s=socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("Ошибка создания сокета");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(MY_PORT);

    if(bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Ошибка связывания сокета с адресом");
        return -1;
    }
    int length = sizeof(serv_addr);
    if(listen(s,5) < 0){
        perror("Ошибка вызова listen()");
        return -1;
    }
    int addrlen;

    addrlen = sizeof(clnt_addr);
    if((ns = accept(s, (struct sockaddr *)&clnt_addr, &addrlen)) < 0){
            perror("Ошибка приема запроса от клиента\n");
            return -1;
    }
    recv(ns, buf, sizeof(buf), 0);
    printf("%s\n",buf);

    send(ns, "Hi", strlen("Hi"), 0);
    close(ns);
    close(s);
    return 0;
}
