## attention
(1)mingw编译需要加上编译选项 -lws2_32  
示例：gcc server.c -o server -lws2_32
  
(2)tcp因为异步存在粘包问题(即数据间无边界性)