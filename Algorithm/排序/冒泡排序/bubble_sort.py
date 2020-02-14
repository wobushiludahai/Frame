# -*- coding:utf-8 -*-
def bubble_sort(raw_list):
    length=len(raw_list)
    for index in range(length):
        for i in range(1,length-index):
            if raw_list[i-1]>raw_list[i]:
                raw_list[i],raw_list[i-1]=raw_list[i-1],raw_list[i]
    return raw_list

print("冒泡排序测试")
print("排序前: ")
testbuf= [100, 7, 9, -2, 20, -50]
print(testbuf)
sorted_list = bubble_sort(testbuf)
print("排序后: ")
print(sorted_list)