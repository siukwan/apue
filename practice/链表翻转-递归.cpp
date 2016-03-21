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
		if (head == NULL || head->next == NULL) return head;

		ListNode* tmp = reverseList(head->next);//把head->next后面的链表翻转
		head->next->next = head;//翻转后的链表，head->next是尾节点，把head连接到尾部
		head->next = NULL;//因为head是尾部，所以指向NULL
		return tmp;
	}
};