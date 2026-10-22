---
title: Majority Element II
layout: problem
parent: Arrays & Hashing
nav_order: 11
difficulty: Medium
time: O(n)
space: O(1)
---

Return every element that appears more than `⌊n / 3⌋` times. Follow-up: O(n) time and O(1) space.

## Examples

```
Input:  nums = [1, 2, 3, 1, 2, 1, 2, 4]
Output: [1, 2]
```

```
Input:  nums = [3, 2, 3]
Output: [3]
```

{: .intuition }
> **Extended Boyer–Moore: cancel three different values at a time.** At most two values can appear more than `n / 3` times, so the map holds up to 2 candidates. When a third distinct value shows up, take one vote off all three and drop any that reach 0. Each cancellation removes 3 elements. A value with more than `n / 3` copies can't be cancelled out completely, so it survives. Survivors are only *candidates*, so a second pass counts them.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ current i</span> · <span class="done">■ processed</span></p>
{% include array.html v="1,2,3,1,2,1,2,4" hl="0" label="i = 0" note="map {1:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="1" done="0" label="i = 1" note="map {1:1, 2:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="2" done="0,1" label="i = 2" note="{1:1, 2:1, 3:1} → 3 keys, −1 each → all 0 → map {}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="3" done="0,1,2" label="i = 3" note="map {1:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="4" done="0,1,2,3" label="i = 4" note="map {1:1, 2:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="5" done="0,1,2,3,4" label="i = 5" note="map {1:2, 2:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="6" done="0,1,2,3,4,5" label="i = 6" note="map {1:2, 2:2}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="7" done="0,1,2,3,4,5,6" label="i = 7" note="{1:2, 2:2, 4:1} → −1 each → 4 hits 0 → map {1:1, 2:1}" %}
{% include array.html v="1,2,3,1,2,1,2,4" hl="0,1,3,4,5,6" label="verify" note="1 ×3 > 2 ✓ · 2 ×3 > 2 ✓ → [1, 2]" %}
</div>

## Code

```cpp
class Solution {
   public:
    bool countcheck(vector<int>& nums, int k) {
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == k) count++;
        }
        if (count > (nums.size() / 3)) return true;
        return false;
    }
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp;
  
        for (int i = 0; i < nums.size(); i++) {
                  vector<int> toerase;
            mp[nums[i]]++;
            if (mp.size() > 2) {
                for (auto& j : mp) {
                    j.second--;
                    if (j.second == 0) toerase.push_back(j.first);
                }
                   for (int i : toerase) mp.erase(i);
            }
        }
     
        vector<int> res;
        for (auto j : mp) {
            if (countcheck(nums, j.first)) {
                res.push_back(j.first);
            }
        }
        return res;
    }
};
```

{: .pitfall }
> **`toerase` must start empty at every cleanup.** It was first declared outside the loop. On `[1,2,3,1,2,1,2,4]` it still held `[1,2,3]` from i = 2, so at i = 7 it erased 1 and 2 even though they had count 1 left. The result was `[]`. Collecting keys first is still right: erasing from the map inside the range-for would invalidate the iterator.

{: .pitfall }
> **The verify pass is required.** On `[1,1,2,3,4]`, 4 survives with count 1 but appears only once, which isn't `> 5/3`.

{: .revisit }
> The usual version skips the map: keep `cand1, cnt1, cand2, cnt2`. If x matches a candidate, add a vote. Else, if a count is 0, take that slot. Else, decrement both. Then verify both candidates. The map here never holds more than 3 keys, so it's still O(1) space. The inner `for (int i : toerase)` shadows the outer `i`, so rename it.
