class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size());

        for (int x : nums) {
            // even => impossible (only prime even is 2)
            if ((x & 1) == 0) {
                ans.push_back(-1);
                continue;
            }

            // find first 0 bit from position 1 onwards
            // (skip bit 0 because odd primes always have bit0 = 1)
            for (int p = 1; p < 32; p++) {
                if (((x >> p) & 1) == 0) {
                    // flip bit (p-1)
                    ans.push_back(x ^ (1 << (p - 1)));
                    break;
                }
            }
        }
        return ans;
    }
};
