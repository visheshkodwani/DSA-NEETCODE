---
title: Two Sum
layout: problem
parent: Arrays & Hashing
nav_order: 2
difficulty: Easy
time: O(n)
space: O(n)
---

Given `nums` and a `target`, return indices `i != j` with `nums[i] + nums[j] == target`, smaller index first. Exactly one valid pair exists.

## Examples

```
Input:  nums = [3, 4, 5, 6], target = 7
Output: [0, 1]
```

```
Input:  nums = [4, 5, 6], target = 10
Output: [0, 2]
```

{: .intuition }
> **For each `x`, the partner is `target - x`.** Keep a map of `value → index` for everything seen so far. If the partner is already in it, you're done. Otherwise store `x` and move on.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ current i / answer</span> · <span class="done">■ in the map</span></p>
{% include array.html v="4,5,6" label="start" note="target = 10, mp = {}" %}
{% include array.html v="4,5,6" hl="0" label="i = 0" note="need 6 → not in mp, store mp = {4:0}" %}
{% include array.html v="4,5,6" hl="1" done="0" label="i = 1" note="need 5 → not in mp, store mp = {4:0, 5:1}" %}
{% include array.html v="4,5,6" hl="0,2" done="1" label="i = 2" note="need 4 → found at 0, return [0, 2]" %}
</div>

## Code

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for (int i = 0 ; i < nums.size();i++){
            if(mp.find(target-nums[i])!=mp.end())
            return {mp[target-nums[i]],i};
            mp[nums[i]]=i;
        }
        return {};
        
    }
};
```

{: .pitfall }
> Check **before** inserting. With `nums = [3, 3], target = 6`, inserting first makes `i = 0` find itself and return `[0, 0]`. Checking first means the map only holds earlier indices.

{: .revisit }
> The smaller index always comes first for free: anything in the map was seen before `i`. Brute force is O(n²). Sorting + two pointers is O(n log n) and loses the original indices unless you sort `(value, index)` pairs.
