#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 2510;
const double INF = 1e9;

int n, m;
int A[N], B[N];
double V[N];
int H[N];
struct EdgeNode {
    int v, n;
} E[N];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int size[N];
int pos[N], cnt;

void dfs(int u) {
    size[u] = 1;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
        size[u] += size[v];
    }
    pos[++cnt] = u;
}

double f[N][N];

bool check(double mid) {
    for (int i = 0; i <= cnt; i++) {
        std::fill_n(f[i] + 1, m, -INF);
    }
    for (int i = 1; i <= n; i++) {
        V[i] = A[i] - mid * B[i];
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = std::max(f[i - 1][j - 1] + V[pos[i]], f[i - size[pos[i]]][j]);
        }
    }
    return f[cnt][m] > 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> m >> n;
    m++; // jyy必选
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        A[i] = b, B[i] = a;
        add(c, i);
    }
    dfs(0);
    double l = 0, r = 1e4;
    while (r - l > 1e-7) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%.3lf\n", l);
    return 0;
}