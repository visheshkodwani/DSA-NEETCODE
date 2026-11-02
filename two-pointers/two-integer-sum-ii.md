---
title: Two Integer Sum II
layout: problem
parent: Two Pointers
nav_order: 7
difficulty: Medium
time: O(n)
space: O(1)
---

`numbers` is sorted. Return the 1-indexed positions `[index1, index2]` of the two numbers that add up to `target`, with `index1 < index2`. Exactly one answer exists, and only O(1) extra space is allowed.

## Examples

```
Input:  numbers = [1,2,3,4], target = 3
Output: [1,2]
```

```
Input:  numbers = [2,7,11,15], target = 9
Output: [1,2]
```

{: .intuition }
> **Squeeze from both ends.** Start with the smallest and largest. If the sum is too big, `numbers[end]` is too big for every remaining partner, since `numbers[start]` is already the smallest left, so drop it with `end--`. If the sum is too small, `numbers[start]` is too small even with the biggest partner, so `start++`. Each step rules out one number, so the answer is found in one pass.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ current pair</span> · <span class="done">■ answer</span></p>
{% include array.html v="1,3,4,5,7,10,11" name="numbers" hl="0,6" ptr="start=0,end=6" vars="target=9,sum=12" label="12 > 9" note="too big → end--" %}
{% include array.html v="1,3,4,5,7,10,11" name="numbers" hl="0,5" ptr="start=0,end=5" vars="target=9,sum=11" label="11 > 9" note="too big → end--" %}
{% include array.html v="1,3,4,5,7,10,11" name="numbers" hl="0,4" ptr="start=0,end=4" vars="target=9,sum=8" label="8 < 9" note="too small → start++" %}
{% include array.html v="1,3,4,5,7,10,11" name="numbers" hl="1,4" ptr="start=1,end=4" vars="target=9,sum=10" label="10 > 9" note="too big → end--" %}
{% include array.html v="1,3,4,5,7,10,11" name="numbers" hl="1,3" ptr="start=1,end=3" vars="target=9,sum=8" label="8 < 9" note="too small → start++" %}
{% include array.html v="1,3,4,5,7,10,11" name="numbers" done="2,3" ptr="start=2,end=3" vars="target=9,sum=9" label="9 == 9" note="found → return {start + 1, end + 1} = [3, 4]" %}
</div>

## Code

```cpp
class Solution {
   public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0;
        int end = numbers.size() - 1;
        while (start < end) {
            if (numbers[start] + numbers[end] == target)
                return {++start, ++end};
            else if (numbers[start] + numbers[end] > target)
                end--;
            else
                start++;
        }
        return {};
    }
};
```

## Best: already optimal

Yours is already the best: O(n) time and O(1) space. Binary-searching for `target - numbers[i]` for each `i` is O(n log n), and the Two Sum hash map needs O(n) space, which this problem forbids.

{: .pitfall }
> The answer is **1-indexed**. `{++start, ++end}` handles it; returning `{start, end}` would be off by one. `start < end` (not `<=`) stops an element from pairing with itself.

{: .revisit }
> This is Two Sum on a sorted array. The squeeze only works because the array is sorted. It's also the inner loop of 3Sum: fix one number, then run this on the rest.
