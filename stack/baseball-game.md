---
title: Baseball Game
layout: problem
parent: Stack
nav_order: 1
difficulty: Easy
time: O(n)
space: O(n)
---

Each entry in `operations` is one of four things. An integer `x` records the score `x`. `"+"` records the sum of the last two scores. `"D"` records double the last score. `"C"` removes the last score. Return the sum of the scores left at the end.

## Examples

```
Input:  operations = ["5","2","C","D","+"]
Output: 30
```

```
Input:  operations = ["5","-2","4","C","D","9","+","+"]
Output: 27
```

{: .intuition }
> **Every operation only touches the most recent scores, so keep the record on a stack.** `"C"` pops the top, `"D"` reads the top, and `"+"` reads the top two. Once all operations are done, add up whatever is left on the stack.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ pushed this step</span> · <span class="done">■ final record</span></p>
{% include array.html v="5" name="st" hl="0" label="\"5\"" note="a number, so push 5" %}
{% include array.html v="5,2" name="st" hl="1" label="\"2\"" note="a number, so push 2" %}
{% include array.html v="5" name="st" label="\"C\"" note="pop 2, so it no longer counts" %}
{% include array.html v="5,10" name="st" hl="1" label="\"D\"" note="top is 5, so push 2 × 5 = 10" %}
{% include array.html v="5,10,15" name="st" hl="2" label="\"+\"" note="top two are 10 and 5, so push 15" %}
{% include array.html v="5,10,15" name="st" done="0,1,2" vars="res=30" label="end" note="5 + 10 + 15 → return 30" %}
</div>

## Code

```cpp
class Solution {
   public:
    int calPoints(vector<string>& operations) {
        stack<string> st;
        for (int i = 0; i < operations.size(); i++) {
            if (operations[i] == "+") {
                int a = stoi(st.top());
                st.pop();
                int b = stoi(st.top());
                st.pop();
                st.push(to_string(b));
                st.push(to_string(a));
                st.push(to_string(a + b));
            } else if (operations[i] == "D") {
                int a = stoi(st.top());
                st.push(to_string(2 * a));
            } else if (operations[i] == "C") {
                st.pop();
            } else
                st.push(operations[i]);
        }
        int res = 0 ;
        while(st.size() > 0){
            res = res + stoi(st.top());
            st.pop();
        }
        return res;
    }
};
```

## Best: `vector<int>` as the stack, O(n) time, O(n) space

The Big-O is the same, but there is less work per step. Store `int`s, so you call `stoi` once per number instead of on every read, and you never call `to_string`. A `vector` lets you read the second-to-top score directly, so `"+"` no longer has to pop two scores and push them back.

```cpp
class Solution {
   public:
    int calPoints(vector<string>& operations) {
        vector<int> st;
        for (string& op : operations) {
            if (op == "+") st.push_back(st[st.size() - 1] + st[st.size() - 2]);
            else if (op == "D") st.push_back(2 * st.back());
            else if (op == "C") st.pop_back();
            else st.push_back(stoi(op));
        }
        return accumulate(st.begin(), st.end(), 0);
    }
};
```

{: .pitfall }
> Check for `"+"`, `"D"` and `"C"` **before** you treat an entry as a number, because `stoi("+")` throws. Negative scores like `"-2"` are fine, since `stoi` parses the sign. With `std::stack`, `"+"` has to pop both scores and push them back in the same order, `b` first and then `a`, before it pushes the sum.

{: .revisit }
> This is the simplest "stack as a history" problem. Min Stack and Evaluate Reverse Polish Notation use the same idea: the next step only needs the most recent values.
