class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        int i = 0;

        // 1️⃣ Strictly increasing
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }
        if (i == 0) return false; // no increasing part

        // 2️⃣ Strictly decreasing
        int p = i;
        while (i + 1 < n && nums[i] > nums[i + 1]) {
            i++;
        }
        if (i == p) return false; // no decreasing part

        // 3️⃣ Strictly increasing again
        int q = i;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }
        if (i == q) return false; // no final increasing part

        // Must reach the end
        return i == n - 1;
    }
};
