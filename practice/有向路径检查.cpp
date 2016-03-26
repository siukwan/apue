#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

int main()
{
	int Test;
	//cin>>Test;
	scanf("%d", &Test);
	for (int tCase = 0; tCase<Test; ++tCase)
	{
		//unordered_map<int,string> mapping;
		unordered_map<string, int> nameMapping;
		int N;
		//cin>>N;
		scanf("%d", &N);
		vector<int> inDegree(N, 0);
		vector<string> mapping(N);
		//vector<unordered_set<int>> graph(N);
		vector<vector<int>>graph(N);
		for (int n = 0; n<N; ++n)
		{

			//cin>>name;
			char buff[15];
			scanf("%s", buff);
			string name = buff;
			mapping[n] = name;
			nameMapping[name] = n;
			//cin>>inDegree[n];
			scanf("%d", &inDegree[n]);
			for (int i = 0; i<inDegree[n]; ++i)
			{
				int tempLabel;
				//cin>>tempLabel;
				scanf("%d", &tempLabel);
				graph[tempLabel].push_back(n);
			}
		}
		vector<string> ans;
		priority_queue<string, vector<string>, greater<string>> q;
		for (int n = 0; n<N; ++n)
		{
			if (inDegree[n] == 0)
			{
				q.push(mapping[n]);
			}
		}
		while (!q.empty())
		{
			string tempNodeName = q.top();
			q.pop();
			ans.push_back(tempNodeName);
			for (vector<int>::iterator it = graph[nameMapping[tempNodeName]].begin();
				it != graph[nameMapping[tempNodeName]].end(); ++it)
			{
				--inDegree[(*it)];
				if (inDegree[(*it)] == 0)
				{
					q.push(mapping[(*it)]);
				}
			}
		}
		if (ans.size() == N)
		{
			for (int i = 0; i<ans.size(); ++i)
			{
				//cout<<ans[i]<<endl;
				printf("%s\n", ans[i].c_str());
			}
		}
		else
		{
			//cout<<"ERROR"<<endl;
			printf("ERROR\n");
		}
		//cout<<endl;
		printf("\n");
	}
	return 0;
}