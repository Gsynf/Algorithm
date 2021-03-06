/*
由于这道题只要求打印最长的增长序列长度，并不要求打印最长增长序列，所以巧妙的利用了替换，如果nums中的数大于dp中最后一个数，
那么就把这个数继续增加到dp中，如果这个数小于dp最后一个数，就把这个数替换了dp中第一个大于它的数，理解时可将lenOfLIS中注释取消掉
*/
#include "pch.h"
#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

int lenOfLIS(vector<int> &nums)
{
	vector<int> dp{ nums[0] };      //指定容器dp中对象的初值列表
	for (int i = 1; i != nums.size(); ++i)
	{
		if (nums[i] > *dp.rbegin())   //始终与dp中最后一个元素，也就是dp中目前最大的元素比较
			dp.push_back(nums[i]);
		else
		{
			std::vector<int>::iterator it = lower_bound(dp.begin(), dp.end(), nums[i]);  //前闭后开,找到大等于num[i]的的第一个元素的位置
			//std::cout << "lower_bound at position " << (it - dp.begin()) << '\n';
			*it = nums[i]; 
			//std::cout << "*it is " << *it << '\n';
			//std::cout << "dp[0] is " << dp.front() << '\n';
			//std::cout << "dp[end] is " << dp.back() << '\n';
		}
	}
	return dp.size();
}

int main()
{
	
	int t = 0;   //T groups test cases
	scanf_s("%d", &t);
	int output[100000];    //存放t次的计算结果
	for(int i=0;i < t; i++)
	{ 
		int n = 0;     //the length of sequence N
		int a[100000];
		scanf_s("%d", &n);
		if (n == 0) return 0;
		for (int i = 0; i < n; i++)
		{
			scanf_s("%d", &a[i]);
		}
		vector<int> seq(a, a + n); // seq : Input Vector
		output[i] = int(lenOfLIS(seq));
	}
	for (int i = 0; i < t; i++)
	{
		printf("%d\n", output[i]);
	}
	return 0;
}
 