---
title: Majority Element
layout: problem
parent: Arrays & Hashing
nav_order: 8
difficulty: Easy
time: O(n)
space: O(1)
---

Return the element that appears more than `⌊n / 2⌋` times. It's guaranteed to exist. Follow-up: O(n) time and O(1) space.

## Examples

```
Input:  nums = [5, 5, 1, 1, 1, 5, 5]
Output: 5
```

```
Input:  nums = [2, 2, 2]
Output: 2
```

{: .intuition }
> **Boyer–Moore voting: pair off different elements and cancel them.** A match adds a vote to the candidate, and a mismatch takes one away. When the count hits 0, the next element becomes the new candidate. The majority has more copies than everything else combined, so it can't be fully cancelled and it's the one left standing.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ current i</span> · <span class="done">■ processed</span></p>
{% include array.html v="5,5,1,1,1,5,5" hl="0" label="i = 0" note="count 0 → ans = 5, count = 1" %}
{% include array.html v="5,5,1,1,1,5,5" hl="1" done="0" label="i = 1" note="5 = ans → count = 2" %}
{% include array.html v="5,5,1,1,1,5,5" hl="2" done="0,1" label="i = 2" note="1 ≠ 5 → count = 1" %}
{% include array.html v="5,5,1,1,1,5,5" hl="3" done="0,1,2" label="i = 3" note="1 ≠ 5 → count = 0" %}
{% include array.html v="5,5,1,1,1,5,5" hl="4" done="0,1,2,3" label="i = 4" note="count 0 → ans = 1, count = 1" %}
{% include array.html v="5,5,1,1,1,5,5" hl="5" done="0,1,2,3,4" label="i = 5" note="5 ≠ 1 → count = 0" %}
{% include array.html v="5,5,1,1,1,5,5" hl="6" done="0,1,2,3,4,5" label="i = 6" note="count 0 → ans = 5, count = 1 → return 5" %}
</div>

## Code

```cpp
class Solution {
   public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int i = 0;
        int ans;
        while (i < nums.size()) {
            if (count == 0) {
                ans = nums[i];
                count++;
            } else if (ans == nums[i]) {
                count++;
            } else if (ans != nums[i])
                count--;
            i++;
        }
        return ans;
    }
};
```

{: .pitfall }
> The final candidate is only guaranteed correct because a majority is **promised**. If it might not exist, say `[1, 2, 3]`, you get some leftover candidate. Then you need a second pass that counts it and checks `> n / 2`.

{: .revisit }
> Other ways: a hash map of counts is O(n) time but O(n) space, and sorting then returning `nums[n / 2]` is O(n log n). Boyer–Moore is the only O(1)-space answer. For Majority Element II (`> n/3`), track **two** candidates with two counts. The last `else if (ans != nums[i])` can just be `else`.
