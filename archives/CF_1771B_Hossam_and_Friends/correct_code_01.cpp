#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using LL = long long;

const int N = int(2e5) + 5;

int n, m;

void solve() {
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> stranger;
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        if (x > y) {
            std::swap(x, y);
        }
        stranger.push_back({x, y});
    }
    // 按陌生人对的左端点排序，左端点相同时按右端点排序。
    std::sort(stranger.begin(), stranger.end());
    // 以当前分段中的位置为左端点，后面的陌生人对也会限制右端点。
    for (int i = m - 2; i >= 0; i--) {
        stranger[i].second = std::min(stranger[i].second, stranger[i + 1].second);
    }
    LL res = 0;
    int pre = 0;
    for (int i = 0; i < m; i++) {
        // 同一左端点的第一次出现已包含全部约束，不重复计数。
        if (i && stranger[i].first == stranger[i - 1].first) {
            continue;
        }

        int cur = stranger[i].first;
        // 左端点在 [pre + 1, cur] 内时共享右边界，先乘后除。
        res += LL(cur - pre) * (2LL * stranger[i].second - pre - 1 - cur) / 2;
        pre = cur;
    }
    // 左端点超过所有陌生人对的左端点后，剩余区间全部合法。
    res += LL(n - pre) * (n - pre + 1) / 2;
    std::cout << res << '\n';
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
