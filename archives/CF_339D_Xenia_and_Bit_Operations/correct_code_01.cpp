#include <algorithm>
#include <iostream>

const int N = (1 << 17) + 5;

int A[N];

struct TreeNode {
    int v;
    bool isOr; // 该节点由左右儿子做 OR(true) 还是 XOR(false) 合并而来
} tr[N * 4];

void pull(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    if (tr[u].isOr) {
        tr[u].v = tr[lc].v | tr[rc].v;
    } else {
        tr[u].v = tr[lc].v ^ tr[rc].v;
    }
}

void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {A[L], false}; // 叶子不参与合并，标记只在父节点使用
        return;
    }

    int mid = (L + R) / 2;
    int lc = u * 2, rc = u * 2 + 1;
    build(lc, L, mid), build(rc, mid + 1, R);
    // 相邻两层运算交替：从叶子往上推，父层与子层标记相反
    tr[u].isOr = !tr[lc].isOr;
    pull(u);
}

void update(int u, int L, int R, int p, int b) {
    if (L == R) {
        tr[u].v = b;
        return;
    }

    int mid = (L + R) / 2;
    if (p <= mid) {
        update(u * 2, L, mid, p, b);
    } else {
        update(u * 2 + 1, mid + 1, R, p, b);
    }
    pull(u); // 只有根到 p 的路径需要重算
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= (1 << n); i++) {
        std::cin >> A[i];
    }
    build(1, 1, 1 << n);
    while (m--) {
        int p, b;
        std::cin >> p >> b;
        update(1, 1, 1 << n, p, b);
        std::cout << tr[1].v << '\n'; // 根节点即最终得到的 v
    }
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
