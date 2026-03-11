class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());  // Sort the array
        int n = nums.size();
        int closest = nums[0] + nums[1] + nums[2];  // Initial closest sum

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int currentSum = nums[i] + nums[left] + nums[right];

                // If it's closer to the target, update closest
                if (abs(currentSum - target) < abs(closest - target)) {
                    closest = currentSum;
                }

                if (currentSum < target) {
                    left++;  // Need a larger sum
                } else {
                    right--;  // Need a smaller sum
                }
            }
        }

        return closest;
    }
};