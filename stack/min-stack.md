---
title: Min Stack
layout: problem
parent: Stack
nav_order: 5
difficulty: Medium
time: O(1) per operation
space: O(n)
---

Design a stack that supports `push(val)`, `pop()`, `top()` and `getMin()`, where `getMin()` returns the smallest element currently in the stack. Every operation has to run in O(1) time.

## Examples

```
Input:  ["MinStack","push","push","push","getMin","pop","top","getMin"]
        [[],[-2],[0],[-3],[],[],[],[]]
Output: [null,null,null,null,-3,null,0,-2]
```

{: .intuition }
> **Remember what the minimum was at every height of the stack.** A second stack, `minstack`, moves in step with the main stack. Its entry at each position is the minimum of everything at or below that position in the main stack. On `push`, add `min(val, minstack.top())`. On `pop`, pop both stacks, and the minimum goes back to what it was before that element arrived. `getMin` just reads `minstack.top()`.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ top</span> · <span class="done">■ current min</span></p>
{% include array.html v="-2" name="s1" hl="0" label="push(-2)" note="the first element is also the minimum" %}
{% include array.html v="-2" name="minstack" done="0" join=true %}
{% include array.html v="-2,0" name="s1" hl="1" label="push(0)" note="0 is not less than -2, so copy the old minimum, -2" %}
{% include array.html v="-2,-2" name="minstack" done="1" join=true %}
{% include array.html v="-2,0,-3" name="s1" hl="2" label="push(-3)" note="-3 < -2, so -3 is the new minimum" %}
{% include array.html v="-2,-2,-3" name="minstack" done="2" join=true %}
{% include array.html v="-2,0,-3" name="s1" label="getMin()" note="read minstack.top() → -3" %}
{% include array.html v="-2,-2,-3" name="minstack" done="2" join=true %}
{% include array.html v="-2,0" name="s1" hl="1" label="pop()" note="pop both stacks. The minimum goes back to -2 by itself" %}
{% include array.html v="-2,-2" name="minstack" done="1" join=true %}
{% include array.html v="-2,0" name="s1" hl="1" label="top(), getMin()" note="top() → 0, getMin() → -2" %}
{% include array.html v="-2,-2" name="minstack" done="1" join=true %}
</div>

## Code

```cpp
class MinStack {
   public:
    stack<int> s1;
    stack<int> minstack;
    MinStack() {}

    void push(int val) {
        s1.push(val);
        if (s1.size() == 1)
            minstack.push(val);
        else if (val < minstack.top())
            minstack.push(val);
        else
            minstack.push(minstack.top());
    }

    void pop() {
        minstack.pop();
        s1.pop();
    }

    int top() { return s1.top(); }

    int getMin() { return minstack.top(); }
};
```

## Best: already optimal

Yours is already the best: every operation is O(1), using O(n) extra space. This is the version to give in an interview. A tidier variant keeps a single `stack<pair<int,int>>` that stores `{val, minSoFar}`, which is the same idea in one container. The three branches in your `push` can also become one line: `minstack.push(minstack.empty() ? val : min(val, minstack.top()));`.

{: .pitfall }
> Popping only the main stack and not `minstack` is the classic bug, because the two stacks have to stay the same size. If you instead push onto `minstack` only when `val` is a new minimum, you have to use `<=`, not `<`. Otherwise a duplicate minimum gets popped too early.

{: .revisit }
> The general idea is to store extra information alongside each stack entry, as it was when that entry was pushed, so that undoing a push also undoes that information for free. The same idea works for a max stack, or for keeping the running sum at each height.
