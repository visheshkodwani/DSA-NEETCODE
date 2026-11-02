---
title: Rotate Array
layout: problem
parent: Two Pointers
nav_order: 10
difficulty: Medium
time: O(n)
space: O(1)
---

Rotate `nums` to the right by `k` steps, in place. `k` can be larger than the array.

## Examples

```
Input:  nums = [1,2,3,4,5,6,7,8], k = 4
Output: [5,6,7,8,1,2,3,4]
```

```
Input:  nums = [1000,2,4,-3], k = 2
Output: [4,-3,1000,2]
```

{: .intuition }
> **Three reverses.** Rotating right by `k` moves the last `k` values to the front, keeping each block's order. Reversing the whole array puts the last `k` values in front, but each block comes out backwards. Reversing each block again fixes its order. Rotating by `n` changes nothing, so first set `k = k % n`.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ reversed this step</span> · <span class="done">■ final</span></p>
{% include array.html v="1,2,3,4,5,6,7" name="nums" vars="n=7,k=3" label="start" note="k % n = 3. The last 3 values (5, 6, 7) must end up in front" %}
{% include array.html v="7,6,5,4,3,2,1" name="nums" hl="0,1,2,3,4,5,6" ptr="l=0,r=6" vars="n=7,k=3" label="reverse all" note="5, 6, 7 are now in front, but backwards" %}
{% include array.html v="5,6,7,4,3,2,1" name="nums" hl="0,1,2" ptr="l=0,r=2" vars="n=7,k=3" label="reverse [0, k)" note="fixes the front block → 5, 6, 7" %}
{% include array.html v="5,6,7,1,2,3,4" name="nums" hl="3,4,5,6" done="0,1,2" ptr="l=3,r=6" vars="n=7,k=3" label="reverse [k, n)" note="fixes the back block → 1, 2, 3, 4" %}
{% include array.html v="5,6,7,1,2,3,4" name="nums" done="0,1,2,3,4,5,6" label="end" note="rotated right by 3" %}
</div>

## Code

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
         k = k % n ;
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin()+k);
        reverse(nums.begin()+k,nums.end());
        
    }
};
```

## Best: already optimal

Yours is already the best: every element is moved a constant number of times, O(n) time and O(1) space. A copy into a second array (`tmp[(i + k) % n] = nums[i]`) is simpler but O(n) space. Cyclic replacements are also O(1) space but much easier to get wrong.

{: .pitfall }
> Don't drop `k = k % n`. With `k > n`, `nums.begin() + k` points past the end and `reverse` is undefined behavior. `k % n` would divide by zero on an empty array, but the constraints guarantee `n ≥ 1`.

{: .revisit }
> Rotating **left** by `k` uses the same three reverses in the other order: reverse `[0, k)`, reverse `[k, n)`, then reverse everything. `std::rotate(nums.begin(), nums.end() - k, nums.end())` does a right rotation in one call.
