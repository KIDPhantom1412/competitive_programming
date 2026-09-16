#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(2e5) + 5;

int n, m;
char S[N], T[N];
int sx[N], sy[N], su[N], sv[N]; // 四类列的前缀和：x=(0,1) y=(1,0) u=(0,0) v=(1,1)

void solve() {
    std::cin >> n >> m;
    std::cin >> S >> T;
    ::memmove(S + 1, S, n); // 转为 1 下标，方便做前缀和
    ::memmove(T + 1, T, n);
    ::memset(sx, 0, sizeof(int) * (n + 1)); // 多测清空
    ::memset(sy, 0, sizeof(int) * (n + 1));
    ::memset(su, 0, sizeof(int) * (n + 1));
    ::memset(sv, 0, sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        if (S[i] == '0' && T[i] == '0') {
            su[i] = 1;
        } else if (S[i] == '0' && T[i] == '1') {
            sx[i] = 1;
        } else if (S[i] == '1' && T[i] == '0') {
            sy[i] = 1;
        } else {
            sv[i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        sx[i] += sx[i - 1];
        sy[i] += sy[i - 1];
        su[i] += su[i - 1];
        sv[i] += sv[i - 1];
    }
    while (m--) {
        int l, r;
        std::cin >> l >> r;
        int x = sx[r] - sx[l - 1]; // 区间内 (0,1) 列数
        int y = sy[r] - sy[l - 1]; // 区间内 (1,0) 列数
        int u = su[r] - su[l - 1]; // 区间内 (0,0) 列数
        int v = sv[r] - sv[l - 1]; // 区间内 (1,1) 列数
        // 好的 <=> |x - y| <= u + v（混合列失衡度不超过纯列库存）
        if (std::abs(x - y) <= u + v) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
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
