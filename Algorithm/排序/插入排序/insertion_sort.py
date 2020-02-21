# -*- coding:utf-8 -*-
def insert_sort(raw_list):
    length = len(raw_list)
    for i in range(1, length):
        temp = raw_list[i]
        #j从i-1 到 0倒序
        for j in range(i-1,-1,-1):
            if(raw_list[j]<=temp):
                break
            if(raw_list[j]>temp):
                raw_list[j],raw_list[j+1] = temp,raw_list[j]
    return raw_list

#测试
print("插入排序测试")
print("排序前: ")
testbuf= [100, 7, 9, -2, 20, -50]
print(testbuf)
sorted_list = insert_sort(testbuf)
print("排序后: ")
print(sorted_list)