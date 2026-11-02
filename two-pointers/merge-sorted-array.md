---
title: Merge Sorted Array
layout: problem
parent: Two Pointers
nav_order: 5
difficulty: Easy
time: O((m+n) log(m+n))
space: O(m+n)
---

`nums1` has length `m + n`: its first `m` values are sorted, and the last `n` slots are `0` placeholders. Merge the sorted `nums2` into it in place so all of `nums1` is sorted.

## Examples

```
Input:  nums1 = [10,20,20,40,0,0], m = 4, nums2 = [1,2], n = 2
Output: [1,2,10,20,20,40]
```

```
Input:  nums1 = [0], m = 0, nums2 = [5], n = 1
Output: [5]
```

{: .intuition }
> **Fill the placeholders, then sort.** The last `n` slots of `nums1` are free, so copy `nums2` into them. Now `nums1` holds every value, just out of order, and a merge sort over the whole array finishes the job.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ changed</span> · <span class="done">■ final</span></p>
{% include array.html v="10,20,20,40,0,0" name="nums1" vars="m=4,n=2" label="start" note="the last n slots of nums1 are placeholders" %}
{% include array.html v="1,2" name="nums2" join=true %}
{% include array.html v="10,20,20,40,1,2" name="nums1" hl="4,5" ptr="i=4" label="copy" note="nums1[i] = nums2[j] for i = m … m + n − 1" %}
{% include array.html v="1,2" name="nums2" hl="0,1" join=true %}
{% include array.html v="10,20,20,1,2,40" name="nums1" hl="3,4,5" label="sort halves" note="mergeSort(0, 2) no change, mergeSort(3, 5) → [1, 2, 40]" %}
{% include array.html v="1,2,10,20,20,40" name="nums1" done="0,1,2,3,4,5" label="merge" note="mergehelper(0, 2, 5) merges the two halves" %}
</div>

## Code

```cpp
class Solution {
   public:
     void mergeSort(vector<int>& arr, int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        mergehelper(arr, l, m, r);
    }

    void mergehelper(vector<int>& arr, int l, int m, int r) {
        vector<int> temp;
        int i = l, j = m + 1;

        while (i <= m && j <= r) {
            if (arr[i] <= arr[j]) {
                temp.push_back(arr[i++]);
            } else {
                temp.push_back(arr[j++]);
            }
        }

        while (i <= m) temp.push_back(arr[i++]);
        while (j <= r) temp.push_back(arr[j++]);

        for (int i = l; i <= r; i++) {
            arr[i] = temp[i - l];
        }
    }
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int j = 0;
        for (int i = m; i < m + n; i++) {
            nums1[i] = nums2[j];
            j++;
        }
        mergeSort(nums1,0,nums1.size()-1);

    }
};
```

## Best: merge from the back, O(m+n) time, O(1) space

The free slots are at the **end** of `nums1`, so fill it from the end. `i` points at the last real value in `nums1`, `j` at the last value in `nums2`, and `k` at the last slot. Each step writes the larger of `nums1[i]` and `nums2[j]` at `k`. `k` never passes `i`, so nothing is overwritten before it's read. Once `nums2` is used up, the rest of `nums1` is already in place.

<div class="viz">
<p class="viz-legend"><span class="hl">■ written</span> · <span class="done">■ final</span></p>
{% include array.html v="10,20,20,40,0,0" name="nums1" ptr="i=3,k=5" label="start" note="i = m − 1, j = n − 1, k = m + n − 1" %}
{% include array.html v="1,2" name="nums2" ptr="j=1" join=true %}
{% include array.html v="10,20,20,40,0,40" name="nums1" hl="5" ptr="i=3,k=5" label="k = 5" note="nums1[i] = 40 > nums2[j] = 2 → write 40, i--" %}
{% include array.html v="1,2" name="nums2" ptr="j=1" join=true %}
{% include array.html v="10,20,20,40,20,40" name="nums1" hl="4" done="5" ptr="i=2,k=4" label="k = 4" note="20 > 2 → write 20, i--" %}
{% include array.html v="1,2" name="nums2" ptr="j=1" join=true %}
{% include array.html v="10,20,20,20,20,40" name="nums1" hl="3" done="4,5" ptr="i=1,k=3" label="k = 3" note="20 > 2 → write 20, i--" %}
{% include array.html v="1,2" name="nums2" ptr="j=1" join=true %}
{% include array.html v="10,20,10,20,20,40" name="nums1" hl="2" done="3,4,5" ptr="i=0,k=2" label="k = 2" note="10 > 2 → write 10, i = −1" %}
{% include array.html v="1,2" name="nums2" ptr="j=1" join=true %}
{% include array.html v="10,2,10,20,20,40" name="nums1" hl="1" done="2,3,4,5" ptr="k=1" vars="i=-1" label="k = 1" note="nums1 is used up → write nums2[j] = 2, j--" %}
{% include array.html v="1,2" name="nums2" hl="1" ptr="j=1" join=true %}
{% include array.html v="1,2,10,20,20,40" name="nums1" hl="0" done="1,2,3,4,5" ptr="k=0" vars="i=-1" label="k = 0" note="write nums2[j] = 1, j = −1 → loop ends" %}
{% include array.html v="1,2" name="nums2" hl="0" done="1" ptr="j=0" join=true %}
</div>

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
        }
    }
};
```

{: .pitfall }
> A full sort throws away the fact that both inputs are already sorted. After the copy, `nums1[0..m-1]` and `nums1[m..m+n-1]` are two sorted runs, so a single `mergehelper(nums1, 0, m - 1, m + n - 1)` is enough. That's `O(m+n)` with no recursion.

{: .revisit }
> Merging from the front would overwrite `nums1` values before they're read. Going backwards works because the empty slots are at the back. Loop on `j >= 0`, not `i >= 0`: leftover `nums1` values are already where they belong.
