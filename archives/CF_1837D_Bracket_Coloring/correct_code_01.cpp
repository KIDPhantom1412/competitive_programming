#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(2e5) + 5;

int n;
char S[N];
int balance[N], res[N];

void solve() {
    std::cin >> n >> S;
    // 移到下标 1 开始的位置，重叠内存必须使用 memmove。
    memmove(S + 1, S, n);
    // balance[0] 是全局数组的零初值，且始终不被修改。
    for (int i = 1; i <= n; i++) {
        if (S[i] == '(') {
            balance[i] = balance[i - 1] + 1;
        } else {
            balance[i] = balance[i - 1] - 1;
        }
    }

    // 每种颜色都必须左右括号等量，所以总平衡值非零时无解。
    if (balance[n]) {
        std::cout << -1 << '\n';
        return;
    }

    int c1 = 0, c2 = 0, k = 0;
    for (int i = 1; i <= n; i++) {
        // 正向段的末尾会回到 0，仍需根据前一个前缀和归入正向段。
        if (balance[i] > 0 || balance[i - 1] > 0) {
            if (!c1) {
                c1 = ++k;
            }
            res[i] = c1;
        } else {
            // 按首次出现顺序分配颜色，只有反向段时也输出颜色 1。
            if (!c2) {
                c2 = ++k;
            }
            res[i] = c2;
        }
    }
    std::cout << k << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
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
