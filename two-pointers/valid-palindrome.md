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
{% include array.html v="a,.,b,?,B,A" name="s" ptr="i=0,j=5" label="start" note="i at the left end, j at the right end" %}
{% include array.html v="a,.,b,?,B,A" name="s" hl="0,5" ptr="i=0,j=5" label="compare" note="tolower: 'a' == 'a' ✓ → i++, j--" %}
{% include array.html v="a,.,b,?,B,A" name="s" hl="2,4" done="0,5" ptr="i=2,j=4" label="compare" note="i skips '.', then 'b' == 'b' ✓" %}
{% include array.html v="a,.,b,?,B,A" name="s" hl="2,4" done="0,5" ptr="i=4,j=2" label="crossed" note="skip '?': pointers crossed, but this loop keeps comparing pairs again" %}
{% include array.html v="a,.,b,?,B,A" name="s" done="0,2,4,5" vars="i=6,j=-1" label="end" note="i ran off the end → true" %}
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

## Best: stop when the pointers meet, O(n) time, O(1) space

Same approach, with every loop bounded by `i < j`. Each pair is compared once, and the skips can never run past each other or off the ends.

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            while (i < j && !isalnum(s[i])) i++;
            while (i < j && !isalnum(s[j])) j--;
            if (tolower(s[i++]) != tolower(s[j--])) return false;
        }
        return true;
    }
};
```

{: .pitfall }
> The loop runs until `i` hits the end, not until the pointers meet, so every pair is checked twice. Worse, on an all-punctuation string like `"?!"` both skips run off the ends and the compare reads `s[-1]`, which is undefined behavior. Bound everything by `i < j` instead.

{: .revisit }
> Building a cleaned, lowercased copy and comparing it with its reverse is also O(n), but it needs O(n) extra space. The two pointers do it in place.
