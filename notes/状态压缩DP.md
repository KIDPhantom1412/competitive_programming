# 状态压缩DP

状态压缩 DP 又称“子集上的 DP”。当问题规模较小（通常 $n \le 20\sim 25$）但直接枚举所有子集/排列/状态不可行时，把状态编码成一个整数（常用二进制），通过 DP 逐位/逐格/逐步转移求解。

常见压缩对象：

1. **排列压缩**：状态表示哪些元素已被使用，关注顺序；
2. **组合压缩**：状态表示哪些元素被选中，不关注顺序；
3. **轮廓线压缩**：状态表示网格上一条分界线的局部信息；
4. **特殊结构压缩**：根据题目自定义状态对象。

## 排列压缩

> 状态表示一个排列或顺序，通常用二进制位记录哪些元素已经被访问/使用。转移时枚举下一个加入排列的元素，因此状态关注“已用集合”以及“当前终点”等信息。典型问题：TSP、Hamilton 路径、按顺序构造序列等。

### 最短Hamilton路径

题目：https://www.acwing.com/problem/content/description/93/

题解：《算法竞赛》p341

```c++
#include <algorithm>
#include <iostream>

const int N = 20, INF = int(1e8);

int n;
int G[N][N];
int f[1 << N][N];

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> G[i][j];
        }
    }
    std::fill_n((int*) f, (1 << N) * N, INF);
    f[1][0] = 0;
    for (int i = 2; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                int s = i ^ (1 << j);
                for (int k = 0; k < n; k++) {
                    if (s >> k & 1) {
                        f[i][j] = std::min(f[i][j], f[s][k] + G[k][j]);
                    }
                }
            }
        }
    }
    std::cout << f[(1 << n) - 1][n - 1] << '\n';
    return 0;
}
```

### Travelling

三进制状态压缩。

题目：https://vjudge.net/problem/HDU-3001

题解：《算法竞赛》p349

```c++
#include <algorithm>
#include <iostream>

const int N = 15, M = int(6e4), INF = int(1e9);

int n, m;
int G[N][N];
int bit[N];
int f[N][M];

void init() {
    std::fill_n((int*) G, N * N, INF);
    std::fill_n((int*) f, N * M, INF);
    for (int i = 1; i <= n; i++) {
        f[i][bit[i - 1]] = 0;
    }
}

void solve() {
    init();
    for (int i = 0; i < m; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        G[a][b] = G[b][a] = std::min(G[a][b], w);
    }
    int res = INF;
    for (int i = 0; i < bit[n]; i++) {
        bool isLegal = true;
        for (int j = 1; j <= n; j++) {
            if (i / bit[j - 1] % 3) {
                int s = i - bit[j - 1];
                for (int k = 1; k <= n; k++) {
                    if (s / bit[k - 1] % 3) {
                        f[j][i] = std::min(f[j][i], f[k][s] + G[k][j]);
                    }
                }
            } else {
                isLegal = false;
            }
        }
        if (isLegal) {
            for (int j = 1; j <= n; j++) {
                res = std::min(f[j][i], res);
            }
        }
    }
    if (res == INF) {
        res = -1;
    }
    std::cout << res << '\n';
}

int main() {
    bit[0] = 1;
    for (int i = 1; i < N; i++) {
        bit[i] = bit[i - 1] * 3;
    }
    while (std::cin >> n >> m) {
        solve();
    }
    return 0;
}
```

### 吃奶酪

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P1433

```c++
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

const int N = 16;
const double INF = 1e8;

int n;
struct Point {
    double x, y;
} P[N];
double f[1 << N][N];

double dist(int a, int b) {
    double dx = P[a].x - P[b].x;
    double dy = P[a].y - P[b].y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    std::cin >> n;
    n++;
    for (int i = 1; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        P[i] = {x, y};
    }
    std::fill_n((double*) f, (1 << N) * N, INF);
    f[1][0] = 0;
    for (int i = 2; i < (1 << n); i++) {
        for (int j = 0; j <= n; j++) {
            if (i >> j & 1) {
                int s = i ^ (1 << j);
                for (int k = 0; k <= n; k++) {
                    if (s >> k & 1) {
                        f[i][j] = std::min(f[i][j], f[s][k] + dist(k, j));
                    }
                }
            }
        }
    }
    double res = *std::min_element(f[(1 << n) - 1], f[(1 << n) - 1] + n);
    std::cout << std::fixed << std::setprecision(2) << res << '\n';
    return 0;
}
```

### No Change G

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3092

题解：https://www.luogu.com.cn/article/x2no534w

