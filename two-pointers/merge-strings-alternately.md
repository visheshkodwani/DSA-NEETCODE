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

`word1 = "ab"`, `word2 = "wxyz"`:

<div class="viz">
<p class="viz-legend"><span class="hl">■ taken this step</span> · <span class="done">■ used</span></p>
{% include array.html v="a,b" name="word1" hl="0" ptr="i=0" label="l = 0" note="l is even → take word1[i], i++" %}
{% include array.html v="w,x,y,z" name="word2" ptr="j=0" join=true %}
{% include array.html v="a" name="ans" hl="0" vars="l=0" join=true %}
{% include array.html v="a,b" name="word1" done="0" ptr="i=1" label="l = 1" note="l is odd → take word2[j], j++" %}
{% include array.html v="w,x,y,z" name="word2" hl="0" ptr="j=0" join=true %}
{% include array.html v="a,w" name="ans" hl="1" vars="l=1" join=true %}
{% include array.html v="a,b" name="word1" hl="1" done="0" ptr="i=1" label="l = 2" note="take word1[i] → i = 2, word1 is used up, main loop ends" %}
{% include array.html v="w,x,y,z" name="word2" done="0" ptr="j=1" join=true %}
{% include array.html v="a,w,b" name="ans" hl="2" vars="l=2" join=true %}
{% include array.html v="a,b" name="word1" done="0,1" label="tail" note="second tail loop appends the rest of word2" %}
{% include array.html v="w,x,y,z" name="word2" hl="1,2,3" done="0" ptr="j=1" join=true %}
{% include array.html v="a,w,b,x,y,z" name="ans" hl="3,4,5" join=true %}
{% include array.html v="a,w,b,x,y,z" name="ans" done="0,1,2,3,4,5" label="end" note="return &quot;awbxyz&quot;" %}
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

## Best: already optimal

Yours is already the best: every character is copied once, O(n + m) time. A shorter version with the same complexity is in the note below.

{: .pitfall }
> At most one of the two tail loops does anything, since the main loop only exits once a string is used up. Running both unconditionally is fine and saves an `if`.

{: .revisit }
> The `l` turn counter isn't needed: push one from each string per iteration. `while (i < n || j < m) { if (i < n) ans += word1[i++]; if (j < m) ans += word2[j++]; }` handles the tails in the same loop. `ans.reserve(n + m)` avoids regrowth.
