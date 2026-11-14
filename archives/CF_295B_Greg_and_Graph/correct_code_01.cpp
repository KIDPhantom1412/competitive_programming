#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    // 初值就是邻接矩阵。没有中转点时，最短路等于直边。
    std::vector<std::vector<int>> dist(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> dist[i][j];
        }
    }
    std::vector<int> X(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> X[i];
    }

    std::vector<int64_t> res(n + 1);
    std::vector<int> alive(n + 1, 0);
    // 逆序加点。加入 X[k] 后，活着的点恰好是删除 X[k] 之前剩下的点。
    for (int k = n; k >= 1; k--) {
        int v = X[k];
        alive[v] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 端点也可以还没加入。这样后加入的点能用上更早的中转点。
                // a[v][v] = 0，所以这一轮 dist[i][v] 和 dist[v][j] 不会变，原地更新是安全的。
                dist[i][j] = std::min(dist[i][j], dist[i][v] + dist[v][j]);
                // 每个点对本轮只经过一次，松弛后立刻累加，等价于整轮结束再求和。
                if (alive[i] && alive[j]) {
                    res[k] += dist[i][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << ' ';
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
