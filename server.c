#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
int main()
{
        int s_fd;
        int n_read;
        char readBuf[128];//定义一个数组
 
        char *msg = "I got your message";
        struct sockaddr_in s_addr;
        struct sockaddr_in c_addr;
        memset(&s_addr,0,sizeof(struct sockaddr_in)); //一般来说先清空空间数据，再配置。避免结构体里面有杂乱数据
        memset(&c_addr,0,sizeof(struct sockaddr_in));
 
        //1.socket
        s_fd = socket(AF_INET,SOCK_STREAM,0);
        if(s_fd == -1){
                perror("socked");
                exit(-1);
        }
 
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(8989);
        s_addr.sin_addr.s_addr=INADDR_ANY;
 
        //2.bind
        bind(s_fd, (struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
 
        //3.listen
        listen(s_fd,10);
 
        //4.accept
        int clen = sizeof(struct sockaddr_in);//长度
        int c_fd = accept(s_fd,(struct sockaddr *)&c_addr, &clen);
        
        if(c_fd == -1){
                perror("accept");
        }
        //成功则打印客户端ip地址
        printf("get connect:%s\n",inet_ntoa(c_addr.sin_addr));    //inet_ntoa()函数，把网络格式的 IP 地址转为字符串形式
 
//服务端与客户端之间数据交互
 
        //5.read
        n_read = read(c_fd,readBuf,128);//把客户端的内容读到readBuf
        
        if(n_read == -1){
                perror("read");
        }else{
                printf("get message: %d,%s\n",n_read,readBuf);//打印readBuf中内容
        }
 
        //6.write
        write(c_fd,msg,strlen(msg));//写入操作
 
        return 0;
}
