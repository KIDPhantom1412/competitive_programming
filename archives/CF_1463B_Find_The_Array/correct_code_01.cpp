#include <iostream>

using LL = long long;

const int N = 55;

int n;
int A[N];

void solve() {
    std::cin >> n;
    // 一侧的和最大约 2.5e10，必须用 long long。
    LL sumOfOdd = 0, sumOfEven = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        if (i % 2 == 0) {
            sumOfEven += A[i];
        } else {
            sumOfOdd += A[i];
        }
    }

    // 元素和较小的那一侧改成 1，1 整除任意正整数。
    for (int i = 1; i <= n; i++) {
        if (sumOfOdd <= sumOfEven) {
            std::cout << (i % 2 == 0 ? A[i] : 1) << ' ';
        } else {
            std::cout << (i % 2 == 0 ? 1 : A[i]) << ' ';
        }
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
