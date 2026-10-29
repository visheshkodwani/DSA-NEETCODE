---
title: Merge Strings Alternately
layout: problem
parent: Two Pointers
nav_order: 4
difficulty: Easy
time: O(n + m)
space: O(1)
---

Merge `word1` and `word2` by taking one character from each in turn, starting with `word1`. When one runs out, append the rest of the other.

## Examples

```
Input:  word1 = "abc", word2 = "xyz"
Output: "axbycz"
```

```
Input:  word1 = "ab", word2 = "wxyz"
Output: "awbxyz"
```

{: .intuition }
> **One pointer per string, take turns.** `i` walks `word1`, `j` walks `word2`. Alternate while both still have characters. Once either is used up, nothing is left to alternate with, so copy whatever remains of the other one onto the end.

## Dry run

`word1 = "ab"`, `word2 = "wxyz"`, showing `ans` after each step:

<div class="viz">
<p class="viz-legend"><span class="hl">■ just added</span> · <span class="done">■ final</span></p>
{% include array.html v="a" hl="0" label="l = 0" note="word1[0], i = 1" %}
{% include array.html v="a,w" hl="1" label="l = 1" note="word2[0], j = 1" %}
{% include array.html v="a,w,b" hl="2" label="l = 2" note="word1[1], i = 2 → word1 done" %}
{% include array.html v="a,w,b,x,y,z" hl="3,4,5" label="tail" note="append rest of word2" %}
{% include array.html v="a,w,b,x,y,z" done="0,1,2,3,4,5" label="end" note="&quot;awbxyz&quot;" %}
</div>

## Code

```cpp
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int i = 0 ;
        int j = 0 ;
        int l = 0;
        string ans;
        while ( i < word1.length() && j < word2.length()){
            if (l % 2 == 0)
            {
            ans.push_back(word1[i]);
            i++;
            }
            else
            {
            ans.push_back(word2[j]);
            j++;
            }
            l++;

        }
        while (i < word1.length())
        {
             ans.push_back(word1[i]);
             i++;
        }
        while ( j < word2.length())
        {
            ans.push_back(word2[j]);
             j++; 
        }
        return ans;

        
    }
};
```

{: .pitfall }
> At most one of the two tail loops does anything, since the main loop only exits once a string is used up. Running both unconditionally is fine and saves an `if`.

{: .revisit }
> The `l` turn counter isn't needed: push one from each string per iteration. `while (i < n || j < m) { if (i < n) ans += word1[i++]; if (j < m) ans += word2[j++]; }` handles the tails in the same loop. `ans.reserve(n + m)` avoids regrowth.
