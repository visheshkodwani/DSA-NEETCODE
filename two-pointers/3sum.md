---
title: 3Sum
layout: problem
parent: Two Pointers
nav_order: 8
difficulty: Medium
time: O(n²)
space: O(1)
---

Return every unique triplet `[nums[i], nums[j], nums[k]]` with distinct indices that sums to `0`. No duplicate triplets, any order.

## Examples

```
Input:  nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
```

```
Input:  nums = [0,0,0,0]
Output: [[0,0,0]]
```

{: .intuition }
> **Fix one number, then run Two Sum II on the rest.** Sort first. For each `nums[i]`, you need two numbers to its right that add to `-nums[i]`, which is exactly the two-pointer squeeze from Two Integer Sum II. Sorting also puts equal values next to each other, so duplicates are easy to skip: skip an `i` equal to the previous one, and after a match move `j` and `end` past their repeats.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ i, j, end</span> · <span class="done">■ triplet found</span></p>
{% include array.html v="-1,0,1,2,-1,-4" name="nums (input)" label="sort" note="sorted, equal values sit together and the squeeze works" %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums (sorted)" join=true %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums" hl="0,1,5" ptr="i=0,j=1,end=5" vars="target=4,sum=1" label="i = 0" note="the largest pair is 1 + 2 = 3 < 4, so j walks up to end with no match" %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums" hl="1,2,5" ptr="i=1,j=2,end=5" vars="target=1,sum=1" label="i = 1" note="sum == target → push [-1, -1, 2], then j++, end--" %}
{% include array.html v="-1,-1,2" name="ans[0]" done="0,1,2" join=true %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums" hl="1,3,4" ptr="i=1,j=3,end=4" vars="target=1,sum=1" label="i = 1" note="sum == target → push [-1, 0, 1]; j++, end-- → pointers cross" %}
{% include array.html v="-1,-1,2" name="ans[0]" done="0,1,2" join=true %}
{% include array.html v="-1,0,1" name="ans[1]" done="0,1,2" join=true %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums" hl="2" ptr="i=2" label="i = 2" note="nums[2] == nums[1] → continue, it would find the same triplets again" %}
{% include array.html v="-4,-1,-1,0,1,2" name="nums" hl="3,4,5" ptr="i=3,j=4,end=5" vars="target=0,sum=3" label="i = 3" note="3 > 0 → end--, pointers meet. i = 3 is the last i (i < n − 2)" %}
{% include array.html v="-1,-1,2" name="ans[0]" done="0,1,2" label="end" note="return both triplets" %}
{% include array.html v="-1,0,1" name="ans[1]" done="0,1,2" join=true %}
</div>

## Code

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int i = 0; i < nums.size() - 2; i++) {

            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int target = -nums[i];

            int j = i + 1;
            int end = nums.size() - 1;

            while (j < end) {

                int sum = nums[j] + nums[end];

                if (sum == target) {

                    ans.push_back({nums[i], nums[j], nums[end]});

                    j++;
                    end--;

                    // Skip duplicate j values
                    while (j < end && nums[j] == nums[j - 1])
                        j++;

                    // Skip duplicate end values
                    while (j < end && nums[end] == nums[end + 1])
                        end--;
                }
                else if (sum > target) {
                    end--;
                }
                else {
                    j++;
                }
            }
        }

        return ans;
    }
};
```

## Best: already optimal

Yours is already the best: O(n²) time and O(1) extra space besides the sort and the output. A hash set per `i` is also O(n²) but costs O(n) space. One cheap speed-up: add `if (nums[i] > 0) break;` at the top of the loop. Once the fixed number is positive, everything to its right is too, so no triplet can sum to 0.

{: .pitfall }
> `nums.size() - 2` is **unsigned**. With fewer than 2 elements it wraps around to a huge number and the loop reads out of bounds. The constraints guarantee `n ≥ 3`, but `(int)nums.size() - 2` is safer. Also, skip duplicate `i` by comparing with `nums[i - 1]`, not `nums[i + 1]`. Comparing forward would skip the first `-1` and lose `[-1, -1, 2]`.

{: .revisit }
> Brute force is O(n³) and needs a set to remove duplicate triplets. The same pattern scales: 4Sum fixes two numbers and runs the squeeze inside, O(n³).
