#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

const int N = 110;

int n, K;
int A[N];

void solve() {
    std::cin >> n >> K;
    std::unordered_set<int> hs;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        hs.insert(A[i]);
    }
    // 周期长度为 k，最多容纳 k 个不同值
    if (hs.size() > K) {
        std::cout << -1 << '\n';
        return;
    }
    // n == k 时只有一个窗口，原数组已经美丽，且避免长度超过 1e4
    if (n == K) {
        std::cout << n << '\n';
        for (int i = 1; i <= n; i++) {
            std::cout << A[i] << ' ';
        }
        std::cout << '\n';
        return;
    }

    // 用全部不同值凑出长度为 k 的周期，空位用 a[1] 填充
    std::vector<int> res(hs.begin(), hs.end());
    while (res.size() < K) {
        res.push_back(A[1]);
    }
    int i = 1, j = 0;
    while (i <= n) {
        if (A[i] == res[j]) { // 当前周期位置能匹配下一个原数组元素
            i++;
        }
        res.push_back(res[j]); // 按周期继续往后写
        j++;
    }
    std::cout << res.size() << '\n';
    for (int ele : res) {
        std::cout << ele << ' ';
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
