#include <algorithm>
#include <iostream>

const int N = int(2e5) + 5;

int n;
struct Segment {
    int l, r;
} S[N];

// 起点是 0。每步把当前可达区间向两侧扩 k，再与第 i 段取交
bool check(int k) {
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        l = std::max(l - k, S[i].l);
        r = std::min(r + k, S[i].r);
        if (l > r) {
            return false;
        }
    }
    return true;
}

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int l, r;
        std::cin >> l >> r;
        S[i] = {l, r};
    }

    // k 单调：可行则更大的 k 也可行。坐标都在 [0, 1e9]，上界 1e9 一定够
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << '\n';
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
