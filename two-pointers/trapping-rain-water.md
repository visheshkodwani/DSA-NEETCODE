---
title: Trapping Rain Water
layout: problem
parent: Two Pointers
nav_order: 13
difficulty: Hard
time: O(n)
space: O(1)
---

`height[i]` is the height of a bar of width 1. After it rains, water collects between the bars. Return how many units of water are trapped.

## Examples

```
Input:  height = [0,2,0,3,1,0,1,3,2,1]
Output: 9
```

```
Input:  height = [4,2,0,3,2,5]
Output: 9
```

{: .intuition }
> **The water above a cell is `min(tallest bar on its left, tallest bar on its right) - height`.** Keep a pointer at each end, plus `leftMax` (the tallest bar already passed on the left) and `rightMax` (the same on the right). If `leftMax < rightMax`, the right side is guaranteed to have a bar at least as tall as `rightMax`, so the left cell's level is just `leftMax`. Fill it and move left. Otherwise the right cell's level is `rightMax`, so fill it and move right. You always work on the side with the lower wall, because that wall is the one that sets the level.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ cell being filled</span> · <span class="done">■ end</span></p>
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="0" ptr="left=0,right=9" vars="leftMax=0,rightMax=1,res=0" label="0 < 1 → fill left" note="0 - 0 = 0. leftMax = 0, left++" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="1" ptr="left=1,right=9" vars="leftMax=0,rightMax=1,res=0" label="0 < 1 → fill left" note="the bar is taller than leftMax, so no water. leftMax = 2, left++" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="9" ptr="left=2,right=9" vars="leftMax=2,rightMax=1,res=0" label="2 ≥ 1 → fill right" note="1 - 1 = 0. right--" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="8" ptr="left=2,right=8" vars="leftMax=2,rightMax=1,res=0" label="2 ≥ 1 → fill right" note="the bar is taller, no water. rightMax = 2, right--" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="7" ptr="left=2,right=7" vars="leftMax=2,rightMax=2,res=0" label="2 ≥ 2 → fill right" note="the bar is taller, no water. rightMax = 3, right--" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="2" ptr="left=2,right=6" vars="leftMax=2,rightMax=3,res=2" label="2 < 3 → fill left" note="2 - 0 = 2. left++" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="3" ptr="left=3,right=6" vars="leftMax=2,rightMax=3,res=2" label="2 < 3 → fill left" note="the bar is taller, no water. leftMax = 3, left++" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="6" ptr="left=4,right=6" vars="leftMax=3,rightMax=3,res=4" label="3 ≥ 3 → fill right" note="3 - 1 = 2. right--" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="5" ptr="left=4,right=5" vars="leftMax=3,rightMax=3,res=7" label="3 ≥ 3 → fill right" note="3 - 0 = 3. right--" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" hl="4" ptr="left=4,right=4" vars="leftMax=3,rightMax=3,res=9" label="left == right, still fill it" note="3 - 1 = 2. This is why the loop needs <=. right-- → stop" %}
{% include array.html v="0,2,0,3,1,0,1,3,2,1" name="height" done="2,4,5,6" ptr="left=4,right=3" vars="res=9" label="end" note="2 + 2 + 3 + 2 → return 9" %}
</div>

## Code

```cpp
class Solution {
   public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int res = 0;
        int leftMax = height[0];
        int rightMax = height[right];
        while (left <= right) {
            if (leftMax < rightMax) {
                if ((leftMax - height[left]) > 0) res = res + leftMax - height[left];
                leftMax = max(height[left], leftMax);
                left++;

            } else {
                if ((rightMax - height[right]) > 0) res = res + rightMax - height[right];
                rightMax = max(height[right], rightMax);
                right--;
            }
        }
        return res;
    }
};
```

## Best: already optimal

Yours is already the best: O(n) time, O(1) space. Two easier versions are also O(n) time but use O(n) extra space. One builds `prefixMax` and `suffixMax` arrays and adds up `min(prefixMax[i], suffixMax[i]) - height[i]`. The other uses a monotonic stack and fills water layer by layer.

{: .pitfall }
> You fill a cell **before** adding it to `leftMax`/`rightMax`, so the cell where the pointers meet is not always the tallest bar. It can still hold water, so the loop has to be `left <= right`. With `left < right`, `[0,5,0,3]` returns `0` instead of `3`. The NeetCode version moves the pointer first and then updates the max. In that version the meeting cell is always the tallest bar, so `<` works there.

{: .revisit }
> Compare with Container With Most Water. There only the two chosen walls matter. Here every cell holds its own column of water, set by the tallest bars on each side.
