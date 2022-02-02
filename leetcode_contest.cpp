#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* current = head;
        ListNode** buffer = new ListNode*[n+1];

        int k = 0;
        while (current) {
            if (k == n+1) {
                for (int i = 0; i <= n; i++)
                    buffer[i] = buffer[i+1];
                buffer[n] = current;
            }
            buffer[k++] = current;
            current = current->next;
        }

        ListNode* to_delete = buffer[0]->next;
        buffer[0]->next = to_delete->next;
        delete to_delete;

        delete [] buffer;

        return head;
    }
};

