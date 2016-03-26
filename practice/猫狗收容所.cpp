/*
题目描述

有家动物收容所只收留猫和狗，但有特殊的收养规则，收养人有两种收养方式，第一种为直接收养所有动物中最早进入收容所的，第二种为选择收养的动物类型（猫或狗），并收养该种动物中最早进入收容所的。
给定一个操作序列int[][2] ope(C++中为vector<vector<int>>)代表所有事件。若第一个元素为1，则代表有动物进入收容所，第二个元素为动物的编号，正数代表狗，负数代表猫；若第一个元素为2，则代表有人收养动物，第二个元素若为0，则采取第一种收养方式，若为1，则指定收养狗，若为-1则指定收养猫。请按顺序返回收养的序列。若出现不合法的操作，即没有可以符合领养要求的动物，则将这次领养操作忽略。
测试样例：
[[1,1],[1,-1],[2,0],[2,-1]]
返回：[1,-1]

注意没有对应的动物的时候
*/

class CatDogAsylum {
public:
	vector<int> asylum(vector<vector<int> > ope) {
		// write code here
		vector<int> result;
		queue<pair<int, int>> cats;
		queue<pair<int, int>> dogs;
		for (int i = 0; i<ope.size(); ++i)
		{
			if (ope[i][0] == 1)
			{
				//dog
				if (ope[i][1]>0)
					dogs.push({ ope[i][1], i });
				else//cats
					cats.push({ ope[i][1], i });
			}
			else
			{
				if (ope[i][1] == 0)
				{
					if (dogs.front().second<cats.front().second &&!dogs.empty())
					{
						result.push_back(dogs.front().first);
						dogs.pop();
					}
					else if (!cats.empty())
					{
						result.push_back(cats.front().first);
						cats.pop();
					}
				}
				else if (ope[i][1] == 1 && !dogs.empty())
				{
					result.push_back(dogs.front().first);
					dogs.pop();
				}
				else if (ope[i][1] == -1 && !cats.empty())
				{
					result.push_back(cats.front().first);
					cats.pop();
				}
			}
		}
		return result;
	}
};