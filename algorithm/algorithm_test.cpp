#include <iostream>
#include <string>

using namespace std;
// @lc code=start

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(0);
        ListNode *p = head;
        int carry = 0;
        while (l1 || l2) {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);
            p = p->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        if (carry) {
            p->next = new ListNode(carry);
        }
        return head->next;
    }

    ListNode *add_two_numbers(ListNode *l1,ListNode *l2)
    {
        ListNode *head = new ListNode(0);
        ListNode *p = head;
        int sum;
        int carry = 0;
        while(l1 || l2)
        {
            sum = l1->val + l2->val + carry;
            carry = sum / 10;
            sum %= 10;
            p->next = new ListNode(sum);

            p = p->next;
            //next list node
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry == 1)
        {
            p->next = new ListNode(1);
        }

        return head->next;
    }
    
    int lengthOfLongestSubstring(string s) {
        int max_len = 0;
        int len = 0;
        int i = 0;
        int j = 0;
        while (i < s.size() && j < s.size()) {
            if (s[i] != s[j]) {
                i++;
                len++;
            } else {
                if (len > max_len) {
                    max_len = len;
                }
                len = 0;
                i = j + 1;
            }
            j++;
        }
        if (len > max_len) {
            max_len = len;
        }
        return max_len;
    }

    int length_of_longest_substring(string s)
    {
        int i = 0;
        int j = 0;
        uint8_t map[256] = {0};
        int max_len = 0;
        while(i < s.size() && j < s.size())
        {
            if(map[s[j]] == 0)
            {
                map[s[j]] = 1;
                j++;
                max_len = max(max_len, j - i);
            }
            else
            {
                map[s[i]] = 0;
                i++;
            }
        }
        return max_len;    
    }
};

int main()
{
    Solution s;
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(8);
    l1->next->next = new ListNode(0);
    ListNode *l2 = new ListNode(0);
    l2->next = new ListNode(1);
    l2->next->next = new ListNode(6);
    ListNode *l3 = s.add_two_numbers(l1, l2);
    while (l3) {
        std::cout << l3->val << " ";
        l3 = l3->next;
    }
    std::cout << std::endl;

    string s1 = "abcabcdb";
    string s2 = "bbbbb";
    cout << s.length_of_longest_substring(s1) << endl;
    return 0;
}