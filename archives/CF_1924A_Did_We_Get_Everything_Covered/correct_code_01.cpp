#include <iostream>
#include <string>
#include <unordered_set>

void solve() {
    int n, K, m;
    std::cin >> n >> K >> m;
    std::string s;
    std::cin >> s;

    // res 记录每一段「第一次收齐全部 K 种字母」时的收尾字符
    std::string res;
    for (int i = 0, j = 0; i < n; i++) {
        std::unordered_set<char> hs; // 当前段内已出现的字母
        for (; j < m; j++) {
            if (s[j] >= 'a' && s[j] < 'a' + K) {
                hs.insert(s[j]);
                if (int(hs.size()) == K) { // 本段收齐 K 种字母
                    res += s[j];
                    // 关键：该字符已被本段消费，下一段必须从 j + 1 开始，
                    // 否则相邻两段重叠，会凭空多凑出段数而误判为 YES
                    j++;
                    break;
                }
            }
        }
        if (int(hs.size()) < K) { // 第 i + 1 段凑不齐，构造反例
            std::cout << "NO" << '\n';
            char c = 'a'; // 取本段缺失的最小字母
            while (c < 'a' + K && hs.count(c)) {
                c++;
            }
            // 已凑出 res.size() 段，还差 n - res.size() 位，全部用缺失字母补齐
            res += std::string(n - res.size(), c);
            std::cout << res << '\n';
            return;
        }
    }
    // 能切出 n 段，则任意长度为 n 的串都是 s 的子序列
    std::cout << "YES" << '\n';
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
