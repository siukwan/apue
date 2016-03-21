/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL)
			return head;

		ListNode* first = head->next;//第一个翻转的节点
		ListNode* tmp;//过度节点

		while (first->next)
		{
			tmp = first->next;
			first->next = tmp->next;
			tmp->next = head->next;
			head->next = tmp;
		}

		//这个时候first为现在最后的节点，head->next为元链表最后的节点
		tmp = head->next;
		head->next = NULL;
		first->next = head;
		return tmp;
	}
};