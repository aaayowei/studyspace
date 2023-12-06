#include <stdio.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
 
int main()
{
        int c_fd;
        int n_read;
        char readBuf[128];
       
       char *msg = "msg from client";
        struct sockaddr_in c_addr;
        memset(&c_addr,0,sizeof(struct sockaddr_in));
 
        //1.socket
        c_fd = socket(AF_INET,SOCK_STREAM,0);
        if(c_fd == -1){
                perror("socked");
                exit(-1);
        }
 
        c_addr.sin_family = AF_INET;
        c_addr.sin_port = htons(8989);
        inet_aton("192.168.56.102",&c_addr.sin_addr);
 
        //2.connect
        if(connect(c_fd,(struct sockaddr *)&c_addr,sizeof(struct sockaddr_in)) == -1){
                perror("connect");
                exit(-1);            //连接不到服务端会阻塞，出错直接跳出程序，以免搞崩代码
        }
        //3.send
        write(c_fd,msg,strlen(msg));
 
//读取服务端的信息
        //4.read
        n_read = read(c_fd,readBuf,128);
        if(n_read == -1){
                perror("read");
        }else{
                printf("get message from server: %d ,%s\n",n_read,readBuf);
        }
        return 0;
}
