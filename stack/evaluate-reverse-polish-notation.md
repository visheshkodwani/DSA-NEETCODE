---
title: Evaluate Reverse Polish Notation
layout: problem
parent: Stack
nav_order: 6
difficulty: Medium
time: O(n)
space: O(n)
---

`tokens` is an arithmetic expression in Reverse Polish Notation, where every operator comes after its two operands. The operators are `+`, `-`, `*` and `/`, and division truncates toward zero. Return the value of the expression.

## Examples

```
Input:  tokens = ["2","1","+","3","*"]
Output: 9            // (2 + 1) * 3
```

```
Input:  tokens = ["4","13","5","/","+"]
Output: 6            // 4 + (13 / 5)
```

{: .intuition }
> **An operator always applies to the two most recent values, so keep the values on a stack.** Push every number. When you reach an operator, pop two values, apply the operator and push the result. That result becomes an operand for a later operator. Once all tokens are used, the only value left on the stack is the answer.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ pushed this step</span> · <span class="done">■ answer</span></p>
{% include array.html v="2" name="st" hl="0" label="\"2\"" note="a number, so push it" %}
{% include array.html v="2,1" name="st" hl="1" label="\"1\"" note="a number, so push it" %}
{% include array.html v="3" name="st" hl="0" label="\"+\"" note="pop b = 1, then a = 2. Push a + b = 3" %}
{% include array.html v="3,3" name="st" hl="1" label="\"3\"" note="a number, so push it" %}
{% include array.html v="9" name="st" done="0" label="\"*\"" note="pop b = 3, then a = 3. Push a * b = 9. No tokens left → return 9" %}
</div>

## Code

```cpp
class Solution {
public:
    int giveTop(stack<string>& st) {
        int p = stoi(st.top());
        st.pop();
        return p;
    }

    int evalRPN(vector<string>& tokens) {
        stack<string> st;

        for (int i = 0; i < tokens.size(); i++) {

            if (tokens[i] == "+" || tokens[i] == "-" ||
                tokens[i] == "*" || tokens[i] == "/") {

                int b = giveTop(st);
                int a = giveTop(st);

                if (tokens[i] == "+")
                    st.push(to_string(a + b));

                else if (tokens[i] == "-")
                    st.push(to_string(a - b));

                else if (tokens[i] == "*")
                    st.push(to_string(a * b));

                else if (tokens[i] == "/")
                    st.push(to_string(a / b));
            }
            else {
                st.push(tokens[i]);
            }
        }

        return stoi(st.top());
    }
};
```

## Best: `stack<int>`, O(n) time, O(n) space

The Big-O is the same, but there is less work per token. Storing `int`s means each number is parsed once, and every operator result skips a `to_string` and a later `stoi`.

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (string& t : tokens) {
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if (t == "+") st.push(a + b);
                else if (t == "-") st.push(a - b);
                else if (t == "*") st.push(a * b);
                else st.push(a / b);
            } else {
                st.push(stoi(t));
            }
        }
        return st.top();
    }
};
```

{: .pitfall }
> The first value you pop is the **right** operand. `["4","2","-"]` is `4 - 2`, so pop `b` first, then `a`, and compute `a - b` and `a / b`. Negative numbers like `"-11"` are numbers, not operators. Comparing the whole token with `== "-"` gets this right, but checking only `t[0] == '-'` does not. C++ `int` division already truncates toward zero, so `-7 / 2` is `-3`, which matches the problem.

{: .revisit }
> This is the same "values on a stack" pattern as Baseball Game. The next step up is Basic Calculator, where you first have to deal with operator precedence and parentheses yourself, for example by converting to RPN first (shunting-yard).
