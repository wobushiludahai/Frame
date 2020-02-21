# -*- coding:utf-8 -*-
def shell_sort(list):
	length=len(list)
	dist=int(length/2)
	while dist>0:
		for i in range(dist,length):
			temp=list[i]
			j=i
			while j>=dist and temp<list[j-dist]:
				list[j]=list[j-dist]
				j-=dist
			list[j]=temp
		dist = int(dist/2)
	return list

#测试
print("希尔排序测试")
print("排序前: ")
testbuf= [100, 7, 9, -2, 20, -50]
print(testbuf)
sorted_list = shell_sort(testbuf)
print("排序后: ")
print(sorted_list)