---
title: Asteroid Collision
layout: problem
parent: Stack
nav_order: 7
difficulty: Medium
time: O(n)
space: O(n)
---

All asteroids move along one line at the same speed. The absolute value of an entry in `asteroids` is that asteroid's size, and its sign is its direction (positive moves right, negative moves left). When two asteroids meet, the smaller one explodes. If they are the same size, both explode. Return the asteroids that are left after every collision.

## Examples

```
Input:  asteroids = [4,5,-5,2,-6,3]
Output: [-6,3]
```

```
Input:  asteroids = [10,2,-5]
Output: [10]
```

{: .intuition }
> **A collision can only happen when a left-moving asteroid meets a right-moving one that came before it.** Keep the survivors so far on a stack. A new asteroid moving right can't hit anything yet, so push it. A new asteroid moving left smashes into the right-movers on top of the stack. It destroys each smaller one, and stops when it meets a bigger one (it explodes), an equal one (both explode), a left-mover, or an empty stack (in the last two cases it survives). Each asteroid is pushed once and popped at most once, so the whole thing is O(n).

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ pushed this step</span> · <span class="done">■ survivors</span></p>
{% include array.html v="4" name="st" hl="0" label="4" note="the stack is empty, so push" %}
{% include array.html v="4,5" name="st" hl="1" label="5" note="the same direction as the top, so they never meet. Push" %}
{% include array.html v="4" name="st" label="-5" note="it meets 5, and they're the same size, so both explode" %}
{% include array.html v="4,2" name="st" hl="1" label="2" note="the same direction, so push" %}
{% include array.html v="-6" name="st" hl="0" label="-6" note="6 > 2, pop. 6 > 4, pop. The stack is empty, so -6 survives. Push" %}
{% include array.html v="-6,3" name="st" done="0,1" label="3" note="-6 moves left and 3 moves right, so they move apart. Push → [-6,3]" %}
</div>

## Code

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        for (int i = 0; i < asteroids.size(); i++) {

            if (st.empty())
                st.push(asteroids[i]);

            else if ((asteroids[i] > 0 && st.top() > 0) ||
                     (asteroids[i] < 0 && st.top() < 0)) {
                st.push(asteroids[i]);
            }

            else if (st.top() > 0 && asteroids[i] < 0) {

                while (!st.empty() && st.top() > 0 &&
                       abs(asteroids[i]) > abs(st.top())) {
                    st.pop();
                }

                if (st.empty()) {
                    st.push(asteroids[i]);
                }
                else if (st.top() > 0 &&
                         abs(st.top()) == abs(asteroids[i])) {
                    st.pop();
                }
                else if (st.top() < 0) {
                    st.push(asteroids[i]);
                }
            }

            else {
                st.push(asteroids[i]);
            }
        }

        vector<int> ans;

        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};
```

## Best: `vector` as the stack, O(n) time, O(n) space

The Big-O is the same, but there's less code. A `vector` can act as the stack and also be returned directly, so you don't need to copy the stack into `ans` and reverse it. Keep a flag `alive` for the new asteroid. The only case where it can collide is when it moves left and the top of the stack moves right. Every other case comes down to "push it", so the four branches become one loop.

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for (int a : asteroids) {
            bool alive = true;
            while (alive && a < 0 && !st.empty() && st.back() > 0) {
                if (st.back() < -a) {
                    st.pop_back();
                    continue;
                }
                if (st.back() == -a) st.pop_back();
                alive = false;
            }
            if (alive) st.push_back(a);
        }
        return st;
    }
};
```

{: .pitfall }
> Only a top that moves **right** with a new asteroid that moves **left** can collide. A top that moves left with a new one that moves right (`[-6, 3]`) means they're moving apart, so don't pop anything. Remember the case where both are the same size: both explode, so pop the top **and** don't push the new one. After a chain of pops, look at the new top again. It might be bigger, equal, a left-mover, or there might be nothing left.

{: .revisit }
> The pattern is that each new element knocks things off the top of the stack until something stops it. Daily Temperatures and Next Greater Element use the same pop loop. It's O(n) because each element is popped at most once.
