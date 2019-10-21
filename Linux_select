select：检测一组socket中某个或某几个是否有事件。
    可读事件：recv/read/accept
    可写事件：send/write
    异常事件：socket出现异常
    
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, timeval *timeout);
nfds:       监听的socket的最大值加1
readfds:    需要监听可读事件的fd集合
writefds:   需要监听可写事件的fd集合
exceptfds:  需要监听异常事件的fd集合
timeout:    超时时间
        
//example
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#include<sys/time.h>
#include<vector>
#include<errno.h>

#define INVALID_FD -1

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
        close(listenfd):
        return -1;
    }
    
    std::vector<int> clientfds;
    int maxfd = listenfd;
    
    while(true)
    {
        fd_set readset;
        FD_ZERO(&readset);
        
        FD_SET(listenfd, &readset);
        for(int i=0;i<clientfds.size();++i)
        {
            if(clientfds[i] != INVALID_FD)
            {
                FD_SET(clientfds[i], &readset);
            }
        }
        
        timeval tm;
        tm.tv_sec = 1;
        tm.tv_usec = 0;
        
        int ret = select(maxfd + 1, &readset, NULL, NULL, &tm);
        if(ret == -1)
        {
            if(errno != EINTR)
                break;
        }
        else if(ret == 0)
        {
            std::cout<<"select timeout"<<std::endl;
            continue;
        }
        else
        {
            if(FD_ISSET(listenfd, &readset))
            {
                sockaddr_in clientaddr;
                socklen_t clientaddrlen = sizeof(clientaddr);
                
                int clientfd = accept(listenfd, (sockaddr*)&clientaddr, &clientaddrlen);
                if(clientfd == -1)
                {
                    std::cout<<"client connect error"<<std::endl;
                    break;
                }
                std::cout<<"accept a new client connection. fd is:"<<clientfd<<std::endl;
                clientfds.push_back(clientfd);
                if(clientfd > maxfd)
                    maxfd = clientfd;
            }
            else
            {
                char recvbuf[64];
                for(int i=0;i<clientfds.size();++i)
                {
                    if(clientfds[i] != INVALID_FD && FD_ISSET(clientfds[i], &readset))
                    {
                        memset(recvbuf, 0, sizeof(recvbuf));
                        int len = recv(clientfds[i], recvbuf, sizeof(recvbuf), 0);
                        if(len <= 0 && errno != EINTR)
                        {
                            std::cout<<"recv data error"<<std::endl;
                            close(clientfds[i]);
                            clientfds[i] = INVALID_FD;
                            continue;
                        }
                        std::cout<<"recv data from client:"<<clientfds[i]<<". data is:"<<recvbuf<<std::endl;
                    }                
                }
            }        
        }
    }
    for(int i=0;i<clientfds.size();++i)
    {
        if(clientfds[i] != INVALID_FD)
            close(clientfds[i]);
    }
    close(listenfd);
    return 0;
}
