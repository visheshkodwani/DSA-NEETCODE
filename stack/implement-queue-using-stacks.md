---
title: Implement Queue Using Stacks
layout: problem
parent: Stack
nav_order: 4
difficulty: Easy
time: push O(1), pop/peek O(n)
space: O(n)
---

Build a FIFO queue that supports `push(x)`, `pop()`, `peek()` and `empty()`, using only stack operations: push to the top, read or pop the top, `size` and `empty`.

## Examples

```
Input:  ["MyQueue","push","push","peek","pop","empty"]
        [[],[1],[2],[],[],[]]
Output: [null,null,null,1,1,false]
```

{: .intuition }
> **A stack hands back the newest element, but a queue needs the oldest, which sits at the bottom.** Pouring one stack into another reverses it, so the bottom comes out on top. Your solution pours the whole stack except the bottom element into `s2`, takes that bottom element, and pours everything back. `push` is O(1), but every `pop` and `peek` costs O(n).

## Dry run (yours)

<div class="viz">
<p class="viz-legend"><span class="hl">■ the element being returned</span> · <span class="done">■ parked in s2</span></p>
{% include array.html v="1,2,3" name="s1 (bottom → top)" hl="0" label="after push(1), push(2), push(3)" note="the oldest element, 1, is at the bottom" %}
{% include array.html v="1" name="s1" hl="0" label="pop(): pour n - 1 elements" note="while s1.size() > 1, move the top of s1 to s2" %}
{% include array.html v="3,2" name="s2 (bottom → top)" done="0,1" join=true %}
{% include array.html v="2,3" name="s1 (bottom → top)" label="pop(): take it and pour back" note="pop 1 from s1 and return it. Pour s2 back into s1, so the order is still 2, 3" %}
</div>

## Code

```cpp
class MyQueue {
   public:
    stack<int> s1;
    stack<int> s2;
    MyQueue() {}

    void push(int x) { s1.push(x); }

    int pop() {
        while (s1.size() > 1) {
            s2.push(s1.top());
            s1.pop();
        }
        int top = s1.top();
        s1.pop();
        while (s2.size() > 0) {
            s1.push(s2.top());
            s2.pop();
        }

        return top;
    }

    int peek() {
        while (s1.size() > 1) {
            s2.push(s1.top());
            s1.pop();
        }
        int top = s1.top();
        s1.pop();
        s2.push(top);
        while (s2.size() > 0) {
            s1.push(s2.top());
            s2.pop();
        }

        return top;
    }

    bool empty() { return s1.size() == 0; }
};
```

## Best: lazy transfer, amortized O(1) for every operation

**Don't pour back.** Use two stacks, `in` and `out`. After a pour, `out` already has the oldest element on top, which is exactly the order a queue needs. So leave the elements in `out`, and only pour `in` into it again once `out` is empty. Each element is pushed onto `in` once, poured into `out` once and popped once. That makes n operations O(n) in total, so each one is amortized O(1), even though a single `pop` can still take O(n).

<div class="viz">
<p class="viz-legend"><span class="hl">■ the element being returned</span> · <span class="done">■ out, the next to leave</span></p>
{% include array.html v="1,2,3" name="in (bottom → top)" label="after push(1), push(2), push(3)" note="out is empty" %}
{% include array.html v="3,2,1" name="out (bottom → top)" hl="2" label="pop(): out is empty, so pour" note="in is now empty, and the oldest element, 1, is on top of out. Pop it" %}
{% include array.html v="4" name="in" label="push(4)" note="only touches in, O(1)" %}
{% include array.html v="3,2" name="out" hl="1" done="0" join=true %}
{% include array.html v="4" name="in" label="pop(): out is not empty" note="no pour needed. Pop 2 from out in O(1). 4 stays in in until out runs dry" %}
{% include array.html v="3" name="out" done="0" join=true %}
</div>

```cpp
class MyQueue {
   public:
    stack<int> in;
    stack<int> out;
    MyQueue() {}

    void push(int x) { in.push(x); }

    void shift() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
    }

    int pop() {
        shift();
        int front = out.top();
        out.pop();
        return front;
    }

    int peek() {
        shift();
        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }
};
```

{: .pitfall }
> Only pour when `out` is **empty**. If you pour while `out` still has elements, the new ones land on top of the older ones and the order breaks. With two stacks, `empty()` has to check both of them. Checking only `out` returns `true` while elements are still waiting in `in`.

{: .revisit }
> Compare with Implement Stack Using Queues. There the lazy trick doesn't work: moving elements between queues keeps their order, so the work can't be saved for later. Moving between stacks reverses the order, and that reversal is what makes amortized O(1) possible.
