#include <cstring>
#include <iostream>

const int MOD = int(1e8);

int n1, n2, k1, k2;
// memo[a][b][t]：还剩 a 个步兵、b 个骑兵，
// 且最后放置的一整块是 t 兵种（0 步兵 / 1 骑兵）的方案数。
// 一整块的内部全是同兵种，长度由枚举的 l 保证不超过 k，故无需记录连续长度。
int memo[110][110][2];

void add(int& a, int b) {
    a = (a + b) % MOD;
}

int dfs(int a, int b, int t) {
    if (a == 0 && b == 0) {
        return 1;
    }
    int& m = memo[a][b][t];
    if (m != -1) {
        return m;
    }

    int res = 0;
    if (t == 0) { // 最后一块是步兵，长度 l，它前面必然是骑兵块
        for (int l = 1; l <= k1 && l <= a; l++) {
            add(res, dfs(a - l, b, 1));
        }
    } else { // 最后一块是骑兵，长度 l，它前面必然是步兵块
        for (int l = 1; l <= k2 && l <= b; l++) {
            add(res, dfs(a, b - l, 0));
        }
    }

    return m = res;
}

void solve() {
    std::cin >> n1 >> n2 >> k1 >> k2;
    memset(memo, -1, sizeof(memo));
    // 末尾块的兵种两种都算上，二者互斥、不重不漏
    std::cout << (dfs(n1, n2, 0) + dfs(n1, n2, 1)) % MOD << '\n';
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
