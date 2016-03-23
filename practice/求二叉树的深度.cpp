/*

求二叉树的深度
描述:
给出一个字符串形式表达的二叉树，求出指定节点深度。
输入的树形结构字符串格式为：
1、以父节点、左子树、右子树表示的二叉树；每个父节点不会超过两个子节点；
2、树的每一个节点采用单个字母表示；树的层次采用数字表示，树根的层次为1，下一层为2，不会超过9层；
3、字符串以“节点名称 层次数 节点名称 层次数…”的形式出现，同一个父节点下，先出现的为左子树。
例如字符串“a1b2c2d3e3f3”生成一棵如下的树：
     a
   /   \
  b     c
 / \   /
d   e f
节点a的深度为3，节点b的深度是2，节点f的深度是1

运行时间限制:	无限制
内存限制:	无限制
输入:
一行字符串，表示一个二叉树
一行字符串，一个字符一个节点，输入确保字符不会存在重复节点
输出:
指定节点的深度，如果节点不存在，返回0；整数之间用空格隔开
样例输入:
a1b2c2d3e3f3
ab
样例输出:
3 2
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
using namespace std;

struct TreeNode{

	char val;
	TreeNode*left;
	TreeNode*right;
	TreeNode(char s) :val(s), left(NULL), right(NULL){};

};
int getHeight(TreeNode* root, map<char, int>&depth)
{
	if (root == NULL) return 0;
	if (depth[root->val] != 0) return depth[root->val];
	depth[root->val] = max(getHeight(root->left, depth), getHeight(root->right, depth)) + 1;
	return depth[root->val];
}
int main()
{
	string str, query;
	cin >> str >> query;
	vector<vector<TreeNode*>> tree;
	for (int i = 0; i < str.size(); i += 2)
	{
		int level = str[i + 1] - '1';
		if (tree.size() == level)
			tree.push_back(vector<TreeNode*>(0));
		tree[level].push_back(new TreeNode(str[i]));
	}
	for (int i = 1; i < tree.size(); ++i)
	{
		for (int j = 0; j < tree[i].size(); ++j)
		{
			for (int k = 0; k < tree[i - 1].size(); ++k)
			{
				if (tree[i - 1][k]->left == NULL)
				{
					tree[i - 1][k]->left = tree[i][j];
					break;
				}
				if (tree[i - 1][k]->right == NULL)
				{
					tree[i - 1][k]->right = tree[i][j];
					break;
				}
			}
		}
	}
	map<char, int>depth;
	if (tree.size()>0 && tree[0].size()>0)
		depth[tree[0][0]->val] = getHeight(tree[0][0], depth);
	for (int i = 0; i < query.size(); ++i)
	{
		printf("%d", depth[query[i]]);
		if (i != query.size() - 1)
			printf(" ");
	}
	printf("\n");
	return 0;
}