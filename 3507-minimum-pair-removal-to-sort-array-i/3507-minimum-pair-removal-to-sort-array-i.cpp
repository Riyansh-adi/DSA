class Solution {
public:
    bool isNonDecreasing(vector<int>& nums) {
        for (int i = 0; i + 1 < (int)nums.size(); i++) {
            if (nums[i] > nums[i + 1]) return false;
        }
        return true;
    }

    int minimumPairRemoval(vector<int>& nums) {
        int ans = 0;

        while (!isNonDecreasing(nums)) {
            int n = nums.size();
            int minSum = INT_MAX;
            int idx = -1;

            // find leftmost adjacent pair with minimum sum
            for (int i = 0; i < n - 1; i++) {
                int sum = nums[i] + nums[i + 1];
                if (sum < minSum) {
                    minSum = sum;
                    idx = i;
                }
            }

            // merge that pair
            nums[idx] = nums[idx] + nums[idx + 1];
            nums.erase(nums.begin() + idx + 1);

            ans++;
        }

        return ans;
    }
};
