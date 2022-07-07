/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i = 0;
        int j = 0;
        bool map[256] = {0};
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
// @lc code=end

