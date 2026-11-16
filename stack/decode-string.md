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
> **A `[` starts a new, smaller problem, and a `]` finishes it and hands the result back to the outer level.** Keep `curr`, the string built so far at this level, and `num`, the repeat count you're reading. On `[`, save the outer level on a stack (its `curr` and the count for the inner part), then start fresh. On `]`, pop the count and the outer `curr`, and set `curr = outer + inner × count`. Letters just go onto `curr`, and digits build `num` one digit at a time, so counts like `10` work.

## Dry run

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

## Code

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

## Best: already optimal

Every character of the output has to be written, and this stack approach does that in one pass over `s`. The only extra cost is that a nested part gets copied once for each level it's merged into (`L` = decoded length, `d` = nesting depth), and the recursive solution pays the same. Keeping the counts in a separate `stack<int>` would skip the `to_string`/`stoi`, but the complexity doesn't change.

{: .pitfall }
> Reset `num` to `0` after you push it on `[`. If you don't, the next count gets added onto the old digits (`3[a2[c]]` would read the inner count as `32`). Also build `num` with `num * 10 + digit`, not `num = digit`, or `10[a]` becomes `0[a]`.

{: .revisit }
> This is the "save the outer context on push, restore it on pop" pattern for nested brackets. Basic Calculator and Number of Atoms use the same loop. You can also write it as recursion: call the function on `[` and return on `]`, so the call stack plays the role of `st`.
