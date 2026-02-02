class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        multiset<long long> small, large;
        long long sumSmall = 0;
        long long ans = LLONG_MAX;

        auto add = [&](long long x) {
            if (small.size() < k - 1) {
                small.insert(x);
                sumSmall += x;
            } else if (!small.empty() && x < *prev(small.end())) {
                auto it = prev(small.end());
                sumSmall -= *it;
                large.insert(*it);
                small.erase(it);

                small.insert(x);
                sumSmall += x;
            } else {
                large.insert(x);
            }
        };

        auto remove = [&](long long x) {
            if (small.find(x) != small.end()) {
                sumSmall -= x;
                small.erase(small.find(x));
                if (!large.empty()) {
                    auto it = large.begin();
                    small.insert(*it);
                    sumSmall += *it;
                    large.erase(it);
                }
            } else {
                large.erase(large.find(x));
            }
        };

        // initial window
        for (int i = 1; i <= dist + 1; i++) {
            add(nums[i]);
        }

        ans = nums[0] + sumSmall;

        // slide window
        for (int i = 2; i + dist < nums.size(); i++) {
            remove(nums[i - 1]);
            add(nums[i + dist]);
            ans = min(ans, nums[0] + sumSmall);
        }

        return ans;
    }
};
