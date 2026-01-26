class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        
        int minDiff = INT_MAX;
        vector<vector<int>> result;
        
        // Step 1: Find minimum difference
        for (int i = 1; i < arr.size(); i++) {
            minDiff = min(minDiff, arr[i] - arr[i - 1]);
        }
        
        // Step 2: Collect pairs with minimum difference
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] - arr[i - 1] == minDiff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }
        
        return result;
    }
};
