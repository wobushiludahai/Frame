# -*- coding:utf-8 -*-
def select_sort(raw_list):
    length=len(raw_list)
    for index in range(length):
        for i in range(index,length):
            if raw_list[index]>raw_list[i]:
                raw_list[index],raw_list[i]=raw_list[i],raw_list[index]
    return raw_list

print("选择排序测试")
print("排序前: ")
testbuf= [100, 7, 9, -2, 20, -50]
print(testbuf)
sorted_list = select_sort(testbuf)
print("排序后: ")
print(sorted_list)