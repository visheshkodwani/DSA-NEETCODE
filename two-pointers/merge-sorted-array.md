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
{% include array.html v="10,20,20,40,0,0" label="start" note="m = 4, last 2 slots are placeholders" %}
{% include array.html v="10,20,20,40,1,2" hl="4,5" label="copy" note="nums1[4..5] = nums2" %}
{% include array.html v="10,20,20,1,2,40" hl="3,4,5" label="sort halves" note="mergeSort(0,2) no change, mergeSort(3,5) → [1,2,40]" %}
{% include array.html v="1,2,10,20,20,40" done="0,1,2,3,4,5" label="merge" note="mergehelper(0, 2, 5)" %}
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

{: .pitfall }
> A full sort throws away the fact that both inputs are already sorted. After the copy, `nums1[0..m-1]` and `nums1[m..m+n-1]` are two sorted runs, so a single `mergehelper(nums1, 0, m - 1, m + n - 1)` is enough. That's `O(m+n)` with no recursion.

{: .revisit }
> The intended `O(1)`-space answer merges from the back, where the free slots are: `int i = m - 1, j = n - 1, k = m + n - 1; while (j >= 0) nums1[k--] = (i >= 0 && nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];`. Writing at `k` never overwrites a `nums1` value that hasn't been read yet, and once `nums2` runs out, the rest of `nums1` is already in place.
