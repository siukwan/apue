/*
题目描述

对于一棵二叉树，请设计一个算法，创建含有某一深度上所有结点的链表。
给定二叉树的根结点指针TreeNode* root，以及链表上结点的深度，请返回一个链表ListNode，代表该深度上所有结点的值，请按树上从左往右的顺序链接，保证深度不超过树的高度，树上结点的值为非负整数且不超过100000。
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

/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
class TreeLevel {
public:
	ListNode* getTreeLevel(TreeNode* root, int dep) {
		// write code here
		if (root == NULL) return NULL;

		queue<TreeNode*> q;
		q.push(root);
		int count1 = 1;
		int count2 = 0;
		int level = 0;
		while (!q.empty())
		{
			level++;
			if (level == dep)
			{
				ListNode* head = new ListNode(q.front()->val);
				q.pop();
				ListNode* tmp = head;
				while (!q.empty())
				{
					tmp->next = new ListNode(q.front()->val);
					tmp = tmp->next;
					q.pop();
				}
				return head;
			}
			for (int i = 0; i<count1; ++i)
			{
				TreeNode* tmp = q.front();
				q.pop();
				if (tmp->left)
				{
					q.push(tmp->left);
					count2++;
				}
				if (tmp->right)
				{
					q.push(tmp->right);
					count2++;
				}
			}

			count1 = count2;
			count2 = 0;

		}
		return NULL;
	}
};