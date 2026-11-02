---
title: Concatenation of Array
layout: problem
parent: Arrays & Hashing
nav_order: 1
difficulty: Easy
time: O(n)
space: O(n)
---

Given `nums` of length `n`, return `ans` of length `2n` where `ans[i] == nums[i]` and `ans[i + n] == nums[i]`, i.e. `nums` followed by `nums` again.

## Examples

```
Input:  nums = [1, 4, 1, 2]
Output: [1, 4, 1, 2, 1, 4, 1, 2]
```

```
Input:  nums = [22, 21, 20, 1]
Output: [22, 21, 20, 1, 22, 21, 20, 1]
```

{: .intuition }
> **Each `nums[i]` goes to two slots: `i` and `i + n`.** Size `ans` to `2n` up front and fill both slots in one pass.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ written this step</span> · <span class="done">■ already filled</span></p>
{% include array.html v="1,4,1,2" name="nums" label="start" note="ans = vector(2n, 0)" vars="n=4" %}
{% include array.html v="0,0,0,0,0,0,0,0" name="ans" join=true %}
{% include array.html v="1,4,1,2" name="nums" hl="0" ptr="i=0" label="i = 0" note="ans[i] = ans[i + n] = nums[i] = 1" vars="n=4" %}
{% include array.html v="1,0,0,0,1,0,0,0" name="ans" hl="0,4" ptr="i=0,i+n=4" join=true %}
{% include array.html v="1,4,1,2" name="nums" hl="1" ptr="i=1" label="i = 1" note="ans[1] = ans[5] = 4" vars="n=4" %}
{% include array.html v="1,4,0,0,1,4,0,0" name="ans" hl="1,5" done="0,4" ptr="i=1,i+n=5" join=true %}
{% include array.html v="1,4,1,2" name="nums" hl="2" ptr="i=2" label="i = 2" note="ans[2] = ans[6] = 1" vars="n=4" %}
{% include array.html v="1,4,1,0,1,4,1,0" name="ans" hl="2,6" done="0,1,4,5" ptr="i=2,i+n=6" join=true %}
{% include array.html v="1,4,1,2" name="nums" hl="3" ptr="i=3" label="i = 3" note="ans[3] = ans[7] = 2" vars="n=4" %}
{% include array.html v="1,4,1,2,1,4,1,2" name="ans" hl="3,7" done="0,1,2,4,5,6" ptr="i=3,i+n=7" join=true %}
{% include array.html v="1,4,1,2,1,4,1,2" name="ans" done="0,1,2,3,4,5,6,7" label="end" note="nums twice" %}
</div>

## Code

```cpp
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n*2,0);
        for (int i = 0 ; i < nums.size();i++){
            ans[i] = nums[i];
            ans[i+n] = nums[i];
        }
        return ans;
        
    }
};
```

## Best: already optimal

Yours is already the best. Every one of the `2n` output slots has to be written, so O(n) time and O(n) space for the answer can't be beaten.

{: .pitfall }
> Don't mix pre-sizing with `push_back`. `vector<int> ans(2*n)` already holds `2n` zeros, so `push_back` would append after them and give length `4n`. Either pre-size and assign by index, or `reserve(2*n)` and `push_back`.

{: .revisit }
> STL one-liner: `vector<int> ans = nums; ans.insert(ans.end(), nums.begin(), nums.end());`. Don't do `nums.insert(nums.end(), nums.begin(), nums.end())` in place: the source range can't come from the same vector (undefined behavior).
