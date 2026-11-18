#include <algorithm>
#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    // idx[v]：数值 v 在 A 中出现的所有位置（递增有序）
    std::vector<std::vector<int>> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        idx[A[i]].push_back(i);
    }

    std::vector<int> res;
    for (int i = 1; i <= n; i++) {
        int j = i; // 当前段 [i, j] 的右端点，至少覆盖 a[i] 本身
        // 依次考察 0, 1, 2, ...，看它们在 i 之后的最早出现位置
        for (int k = 0; k <= n; k++) {
            auto it = std::lower_bound(idx[k].begin(), idx[k].end(), i);
            if (it == idx[k].end()) {
                // k 在剩余后缀 a[i..n] 中不存在 => 整个后缀的 MEX 就是 k
                // 段 [i, j] 已含 0..k-1，又不含 k，故本段 MEX = k
                res.push_back(k);
                break;
            }
            j = std::max(j, *it); // 段必须包含 k 的首次出现位置
        }
        i = j; // 配合循环的 ++i 跳过整段，从 j + 1 继续
    }

    std::cout << res.size() << '\n';
    for (int x : res) {
        std::cout << x << ' ';
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
