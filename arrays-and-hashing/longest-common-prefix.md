---
title: Longest Common Prefix
layout: problem
parent: Arrays & Hashing
nav_order: 6
difficulty: Easy
time: O(n·m)
space: O(m)
---

Return the longest prefix shared by every string in `strs`, or `""` if they share none.

## Examples

```
Input:  strs = ["bat", "bag", "bank", "band"]
Output: "ba"
```

```
Input:  strs = ["dance", "dag", "danger", "damage"]
Output: "da"
```

{: .intuition }
> **The common prefix can only shrink.** Start with `lcp = strs[0]`, then cut it down to what it shares with each next string. Whatever's left after the last string is the answer.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="done">■ matches lcp</span> · <span class="hl">■ mismatch</span></p>
{% include array.html v="b,a,t" label="start" note="lcp = strs[0] = &quot;bat&quot;" %}
{% include array.html v="b,a,g" done="0,1" hl="2" label="&quot;bag&quot;" note="g ≠ t at index 2 → lcp = &quot;ba&quot;" %}
{% include array.html v="b,a,n,k" done="0,1" label="&quot;bank&quot;" note="lcp runs out at 2 → lcp = &quot;ba&quot;" %}
{% include array.html v="b,a,n,d" done="0,1" label="&quot;band&quot;" note="lcp runs out at 2 → lcp = &quot;ba&quot;" %}
</div>

## Code

```cpp
class Solution {
   public:
    string lcpf(string a, string b) {
        int i = 0;
        int j = 0;
        int m = a.length();
        int n = b.length();
        while (i < m && j < n && a[i] == b[j]) {
            i++;
            j++;
        }
        return a.substr(0, i);
    }
    string longestCommonPrefix(vector<string>& strs) {
        string lcp = strs[0];
        for (int i = 0; i < strs.size(); i++) lcp = lcpf(strs[i], lcp);
            return lcp;
    }

};
```

{: .pitfall }
> `lcpf(string a, string b)` takes both strings **by value**, so each call copies two strings. Use `const string&`. Also, `i` and `j` always move together, so one index is enough.

{: .revisit }
> Add `if (lcp.empty()) break;` to stop early once there's nothing left to share. The loop can start at `i = 1`, since comparing `strs[0]` with itself does nothing. Alternative: sort `strs` and compare only the first and last strings. They differ the most, so their common prefix is everyone's.