```c++
#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5, M = 16, INF = int(1e9) + 10;

int n, m;
int coin[M], cost[N];
int R[M][N];
int f[1 << M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> m >> n;
    for (int i = 0; i < m; i++) {
        std::cin >> coin[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> cost[i];
    }
    for (int i = 0; i < m; i++) {
        int sum = 0, r = -1;
        for (int l = 0; l < n; l++) {
            r = std::max(r, l - 1);
            while (r + 1 < n && sum + cost[r + 1] <= coin[i]) {
                r++;
                sum += cost[r];
            }
            R[i][l] = r; // r < l意味着coin[i]连cost[l]也买不了
            if (sum) {
                sum -= cost[l];
            }
        }
    }
    int res = -1;
    std::fill_n(f, 1 << m, -1);
    for (int i = 1; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                int k = i ^ (1 << j);
                if (f[k] == n - 1) {
                    f[i] = n - 1;
                    break;
                } else {
                    f[i] = std::max(f[i], R[j][f[k] + 1]);
                    if (f[i] == n - 1) {
                        int sum = 0;
                        for (int s = 0; s < m; s++) {
                            if (!(i >> s & 1)) {
                                sum += coin[s];
                            }
                        }
                        res = std::max(res, sum);
                        break;
                    }
                }
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

### 邦邦的大合唱站队

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3694

题解：https://www.luogu.com.cn/article/je7yfpog

```c++
#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5, M = 20;

int n, m;
int cnt[M], sum[N][M];
int L[1 << M], f[1 << M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        std::cin >> a;
        a--;
        std::copy(sum[i - 1], sum[i - 1] + m, sum[i]);
        cnt[a]++, sum[i][a]++;
    }
    for (int i = 0; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                L[i] += cnt[j];
            }
        }
    }
    std::fill_n(f, 1 << m, N);
    f[0] = 0;
    for (int i = 1; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                int k = i ^ (1 << j);
                int l = L[k];
                int r = l + cnt[j];
                f[i] = std::min(f[i], f[k] + cnt[j] - (sum[r][j] - sum[l][j]));
            }
        }
    }
    std::cout << f[(1 << m) - 1] << '\n';
    return 0;
}
```

### Scarlet的字符串不可能这么可爱

本题和状态压缩DP没有什么关系，主要是考察回文串的性质。

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4925

题解：https://www.luogu.com.cn/article/cg5vccjy

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

LL fp(LL a, LL b, LL p) {
    LL res = 1;
    a %= p;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    LL k, l, p, s, w;
    std::cin >> k >> l >> p >> s >> w;
    LL res = 1;
    if (!s) {
        if (l <= 2) {
            for (int i = 0; i < l; i++) {
                res = res * ((k - i) % p) % p;
            }
        } else {
            for (int i = 0; i < 2; i++) {
                res = res * ((k - i) % p) % p;
            }
            res = res * fp(k - 2, l - 2, p) % p;
        }
    } else {
        if (l > 1) { // k = 1让它完蛋
            res = res * ((k - 1) % p) % p;
        }
        if (k >= 2 && l > 2) { // k = 2也让它完蛋
            res = res * fp(k - 2, l - 2, p) % p;
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

### 学校食堂

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2157

题解：https://www.luogu.com.cn/article/4vif0c44

```c++
#include <algorithm>
#include <iostream>

const int N = 1010, M = 8, K = 16, INF = int(1e8);

int n, m;
int B[N], T[N];
int f[N][1 << M][K];

