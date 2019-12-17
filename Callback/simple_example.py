'''
@Description: 回调函数python版本示例
@Author: 陆海
@Date: 2019-12-17 17:56:50
@LastEditTime: 2019-12-17 18:08:21
@LastEditors: Please set LastEditors
'''

def double(x):
    return x*2

def quadruple(x):
    return x*4

def getOddNumber(k, getNumber):
    return 1 + getNumber(k)

def main():
    k = 1
    
    i = getOddNumber(k, double)
    print(i)

    i = getOddNumber(k, quadruple)
    print(i)

    i = getOddNumber(k, lambda x:8*x)
    print(i)

if __name__ == "__main__":
    main()