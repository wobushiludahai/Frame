## attention
(1)mingw编译需要加上编译选项 -lws2_32  
示例：gcc server.c -o server -lws2_32
  
(2)tcp因为异步存在粘包问题(即数据间无边界性)

(3)数据传输ack = seq + 收到的字节数 + 1  
  
(4)重传超时时间(RTO)使用自适应动态算法，重传次数因不同的系统不同  
(5)四次挥手后，客户端存在TIME_WAIT状态。即客户端回复最后ack包后，将等待2MSL（报文最大生存时间）  
(6)网络字节转换函数  
htons()：host to network short，将 short 类型数据从主机字节序转换为网络字节序。  
ntohs()：network to host short，将 short 类型数据从网络字节序转换为主机字节序。  
htonl()：host to network long，将 long 类型数据从主机字节序转换为网络字节序。  
ntohl()：network to host long，将 long 类型数据从网络字节序转换为主机字节序。  
