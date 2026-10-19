#include <iostream>
#include <queue>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    struct Node {
        int len; // 全零区间长度
        int l;   // 全零区间左端点
        // 大根堆排序：长度长的优先，等长时左端点小的优先。
        bool operator<(const Node& ct) const {
            if (len != ct.len) {
                return len < ct.len;
            }
            return l >= ct.l;
        }
    };
    std::priority_queue<Node> pq;
    pq.push({n, 1});
    int idx = 0;
    while (!pq.empty()) {
        auto [len, l] = pq.top();
        pq.pop();
        // 题面两种情况统一为中点下取整：奇数长取 (l+r)/2，偶数长取 (l+r-1)/2。
        int mid = l + (len - 1) / 2, r = l + len - 1;
        A[mid] = ++idx;
        // 分裂出左右子区间，非空才入堆。
        if (mid - l > 0) {
            pq.push({mid - l, l});
        }
        if (r - mid > 0) {
            pq.push({r - mid, mid + 1});
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
