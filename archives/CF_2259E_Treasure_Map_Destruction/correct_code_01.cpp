#include <algorithm>
#include <iostream>

const int N = int(2e5) + 5;

int n;
int B[N];
int diff[N];
bool st[N];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> B[i];
    }
    std::fill_n(diff, n + 2, 0);
    // b[i] > 0 时，(i - b[i], i + b[i]) 的严格内部必须没有宝藏
    // b[i] == 0 的禁放区间为空，必须跳过：否则会在 i 处留下一格 -1 的假贡献，
    // 既抵消别的约束在 i 上的禁放标记，又漏判「i 必须放宝藏」的冲突
    for (int i = 1; i <= n; i++) {
        if (B[i] > 0) {
            diff[std::max(1, i - B[i] + 1)]++;
            diff[std::min(n + 1, i + B[i])]--;
        }
    }
    for (int i = 1, cur = 0; i <= n; i++) {
        cur += diff[i];
        st[i] = cur > 0; // st[i] 为真表示 i 落在禁放区，不能放宝藏
    }
    for (int i = 1; i <= n; i++) {
        if (B[i] >= 0) {
            // 已知 b[i] 时，两侧距离恰为 b[i] 的位置至少有一个可放宝藏
            // b[i] == 0 时该条件化简为 !st[i]，恰好检测出「i 被禁放」的冲突
            if (!(i - B[i] >= 1 && !st[i - B[i]]) && !(i + B[i] <= n && !st[i + B[i]])) {
                std::cout << -1 << '\n';
                return;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << (st[i] ? 0 : 1); // 禁放区取补集即为宝藏集合（必非空）
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
