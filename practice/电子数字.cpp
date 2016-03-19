#include<string>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<stack>
#include<set>
#include<queue>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include <sstream>
#include <list>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
using namespace std;

vector<vector<bool>> digit = {
	{ 0, 1, 1, 1, 0, 1, 1, 1 },//0
	{ 0, 0, 0, 1, 0, 0, 1, 0 }, //1
	{ 0, 1, 0, 1, 1, 1, 0, 1 },//2
	{ 0, 1, 0, 1, 1, 0, 1, 1 }, //3
	{ 0, 0, 1, 1, 1, 0, 1, 0 }, //4
	{ 0, 1, 1, 0, 1, 0, 1, 1 }, //5
	{ 0, 1, 1, 0, 1, 1, 1, 1 }, //6
	{ 0, 1, 0, 1, 0, 0, 1, 0 }, //7
	{ 0, 1, 1, 1, 1, 1, 1, 1 }, //8
	{ 0, 1, 1, 1, 1, 0, 1, 1 }, //7
};
bool judge(vector<int>& seg, int num)
{
	if (seg.size() == 0) return true;//什么都没亮
	for (int i = 0; i < seg.size(); ++i)
	{
		if (!digit[num][seg[i]])
			return false;
	}
	return true;
}
void dfs(vector<vector<int>>&total, int&maxNum, int&result, int count, int num)
{
	if (count == total.size())
	{
		if (num < maxNum)
			result++;
	}
	else
	{
		for (int i = 0; i <= 9; ++i)
		{
			if (judge(total[count], i))
			{
				dfs(total, maxNum, result, count + 1, num * 10 + i);
			}
		}
	}
}
int main()
{
	int S;
	cin >> S;
	while (S--)
	{
		int total, maxNum;
		cin >> total >> maxNum;
		string str;
		getline(cin, str);
		vector<vector<int>> inNum;
		for (int i = 0; i < total; ++i)
		{
			getline(cin, str);
			vector<int> tmp;
			for (int j = 0; j < str.size(); ++j)
			{
				if (str[j] <= '9'&&str[j] >= '0')
					tmp.push_back(str[j] - '0');
			}
			inNum.push_back(tmp);
		}

		int result = 0;
		dfs(inNum, maxNum, result, 0, 0);
		printf("%d\n", result);
	}

	return 0;
}