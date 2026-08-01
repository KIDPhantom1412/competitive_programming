#include <algorithm>
#include <iostream>

const int N = int(2e5) + 10;

int n, m;
int A[N];  // 原数组（叶子值），单点更新的旧值判断和 query 的散点取值都要用它
int tr[N]; // 树状数组：tr[i] = max{A[i - lowbit(i) + 1 .. i]}，即"区间最大值型 BIT"

// 单点更新：把 A[x] 改为 v，并同步维护所有覆盖 x 的 BIT 节点
void update(int x, int v) {
    // 关键：必须和旧值 A[x] 比较来判断是"升值"还是"降值"
    // （若错写成 v >= tr[x]，由于 tr[x] 是后缀区间的最大值，
    //  当区间内其他位置比 x 大时会把降值误判为升值，导致降值后 tr 不刷新而出错）
    bool up = v >= A[x];
    A[x] = v;
    // 沿 BIT 祖先链向上，枚举所有"管辖范围包含 x"的节点 i（共 O(log n) 个）
    for (int i = x; i <= n; i += i & -i) {
        if (up) {
            // 升值：i 管辖区间内的最大值只会不变或变成 v，取 max 即可，O(1)
            tr[i] = std::max(tr[i], v);
        } else {
            // 降值：x 可能就是区间最大值来源，必须重算整个区间
            // tr[i] 管辖 (i-lowbit(i), i]，直接分裂为：
            //   叶子 A[i] + 子块 tr[i-1], tr[i-2], tr[i-4], ...（按二进制逐级跳）
            // 共 lowbit(i) 的位数个候选，累计 O(log n)
            tr[i] = A[i];
            for (int j = 1; j < (i & -i); j <<= 1) {
                tr[i] = std::max(tr[i], tr[i - j]);
            }
        }
    }
}

// 区间查询 [l, r] 的最大值：max 不可逆（没有"差分"），只能从右往左扫描
int query(int l, int r) {
    int res = 0; // 成绩为正整数，0 作初始值安全
    // 不变式：res 保存已扫描部分 (i, r] 的最大值，i 是当前右端点
    for (int i = r; i >= l; i--) {
        int j = i - (i & -i) + 1; // tr[i] 管辖区间的左端点
        if (j >= l) {
            // 整块 [j, i] 都在 [l, r] 内：直接用 tr[i]，并跳过整块
            res = std::max(res, tr[i]);
            i = j; // 循环体末尾 i--，下一步 i 变为 j - 1
        } else {
            // 块越出左界：只能逐点取 A[i]，左移一格
            res = std::max(res, A[i]);
        }
    }
    return res;
}

void solve() {
    std::fill(tr + 1, tr + 1 + n, 0); // 多组数据，每组必须重置 tr
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        update(i, A[i]); // 建树：逐个插入，O(n log n)；n<=2e5 足够快
    }
    while (m--) {
        std::string op;
        int a, b;
        std::cin >> op >> a >> b;
        if (op == "Q") {
            std::cout << query(a, b) << '\n';
        } else { // 'U'
            update(a, b);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m) { // 处理到文件结束
        solve();
    }

    return 0;
}
