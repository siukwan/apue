/*
题目描述

对于一个有向图，请实现一个算法，找出两点之间是否存在一条路径。
给定图中的两个结点的指针UndirectedGraphNode* a,UndirectedGraphNode* b(请不要在意数据类型，图是有向图),请返回一个bool，代表两点之间是否存在一条路径(a到b或b到a)。

*/


/*
struct UndirectedGraphNode {
int label;
vector<struct UndirectedGraphNode *> neighbors;
UndirectedGraphNode(int x) : label(x) {}
};*/

class Path {
public:
	bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
		// write code here
		return checkPath1(a, b) || checkPath1(b, a);
	}

	bool checkPath1(UndirectedGraphNode* a, UndirectedGraphNode* b) {
		if (a->label == b->label) return true;
		map<UndirectedGraphNode*, bool> visited;
		queue<UndirectedGraphNode*> q;
		q.push(a);
		int count1 = 1;
		int count2 = 0;

		while (!q.empty())
		{
			for (int i = 0; i<count1; ++i)
			{
				UndirectedGraphNode* tmp = q.front();
				q.pop();
				if (tmp->label == b->label) return true;

				for (int j = 0; j<tmp->neighbors.size(); ++j)
				{
					if (tmp->neighbors[j]->label == b->label) return true;
					if (!visited[tmp->neighbors[j]])//注意存在回环，需要标记已经遍历过的节点
					{
						visited[tmp->neighbors[j]] = true;
						q.push(tmp->neighbors[j]);
						count2++;
					}
				}
			}
			count1 = count2;
			count2 = 0;
		}

		return false;

	}
};