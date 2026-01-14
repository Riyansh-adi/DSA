#include <bits/stdc++.h>
using namespace std;

class SegTree {
public:
    vector<long long> xs;     // compressed x coordinates
    vector<int> cnt;          // coverage count
    vector<long long> cover;  // covered length
    int n;

    SegTree(const vector<long long>& coords) {
        xs = coords;
        n = (int)xs.size() - 1; // number of x-segments
        cnt.assign(4 * n, 0);
        cover.assign(4 * n, 0);
    }

    void pull(int idx, int l, int r) {
        if (cnt[idx] > 0) {
            cover[idx] = xs[r + 1] - xs[l];
        } else if (l == r) {
            cover[idx] = 0;
        } else {
            cover[idx] = cover[idx * 2] + cover[idx * 2 + 1];
        }
    }

    void add(int idx, int l, int r, long long ql, long long qr, int val) {
        if (qr <= xs[l] || xs[r + 1] <= ql) return;

        if (ql <= xs[l] && xs[r + 1] <= qr) {
            cnt[idx] += val;
            pull(idx, l, r);
            return;
        }

        int mid = (l + r) / 2;
        add(idx * 2, l, mid, ql, qr, val);
        add(idx * 2 + 1, mid + 1, r, ql, qr, val);
        pull(idx, l, r);
    }

    void addInterval(long long xl, long long xr, int val) {
        add(1, 0, n - 1, xl, xr, val);
    }

    long long coveredWidth() {
        return cover[1];
    }
};

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        struct Event {
            long long y;
            int delta;
            long long xl, xr;
            bool operator<(const Event& other) const {
                return y < other.y;
            }
        };

        vector<Event> events;
        vector<long long> xs;

        for (auto &sq : squares) {
            long long x = sq[0], y = sq[1], l = sq[2];
            long long xl = x, xr = x + l;
            events.push_back({y, +1, xl, xr});
            events.push_back({y + l, -1, xl, xr});
            xs.push_back(xl);
            xs.push_back(xr);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(events.begin(), events.end());

        auto union_area = [&]() -> long double {
            SegTree st(xs);
            long double total = 0;
            long long prevY = events[0].y;

            for (auto &e : events) {
                long long width = st.coveredWidth();
                total += (long double)width * (e.y - prevY);
                st.addInterval(e.xl, e.xr, e.delta);
                prevY = e.y;
            }
            return total;
        };

        long double total = union_area();
        long double half = total / 2.0;

        // sweep again to find y
        SegTree st(xs);
        long double area = 0;
        long long prevY = events[0].y;

        for (auto &e : events) {
            long long width = st.coveredWidth();
            long long h = e.y - prevY;
            long double slabArea = (long double)width * h;

            if (width > 0 && area + slabArea >= half) {
                // inside this slab
                return (double)(prevY + (half - area) / width);
            }

            area += slabArea;
            st.addInterval(e.xl, e.xr, e.delta);
            prevY = e.y;
        }

        return (double)prevY; // fallback
    }
};
