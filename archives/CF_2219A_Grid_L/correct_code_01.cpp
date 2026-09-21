#include <cmath>
#include <cstdlib>
#include <iostream>

void solve() {
    int p, q;
    std::cin >> p >> q;
    // 假定 m >= n 时 p+2q >= 2n(n+1) => n <= sqrt(p/2+q)
    for (int n = std::sqrt(p / 2 + q); n >= 1; n--) {
        // p+2q = (2n+1)m + n  =>  m = (p+2q-n)/(2n+1)
        if ((p + q * 2 - n) % (n * 2 + 1) == 0) {
            int m = (p + q * 2 - n) / (n * 2 + 1);
            if (m >= 1 && std::abs(m - n) <= p) { // 横竖差必须由直线段承担
                std::cout << n << ' ' << m << '\n';
                return;
            }
        }
    }
    std::cout << -1 << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
