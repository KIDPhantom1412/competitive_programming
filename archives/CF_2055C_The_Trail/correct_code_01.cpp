#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// 公共和必须取 0：全体元素之和既等于 n*x 也等于 m*x，n 可以不等于 m。
// 沿路径每走一步就永久离开当前行或当前列，此时该行/列只剩当前格未定，
// 把它填成其余格子之和的相反数。终点用最后一行确定，最后一列随之为 0。
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::string op;
    std::cin >> op;
    std::vector<std::vector<int64_t>> A(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            std::cin >> a;
            A[i].push_back(a);
        }
    }
    int x = 0, y = 0;
    for (char c : op) {
        if (c == 'R') {
            // 向右离开第 y 列，这一列不会再经过
            int64_t sum = 0;
            for (int i = 0; i < n; i++) {
                sum += A[i][y];
            }
            A[x][y] = -sum;
            y++;
        } else {
            // 向下离开第 x 行，这一行不会再经过
            int64_t sum = 0;
            for (int j = 0; j < m; j++) {
                sum += A[x][j];
            }
            A[x][y] = -sum;
            x++;
        }
    }
    // 当前格仍是 0，reduce 得到的就是最后一行其余格子之和
    A[n - 1][m - 1] = -std::reduce(A.back().begin(), A.back().end());
    for (auto& row : A) {
        for (auto& ele : row) {
            std::cout << ele << ' ';
        }
        std::cout << '\n';
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
