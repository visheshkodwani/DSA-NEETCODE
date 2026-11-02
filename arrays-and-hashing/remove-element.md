---
title: Remove Element
layout: problem
parent: Arrays & Hashing
nav_order: 7
difficulty: Easy
time: O(n)
space: O(1)
---

Remove every `val` from `nums` in place and return `k`, the number of elements left. The first `k` slots must hold those elements, in any order. Anything after them doesn't matter.

## Examples

```
Input:  nums = [3, 2, 2, 3], val = 3
Output: k = 2, nums = [2, 2, _, _]
```

```
Input:  nums = [0, 1, 2, 2, 3, 0, 4, 2], val = 2
Output: k = 5, nums = [0, 1, 3, 0, 4, _, _, _]
```

{: .intuition }
> **`nvi` is where the next keeper goes.** Scan with `i`. Every element that isn't `val` gets swapped to `nums[nvi]`, then `nvi++`. Everything left of `nvi` is a keeper, and `nvi` itself is the answer.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ swapped</span> · <span class="done">■ kept (index &lt; nvi)</span></p>
{% include array.html v="0,1,2,2,3,0,4,2" name="nums" hl="0" done="" ptr="i=0,nvi=0" vars="val=2" label="i = 0" note="0 ≠ val → swap(nums[0], nums[0]), nvi = 1" %}
{% include array.html v="0,1,2,2,3,0,4,2" name="nums" hl="1" done="0" ptr="i=1,nvi=1" vars="val=2" label="i = 1" note="1 ≠ val → swap in place, nvi = 2" %}
{% include array.html v="0,1,2,2,3,0,4,2" name="nums" hl="" done="0,1" ptr="i=2,nvi=2" vars="val=2" label="i = 2" note="2 = val → skip" %}
{% include array.html v="0,1,2,2,3,0,4,2" name="nums" hl="" done="0,1" ptr="i=3,nvi=2" vars="val=2" label="i = 3" note="2 = val → skip" %}
{% include array.html v="0,1,3,2,2,0,4,2" name="nums" hl="2,4" done="0,1" ptr="i=4,nvi=2" vars="val=2" label="i = 4" note="3 ≠ val → swap(nums[2], nums[4]), nvi = 3" %}
{% include array.html v="0,1,3,0,2,2,4,2" name="nums" hl="3,5" done="0,1,2" ptr="i=5,nvi=3" vars="val=2" label="i = 5" note="0 ≠ val → swap(nums[3], nums[5]), nvi = 4" %}
{% include array.html v="0,1,3,0,4,2,2,2" name="nums" hl="4,6" done="0,1,2,3" ptr="i=6,nvi=4" vars="val=2" label="i = 6" note="4 ≠ val → swap(nums[4], nums[6]), nvi = 5" %}
{% include array.html v="0,1,3,0,4,2,2,2" name="nums" hl="" done="0,1,2,3,4" ptr="i=7,nvi=5" vars="val=2" label="i = 7" note="2 = val → skip · return nvi = 5" %}
</div>

## Code

```cpp
class Solution {
   public:
    int removeElement(vector<int>& nums, int val) {
        int nvi = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                swap(nums[i], nums[nvi]);
                nvi++;
            }
        }
        return nvi;
    }
};
```

## Best: already optimal

Yours is already the best: one pass, O(n) time, O(1) space. Copying instead of swapping (`nums[nvi++] = nums[i]`) does fewer writes, with the same complexity.

{: .pitfall }
> Don't `erase` inside the loop. Each `erase` shifts the whole tail, which makes it O(n²), and it breaks your index: after erasing, `i++` skips the element that just slid into slot `i`.

{: .revisit }
> Same "write index" pattern as Move Zeroes and Remove Duplicates. Here you don't care what's past `k`, so `nums[nvi++] = nums[i]` (copy) is enough. The swap only matters when the tail has to keep the removed values, as in Move Zeroes.
