// 1929. Concatenation of Array
// https://leetcode.com/problems/concatenation-of-array/
// Return nums concatenated with itself (length 2n).
// Time: O(n), Space: O(n)

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n*2,0);
        for (int i = 0 ; i < nums.size();i++){
            ans[i] = nums[i];
            ans[i+n] = nums[i];
        }
        return ans;

    }
};
