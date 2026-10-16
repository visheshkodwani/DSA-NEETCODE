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
{% include array.html v="1,4,1,2" label="nums" note="n = 4" %}
{% include array.html v="0,0,0,0,0,0,0,0" label="start" note="ans = vector(8, 0)" %}
{% include array.html v="1,0,0,0,1,0,0,0" hl="0,4" label="i = 0" note="ans[0] = ans[4] = 1" %}
{% include array.html v="1,4,0,0,1,4,0,0" hl="1,5" done="0,4" label="i = 1" note="ans[1] = ans[5] = 4" %}
{% include array.html v="1,4,1,0,1,4,1,0" hl="2,6" done="0,1,4,5" label="i = 2" note="ans[2] = ans[6] = 1" %}
{% include array.html v="1,4,1,2,1,4,1,2" hl="3,7" done="0,1,2,4,5,6" label="i = 3" note="ans[3] = ans[7] = 2" %}
{% include array.html v="1,4,1,2,1,4,1,2" done="0,1,2,3,4,5,6,7" label="end" note="nums twice" %}
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

{: .pitfall }
> Don't mix pre-sizing with `push_back`. `vector<int> ans(2*n)` already holds `2n` zeros, so `push_back` would append after them and give length `4n`. Either pre-size and assign by index, or `reserve(2*n)` and `push_back`.

{: .revisit }
> STL one-liner: `vector<int> ans = nums; ans.insert(ans.end(), nums.begin(), nums.end());`. Don't do `nums.insert(nums.end(), nums.begin(), nums.end())` in place: the source range can't come from the same vector (undefined behavior).
