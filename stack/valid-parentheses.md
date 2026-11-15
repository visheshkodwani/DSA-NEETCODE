---
title: Valid Parentheses
layout: problem
parent: Stack
nav_order: 2
difficulty: Easy
time: O(n)
space: O(n)
---

`s` contains only the characters `()[]{}`. It is valid if every opening bracket is closed by a bracket of the same type, and brackets close in the correct order (the most recently opened one closes first). Return whether `s` is valid.

## Examples

```
Input:  s = "([{}])"
Output: true
```

```
Input:  s = "[(])"
Output: false
```

{: .intuition }
> **The bracket that closes next has to be the one that opened most recently, so keep the open ones on a stack.** Push every opening bracket. When a closing bracket shows up, the top of the stack must be its matching opener, so pop it. If the stack is empty or the top doesn't match, `s` is invalid. At the end, the stack has to be empty, otherwise some brackets were never closed.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ top of the stack</span> · <span class="done">■ matched</span></p>
{% include array.html v="(" name="st" hl="0" label="'('" note="opening bracket, so push it" %}
{% include array.html v="(,[" name="st" hl="1" label="'['" note="opening bracket, so push it" %}
{% include array.html v="(,[,{" name="st" hl="2" label="'{'" note="opening bracket, so push it" %}
{% include array.html v="(,[" name="st" hl="1" label="'}'" note="the top is '{', which matches, so pop it" %}
{% include array.html v="(" name="st" hl="0" label="']'" note="the top is '[', which matches, so pop it" %}
{% include array.html v="(,[,{,},],)" name="s" done="0,1,2,3,4,5" label="')'" note="the top is '(', which matches, so pop it. The stack is empty → return true" %}
</div>

## Code

```cpp
class Solution {
   public:
    bool isValid(string s) {
        stack<char> st;
        for (int i = 0; i < s.length(); i++) {
            switch (s[i]) {
                case ']':
                    if (st.size() > 0 && st.top() == '[') {
                        st.pop();
                        break;
                    } else
                        return false;
                case '}':
                    if (st.size() > 0 && st.top() == '{') {
                        st.pop();
                        break;

                    } else
                        return false;
                case ')':
                    if (st.size() > 0 && st.top() == '(') {
                        st.pop();
                        break;

                    } else
                        return false;
                default:
                    st.push(s[i]);
            }
        }
        if (st.size() == 0)
            return true;
        else
            return false;
    }
};
```

## Best: already optimal

Yours is already the best: O(n) time, and the stack takes O(n) space in the worst case (for example `"(((((("`). A small extra: a string with odd length can never be valid, so you can `return false` right away. A `{')':'(', ']':'[', '}':'{'}` map can also replace the three almost identical `case`s.

{: .pitfall }
> Check `st.size() > 0` before you call `st.top()`. On an input like `")"`, calling `top()` on an empty stack is undefined behaviour. The `break` inside the `if` is fine, because it leaves the `switch` and the loop keeps going. Don't skip the final check either: `"(("` never fails a match, but it still isn't valid. You can write that check as `return st.empty();`.

{: .revisit }
> This is the basic matching-brackets pattern. Generate Parentheses and Longest Valid Parentheses build on it, and so does any problem where the most recent open item has to close first.
