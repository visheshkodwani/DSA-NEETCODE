---
title: Boats to Save People
layout: problem
parent: Two Pointers
nav_order: 11
difficulty: Medium
time: O(n log n)
space: O(1)
---

Each boat holds at most **two** people with total weight at most `limit`. Return the minimum number of boats needed to carry everyone. Every person weighs at most `limit`, so each one fits in a boat alone.

## Examples

```
Input:  people = [5,1,4,2], limit = 6
Output: 2
```

```
Input:  people = [1,3,2,3,2], limit = 3
Output: 4
```

{: .intuition }
> **The heaviest person goes in a boat now, either way.** Sort, then look at the heaviest person left (`end`). The best partner for them is the lightest person left (`start`): if even the lightest can't share their boat, nobody can, so they go alone. If the lightest fits, pairing them costs nothing, because any other partner would be heavier. Either way one boat leaves and `end--`; `start++` only when the pair fits.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ start, end</span> · <span class="done">■ already in a boat</span></p>
{% include array.html v="1,3,2,3,2" name="people (input)" vars="limit=3" label="sort" note="lightest on the left, heaviest on the right" %}
{% include array.html v="1,2,2,3,3" name="people (sorted)" join=true %}
{% include array.html v="1,2,2,3,3" name="people" hl="0,4" ptr="start=0,end=4" vars="sum=4,boats=1" label="4 > 3" note="the heaviest can't share even with the lightest → sails alone. end--, boats++" %}
{% include array.html v="1,2,2,3,3" name="people" hl="0,3" done="4" ptr="start=0,end=3" vars="sum=4,boats=2" label="4 > 3" note="same again → 3 sails alone. end--, boats++" %}
{% include array.html v="1,2,2,3,3" name="people" hl="0,2" done="3,4" ptr="start=0,end=2" vars="sum=3,boats=3" label="3 ≤ 3" note="1 and 2 share a boat → start++, end--, boats++" %}
{% include array.html v="1,2,2,3,3" name="people" hl="1" done="0,2,3,4" ptr="start=1,end=1" vars="sum=4,boats=4" label="start == end" note="one person left. The sum counts them twice (4 > 3), so the else branch sends them alone. boats++" %}
{% include array.html v="1,2,2,3,3" name="people" done="0,1,2,3,4" vars="boats=4" label="end" note="start > end → return 4" %}
</div>

## Code

```cpp
class Solution {
   public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int start = 0;
        int end = people.size() - 1;
        int ans = 0;
        while (start <= end) {
            if (people[start] + people[end] <= limit) {
                start++;
                end--;
                ans++;
            } else  {
                end--;
                ans++;
            }
        }
        return ans;
    }
};
```

## Best: already optimal

Yours is the standard best answer: O(n log n) for the sort, then one O(n) pass with O(1) extra space. The sort is the only cost. Since weights are bounded (`people[i] ≤ limit ≤ 3·10⁴`), a counting sort brings it down to O(n + limit), but the greedy is unchanged. Both branches do `end--` and `ans++`, so the loop can be shortened to:

```cpp
while (start <= end) {
    if (people[start] + people[end] <= limit) start++;
    end--;
    ans++;
}
```

{: .pitfall }
> Use `start <= end`, not `<`. With `<`, the last person left when the pointers meet never gets a boat. When `start == end`, the check adds that person's weight twice. That's harmless: whichever branch runs, exactly one boat is counted and the loop ends.

{: .revisit }
> This greedy works because a boat holds **at most two** people. With three or more per boat, pairing heaviest with lightest is no longer enough, and the problem turns into bin packing. Same squeeze as Two Integer Sum II, but here a failed pair only drops `end`.
