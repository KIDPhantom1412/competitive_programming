#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    // 把 n 的各位压成 (数字, 位置) 序列，位置 i 对应权值 10^i
    std::vector<std::pair<int, int>> ds;
    for (int i = 0; n; i++) {
        ds.push_back({n % 10, i});
        n /= 10;
    }
    std::vector<int> ws; // 每位的权值 10^i，末尾多一项便于挖位
    int cur = 0, w = 1;
    for (size_t i = 0; i < ds.size(); i++) {
        ws.push_back(w);
        cur += w; // cur = 11...1（与 n 等长的全 1 模板）
        w *= 10;
    }
    ws.push_back(w);
    // 按数字升序处理：先把数字小的位从模板中挖掉，再按需生成加数
    std::sort(ds.begin(), ds.end());
    std::vector<int> res;
    int sub = 0; // 已生成的加数个数
    for (size_t i = 0; i < ds.size(); i++) {
        // 该位数字为 ds[i].first，加入模板直到已生成个数达到它
        while (sub < ds[i].first) {
            res.push_back(cur);
            sub++;
        }
        // 把模板的第 ds[i].second 位清零（保留高位与低位）
        int k = ws[ds[i].second + 1];
        cur = cur / k * k + cur % (k / 10);
    }
    std::cout << res.size() << '\n';
    for (int binary : res) {
        std::cout << binary << ' ';
    }
    std::cout << '\n';
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
