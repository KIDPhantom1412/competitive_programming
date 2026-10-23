#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int N = int(1e4) + 5;

// 31 以内的全部 11 个素数：合数 a_i <= 1000 的最小素因子必在其中
// （最小素因子 p >= 37 时 a_i >= p^2 >= 1369 > 1000，矛盾），无需筛素数
std::vector<int> prime{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1), color(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    int num = 0;
    // 从小到大枚举素数 p：把所有未染色且被 p 整除的元素染成同一种新颜色。
    // 每个元素恰在最小素因子处被染色，同色元素共享素因子 p，gcd >= p > 1；
    // 颜色按使用顺序从 1 连续编号，素数至多 11 个，故 m <= 11。
    for (int i = 0; i < int(prime.size()); i++) {
        int p = prime[i];
        bool usePrime = false;
        for (int j = 1; j <= n; j++) {
            if (color[j] == 0 && A[j] % p == 0) {
                color[j] = num + 1;
                usePrime = true;
            }
        }
        if (usePrime) {
            num++;
        }
    }
    std::cout << num << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << color[i] << ' ';
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
