---
title: Remove Duplicates From Sorted Array
layout: problem
parent: Two Pointers
nav_order: 6
difficulty: Easy
time: O(n)
space: O(1)
---

`nums` is sorted. Remove duplicates in place so each value appears once, keep the order, and return the number of unique values `k`. Only the first `k` slots are checked.

## Examples

```
Input:  nums = [1,1,2,3,4]
Output: 4
```

```
Input:  nums = [2,10,10,30,30,30]
Output: 3
```

{: .intuition }
> **Sorted means duplicates sit next to each other.** `ndi` marks the last unique value kept so far. Walk `i` forward; whenever `nums[i]` differs from `nums[ndi]`, it's a new value, so grow the unique block by one (`ndi++`) and move `nums[i]` into that slot. The answer is the block's length, `ndi + 1`.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ swapped</span> · <span class="done">■ unique block [0..ndi]</span></p>
{% include array.html v="1,1,2,3,3,4" name="nums" ptr="ndi=0,i=1" label="start" note="nums[0] is always kept, so ndi = 0" %}
{% include array.html v="1,1,2,3,3,4" name="nums" done="0" ptr="ndi=0,i=1" label="i = 1" note="1 == nums[ndi] → duplicate, skip" %}
{% include array.html v="1,2,1,3,3,4" name="nums" hl="1,2" done="0" ptr="ndi=1,i=2" label="i = 2" note="2 ≠ 1 → ndi++, swap(nums[2], nums[1])" %}
{% include array.html v="1,2,3,1,3,4" name="nums" hl="2,3" done="0,1" ptr="ndi=2,i=3" label="i = 3" note="3 ≠ 2 → ndi++, swap(nums[3], nums[2])" %}
{% include array.html v="1,2,3,1,3,4" name="nums" done="0,1,2" ptr="ndi=2,i=4" label="i = 4" note="3 == nums[ndi] → duplicate, skip" %}
{% include array.html v="1,2,3,4,3,1" name="nums" hl="3,5" done="0,1,2" ptr="ndi=3,i=5" label="i = 5" note="4 ≠ 3 → ndi++, swap(nums[5], nums[3])" %}
{% include array.html v="1,2,3,4,3,1" name="nums" done="0,1,2,3" vars="k=4" label="end" note="return ++ndi = 4" %}
</div>

## Code

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int ndi = 0 ;
        for (int i = 1 ; i < nums.size();i++){
            if (nums[i]!=nums[ndi]){
                                ndi++;
                swap(nums[i],nums[ndi]);
            }
        }
        return ++ndi;
        
    }
};
```

## Best: already optimal

Yours is already the best: one pass, O(n) time, O(1) space. A plain copy (`nums[++ndi] = nums[i]`) works in place of the swap, since nothing past `k` is checked.

{: .pitfall }
> Compare against `nums[ndi]`, the last value **kept**, not `nums[i - 1]`. After a swap, `nums[i - 1]` may hold a moved value rather than the original neighbor. On an empty array this returns 1, but the constraints guarantee at least one element.

{: .revisit }
> Same write-index pattern as Remove Element. For Remove Duplicates II (each value at most twice), compare with `nums[k - 2]` instead of the last kept value.
