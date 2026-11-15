---
title: Daily Temperatures
layout: problem
parent: Stack
nav_order: 8
difficulty: Medium
time: O(n)
space: O(n)
---

`temperatures[i]` is the temperature on day `i`. Return an array `ans` where `ans[i]` is the number of days you have to wait after day `i` to get a strictly warmer day. If no later day is warmer, `ans[i] = 0`.

## Examples

```
Input:  temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

```
Input:  temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

{: .intuition }
> **Walk from the right, and keep a stack of days that could still be someone's "next warmer day".** When you reach day `i`, any day on the stack that is no warmer than `temperatures[i]` can never be the answer for an earlier day, because day `i` is both closer and at least as warm. Pop those days. Whatever is left on top is the nearest warmer day, so `ans[i] = top.index - i`, or `0` if the stack is empty. Then push day `i`. The stack stays strictly decreasing from bottom to top (a monotonic stack), and each day is pushed and popped at most once.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ day i</span> · <span class="done">■ stack, written as temp@index (bottom → top)</span></p>
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="7" vars="ans[7]=0" label="i = 7" note="the stack is empty, so there's no warmer day. ans = 0, push 73@7" %}
{% include array.html v="73@7" name="st" done="0" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="6" vars="ans[6]=0" label="i = 6" note="76 ≥ 73, pop. The stack is empty → 0. Push 76@6" %}
{% include array.html v="76@6" name="st" done="0" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="5" vars="ans[5]=1" label="i = 5" note="72 < 76, so the top is warmer. 6 - 5 = 1. Push 72@5" %}
{% include array.html v="76@6,72@5" name="st" done="0,1" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="4" vars="ans[4]=1" label="i = 4" note="69 < 72. 5 - 4 = 1. Push 69@4" %}
{% include array.html v="76@6,72@5,69@4" name="st" done="0,1,2" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="3" vars="ans[3]=2" label="i = 3" note="71 ≥ 69, pop. 71 < 72. 5 - 3 = 2. Push 71@3" %}
{% include array.html v="76@6,72@5,71@3" name="st" done="0,1,2" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="2" vars="ans[2]=4" label="i = 2" note="75 pops 71 and 72. 75 < 76. 6 - 2 = 4. Push 75@2" %}
{% include array.html v="76@6,75@2" name="st" done="0,1" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="1" vars="ans[1]=1" label="i = 1" note="74 < 75. 2 - 1 = 1. Push 74@1" %}
{% include array.html v="76@6,75@2,74@1" name="st" done="0,1,2" join=true %}
{% include array.html v="73,74,75,71,69,72,76,73" name="temps" hl="0" vars="ans[0]=1" label="i = 0" note="73 < 74. 1 - 0 = 1. Reverse the answers → [1,1,4,2,1,1,0,0]" %}
{% include array.html v="76@6,75@2,74@1,73@0" name="st" done="0,1,2,3" join=true %}
</div>

## Code

```cpp
class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int, int>> st;
        vector<int> ans;
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            if (st.size() == 0) {
                st.push({temperatures[i], i});
                ans.push_back(0);
            } else if (temperatures[i] >= st.top().first) {
                while (st.size() > 0 && temperatures[i] >= st.top().first) st.pop();
                if (st.size() == 0) {
                    st.push({temperatures[i], i});
                    ans.push_back(0);
                } else {
                    ans.push_back(st.top().second - i);

                    st.push({temperatures[i], i});
                }

            } else {
                ans.push_back(st.top().second - i);

                st.push({temperatures[i], i});
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
```

## Best: left to right, store only indices, O(n) time, O(n) space

The Big-O is the same, but the code is simpler. Walk left to right and keep the indices of days that are still waiting for a warmer day. When `temperatures[i]` is warmer than the day on top of the stack, day `i` is that day's answer, so fill it in and pop. You can get each temperature from its index, so pairs aren't needed. Start with `ans(n, 0)`, so days that never find a warmer day are already `0`, and there's nothing to reverse.

```cpp
class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};
```

{: .pitfall }
> "Warmer" means **strictly** warmer. Going right to left, pop every stored day that is no warmer than day `i` (`temperatures[i] >= top`). A day with the same temperature doesn't count, so it's popped too. Going left to right, only resolve days that are `<` the current temperature. If you mix these up, equal temperatures get counted as warmer days.

{: .revisit }
> This is the monotonic stack pattern. Next Greater Element, Online Stock Span, Car Fleet and Largest Rectangle in Histogram all use the same push-and-pop loop. It's O(n) and not O(n²), because each index is pushed once and popped at most once.
