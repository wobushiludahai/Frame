# -*- coding:utf-8 -*-
def kp(arr,i,j):#快排总函数
                #制定从哪开始快排
    if i<j:
        base=kpgc(arr,i,j)
        kp(arr,i,base)
        kp(arr,base+1,j)
def kpgc(arr,i,j):#快排排序过程
    base=arr[i]
    while i<j:
        while i<j and arr[j]>=base:
            j-=1
        while i<j and arr[j]<base:
            arr[i]=arr[j]
            i+=1
            arr[j]=arr[i]
        arr[i]=base
    return i

print("快速排序测试")
print("排序前: ")
testbuf= [100, 7, 9, -2, 20, -50]
print(testbuf)
kp(testbuf, 0, len(testbuf) -1)
print("排序后: ")
print(testbuf)