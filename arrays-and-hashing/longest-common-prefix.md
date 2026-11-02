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
<p class="viz-legend"><span class="hl">■ mismatch</span> · <span class="done">■ matches lcp</span></p>
{% include array.html v="b,a,t" name="lcp" label="start" note="lcp = strs[0] = &quot;bat&quot;" %}
{% include array.html v="b,a,t" name="lcp" done="0,1" hl="2" ptr="i=2" label="strs[1]" note="lcpf: 'g' ≠ 't' at i = 2 → lcp = &quot;ba&quot;" %}
{% include array.html v="b,a,g" name="strs[1]" done="0,1" hl="2" ptr="i=2" join=true %}
{% include array.html v="b,a" name="lcp" done="0,1" label="strs[2]" note="lcp runs out at i = 2 → still &quot;ba&quot;" %}
{% include array.html v="b,a,n,k" name="strs[2]" done="0,1" ptr="i=2" join=true %}
{% include array.html v="b,a" name="lcp" done="0,1" label="strs[3]" note="lcp runs out at i = 2 → still &quot;ba&quot;" %}
{% include array.html v="b,a,n,d" name="strs[3]" done="0,1" ptr="i=2" join=true %}
{% include array.html v="b,a" name="lcp" done="0,1" label="end" note="return &quot;ba&quot;" %}
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

## Best: vertical scan, O(S) time, O(1) extra space

Compare column by column: check character `i` of every string against `strs[0][i]`, and stop at the first string that's too short or differs. Nothing is copied until the single `substr` at the end, and it reads no character past the first mismatch. `S` is the total number of characters.

<div class="viz">
<p class="viz-legend"><span class="hl">■ compared</span> · <span class="done">■ common prefix</span></p>
{% include array.html v="b,a,t" name="strs[0]" hl="0" done="" ptr="i=0" label="i = 0" note="every s[0] == 'b' ✓" %}
{% include array.html v="b,a,g" name="strs[1]" hl="0" done="" ptr="i=0" join=true %}
{% include array.html v="b,a,n,k" name="strs[2]" hl="0" done="" ptr="i=0" join=true %}
{% include array.html v="b,a,n,d" name="strs[3]" hl="0" done="" ptr="i=0" join=true %}
{% include array.html v="b,a,t" name="strs[0]" hl="1" done="0" ptr="i=1" label="i = 1" note="every s[1] == 'a' ✓" %}
{% include array.html v="b,a,g" name="strs[1]" hl="1" done="0" ptr="i=1" join=true %}
{% include array.html v="b,a,n,k" name="strs[2]" hl="1" done="0" ptr="i=1" join=true %}
{% include array.html v="b,a,n,d" name="strs[3]" hl="1" done="0" ptr="i=1" join=true %}
{% include array.html v="b,a,t" name="strs[0]" hl="2" done="0,1" ptr="i=2" label="i = 2" note="strs[1][2] = 'g' ≠ 't' → return substr(0, 2) = &quot;ba&quot;" %}
{% include array.html v="b,a,g" name="strs[1]" hl="2" done="0,1" ptr="i=2" join=true %}
{% include array.html v="b,a,n,k" name="strs[2]" hl="" done="0,1" ptr="i=2" join=true %}
{% include array.html v="b,a,n,d" name="strs[3]" hl="" done="0,1" ptr="i=2" join=true %}
</div>

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        for (int i = 0; i < strs[0].size(); i++)
            for (const string& s : strs)
                if (i == s.size() || s[i] != strs[0][i]) return strs[0].substr(0, i);
        return strs[0];
    }
};
```

{: .pitfall }
> `lcpf(string a, string b)` takes both strings **by value**, so each call copies two strings. Use `const string&`. Also, `i` and `j` always move together, so one index is enough.

{: .revisit }
> Add `if (lcp.empty()) break;` to stop early once there's nothing left to share. The loop can start at `i = 1`, since comparing `strs[0]` with itself does nothing. Alternative: sort `strs` and compare only the first and last strings. They differ the most, so their common prefix is everyone's.
