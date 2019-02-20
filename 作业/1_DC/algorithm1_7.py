#!usr/bin/env python3
#coding:utf-8
'''
输入list中元素个数，输入第几个
输入list
input默认为string，所以需要转化为整数
'''
import heapq
a,k= map(int,input().split())
nums=[]
num=input()
numlist=num.split(" ")
nums=[int(numlist[i]) for i in range(a)]
heapq.heapify(nums)
for i in range(k):
    res = heapq.heappop(nums)
print(res)