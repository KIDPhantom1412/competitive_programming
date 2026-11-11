#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

const int N = int(1e6) + 5;

std::unordered_set<int> primes;

void init() {
    static int prime[N], cnt;
    static bool st[N];
    for (int i = 2; i < N; i++) {
        if (!st[i]) {
            prime[cnt++] = i;
            primes.insert(i);
        }
        for (int j = 0; int64_t(prime[j]) * i < N; j++) {
            st[prime[j] * i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> res(n, std::vector<int>(m));
    for (int i = 0, cnt = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i][j] = ++cnt;
        }
    }

    // m 为素数时，同列相邻差是 m，不合法。
    // 第 i 行循环左移 i%m 位后，同列差只剩 1 或 m+1，都不是素数。
    if (primes.count(m)) {
        for (int i = 1; i < n; i++) {
            int delta = i % m;
            std::rotate(res[i].begin(), res[i].begin() + delta, res[i].end());
        }
    }

    for (const auto& row : res) {
        for (int ele : row) {
            std::cout << ele << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();

    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
