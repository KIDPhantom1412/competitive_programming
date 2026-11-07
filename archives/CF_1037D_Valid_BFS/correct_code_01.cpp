#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    // 邻接表用哈希表存，方便 O(1) 判断两点是否相邻
    std::unordered_map<int, std::unordered_set<int>> G;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].insert(b);
        G[b].insert(a);
    }
    std::vector<int> A(n);
    for (int& a : A) {
        std::cin >> a;
    }
    std::vector<bool> st(n + 1); // st[v]：v 是否已被认领（已访问）
    std::queue<int> Q;
    if (A[0] != 1) { // BFS 必须从 1 号点出发
        std::cout << "NO" << '\n';
        return;
    }
    int idx = 1; // A[idx..] 是尚未被认领的后缀
    st[1] = true;
    Q.push(1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        // u 的儿子们必须在序列中连续出现，且每个都是 u 的邻居
        while (idx < n && !st[A[idx]] && G[u].count(A[idx])) {
            st[A[idx]] = true;
            Q.push(A[idx]);
            idx++;
        }
    }
    // 全部 n 个点都被成功认领才合法
    std::cout << (idx == n ? "YES" : "NO") << '\n';
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
