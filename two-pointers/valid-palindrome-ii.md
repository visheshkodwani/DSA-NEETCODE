---
title: Valid Palindrome II
layout: problem
parent: Two Pointers
nav_order: 3
difficulty: Easy
time: O(n)
space: O(1)
---

Return `true` if `s` can become a palindrome after deleting at most one character.

## Examples

```
Input:  s = "aca"
Output: true
```

```
Input:  s = "abbadc"
Output: false
```

{: .intuition }
> **Walk in from both ends until the first mismatch.** Everything matched so far is fine. At the mismatch `s[i] != s[j]`, one of the two must be the deleted character, so try both: is `s[i..j-1]` a palindrome (drop `s[j]`), or is `s[i+1..j]` (drop `s[i]`)? Only one deletion is allowed, so those inner checks are plain palindrome checks with no more skipping.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ compared</span> · <span class="done">■ matched</span></p>
{% include array.html v="a,b,b,c,a" label="start" note="i = 0, j = 4" %}
{% include array.html v="a,b,b,c,a" hl="0,4" label="i=0 j=4" note="'a' == 'a' ✓" %}
{% include array.html v="a,b,b,c,a" hl="1,3" done="0,4" label="i=1 j=3" note="'b' != 'c' → mismatch" %}
{% include array.html v="a,b,b,c,a" hl="1,2" done="0,4" label="drop s[3]" note="isPalindrome(1, 2): 'bb' ✓" %}
{% include array.html v="a,b,b,c,a" done="0,1,2,4" label="end" note="one deletion works → true" %}
</div>

## Code

```cpp
class Solution {
   public:
    bool isPalindrome(string s, int a, int b) {
        while (a < b) {
            if (s[a] != s[b]) {
                return false;
            }
            a++;
            b--;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int i = 0;
        int j = s.length() - 1;
        while (i < s.length() && j >= 0) {
            while (i < s.length() && j >= 0 && s[i] == s[j]) {
                i++;
                j--;
            }
            if (isPalindrome(s, i, j - 1) || isPalindrome(s, i + 1, j))
                return true;
            else
                return false;
        }
        return true;
    }
};
```

{: .pitfall }
> `isPalindrome(string s, ...)` takes the string by value, so each call copies all `n` characters. Pass `const string& s`. The outer `while` also never loops a second time, because its body always returns.

{: .revisit }
> Tighter version: `int i = 0, j = s.size() - 1; while (i < j && s[i] == s[j]) i++, j--; return i >= j || isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);`. Stopping at `i < j` also means a palindrome input isn't scanned twice.
