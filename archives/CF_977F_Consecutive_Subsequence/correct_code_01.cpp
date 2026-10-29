#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    // ht[v] 按位置递增记录「以 v 结尾、长度达到新最大值」的 (下标, 长度)
    // 由于 dp[v] 只增不减，同一 v 的长度序列单调不减
    std::unordered_map<int, std::vector<std::pair<int, int>>> ht;
    int maxLen = 0, maxVal = 0;
    for (int i = 1; i <= n; i++) {
        // 以 A[i] 结尾的最长连续上升子序列长度
        int len = ht.count(A[i] - 1) ? ht[A[i] - 1].back().second + 1 : 1;
        if (!ht.count(A[i]) || len > ht[A[i]].back().second) {
            ht[A[i]].push_back({i, len});
        }
        if (len > maxLen) {
            maxLen = len;
            maxVal = A[i];
        }
    }
    // 从最大值往回，对每个值二分出「长度 >= len」的最早下标
    std::vector<int> res;
    for (int len = maxLen, val = maxVal; len >= 1; len--, val--) {
        int l = 0, r = ht[val].size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (ht[val][mid].second >= len) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        res.push_back(ht[val][l].first);
    }
    std::cout << res.size() << '\n';
    // 找出的下标是倒序的，逆序输出即为原数组中的先后顺序
    for (auto it = res.rbegin(); it != res.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}
