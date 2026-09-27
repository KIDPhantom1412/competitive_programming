#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>

const int N = int(2e5) + 5;

int n;
int A[N];

void solve() {
    std::cin >> n;
    std::unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        cnt[A[i]]++;
    }

    // 每次取出现次数最大的两个值，各删掉一个
    std::priority_queue<std::pair<int, int>> pq;
    for (auto [k, v] : cnt) {
        pq.push({v, k});
    }

    int size = n;
    while (pq.size() >= 2) {
        auto [cnt1, v1] = pq.top();
        pq.pop();
        auto [cnt2, v2] = pq.top();
        pq.pop();
        cnt1--;
        cnt2--;
        size -= 2;
        if (cnt1) {
            pq.push({cnt1, v1});
        }
        if (cnt2) {
            pq.push({cnt2, v2});
        }
    }

    std::cout << size << '\n';
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