void solve() {
    std::fill_n(B, N, 0);
    std::fill_n(T, N, 0);
    std::fill_n((int*) f, sizeof(f) / sizeof(int), INF);
    std::cin >> n;
    m = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> T[i] >> B[i];
        m = std::max(m, B[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << (m + 1)); j++) {
            for (int k = std::max(-(m + 1), -i); k <= m; k++) {
                if (i + k == 0 && (j != 0 || i != 1)) { // 非法状态
                    continue;
                }
                if (j & 1 && k + m >= 0) {
                    f[i + 1][j >> 1][k + m] = std::min(f[i + 1][j >> 1][k + m], f[i][j][k + m + 1]);
                } else if (!(j & 1)) {
                    int r = INF;
                    for (int s = 0; s < m + 1; s++) {
                        if (!(j >> s & 1) && i + s <= n) {
                            if (i + s > r) {
                                break;
                            }
                            r = std::min(r, i + s + B[i + s]);
                            int t = j ^ (1 << s);
                            if (i + k == 0) { // 没有上一个人，那么当前枚举的s就是第一个吃饭的人
                                f[i][t][s + m + 1] = 0;
                            } else {
                                f[i][t][s + m + 1] = std::min(
                                    f[i][t][s + m + 1], f[i][j][k + m + 1] + (T[i + k] ^ T[i + s]));
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << *std::min_element(f[n][1], f[n][1] + m + 2) << '\n';
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
```

### yyy loves Maths VII

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2396

题解：https://www.luogu.com.cn/article/uuzhr9rf

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 24, P = int(1e9) + 7;

int n, m;
LL dist[1 << N];
int b0, b1;
int f[1 << N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> dist[1 << i];
    }
    std::cin >> m;
    if (m > 0) {
        std::cin >> b0;
    }
    if (m > 1) {
        std::cin >> b1;
    }
    f[0] = 1;
    for (int i = 1; i < (1 << n); i++) {
        int x = i;
        for (int j = x & -x; j; x ^= j, j = x & -x) {
            int k = i ^ j;
            dist[i] = dist[k] + dist[j];
            if (dist[i] == b0 || dist[i] == b1) {
                f[i] = 0;
            } else {
                f[i] = (f[i] + f[k]) % P;
            }
        }
    }
    std::cout << f[(1 << n) - 1] << '\n';
    return 0;
}
```

## 组合压缩

> 状态表示一个集合，只关心哪些元素被选中，不关心它们的顺序。通常用于集合覆盖、选择方案计数/最优化等问题。与排列压缩不同，组合压缩不记录元素先后关系，转移时只考虑“选或不选”每个元素。
>
> 常用技巧：最低位递推优化（lowbit 枚举）。由于状态不依赖顺序，有时可以通过只扩展最低位的 0 来减少重复枚举，或预处理所有合法转移集合。

### 愤怒的小鸟

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2831

题解：https://www.luogu.com.cn/article/oc8h61kt

```c++
#include <algorithm>
#include <iostream>

const int N = 18, M = 18 * 17 / 2 + N + 5;
const double eps = 1e-8;

int n, m;
struct Point {
    double x, y;
} P[N];

int path[M], cnt;

bool getPath(const Point& p1, const Point& p2, double& a, double& b) {
    if (std::abs(p1.x - p2.x) < eps) {
        return false;
    }
    a = (p1.y / p1.x - p2.y / p2.x) / (p1.x - p2.x);
    b = p1.y / p1.x - a * p1.x;
    return a < -eps;
}

int f[1 << N];

void solve() {
    cnt = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> P[i].x >> P[i].y;
    }
    for (int i = 0; i < n; i++) {
        path[cnt++] = 1 << i; // 只打一只猪
        for (int j = 0; j < i; j++) {
            int s = (1 << i) | (1 << j);
            bool exists = false;
            for (int k = 0; k < cnt; k++) {
                if ((s & path[k]) == s) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                continue;
            }
            double a, b;
            if (!getPath(P[i], P[j], a, b)) {
                continue;
            }
            for (int k = 0; k < n; k++) {
                auto [x, y] = P[k];
                if (std::abs(a * x * x + b * x - y) < eps) {
                    s |= 1 << k;
                }
            }
            path[cnt++] = s; // 至少打两只猪
        }
    }
    std::fill_n(f, 1 << n, M);
    f[0] = 0;
    for (int i = 0; i < (1 << n) - 1; i++) {
        for (int j = 0; j < cnt; j++) {
            int k = i | path[j];
            if (k != i) {
                f[k] = std::min(f[k], f[i] + 1);
            }
        }
    }
    std::cout << f[(1 << n) - 1] << '\n';
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
```

**最低位递推优化**

题解：https://www.luogu.com.cn/article/3qr2i0cr

```c++
#include <algorithm>
#include <iostream>

const int N = 18;
const double eps = 1e-8;

int n, m;
struct Point {
    double x, y;
} P[N];

int path[N][N];

int cmp(double a, double b) {
    if (std::abs(a - b) < eps) {
        return 0;
    }
    return a > b ? 1 : -1;
}

bool getPath(double& a, double& b, const Point& p1, const Point& p2) {
    if (!cmp(p1.x, p2.x)) {
        return false;
    }
    a = (p1.y / p1.x - p2.y / p2.x) / (p1.x - p2.x);
    b = p1.y / p1.x - a * p1.x;
    return a < -eps;
}

int lowbit(int x) {
    return x & -x;
}

int f[1 << N];

void solve() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> P[i].x >> P[i].y;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double a, b;
            if (getPath(a, b, P[i], P[j])) {
                path[i][j] = (1 << i) | (1 << j);
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) {
                        auto [x, y] = P[k];
                        if (std::abs(a * x * x + b * x - y) < eps) {
                            path[i][j] |= 1 << k;
                        }
                    }
                }
                path[j][i] = path[i][j];
            } else {
                path[i][j] = path[j][i] = 0;
            }
        }
    }
    std::fill_n(f, 1 << N, N * N);
    f[0] = 0;
    for (int i = 0; i < (1 << n) - 1; i++) {
        int s = lowbit(~i), k = 0;
        for (int j = 0; j < n; j++) {
            if (s >> j & 1) {
                k = j;
                break;
            }
        }
        for (int j = 0; j < n; j++) {
            f[path[k][j] | i] = std::min(f[path[k][j] | i], f[i] + 1);
        }
    }
    std::cout << f[(1 << n) - 1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (int i = 0; i < N; i++) {
        path[i][i] = 1 << i;
    }
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```



## 轮廓线压缩

> 在二维网格上按行或按格递推时，用一串二进制位表示当前处理位置的“轮廓”状态。轮廓线通常记录已处理区域与未处理区域交界处的信息，例如哪些格子已被覆盖、插头连接情况等。
>
> 常见实现方式：
> 1. 行递推：以整行为单位转移，状态长度等于列数，适用于棋盘行内约束简单的问题（如炮兵阵地、Corn Fields）。
> 2. 格递推 / 插头 DP：以单个格子为单位转移，状态更细，能处理格子间复杂连接关系（如铺砖、回路计数、神奇游乐园）。

### 行递推轮廓线DP

> 状态表示整行的选择方案，通常用 $m$ 位二进制表示每一列是否被选中/覆盖。转移时只考虑当前行与上一行（或上几行）的状态兼容性，状态数为 $2^m$。适用于每行内部选择独立、行与行之间只有相邻约束的问题。
>
> 行递推的“行”也可以是列：当一行有 $n$ 个元素时状态数会达到 $2^n$，通常选择较短的一边作为递推方向，以降低状态规模。

#### 郑厂长系列故事――排兵布阵

题目：https://vjudge.net/problem/HDU-4539

题解：《算法竞赛》p347

```c++
#include <algorithm>
#include <iostream>

const int N = 110;
const int M = 200; // 一行的合法状态数的最大值

int n, m;
int grid[N][M];
int st[M], cnt;
int f[2][M][M];

void init() {
    cnt = 0;
    for (int i = 0; i < (1 << m); i++) {
        if (!(i & (i >> 2))) {
            st[cnt++] = i;
        }
    }
    std::fill_n((int*) f, 2 * M * M, 0);
    std::fill_n((int*) grid, N * M, 0);
}

int countLine(int line, int s) {
    int res = 0;
    for (int i = 0; i < m; i++) {
        if (s >> i & 1) {
            res += grid[line][i];
        }
    }
    return res;
}

void solve() {
    init();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> grid[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        std::fill_n((int*) f[i & 1], M * M, 0);
        for (int j = 0; j < cnt; j++) {
            if (!i) {
                f[0][j][0] = std::max(f[0][j][0], countLine(0, st[j]));
                res = std::max(res, f[0][j][0]);
            } else {
                for (int k = 0; k < cnt; k++) {
                    int& cur = f[i & 1][j][k];
                    if (!(st[j] & (st[k] >> 1)) && !(st[k] & (st[j] >> 1))) {
                        for (int s = 0; s < cnt; s++) {
                            if (!(st[s] & (st[k] >> 1)) && !(st[k] & (st[s] >> 1)) &&
                                !(st[s] & st[j])) {
                                cur = std::max(cur, f[i - 1 & 1][k][s]);
                            }
                        }
                        cur += countLine(i, st[j]);
                    }
                    res = std::max(res, cur);
                }
            }
        }
    }
    std::cout << res << '\n';
}

int main() {
    while (std::cin >> n >> m) {
        solve();
    }
    return 0;
}
```

#### 炮兵阵地

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2704

```c++
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 110, M = 10;

int n, m;
int grid[N];
int f[2][N][N];
int st[N], cnt;

void init() {
    for (int i = 0; i < (1 << m); i++) {
        if (!(i >> 1 & i) && !(i >> 2 & i)) {
            st[cnt++] = i;
        }
    }
}

int bitCnt(int s) {
    int res = 0;
    while (s) {
        s &= s - 1;
        res++;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    init();
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'P') {
                grid[i] |= 1 << j;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        std::fill_n((int*) f[i & 1], N * N, 0);
        for (int j = 0; j < cnt; j++) {
            if (!i) {
                f[0][j][0] = std::max(f[0][j][0], bitCnt(st[j] & grid[0]));
                res = std::max(res, f[0][j][0]);
            } else {
                for (int k = 0; k < cnt; k++) {
                    if (!(st[j] & st[k])) {
                        for (int s = 0; s < cnt; s++) {
                            if (!(st[s] & st[k]) && !(st[s] & st[j])) {
                                f[i & 1][j][k] = std::max(
                                    f[i & 1][j][k], f[i - 1 & 1][k][s] + bitCnt(st[j] & grid[i]));
                                res = std::max(res, f[i & 1][j][k]);
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

#### Corn Fields G（玉米田）

 题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P1879

```c++
#include <algorithm>
#include <iostream>
#include <numeric>

const int N = 12, MOD = int(1e8);

int n, m;
int grid[N];
int valid[N][1 << N], cnt[N];
int f[2][1 << N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            std::cin >> x;
            grid[i] |= x << j;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            if (!(j >> 1 & j) && (j & grid[i]) == j) {
                valid[i][cnt[i]++] = j;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        std::fill_n(f[i & 1], cnt[i], 0);
        for (int j = 0; j < cnt[i]; j++) {
            int cur = valid[i][j];
            if (!i) {
                f[0][j] = 1;
            } else {
                for (int k = 0; k < cnt[i - 1]; k++) {
                    int pre = valid[i - 1][k];
                    if (!(cur & pre)) {
                        f[i & 1][j] = (f[i & 1][j] + f[i - 1 & 1][k]) % MOD;
                    }
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < cnt[n - 1]; i++) {
        res = (res + f[n - 1 & 1][i]) % MOD;
    }
    std::cout << res << '\n';
    return 0;
}
```

#### 互不侵犯/小国王

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P1896

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 9;

int n, m;
LL f[N][1 << N][N * N + 1];
int st[1 << N], cnt;
int ones[1 << N];

int bitCnt(int x) {
    int res = 0;
    while (x) {
        x &= x - 1;
        res++;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < (1 << n); i++) {
        if (!(i >> 1 & i)) {
            st[cnt++] = i;
            ones[i] = bitCnt(i);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cnt; j++) {
            if (!i) {
                f[0][j][ones[st[j]]] = 1;
            } else {
                for (int k = 0; k < cnt; k++) {
                    if (!(st[k] & st[j]) && !(st[j] >> 1 & st[k]) && !(st[k] >> 1 & st[j])) {
                        for (int s = 0; s <= m; s++) {
                            int t = s - ones[st[j]];
                            if (t >= 0) {
                                f[i][j][s] += f[i - 1][k][t];
                            }
                        }
                    }
                }
            }
        }
    }
    LL res = 0;
    for (int i = 0; i < cnt; i++) {
        res += f[n - 1][i][m];
    }
    std::cout << res << '\n';
    return 0;
}
```

#### 中国象棋 - 摆上马

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P5005

```c++
#include <algorithm>
#include <iostream>

const int N = 100, M = 6, P = int(1e9) + 7;

int n, m;
int f[2][1 << M][1 << M];

bool checkNeighbor(int j, int k) {
    return !(((((k << 1) & k) ^ k) >> 2) & j) && !(((((k >> 1) & k) ^ k) << 2) & j) &&
           !(((((j << 1) & j) ^ j) >> 2) & k) && !(((((j >> 1) & j) ^ j) << 2) & k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::fill_n((int*) f[i & 1], sizeof(f[0]) / sizeof(int), 0);
        for (int j = 0; j < (1 << m); j++) {
            if (!i) {
                f[0][j][0] = 1;
                continue;
            }
            for (int k = 0; k < (1 << m); k++) {
                if (checkNeighbor(j, k)) {
                    for (int r = 0; r < (1 << m); r++) {
                        if (checkNeighbor(k, r)) {
                            int s = (j & k) ^ j;
                            int t = (r & k) ^ r;
                            if (!(t >> 1 & j) && !(j >> 1 & t) && !(s >> 1 & r) && !(r >> 1 & s)) {
                                f[i & 1][j][k] = (f[i & 1][j][k] + f[i - 1 & 1][k][r]) % P;
                            }
                        }
                    }
                }
            }
        }
    }
    int res = 0;
    for (int j = 0; j < (1 << m); j++) {
        for (int k = 0; k < (1 << m); k++) {
            res = (res + f[n - 1 & 1][j][k]) % P;
        }
    }
    std::cout << res << '\n';
    return 0;
}
```



### 格递推轮廓线DP

> 状态按单个格子推进，记录轮廓线上每个位置的插头状态或连接情况。状态通常比行递推更复杂，但表达能力更强，能处理格子间需要连接成路径、回路或特定形状的问题。典型技术：插头 DP（plug DP）。

#### Mondriaan's Dream（蒙德里安的梦想）

本题可以用格递推的方式来做，并且时间复杂度更低，不过做法更复杂。

题目：

https://www.acwing.com/problem/content/293/

https://vjudge.net/problem/OpenJ_Bailian-2411

**行递推**

题解：https://www.acwing.com/solution/content/15616/

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 12;

int n, m;
LL f[N][1 << N];
bool st[1 << N];

void solve() {
    if (n > m) {
        std::swap(n, m);
    }
    for (int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                if (cnt % 2) {
                    break;
                }
            } else {
                cnt++;
            }
        }
        st[i] = !(cnt % 2);
    }
    std::fill_n((LL*) f, (1 << N) * N, 0);
    f[0][0] = 1; // 0列是一个虚拟列
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = 0; k < (1 << n); k++) {
                if (!(j & k) && st[j | k]) {
                    f[i][j] += f[i - 1][k];
                }
            }
        }
    }
    std::cout << f[m][0] << '\n';
}

int main() {
    while (std::cin >> n >> m, n || m) {
        solve();
    }
    return 0;
}
```

**格递推**

题解：《算法竞赛》p344

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 12;

int n, m;
LL f[2][1 << N];

void solve() {
    if (m > n) {
        std::swap(m, n);
    }
    int cur = 0, nxt = 1;
    std::fill_n(f[cur], 1 << N, 0);
    f[cur][(1 << m) - 1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::fill_n(f[nxt], 1 << N, 0);
            for (int k = 0; k < (1 << m); k++) {
                if (k >> (m - 1) & 1) { // 情况1：不放
                    int s = (k << 1) ^ (1 << m);
                    f[nxt][s] += f[cur][k];
                    if (j > 1 && !(k & 1)) { // 情况3：横着放
                        f[nxt][s | 3] += f[cur][k];
                    }
                } else if (i > 1) { // 情况2：竖着放
                    f[nxt][(k << 1) | 1] += f[cur][k];
                }
            }
            std::swap(cur, nxt);
        }
    }
    std::cout << f[cur][(1 << m) - 1] << '\n';
}

int main() {
    while (std::cin >> n >> m, n || m) {
        solve();
    }
    return 0;
}
```



#### 一双木棋 chess

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4363

题解：https://www.luogu.com.cn/article/6mfih0gu

```c++
#include <algorithm>
#include <iostream>

const int N = 10, INF = int(1e8);

int n, m;
int A[N][N], B[N][N];
int f[1 << (N * 2)];

int dfs(int cur, bool isFei) {
    if (f[cur] != INF) {
        return f[cur];
    }
    f[cur] = isFei ? -INF : INF;
    int x = n, y = 0;
    for (int i = 0; i < n + m - 1; i++) {
        if (cur >> i & 1) {
            x--;
        } else {
            y++;
        }
        if ((cur >> i & 0b11) == 0b01) {
            int nxt = cur ^ (0b11 << i);
            if (isFei) {
                f[cur] = std::max(f[cur], dfs(nxt, !isFei) + A[x][y]);
            } else {
                f[cur] = std::min(f[cur], dfs(nxt, !isFei) - B[x][y]);
            }
        }
    }
    return f[cur];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> B[i][j];
        }
    }
    std::fill_n(f, sizeof(f) / sizeof(int), INF);
    f[((1 << n) - 1) << m] = 0;
    std::cout << dfs((1 << n) - 1, true) << '\n';
    return 0;
}
```

#### 插头DP

题目：

https://www.acwing.com/problem/content/description/2937/

https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P5056

题解：https://www.acwing.com/solution/content/167520/

图解：https://www.luogu.com.cn/article/rx5k5drf

```c++
#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 15, M = 100343;

int n, m;
int lastX, lastY;
char G[N][N];
int f[2][M], cnt[2]; // 存储哈希表的下标
int K[2][M];         // 哈希表
LL V[2][M];

void init(int t) {
    cnt[t] = 0;
    std::fill_n(K[t], sizeof(K[t]) / sizeof(int), -1);
}

int find(int t, int s) {
    int x = s % M;
    while (K[t][x] != -1 && K[t][x] != s) {
        x = (x + 1) % M;
    }
    return x;
}

void update(int t, int s, LL d) {
    int x = find(t, s);
    if (K[t][x] == -1) {
        f[t][cnt[t]++] = x;
        K[t][x] = s;
        V[t][x] = d;
    } else {
        V[t][x] += d;
    }
}

int get(int s, int i) {
    return s >> (i * 2) & 0b11;
}

int mask(int i, int x) {
    return x << (i * 2);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> G[i];
        for (int j = 0; j < m; j++) {
            G[i][j] = G[i][j] == '.';
            if (G[i][j]) {
                lastX = i, lastY = j;
            }
        }
    }
    LL res = 0;
    int pre = 0, cur = 1;
    init(cur);
    update(cur, 0, 1); // 初始状态
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cnt[cur]; j++) {
            K[cur][f[cur][j]] <<= 2;
        }
        for (int j = 0; j < m; j++) {
            std::swap(pre, cur);
            init(cur);
            for (int k = 0; k < cnt[pre]; k++) {
                int ps = K[pre][f[pre][k]];
                LL pv = V[pre][f[pre][k]];
                int px = get(ps, j), py = get(ps, j + 1);
                if (!G[i][j]) { // 虽然总体上是按照px和py分类，不过最开始得把不能走的先过滤掉
                    if (!px && !py) {
                        update(cur, ps, pv);
                    }
                } else if (!px && !py) {
                    if (G[i + 1][j] && G[i][j + 1]) {
                        update(cur, ps + mask(j, 1) + mask(j + 1, 2), pv);
                    }
                } else if (!px && py) {
                    if (G[i + 1][j]) {
                        update(cur, ps + mask(j, py) - mask(j + 1, py), pv);
                    }
                    if (G[i][j + 1]) {
                        update(cur, ps, pv);
                    }
                } else if (px && !py) {
                    if (G[i + 1][j]) {
                        update(cur, ps, pv);
                    }
                    if (G[i][j + 1]) {
                        update(cur, ps - mask(j, px) + mask(j + 1, px), pv);
                    }
                } else if (px == 1 && py == 1) {
                    int s = 1; // 找到从j+2开始的第一个右插头
                    for (int r = j + 2; r <= m; r++) {
                        int t = get(ps, r);
                        if (t == 1) {
                            s++;
                        } else if (t == 2) {
                            if (--s == 0) {
                                update(cur, ps - mask(j, 1) - mask(j + 1, 1) - mask(r, 1), pv);
                                break;
                            }
                        }
                    }
                } else if (px == 1 && py == 2) {
                    if (i == lastX && j == lastY) {
                        res += pv;
                    }
                } else if (px == 2 && py == 1) {
                    update(cur, ps ^ mask(j, 2) ^ mask(j + 1, 1), pv);
                } else { // px == 2 && py == 2
                    int s = 1;
                    for (int r = j - 1; r >= 0; r--) {
                        int t = get(ps, r);
                        if (t == 2) {
                            s++;
                        } else if (t == 1) {
                            if (--s == 0) {
                                update(cur, ps - mask(j, 2) - mask(j + 1, 2) + mask(r, 1), pv);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

#### 神奇游乐园

题目：https://www.acwing.com/problem/content/2146/

题解：https://www.acwing.com/solution/content/167712/

```c++
#include <algorithm>
#include <iostream>

const int N = 110, M = 10, P = 991, INF = int(1e8);

int n, m;
int G[N][M];
int f[2][P], cnt[2];
int K[2][P], V[2][P];

void init(int t) {
    cnt[t] = 0;
    std::fill_n(K[t], P, -1);
}

int find(int t, int s) {
    int x = s % P;
    while (K[t][x] != -1 && K[t][x] != s) {
        x = (x + 1) % P;
    }
    return x;
}

void update(int t, int s, int d) {
    int x = find(t, s);
    if (K[t][x] == -1) {
        f[t][cnt[t]++] = x;
        K[t][x] = s;
        V[t][x] = d;
    } else {
        V[t][x] = std::max(V[t][x], d);
    }
}

int get(int s, int i) {
    return s >> (i * 2) & 0b11;
}

int mask(int i, int x) {
    return x << (i * 2);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> G[i][j];
        }
    }
    int res = -INF;
    int pre = 1, cur = 0;
    init(cur);
    update(cur, 0, 0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < cnt[cur]; k++) {
            K[cur][f[cur][k]] <<= 2;
        }
        for (int j = 0; j < m; j++) {
            std::swap(pre, cur);
            init(cur);
            for (int k = 0; k < cnt[pre]; k++) {
                int ps = K[pre][f[pre][k]], pv = V[pre][f[pre][k]];
                int px = get(ps, j), py = get(ps, j + 1);
                if (!px && !py) {
                    update(cur, ps, pv);
                    if (i + 1 < n && j + 1 < m) {
                        update(cur, ps + mask(j, 1) + mask(j + 1, 2), pv + G[i][j]);
                    }
                } else if (px && !py) {
                    if (i + 1 < n) {
                        update(cur, ps, pv + G[i][j]);
                    }
                    if (j + 1 < m) {
                        update(cur, ps - mask(j, px) + mask(j + 1, px), pv + G[i][j]);
                    }
                } else if (!px && py) {
                    if (i + 1 < n) {
                        update(cur, ps + mask(j, py) - mask(j + 1, py), pv + G[i][j]);
                    }
                    if (j + 1 < m) {
                        update(cur, ps, pv + G[i][j]);
                    }
                } else if (px == 1 && py == 1) {
                    int s = 1;
                    for (int r = j + 2; r <= m; r++) {
                        int t = get(ps, r);
                        if (t == 1) {
                            s++;
                        } else if (t == 2) {
                            if (--s == 0) {
                                update(cur,
                                       ps - mask(j, 1) - mask(j + 1, 1) - mask(r, 1),
                                       pv + G[i][j]);
                                break;
                            }
                        }
                    }
                } else if (px == 1 && py == 2) {
                    if (ps - mask(j, 1) - mask(j + 1, 2) == 0) {
                        res = std::max(res, pv + G[i][j]);
                    }
                } else if (px == 2 && py == 1) {
                    update(cur, ps - mask(j, 2) - mask(j + 1, 1), pv + G[i][j]);
                } else { // px == 2 && py == 2
                    int s = 1;
                    for (int r = j - 1; r >= 0; r--) {
                        int t = get(ps, r);
                        if (t == 2) {
                            s++;
                        } else if (t == 1) {
                            if (--s == 0) {
                                update(cur,
                                       ps + mask(r, 1) - mask(j, 2) - mask(j + 1, 2),
                                       pv + G[i][j]);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

#### 地板

题目：https://www.acwing.com/problem/content/description/2646/

题解：https://www.acwing.com/solution/content/167819/

```c++
#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 110, S = 180010, M = 10, P = S * 4 + 7, MOD = 20110520;

int n, m;
bool G[N][N];
int f[2][S], cnt[2];
int K[2][P], V[2][P];

void init(int t) {
    cnt[t] = 0;
    std::fill_n(K[t], P, -1);
}

int find(int t, int s) {
    int x = s % P;
    while (K[t][x] != -1 && K[t][x] != s) {
        x = (x + 1) % P;
    }
    return x;
}

void update(int t, int s, int d) {
    int x = find(t, s);
    if (K[t][x] == -1) {
        K[t][x] = s;
        V[t][x] = d;
        f[t][cnt[t]++] = x;
    } else {
        V[t][x] = (V[t][x] + d) % MOD;
    }
}

int get(int s, int i) {
    return s >> (i * 2) & 0b11;
}

int mask(int i, int x) {
    return x << (i * 2);
}

void transpose() {
    static bool tmp[N][N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tmp[j][i] = G[i][j];
        }
    }
    std::swap(n, m);
    memcpy(G, tmp, sizeof(G));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            G[i][j] = s[j] == '_';
        }
    }
    if (m > M) {
        transpose();
    }
    int pre = 0, cur = 1;
    init(cur);
    update(cur, 0, 1);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < cnt[cur]; k++) {
            K[cur][f[cur][k]] <<= 2;
        }
        for (int j = 0; j < m; j++) {
            std::swap(pre, cur);
            init(cur);
            for (int k = 0; k < cnt[pre]; k++) {
                int ps = K[pre][f[pre][k]], pv = V[pre][f[pre][k]];
                int px = get(ps, j), py = get(ps, j + 1);
                if (!G[i][j]) {
                    if (!px && !py) {
                        update(cur, ps, pv);
                    }
                } else if (!px && !py) {
                    if (G[i + 1][j]) {
                        update(cur, ps + mask(j, 1), pv);
                    }
                    if (G[i][j + 1]) {
                        update(cur, ps + mask(j + 1, 1), pv);
                    }
                    if (G[i + 1][j] && G[i][j + 1]) {
                        update(cur, ps + mask(j, 2) + mask(j + 1, 2), pv);
                    }
                } else if (px && !py) {
                    if (px == 2) {
                        update(cur, ps - mask(j, 2), pv);
                    }
                    if (G[i + 1][j] && px == 1) {
                        update(cur, ps + mask(j, 1), pv);
                    }
                    if (G[i][j + 1]) {
                        update(cur, ps - mask(j, px) + mask(j + 1, px), pv);
                    }
                } else if (!px && py) {
                    if (py == 2) {
                        update(cur, ps - mask(j + 1, 2), pv);
                    }
                    if (G[i + 1][j]) {
                        update(cur, ps + mask(j, py) - mask(j + 1, py), pv);
                    }
                    if (G[i][j + 1] && py == 1) {
                        update(cur, ps + mask(j + 1, 1), pv);
                    }
                } else if (px == 1 && py == 1) {
                    update(cur, ps - mask(j, 1) - mask(j + 1, 1), pv);
                }
            }
        }
    }
    int res = 0;
    int x = find(cur, 0);
    if (K[cur][x] != -1) {
        res = V[cur][x];
    }
    std::cout << res << '\n';
    return 0;
}
```



## 特殊结构压缩

> 状态压缩对象不是经典子集、排列或轮廓线，而是根据题目自定义的特殊结构。例如字符串前缀匹配、互质整数集合等。这类问题需要根据具体性质设计状态编码方式。

### 字符串前缀匹配压缩

> 用二进制状态表示多个字符串在当前位置上的匹配情况。每一位对应一个字符串，转移时根据当前字符更新哪些字符串仍然匹配前缀。常用于多模式串匹配计数问题。

#### Bill的挑战

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2167

题解：https://www.luogu.com.cn/article/8h5hoyd6

```c++
#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 15, M = 55, P = 1000003;

int n, m;
char S[N][M];
int len;
int f[M][1 << N];
int g[M][30];
int bitCnt[1 << N];

int init = []() -> int {
    for (int i = 0; i < (1 << N); i++) {
        int x = i, cnt = 0;
        while (x) {
            x &= x - 1;
            cnt++;
        }
        bitCnt[i] = cnt;
    }
    return 0;
}();

void solve() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> S[i];
    }
    len = strlen(S[0]);
    std::fill_n((int*) g, sizeof(g) / sizeof(int), 0);
    for (int i = 0; i < len; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            for (int j = 0; j < n; j++) {
                if (S[j][i] == '?' || S[j][i] == c) {
                    g[i][c - 'a'] |= 1 << j;
                }
            }
        }
    }
    std::fill_n((int*) f, sizeof(f) / sizeof(int), 0);
    for (char c = 'a'; c <= 'z'; c++) {
        f[0][g[0][c - 'a']]++;
    }
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (char c = 'a'; c <= 'z'; c++) {
                int& cur = f[i + 1][j & g[i + 1][c - 'a']];
                cur = (cur + f[i][j]) % P;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (bitCnt[i] == m) {
            res = (res + f[len - 1][i]) % P;
        }
    }
    std::cout << res << '\n';
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
```

### 互质整数集合压缩

> 把每个整数的质因数集合编码成二进制状态。转移时保证所选数的质因数状态不冲突（即无公共质因数），从而实现互质集合的构造与计数。

#### 寿司晚宴

题目：https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2150

题解：https://www.luogu.com.cn/article/557g5r99

```c++
#include <algorithm>
#include <iostream>

const int N = 510, M = 1 << 8;
const int prime[8] = {2, 3, 5, 7, 11, 13, 17, 19};

int n, p;
int f[M][M], f1[M][M], f2[M][M];
struct Node {
    int mx, st; // 最大质因数、质因数状态
    bool operator<(const Node& ct) const {
        return mx < ct.mx;
    }
} E[N];

int mod(int a, int p) {
    return (a % p + p) % p;
}

void update() {
    for (int j = M - 1; j >= 0; j--) {
        for (int k = j ^ (M - 1); k >= 0; k--) {
            if (!(j & k)) {
                f1[j][k] = f2[j][k] = f[j][k] = mod((f1[j][k] + f2[j][k]) % p - f[j][k], p);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> p;
    for (int i = 2; i <= n; i++) {
        int x = i, s = 0;
        for (int j = 0; j < 8; j++) {
            if (x % prime[j] == 0) {
                while (x % prime[j] == 0) {
                    x /= prime[j];
                }
                s |= 1 << j;
            }
        }
        E[i] = {x, s};
    }
    std::sort(E + 2, E + n + 1);
    f1[0][0] = 1 % p;
    for (int i = 2; i <= n; i++) {
        if (E[i].mx == 1 || E[i].mx != E[i - 1].mx) {
            update();
        }
        int s = E[i].st;
        for (int j = M - 1; j >= 0; j--) {
            for (int k = j ^ (M - 1); k >= 0; k--) {
                if (!(j & k)) {
                    if (!(s & k)) {
                        f1[j | s][k] = (f1[j | s][k] + f1[j][k]) % p;
                    }
                    if (!(s & j)) {
                        f2[j][k | s] = (f2[j][k | s] + f2[j][k]) % p;
                    }
                }
            }
        }
    }
    update();
    int res = 0;
    for (int j = M - 1; j >= 0; j--) {
        for (int k = j ^ (M - 1); k >= 0; k--) {
            if (!(j & k)) {
                res = (res + f[j][k]) % p;
            }
        }
    }
    std::cout << res << '\n';
    return 0;
}
```

