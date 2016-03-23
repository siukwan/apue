/*

描述:
用户输入有符号整型数组（十进制），去掉重复值后，按照升序输出整型数组（十进制）。
运行时间限制:	无限制
内存限制:	无限制
输入:
整数N，表示数组的个数；N个整数，整数之间以空格隔开
输出:
去掉重复后，按照升序输出数组
样例输入:
4 6 3 3 9
样例输出:
3 6 9
答案提示:

*/
#include <stdio.h>  
#include <iostream>  
#include <vector>  
#include <stack>  
#include <algorithm>  
#include <string>  
#include <unordered_map>  
#include <set>  
using namespace std;

int main()
{
	set<int> s;
	int n, d;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &d);
		s.insert(d);
	}

	for (auto i : s)
	{
		printf("%d ", i);
	}

	return 0;
}