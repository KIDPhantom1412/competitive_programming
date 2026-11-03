#include <iostream>
#include <queue>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    // 大根堆，按剩余可发言次数排序，first 是次数，second 是人的编号
    std::priority_queue<std::pair<int, int>> pq;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        if (A[i] > 0) {
            // 次数为 0 的人一开始就离场，不参与匹配
            pq.push({A[i], i});
        }
    }
    std::vector<std::pair<int, int>> res;
    // 每次取剩余次数最多的两人交谈一次，各自次数减一
    while (pq.size() >= 2) {
        auto [a, i] = pq.top();
        pq.pop();
        auto [b, j] = pq.top();
        pq.pop();
        res.push_back({i, j});
        if (a - 1 > 0) {
            pq.push({a - 1, i});
        }
        if (b - 1 > 0) {
            pq.push({b - 1, j});
        }
    }
    std::cout << res.size() << '\n';
    for (auto [a, b] : res) {
        std::cout << a << ' ' << b << '\n';
    }
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
