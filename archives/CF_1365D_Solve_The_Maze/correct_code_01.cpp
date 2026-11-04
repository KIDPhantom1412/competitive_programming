#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++) {
        std::cin >> grid[i];
    }

    int cntG = 0; // 尚未被出口 BFS 访问到的好人数
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cntG += grid[i][j] == 'G';
            if (grid[i][j] == 'B') {
                // 坏人四邻必须封堵；若四邻有好人则坏人必被好人"护送"到出口，无解
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        if (grid[x][y] == 'G') {
                            std::cout << "NO" << '\n';
                            return;
                        } else if (grid[x][y] == '.') {
                            grid[x][y] = '#';
                        }
                    }
                }
            }
        }
    }

    // 从出口反向 BFS，检查可达性
    std::vector<std::vector<bool>> st(n, std::vector<bool>(m));
    std::queue<std::pair<int, int>> Q;
    auto visit = [&](int x, int y) -> bool {
        if (grid[x][y] == 'G') {
            cntG--; // 该好人可以逃出
        } else if (grid[x][y] == 'B') {
            // 坏人能走到出口，封堵失败
            std::cout << "NO" << '\n';
            return false;
        }
        st[x][y] = true;
        return true;
    };
    if (grid[n - 1][m - 1] != '#') { // 出口本身被封堵时直接不可达
        if (!visit(n - 1, m - 1)) {
            return;
        }
        Q.push({n - 1, m - 1});
    }
    while (!Q.empty()) {
        auto [px, py] = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int x = px + dx[i], y = py + dy[i];
            if (x >= 0 && x < n && y >= 0 && y < m && !st[x][y] && grid[x][y] != '#') {
                if (!visit(x, y)) {
                    return;
                }
                Q.push({x, y});
            }
        }
    }

    std::cout << (cntG ? "NO" : "YES") << '\n';
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
