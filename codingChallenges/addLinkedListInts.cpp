/**
example io:
i1: 5 - 4 - 9
i2: 3 - 7 - 8
o : 8 - 1 - 8 - 1
description : 945 + 873 = 1818 (read right-to-left)

 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* emptyHeadNode = new ListNode();
        ListNode* headPtr = emptyHeadNode;
        
        int sum = 0;
        int carry = 0;
        while(l1  || l2)
        {
            sum = 0;
            if(l1) sum += l1->val;
            if(l2) sum += l2->val;
            sum += carry;

            carry = sum / 10;
            sum = sum % 10;
            
            ListNode* l = new ListNode(sum);
            headPtr->next = l;
            headPtr = headPtr->next;
            
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        
        if(carry > 0)
        {
            ListNode* l = new ListNode(carry);
            headPtr->next = l;
        }
        
        return emptyHeadNode->next;
    }
};