---
title: Decode String
layout: problem
parent: Stack
nav_order: 9
difficulty: Medium
time: O(L·d)
space: O(L)
---

`s` is an encoded string where `k[text]` means `text` repeated exactly `k` times. Brackets can be nested, `k` is always a positive integer, and the input is always valid. Return the decoded string.

## Examples

```
Input:  s = "3[a]2[bc]"
Output: "aaabcbc"
```

```
Input:  s = "3[a2[c]]"
Output: "accaccacc"
```

```
Input:  s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
```

{: .intuition }
> **Push every character until you hit a `]`. That `]` closes the innermost bracket, and everything you need to decode it sits on top of the stack.** Pop letters until the `[` to get the text, pop the `[`, then pop digits to get the count. Both come off backwards, so reverse them. Repeat the text `count` times and push the result back onto the stack, because it may be the text of an outer bracket. When the input ends, the stack holds the fully decoded string, bottom to top.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ s[i]</span> · <span class="done">■ stack (bottom → top)</span></p>
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="0,1,2,3,4,5" label="i = 0..5" note="no ], so push each character" %}
{% include array.html v="3,[,a,2,[,c" name="st" done="0,1,2,3,4,5" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="6" vars="temp=c,num=2" label="']'" note="pop c until the [, pop [, pop the digit 2. 'c' × 2 = 'cc', push it back" %}
{% include array.html v="3,[,a,c,c" name="st" done="0,1,2,3,4" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="7" vars="temp=acc,num=3" label="']'" note="pop c, c, a and reverse → 'acc'. Pop [, pop 3. 'acc' × 3, push it back" %}
{% include array.html v="a,c,c,a,c,c,a,c,c" name="st" done="0,1,2,3,4,5,6,7,8" join=true %}
{% include array.html v="a,c,c,a,c,c,a,c,c" name="st" done="0,1,2,3,4,5,6,7,8" label="end" note="pop everything and reverse → 'accaccacc'" %}
</div>

## Code

```cpp
class Solution {
   public:
    string decodeString(string s) {
        stack<char> st;
        string ans = "";
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ']') {
                string temp;
                while (st.size() > 0 && st.top() != '[') {
                    temp.push_back(st.top());
                    st.pop();
                }
                reverse(temp.begin(), temp.end());
                st.pop();
                string tempnum;
                while (st.size() > 0 && isdigit(st.top())) {
                    tempnum.push_back(st.top());
                    st.pop();
                }
                int tempnumber;
                reverse(tempnum.begin(), tempnum.end());
                if (tempnum.empty() == true)
                    tempnumber = 1;
                else
                    tempnumber = stoi(tempnum);
                while (tempnumber) {
                    ans = ans + temp;
                    tempnumber--;
                }
                for (int j = 0; j < ans.length(); j++) {
                    st.push(ans[j]);
                }
                ans = "";
            } else
                st.push(s[i]);
        }
        while (st.size() > 0) {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## Best: stack of strings, O(L·d) time, O(L) space

The Big-O is the same (`L` = decoded length, `d` = nesting depth), but it does less work. The char stack pops every decoded character and pushes it back one at a time at each level, and it reverses `temp` and the count. This version never puts decoded text back on a stack. It keeps `curr`, the string built so far at this level, and `num`, the count being read. On `[` it saves both and starts fresh. On `]` it pops them and sets `curr = prev + curr × count`. Nothing comes off backwards, so nothing needs reversing.

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        string curr = "";
        int num = 0;

        for (int i = 0; i < s.length(); i++) {

            if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
            }

            else if (s[i] == '[') {
                st.push(curr);
                st.push(to_string(num));

                curr = "";
                num = 0;
            }

            else if (s[i] == ']') {
                int count = stoi(st.top());
                st.pop();

                string prev = st.top();
                st.pop();

                string temp = "";

                while (count--) {
                    temp += curr;
                }

                curr = prev + temp;
            }

            else {
                curr += s[i];
            }
        }

        return curr;
    }
};
```

`''` is the empty string.

<div class="viz">
<p class="viz-legend"><span class="hl">■ s[i]</span> · <span class="done">■ stack (bottom → top)</span></p>
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="0" vars="curr='',num=3" label="'3'" note="a digit, so num = 3" %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="1" vars="curr='',num=0" label="'['" note="push curr '' and num 3, then reset both" %}
{% include array.html v="'',3" name="st" done="0,1" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="2" vars="curr=a,num=0" label="'a'" note="a letter, so add it to curr" %}
{% include array.html v="'',3" name="st" done="0,1" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="3" vars="curr=a,num=2" label="'2'" note="a digit, so num = 2" %}
{% include array.html v="'',3" name="st" done="0,1" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="4" vars="curr='',num=0" label="'['" note="push curr 'a' and num 2, then reset both" %}
{% include array.html v="'',3,a,2" name="st" done="0,1,2,3" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="5" vars="curr=c,num=0" label="'c'" note="a letter, so add it to curr" %}
{% include array.html v="'',3,a,2" name="st" done="0,1,2,3" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="6" vars="curr=acc,num=0" label="']'" note="pop count 2 and prev 'a'. curr = 'a' + 'cc' = 'acc'" %}
{% include array.html v="'',3" name="st" done="0,1" join=true %}
{% include array.html v="3,[,a,2,[,c,],]" name="s" hl="7" vars="curr=accaccacc,num=0" label="']'" note="pop count 3 and prev ''. curr = '' + 'acc' × 3. Return 'accaccacc'" %}
{% include array.html v="" name="st" join=true %}
</div>

{: .pitfall }
> Everything comes off a stack in reverse. The text between `[` and `]` and the digits of the count both need a `reverse`. Without it, `ab` decodes as `ba` and `12[a]` repeats 21 times. The final string needs one too, because popping the whole stack reads it top to bottom.

{: .revisit }
> This is the "save the outer context on push, restore it on pop" pattern for nested brackets. Basic Calculator and Number of Atoms use the same loop. You can also write it as recursion: call the function on `[` and return on `]`, so the call stack plays the role of `st`.
