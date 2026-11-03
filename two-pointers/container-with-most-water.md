---
title: Container With Most Water
layout: problem
parent: Two Pointers
nav_order: 12
difficulty: Medium
time: O(n)
space: O(1)
---

`heights[i]` is the height of bar `i`. Pick any two bars to form a container. The water it holds is `min(heights[i], heights[j]) * (j - i)`. Return the most water any container can store.

## Examples

```
Input:  heights = [1,7,2,5,4,7,3,6]
Output: 36
```

```
Input:  heights = [2,2,2]
Output: 4
```

{: .intuition }
> **Start at the widest container, then always drop the shorter wall.** The water level is set by the shorter wall. Any container that keeps the shorter wall and moves the other one inward is narrower, and its level still can't rise above that shorter wall. So the shorter wall can't beat what it holds right now, and you can throw it away. Each step drops one bar, so all useful pairs are checked in one pass.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ current walls</span> · <span class="done">■ best container</span></p>
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="0,7" ptr="start=0,end=7" vars="area=7,ans=7" label="min(1, 6) × 7 = 7" note="1 ≤ 6 → the left wall is shorter, start++" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="1,7" ptr="start=1,end=7" vars="area=36,ans=36" label="min(7, 6) × 6 = 36" note="new best. 7 > 6 → end--" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="1,6" ptr="start=1,end=6" vars="area=15,ans=36" label="min(7, 3) × 5 = 15" note="7 > 3 → end--" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="1,5" ptr="start=1,end=5" vars="area=28,ans=36" label="min(7, 7) × 4 = 28" note="tie, so 7 ≤ 7 → start++. Moving either wall is safe" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="2,5" ptr="start=2,end=5" vars="area=6,ans=36" label="min(2, 7) × 3 = 6" note="2 ≤ 7 → start++" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="3,5" ptr="start=3,end=5" vars="area=10,ans=36" label="min(5, 7) × 2 = 10" note="5 ≤ 7 → start++" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" hl="4,5" ptr="start=4,end=5" vars="area=4,ans=36" label="min(4, 7) × 1 = 4" note="4 ≤ 7 → start++ → start == end, stop" %}
{% include array.html v="1,7,2,5,4,7,3,6" name="heights" done="1,7" ptr="start=1,end=7" vars="ans=36" label="end" note="bars 1 and 7: level 6, width 6 → return 36" %}
</div>

## Code

```cpp
class Solution {
public:
    int maxArea(vector<int>& heights) {
       int start = 0 ; 
       int end = heights.size()-1;
       int ans = INT_MIN;
       while (start < end){
        int res = min(heights[start],heights[end]) * (end-start);
        ans = max(res,ans);
        if (heights[start]<=heights[end])
        start++;
        else
        end--;
       }
       return ans;
        
    }
};
```

## Best: already optimal

Yours is already the best: O(n) time, O(1) space. Brute force tries every pair in O(n²). A small speed-up that keeps O(n): after moving a wall, keep moving it past any bar no taller than the wall you just dropped. Those bars can only hold less water, so there's no need to compute their areas.

{: .pitfall }
> Start `ans` at `0`, not `INT_MIN`. Areas are never negative, and with fewer than 2 bars the loop never runs, so your code would return `INT_MIN`. The constraints guarantee at least 2 bars, so it passes. Also move the **shorter** wall. Moving the taller one can never help, because the level is still capped by the shorter wall and the width shrinks.

{: .revisit }
> Don't confuse this with Trapping Rain Water, where every bar holds water above it. Here only the two chosen walls matter, and the bars between them are ignored.
