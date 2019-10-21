#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000
#define SEND_DATA "hellodog"

int main()
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1)
    {
        std::cout<<"create client socket error"<<std::endl;
        return -1;
    }
    
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    //serveraddr.sin_addr.s_addr = htonl(0);
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    
    if(connect(clientfd, (sockaddr*)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout<<"connect error"<<std::endl;
        close(clientfd);
        return -1;
    }
    
    int count = 100;
    while(count--)
    {
        int len = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
        if(len != strlen(SEND_DATA))
        {
            std::cout<<"send data error"<<std::endl;
            break;
        }
    }
    close(clientfd);
    return 0;
}



