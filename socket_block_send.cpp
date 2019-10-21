#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<string.h>

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        std::cout<<"create socket error"<<std::endl;
        return -1;
    }
    
    sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    
    if(bind(listenfd, (sockaddr*)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout<<"bind error"<<std::endl;
        close(listenfd);
        return -1;
    }
    
    if(listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout<<"listen error"<<std::endl;
        close(listenfd);
        return -1;
    }
    
    while(true)
    {   
        sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        
        //accept client connect
        int clientfd = accept(listenfd, (sockaddr*)&clientaddr, &clientaddrlen);
        if(clientfd != -1)
        {
            //no error
            //data process
            
            close(clientfd);
        }
        else
        {
            break;
        }
    }
    close(listenfd);
    return 0;
}
