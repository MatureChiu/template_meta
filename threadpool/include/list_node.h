#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

/**
 * Definition for singly-linked list. 
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

#endif
