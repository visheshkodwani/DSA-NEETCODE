---
title: Product of Array Except Self
layout: problem
parent: Arrays & Hashing
nav_order: 5
difficulty: Medium
time: O(n)
space: O(n)
---

Return an array where `output[i]` is the product of every element of `nums` except `nums[i]`, in O(n) time and **without using division**.

## Examples

```
Input:  nums = [1, 2, 4, 6]
Output: [48, 24, 12, 8]
```

```
Input:  nums = [-1, 0, 1, 2, 3]
Output: [0, -6, 0, 0, 0]
```

{: .intuition }
> **Everything except `i` = (everything left of `i`) × (everything right of `i`).** One pass left to right builds the prefix products, one pass right to left builds the suffix products, and you multiply them together.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ built this step</span> · <span class="done">■ answer</span></p>
{% include array.html v="1,2,4,6" name="nums" label="pass 1" note="prefix[i] = product of nums[0..i-1]" %}
{% include array.html v="1,1,2,8" name="prefix" hl="0,1,2,3" join=true %}
{% include array.html v="1,2,4,6" name="nums" label="pass 2" note="suffix[i] = product of nums[i+1..n-1], built backwards then reversed" %}
{% include array.html v="1,1,2,8" name="prefix" join=true %}
{% include array.html v="48,24,6,1" name="suffix" hl="0,1,2,3" join=true %}
{% include array.html v="1,1,2,8" name="prefix" label="pass 3" note="nums[i] = prefix[i] × suffix[i]: 1·48, 1·24, 2·6, 8·1" %}
{% include array.html v="48,24,6,1" name="suffix" join=true %}
{% include array.html v="48,24,12,8" name="nums" done="0,1,2,3" join=true %}
</div>

## Code

```cpp
class Solution {
   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int prefixProduct = 1;
        vector<int> prefixProductarray;
        vector<int> suffixProductarray;
        for (int i = 0; i < nums.size(); i++) {
            prefixProductarray.push_back(prefixProduct);
            prefixProduct = prefixProduct * nums[i];
        }
        int suffixProduct = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            suffixProductarray.push_back(suffixProduct);
            suffixProduct = suffixProduct * nums[i];
        }
        reverse(suffixProductarray.begin(), suffixProductarray.end());
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = suffixProductarray[i] * prefixProductarray[i];
        }
        return nums;
    }
};
```

## Best: O(n) time, O(1) extra space

You don't need either helper array. Write the prefix products straight into `res`, then walk right to left with a single running `suffix` and multiply it in. The output array doesn't count as extra space, so this is O(1) extra.

<div class="viz">
<p class="viz-legend"><span class="hl">■ multiplied this step</span> · <span class="done">■ final</span></p>
{% include array.html v="1,2,4,6" name="nums" vars="suffix=1" label="after pass 1" note="res holds the prefix products" %}
{% include array.html v="1,1,2,8" name="res" join=true %}
{% include array.html v="1,2,4,6" name="nums" ptr="i=3" vars="suffix=1" label="i = 3" note="res[3] = 8 × 1 = 8, then suffix ×= 6" %}
{% include array.html v="1,1,2,8" name="res" hl="3" done="" ptr="i=3" join=true %}
{% include array.html v="1,2,4,6" name="nums" ptr="i=2" vars="suffix=6" label="i = 2" note="res[2] = 2 × 6 = 12, then suffix ×= 4" %}
{% include array.html v="1,1,12,8" name="res" hl="2" done="3" ptr="i=2" join=true %}
{% include array.html v="1,2,4,6" name="nums" ptr="i=1" vars="suffix=24" label="i = 1" note="res[1] = 1 × 24 = 24, then suffix ×= 2" %}
{% include array.html v="1,24,12,8" name="res" hl="1" done="2,3" ptr="i=1" join=true %}
{% include array.html v="1,2,4,6" name="nums" ptr="i=0" vars="suffix=48" label="i = 0" note="res[0] = 1 × 48 = 48 → done" %}
{% include array.html v="48,24,12,8" name="res" hl="0" done="1,2,3" ptr="i=0" join=true %}
</div>

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 1; i < n; i++) res[i] = res[i - 1] * nums[i - 1];  // prefix
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= suffix;     // prefix × suffix
            suffix *= nums[i];
        }
        return res;
    }
};
```

{: .pitfall }
> Don't use "total product ÷ `nums[i]`". It's banned here, and it breaks on zeros: one zero makes every other entry 0, and dividing by that zero is undefined. Prefix × suffix never divides, so zeros just work.

{: .revisit }
> Push the running product **before** multiplying in `nums[i]`, so `prefix[i]` excludes `nums[i]`. The suffix array is built backwards, hence the `reverse`. You could skip that by sizing it to `n` and writing `suffix[i]` directly.
