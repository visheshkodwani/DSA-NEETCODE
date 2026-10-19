---
title: Sort Colors
layout: problem
parent: Arrays & Hashing
nav_order: 10
difficulty: Medium
time: O(n)
space: O(1)
---

`nums` holds only `0`, `1` and `2` (red, white, blue). Sort it in place, in one pass, without a library sort.

## Examples

```
Input:  nums = [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]
```

```
Input:  nums = [2, 0, 1]
Output: [0, 1, 2]
```

{: .intuition }
> **Dutch national flag: three regions, three pointers.** `[0, start)` is all 0s, `[start, mid)` is all 1s, `[mid, end]` is not yet checked, and `(end, n)` is all 2s. Look at `nums[mid]`: a 1 stays put, a 0 swaps to the `start` side, and a 2 swaps to the `end` side. Stop when the unchecked region is empty (`mid > end`).

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ looked at / swapped</span> · <span class="done">■ settled (outside [mid, end])</span></p>
{% include array.html v="2,0,2,1,1,0" label="start" note="start = 0, mid = 0, end = 5" %}
{% include array.html v="0,0,2,1,1,2" hl="0,5" label="mid = 0" note="2 → swap(0, 5), end = 4 · mid stays" %}
{% include array.html v="0,0,2,1,1,2" hl="0" done="5" label="mid = 0" note="0 → swap(0, 0), start = 1, mid = 1" %}
{% include array.html v="0,0,2,1,1,2" hl="1" done="0,5" label="mid = 1" note="0 → swap(1, 1), start = 2, mid = 2" %}
{% include array.html v="0,0,1,1,2,2" hl="2,4" done="0,1,5" label="mid = 2" note="2 → swap(2, 4), end = 3 · mid stays" %}
{% include array.html v="0,0,1,1,2,2" hl="2" done="0,1,4,5" label="mid = 2" note="1 → mid = 3" %}
{% include array.html v="0,0,1,1,2,2" hl="3" done="0,1,2,4,5" label="mid = 3" note="1 → mid = 4 > end → stop" %}
</div>

## Code

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int start = 0 ;
        int end = nums.size()-1;
        int mid = 0;
        while(mid<=end){
            if (nums[mid] == 1)
            mid++;
            else if (nums[mid] == 0)
            {
                swap(nums[start],nums[mid]);
                start++;
                mid++;
            }
            else if (nums[mid] == 2) {
                swap(nums[end],nums[mid]);
                end--;
            }
        }
        
    }
};
```

## Why no `mid++` after swapping with `end`?

It depends on **where the swapped-in value came from**.

- **Swap with `end`:** `nums[end]` is in the unchecked region `[mid, end]`, so you have no idea what it is. It could be a 0, 1 or 2. After the swap, that unknown value sits at `mid` and has to be checked on the next loop. Only `end--` is safe, because the 2 you just sent there is final.
- **Swap with `start`:** `nums[start]` is in `[start, mid)`, which you've already checked and which holds only 1s (or `start == mid`, and it's the same element). The value coming back to `mid` is a known 1, so `mid++` is safe.

`[1, 2, 0]` shows it. With `mid++` after the 2-swap, the 0 that comes back from the end is skipped:

<div class="viz">
<p class="viz-legend"><span class="hl">■ swapped</span> · <span class="done">■ settled</span></p>
{% include array.html v="1,2,0" label="mid = 0" note="1 → mid = 1" %}
{% include array.html v="1,0,2" hl="1,2" label="mid = 1" note="2 → swap(1, 2), end = 1 · nums[1] is now 0 (unchecked)" %}
{% include array.html v="1,0,2" done="2" label="✗ mid++" note="mid = 2 > end → stops with [1, 0, 2], wrong" %}
{% include array.html v="0,1,2" hl="0,1" done="2" label="✓ mid stays" note="mid = 1: 0 → swap(0, 1) → [0, 1, 2]" %}
</div>

{: .pitfall }
> The loop is `mid <= end`, not `mid < end`. When `mid == end`, there's still one unchecked element. `[1, 0]` with `<` stops after the 1 and returns `[1, 0]` unsorted.

{: .revisit }
> Two-pass alternative: count the 0s, 1s and 2s, then overwrite the array. That's also O(n), but the problem asks for one pass. The same three-way partition fixes quick sort on arrays with many duplicates (see Sort an Array).
