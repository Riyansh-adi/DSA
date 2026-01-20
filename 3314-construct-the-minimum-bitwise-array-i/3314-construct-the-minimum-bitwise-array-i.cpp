class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size());

        for (int num : nums) {
            if (num == 2) { // only even prime
                ans.push_back(-1);
                continue;
            }

            int mask = 1;
            // find the first 0 bit from right
            while (num & mask) mask <<= 1;

            // leading 1 of trailing ones group
            mask >>= 1;

            ans.push_back(num - mask);
        }

        return ans;
    }
};
