---
title: Implement Stack Using Queues
layout: problem
parent: Stack
nav_order: 3
difficulty: Easy
time: push O(1), pop/top O(n)
space: O(n)
---

Build a LIFO stack that supports `push(x)`, `pop()`, `top()` and `empty()`, using only queue operations: push to the back, read or pop the front, `size` and `empty`.

## Examples

```
Input:  ["MyStack","push","push","top","pop","empty"]
        [[],[1],[2],[],[],[]]
Output: [null,null,null,2,2,false]
```

{: .intuition }
> **A queue hands back the oldest element, but a stack needs the newest, so somebody has to walk past the rest.** Either `push` does the walking, rotating every time so the newest element ends up at the front, or `pop`/`top` do it, moving everything except the last element out of the way. Your solution uses the second option: `push` is O(1), and `pop`/`top` move the first `n - 1` elements into `q2` and then back.

## Dry run (yours: cheap push)

<div class="viz">
<p class="viz-legend"><span class="hl">■ the element being returned</span> · <span class="done">■ parked in q2</span></p>
{% include array.html v="1" name="q1" label="push(1)" note="push onto the back of q1, O(1)" %}
{% include array.html v="1,2" name="q1" label="push(2)" note="push onto the back of q1" %}
{% include array.html v="1,2,3" name="q1" hl="2" label="push(3)" note="the newest element is at the back, but a queue can only read its front" %}
{% include array.html v="3" name="q1" hl="0" label="pop(): move n - 1 elements" note="while q1.size() > 1, move the front of q1 to q2" %}
{% include array.html v="1,2" name="q2" done="0,1" join=true %}
{% include array.html v="1,2" name="q1" label="pop(): take it and move back" note="pop 3 from q1 and return it. Move q2 back into q1, so the order is still 1, 2" %}
</div>

## Code

```cpp
class MyStack {
   public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {}

    void push(int x) { q1.push(x); }

    int pop() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int front = q1.front();
        q1.pop();
        while (q2.size() > 0) {
            q1.push(q2.front());
            q2.pop();
        }
        return front;
    }

    int top() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int front = q1.front();
        q2.push(front);
        q1.pop();
        while (q2.size() > 0) {
            q1.push(q2.front());
            q2.pop();
        }
        return front;
    }

    bool empty() {
        if (q1.size() == 0)
            return true;
        else
            return false;
    }
};
```

## Best: one queue, costly push, push O(n), pop/top O(1)

Do the walking once, in `push`. Push `x` onto the back, then move the `size - 1` elements in front of it to the back. Now `x` is at the front, so the queue's front is always the top of the stack. `pop` and `top` become O(1), and you only need one queue. Usually this is the better trade, because `top` gets called more often than anything else and here it's free. In your version it's O(n).

<div class="viz">
<p class="viz-legend"><span class="hl">■ just pushed</span> · <span class="done">■ front = top of stack</span></p>
{% include array.html v="2,1" name="q" done="0" label="before push(3)" note="2 is at the front, and it's the current top" %}
{% include array.html v="2,1,3" name="q" hl="2" label="q.push(3)" note="3 goes to the back" %}
{% include array.html v="1,3,2" name="q" label="rotate 1 of 2" note="move the front to the back" %}
{% include array.html v="3,2,1" name="q" hl="0" label="rotate 2 of 2" note="3 is at the front now, so pop() and top() just read the front" %}
</div>

```cpp
class MyStack {
   public:
    queue<int> q;
    MyStack() {}

    void push(int x) {
        q.push(x);
        for (int i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int front = q.front();
        q.pop();
        return front;
    }

    int top() { return q.front(); }

    bool empty() { return q.empty(); }
};
```

## Deque: O(1) everything

A `deque` lets you push and pop at both ends, so the back of the deque works as the top of the stack and nothing has to be rotated. Every operation is O(1). The catch is that `pop_back` and `back` aren't queue operations, so this breaks the problem's rule. Use it when you just need a stack, but not in an interview that asks for queues only. `std::stack` uses a `deque` under the hood by default.

```cpp
class MyStack {
   public:
    deque<int> dq;
    MyStack() {}

    void push(int x) { dq.push_back(x); }

    int pop() {
        int top = dq.back();
        dq.pop_back();
        return top;
    }

    int top() { return dq.back(); }

    bool empty() { return dq.empty(); }
};
```

{: .pitfall }
> In your `top()`, the last element has to go into `q2` as well (`q2.push(front)`), so it isn't lost when everything moves back. Yours does this. Also, `q.size()` is unsigned, so `q.size() - 1` on an empty queue wraps around to a huge number. In the costly-push version this is safe only because `push` has just made the size at least 1. If you want O(1) `top()` while keeping your cheap push, store a `topElem` variable that you update on every push. `pop()` still has to walk.

{: .revisit }
> The reverse problem is Implement Queue Using Stacks. There the two-stack version gets **amortized** O(1), because each element moves from one stack to the other at most once. Queues don't allow that trick here: every walk only rotates the elements, so their order never flips and nothing is saved for later.
