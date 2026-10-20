#include <iostream>
#include <string>

void solve() {
    int a, b, c; // a = n0, b = n1, c = n2
    std::cin >> a >> b >> c;
    std::string res;

    if (b == 0) {
        // 没有混合对，整串只能是一种字符
        if (a) {
            res.resize(a + 1, '0');
        } else {
            res.resize(c + 1, '1');
        }
    } else {
        // 0 段贡献 a 个 "00"，1 段贡献 c 个 "11"，
        // 两段交界处恰好产生 1 个 "01"
        res += std::string(a + 1, '0');
        res += std::string(c + 1, '1');

        // 末尾字符是 '1'，交替追加 b-1 个字符：
        // 新增的每对都是 "10" 或 "01"，正好补足 b-1 个混合对
        char cur = '0';
        while ((b--) > 1) {
            res += cur;
            cur = '1' - cur + '0';
        }
    }

    std::cout << res << '\n';
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
