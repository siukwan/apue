/*
题目描述

请设计一个算法，寻找二叉树中指定结点的下一个结点（即中序遍历的后继）。
给定树的根结点指针TreeNode* root和结点的值int p，请返回值为p的结点的后继结点的值。保证结点的值大于等于零小于等于100000且没有重复值，若不存在后继返回-1。
*/

/*
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};*/

class Successor {
public:
	int findSucc(TreeNode* root, int p) {
		// write code here
		vector<int> arr;
		inOrder(root, arr);
		for (int i = 0; i<arr.size(); ++i)
		{
			if (arr[i] == p)
			{
				if (i<arr.size() - 1)
					return arr[i + 1];
				else return -1;
			}
		}
		return -1;
	}
	void inOrder(TreeNode* root, vector<int>&arr)
	{
		if (root == NULL) return;
		inOrder(root->left, arr);
		arr.push_back(root->val);
		inOrder(root->right, arr);
	}
};