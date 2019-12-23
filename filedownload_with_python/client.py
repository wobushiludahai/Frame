#客户端代码
import socket

if __name__ == '__main__':
    #创建套接字
    tcp_client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #连接服务器
    server_ip = input("请输入服务器IP：")
    tcp_client_socket.connect((server_ip, 3356))
    #发送下载文件的请求
    file_name = input("请输入要下载的文件名：")
    #编码
    file_name_data  = file_name.encode("utf-8")
    #发送文件下载请求数据
    tcp_client_socket.send(file_name_data)
    #接收要下载的文件信息
    file_info = tcp_client_socket.recv(1024)
    #文件信息解码
    info_decode = file_info.decode("utf-8")
    print(info_decode)
    #获取文件大小   
    filesize = float(info_decode.split(':')[1].split('MB')[0])
    filesize2 = filesize*1024
    opts = input("是否下载？（y 确认  q 取消）")
    if opts == 'q':
        print("下载取消程序退出")
    else:
        print("正在下载 》》》")
        #向服务器确认正在下载
        tcp_client_socket.send(b'y')

        #把数据写入到文件里
        with open("./" + file_name, "wb") as file:
            #目前接收到的数据包数目
            cnum = 0

            while True:
                #循环接收文件数据
                file_data = tcp_client_socket.recv(1024)
                #接收到数据
                if file_data:
                    #写入数据
                    file.write(file_data)
                    cnum  = cnum + 1
                    jindu = cnum/filesize2*100
                    print("当前已下载：%.2f%%"%(jindu), end = "\r")
                else:
                    print("下载结束!")
                    break
    #关闭套接字
    tcp_client_socket.close()