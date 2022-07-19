/*
 * @lc app=leetcode.cn id=20 lang=c
 *
 * [20] 有效的括号
 */

// @lc code=start


bool isValid(char * s){
    int len = strlen(s);
    if(len == 0) return true;
    if(len % 2 != 0) return false;
    char * stack = (char *)malloc(sizeof(char) * len);
    int top = -1;
    for(int i = 0; i < len; i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            stack[++top] = s[i];
        }else{
            if(top == -1) return false;
            if(s[i] == ')' && stack[top] == '(') top--;
            else if(s[i] == ']' && stack[top] == '[') top--;
            else if(s[i] == '}' && stack[top] == '{') top--;
            else return false;
        }
    }
    if(top == -1) return true;
    else return false;
}
// @lc code=end

