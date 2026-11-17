#include <iostream>
#include <string>
#include <unordered_map>

void solve() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        cnt[a]++;
    }
    // two 是全局对数，four 是全局四元组数。
    // 正方形用掉同一长度的 2 对，长方形还要 2 对，因此需要 four >= 1 且 two >= 4。
    int two = 0, four = 0;
    for (const auto& kv : cnt) {
        two += kv.second / 2;
        four += kv.second / 4;
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::string op;
        std::cin >> op;
        int x;
        std::cin >> x;
        if (op == "+") {
            cnt[x]++;
            // 奇数变偶数时多 1 对；数量变成 4 的倍数时多 1 个四元组。
            if (cnt[x] % 2 == 0) {
                two++;
            }
            if (cnt[x] % 4 == 0) {
                four++;
            }
        } else {
            // 按删除前的数量回退，再减数量。4→3 同时少 1 对和 1 个四元组，5→4 两者都不变。
            if (cnt[x] % 2 == 0) {
                two--;
            }
            if (cnt[x] % 4 == 0) {
                four--;
            }
            cnt[x]--;
        }
        if (four >= 1 && two >= 4) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}
