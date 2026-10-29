#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// 贪心：按输入顺序把每个块放到当前最矮的塔上。
// 因为 h_i <= x，无论怎么放，最大塔高 - 最小塔高始终 <= x，
// 所以答案恒为 YES。
void solve() {
    int n, m, x;
    std::cin >> n >> m >> x;
    std::vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> h[i];
    }

    // 维护每座塔的当前高度和编号
    struct Node {
        int height;
        int index;

        // 注意：priority_queue 默认是大根堆，这里把比较「反过来写」，
        // 让大根堆的效果等价于小根堆（堆顶是最矮的塔）。
        // 必须用严格弱序（height > ct.height），不能写 >=，
        // 否则 a < a 会为真，属于未定义行为。
        bool operator<(const Node& ct) const {
            return height > ct.height;
        }
    };
    std::priority_queue<Node> pq;

    std::vector<int> res(n + 1);
    // 前 m 块各占一座塔，保证每座塔至少有一个块
    for (int i = 1; i <= m; i++) {
        pq.push({h[i], i});
        res[i] = i;
    }
    // 剩余块依次丢给当前最矮的塔
    for (int i = m + 1; i <= n; i++) {
        auto [cur, idx] = pq.top();
        pq.pop();
        pq.push({cur + h[i], idx});
        res[i] = idx;
    }

    std::cout << "YES" << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << res[i] << " \n"[i == n];
    }
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
