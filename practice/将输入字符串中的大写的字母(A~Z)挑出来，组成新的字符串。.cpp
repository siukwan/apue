/*
描述:
将输入字符串中的大写的字母(A~Z)挑出来，组成新的字符串。
运行时间限制:	无限制
内存限制:	128 MByte
输入:
字符串长度,字符串
输出:
大写字符串
样例输入:
9,AUStralia
样例输出:
AUS
答案提示:
1 输出的时候不需要考虑空格，只需要输出大写字符串，也就是说空格是忽略的
2 不需要考虑重复，也就是AAa,需要输出AA
3 需要输出的只有大写字母，不能输出其他字符
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
	int strlen;
	scanf("%d", &strlen);
	char *str = new char[strlen + 2];
	scanf("%s", str);

	while (*str != 0)
	{
		if (*str <= 'Z'&&*str >= 'A')
			printf("%c", *str);
		str++;
	}

	return 0;
}