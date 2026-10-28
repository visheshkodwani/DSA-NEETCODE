---
title: Valid Palindrome
layout: problem
parent: Two Pointers
nav_order: 2
difficulty: Easy
time: O(n)
space: O(1)
---

Return `true` if `s` reads the same forward and backward, ignoring case and every non-alphanumeric character.

## Examples

```
Input:  s = "Was it a car or a cat I saw?"
Output: true
```

```
Input:  s = "tab a cat"
Output: false
```

{: .intuition }
> **Compare from both ends, skipping junk.** `i` starts left, `j` starts right. Before each comparison, move `i` forward and `j` backward past anything that isn't a letter or digit, then compare with `tolower`. One mismatch means `false`. No need to build a cleaned copy of the string.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ compared</span> · <span class="done">■ matched</span></p>
{% include array.html v="a,.,b,?,B,A" label="start" note="i = 0, j = 5" %}
{% include array.html v="a,.,b,?,B,A" hl="0,5" label="i=0 j=5" note="'a' == 'a' ✓" %}
{% include array.html v="a,.,b,?,B,A" hl="2,4" done="0,5" label="i=2 j=4" note="i skips '.', 'b' == 'b' ✓" %}
{% include array.html v="a,.,b,?,B,A" hl="2,4" done="0,5" label="i=4 j=2" note="skip '?', pointers crossed but loop keeps going" %}
{% include array.html v="a,.,b,?,B,A" done="0,2,4,5" label="end" note="i = 6, j = -1 → true" %}
</div>

## Code

```cpp
class Solution {
   public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = s.length() - 1;
        while (i < s.length() && j >= 0) {
            while (i < s.length() && !isalnum(s[i])) i++;
            while (j >= 0 && !isalnum(s[j])) j--;
            if (tolower(s[i]) == tolower(s[j])) {
                i++;
                j--;
            } else
                return false;
        }
        return true;
    }
};
```

{: .pitfall }
> The loop runs until `i` hits the end, not until the pointers meet, so every pair is checked twice. Worse, on an all-punctuation string like `"?!"` both skips run off the ends and the compare reads `s[-1]`, which is undefined behavior. Bound everything by `i < j` instead.

{: .revisit }
> Tighter version: `while (i < j) { while (i < j && !isalnum(s[i])) i++; while (i < j && !isalnum(s[j])) j--; if (tolower(s[i++]) != tolower(s[j--])) return false; } return true;`. Half the comparisons, no out-of-bounds reads.
