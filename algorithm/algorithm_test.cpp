#include <iostream>
#include <string>
#include <vector>
#include <string.h>

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
    
    // 2.两数相加
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

    // 2.两数相加
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
    
    // 3.无重复字符的最长子串
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

    //无重复字符的最长子串,maps 
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

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
    }

    string longestPalindrome(string s) {
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
        return s.substr(i - max_len, max_len);
    }


    // 66.加一
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;
        
        //数组末尾开始判断，如果为9，则需要进位，否则直接加1
        while (i >= 0 && digits[i] == 9) {
            digits[i] = 0;
            i--;
        }
        if (i < 0) {
            digits.insert(digits.begin(), 1);
        } else {
            digits[i]++;
        }
        return digits;
    }

    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        string prefix = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.size() - 1);
                if (prefix.empty()) {
                    return "";
                }
            }
        }
        return prefix;    
    }
    
};


bool isValid(char * s){
    int len = strlen(s);
    if(len == 0) return true;
    if(len % 2 == 1) return false;
    char stack[len / 2];
    int pos = 0;
    for(int i =0;i < len;i++)
    {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            stack[pos++] = s[i];
        }
        else
        {
            if(pos == 0) return false;
            if(s[i] == ')' && stack[--pos] != '(') return false;
            if(s[i] == ']' && stack[--pos] != '[') return false;
            if(s[i] == '}' && stack[--pos] != '{') return false;
        }
    }
}

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