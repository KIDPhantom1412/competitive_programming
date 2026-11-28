#include <iostream>
#include <vector>

void solve() {
    int n, K;
    std::cin >> n >> K;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    // 每个值最多保留 K 个出现位置（同一颜色中每个值只能用一次）
    std::vector<std::vector<int>> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        if (int(pos[A[i]].size()) < K) {
            pos[A[i]].push_back(i);
        }
    }
    // 按值分组拉平：同一值的出现位置连续，且组内长度 <= K
    std::vector<int> seq;
    seq.reserve(n);
    for (int v = 1; v <= n; v++) {
        seq.insert(seq.end(), pos[v].begin(), pos[v].end());
    }
    // 每种颜色染 m 个，共 m*K 个，取序列前 m*K 个循环染色
    int m = int(seq.size()) / K;
    std::vector<int> C(n + 1);
    for (int j = 0; j < m * K; j++) {
        C[seq[j]] = j % K + 1;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << C[i] << ' ';
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
