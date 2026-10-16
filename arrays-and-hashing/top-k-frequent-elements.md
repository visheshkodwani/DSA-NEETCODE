---
title: Top K Frequent Elements
layout: problem
parent: Arrays & Hashing
nav_order: 4
difficulty: Medium
time: O(n log n)
space: O(n)
---

Given `nums` and `k`, return the `k` most frequent elements, in any order. The answer is guaranteed to be unique.

## Examples

```
Input:  nums = [1, 2, 2, 3, 3, 3], k = 2
Output: [2, 3]
```

```
Input:  nums = [7, 7], k = 1
Output: [7]
```

{: .intuition }
> **Count, then rank by count.** A hash map gives each number's frequency. Put `(freq, num)` pairs in a vector, sort by frequency descending, and take the first `k`.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="done">■ taken</span></p>
{% include array.html v="1,2,2,3,3,3" label="nums" note="mp = {1:1, 2:2, 3:3}" %}
{% include array.html v="3,2,1" label="sorted" note="numbers by freq desc: (3,3) (2,2) (1,1)" %}
{% include array.html v="3,2,1" done="0,1" label="take k = 2" note="res = [3, 2]" %}
</div>

## Code

```cpp
class Solution {
   public:
   static bool customcomparator(pair<int,int> a1, pair<int,int> a2){
    return a1.first > a2.first;
   }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) mp[nums[i]]++;
        vector<pair<int, int>> ans;
        for (auto i : mp) ans.push_back({i.second, i.first});
        sort(ans.begin(), ans.end(), customcomparator);
        vector<int> res;
        for (int i = 0; i < k; i++) res.push_back(ans[i].second);
        return res;
    }
};
```

## Better: min-heap of size k, O(n log k)

You only need the top `k`, so don't sort all `m` distinct numbers. Keep a **min-heap** of at most `k` pairs. Push each `(freq, num)`; when the heap grows past `k`, pop the smallest. Whatever survives is the top `k`. This is the answer to give if you don't know bucket sort.

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // min-heap by freq
        for (auto& [num, f] : mp) {
            pq.push({f, num});
            if (pq.size() > k) pq.pop();  // drop the least frequent
        }
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};
```

## Better: bucket sort, O(n)

A frequency can only be `1..n`. So make `n + 1` buckets where `bucket[f]` holds the numbers seen exactly `f` times. Walk the buckets from `n` down to `1` and collect numbers until you have `k`. No comparisons at all.

<div class="viz">
<p class="viz-legend"><span class="hl">■ collecting</span> · <span class="done">■ taken</span> · index = frequency</p>
{% include array.html v="-,1,2,3,-,-,-" label="bucket" note="bucket[f] = numbers that appear f times" %}
{% include array.html v="-,1,2,3,-,-,-" hl="3" label="f = 3" note="f = 6, 5, 4 are empty → take 3, res = [3]" %}
{% include array.html v="-,1,2,3,-,-,-" hl="2" done="3" label="f = 2" note="take 2, res = [3, 2] → size k, return" %}
</div>

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int x : nums) mp[x]++;
        vector<vector<int>> bucket(nums.size() + 1);  // bucket[f] = numbers seen f times
        for (auto& [num, f] : mp) bucket[f].push_back(num);
        vector<int> res;
        for (int f = nums.size(); f > 0; f--)
            for (int num : bucket[f]) {
                res.push_back(num);
                if (res.size() == k) return res;
            }
        return res;
    }
};
```

{: .pitfall }
> The comparator takes `pair<int,int>` **by value**, so every comparison copies two pairs. Use `const pair<int,int>&`. A lambda also works: `sort(..., [](auto& a, auto& b) { return a.first > b.first; })`.

{: .revisit }
> **Ladder:** sort O(n log n) → min-heap O(n log k) → bucket O(n). A min-heap, not a max-heap: you evict the *smallest* so the big ones survive. Bucket sort works because frequencies are bounded by `n`.
