---
title: Reverse String
layout: problem
parent: Two Pointers
nav_order: 1
difficulty: Easy
time: O(n)
space: O(1)
---

Reverse the character array `s` in place, using `O(1)` extra memory.

## Examples

```
Input:  s = ["n","e","e","t"]
Output: ["t","e","e","n"]
```

```
Input:  s = ["r","a","c","e","c","a","r"]
Output: ["r","a","c","e","c","a","r"]
```

{: .intuition }
> **Swap the mirror pairs.** `s[i]` belongs where `s[n - 1 - i]` is, and vice versa. Swap each pair once, so stop at the middle: `i < n / 2`. On odd lengths the middle character is already in place.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ swapped</span> · <span class="done">■ final</span></p>
{% include array.html v="h,e,l,l,o" label="start" note="n = 5, loop i < 2" %}
{% include array.html v="o,e,l,l,h" hl="0,4" label="i = 0" note="swap(s[0], s[4])" %}
{% include array.html v="o,l,l,e,h" hl="1,3" done="0,4" label="i = 1" note="swap(s[1], s[3])" %}
{% include array.html v="o,l,l,e,h" done="0,1,2,3,4" label="end" note="middle s[2] never moves" %}
</div>

## Code

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0 ; i < s.size()/2;i++){
            swap(s[i],s[s.size()-1-i]);
        }
        
    }
};
```

{: .pitfall }
> Loop to `n / 2`, not `n`. Going all the way swaps every pair twice, and you end up with the original string.

{: .revisit }
> The usual two-pointer form: `int l = 0, r = s.size() - 1; while (l < r) swap(s[l++], s[r--]);`. Same pass, and it's the template for Valid Palindrome. In real code, use `reverse(s.begin(), s.end())`.
