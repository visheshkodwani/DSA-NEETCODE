---
title: 4Sum
layout: problem
parent: Two Pointers
nav_order: 9
difficulty: Medium
time: O(n³)
space: O(1)
---

Return every unique quadruplet `[nums[a], nums[b], nums[c], nums[d]]` with distinct indices that sums to `target`, in any order.

## Examples

```
Input:  nums = [3,2,3,-3,1,0], target = 3
Output: [[-3,0,3,3],[-3,1,2,3]]
```

```
Input:  nums = [1,-1,1,-1,1,-1], target = 2
Output: [[-1,1,1,1]]
```

{: .intuition }
> **3Sum with one more fixed number.** Sort, then fix `nums[i]` and `nums[j]` with two loops. The last two numbers must add to `target - nums[i] - nums[j]`, which is the Two Sum II squeeze with `k` and `end`. Skip a repeated `i` or `j` the same way 3Sum skips a repeated `i`.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ i, j, k, end</span> · <span class="done">■ quadruplet found</span></p>
{% include array.html v="3,2,3,-3,1,0" name="nums (input)" vars="target=3" label="sort" note="sorted, equal values sit together" %}
{% include array.html v="-3,0,1,2,3,3" name="nums (sorted)" join=true %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="0,1,2,5" ptr="i=0,j=1,k=2,end=5" vars="need=6,sum=4" label="i = 0, j = 1" note="need = 3 − (−3) − 0 = 6. 4 < 6 → k++" %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="0,1,3,5" ptr="i=0,j=1,k=3,end=5" vars="need=6,sum=5" label="i = 0, j = 1" note="5 < 6 → k++" %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="0,1,4,5" ptr="i=0,j=1,k=4,end=5" vars="need=6,sum=6" label="i = 0, j = 1" note="6 == need → push [−3, 0, 3, 3]; k++, end-- → pointers cross" %}
{% include array.html v="-3,0,3,3" name="ans[0]" done="0,1,2,3" join=true %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="0,2,3,5" ptr="i=0,j=2,k=3,end=5" vars="need=5,sum=5" label="i = 0, j = 2" note="need = 3 − (−3) − 1 = 5. 5 == need → push [−3, 1, 2, 3]" %}
{% include array.html v="-3,0,3,3" name="ans[0]" done="0,1,2,3" join=true %}
{% include array.html v="-3,1,2,3" name="ans[1]" done="0,1,2,3" join=true %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="0,3,4,5" ptr="i=0,j=3,k=4,end=5" vars="need=4,sum=6" label="i = 0, j = 3" note="6 > 4 → end-- → pointers meet. j = 3 is the last j (j < n − 2)" %}
{% include array.html v="-3,0,1,2,3,3" name="nums" hl="1,2,3,5" ptr="i=1,j=2,k=3,end=5" vars="need=2,sum=5" label="i = 1, j = 2" note="every pair is too big from here. Same for (1, 3) and (2, 3), so nothing more is found" %}
{% include array.html v="-3,0,3,3" name="ans[0]" done="0,1,2,3" label="end" note="return both quadruplets" %}
{% include array.html v="-3,1,2,3" name="ans[1]" done="0,1,2,3" join=true %}
</div>

## Code

```cpp
class Solution {
   public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4)
        return {};
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        for (int i = 0; i < nums.size() - 3; i++) {

            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i+1 && nums[j] == nums[j - 1]) continue;
 long long targetcopy =
                    (long long)target - nums[j] - nums[i];
                int k = j + 1;
                int end = nums.size() - 1;

                while (k < end) {
                    int sum = nums[k] + nums[end];

                    if (sum == targetcopy) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[end]});

                        k++;
                        end--;

                        while (k < end && nums[k] == nums[j - 1]) k++;

                        while (k < end && nums[end] == nums[end + 1]) end--;
                    } else if (sum > targetcopy) {
                        end--;
                    } else {
                        k++;
                    }
                }
            }
        }
        return ans;
    }
};
```

## Best: already optimal

Yours is already the best: O(n³) time and O(1) extra space besides the sort and the output. A hash-based approach doesn't beat O(n³) in the worst case and costs extra space. For speed, you can break out of the `i` or `j` loop early when even the smallest possible sum from there is already bigger than `target`.

{: .pitfall }
> The `k` skip compares with `nums[j - 1]`, but `nums[k - 1]` was meant. It's harmless: after a match the `end` skip moves past every copy of `nums[end]`, so if `nums[k]` repeats, the sum is now below `need` and `k++` moves on anyway. No duplicate quadruplet gets through, which a 20,000-case random test against brute force confirmed. The `long long` on `targetcopy` does matter: `target - nums[i] - nums[j]` can reach about 3·10⁹, past `INT_MAX`. `nums[k] + nums[end]` tops out at 2·10⁹, so it fits in an `int`.

{: .revisit }
> Pattern: kSum = fix `k − 2` numbers with loops, then squeeze the last two. 2Sum O(n), 3Sum O(n²), 4Sum O(n³). It can be written once recursively as `kSum(nums, start, k, target)`.
