#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 前缀函数（字符串 1 下标，p[0] 为占位符）：
// pi[i] 为 p[1..i] 的最长真 border 长度
std::vector<int> getPi(std::string& p) {
    std::vector<int> pi(p.size());
    for (int i = 2, j = 0; i < int(pi.size()); i++) {
        while (j && p[i] != p[j + 1]) {
            j = pi[j];
        }
        if (p[i] == p[j + 1]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

void solve() {
    std::string s;
    std::cin >> s;
    s = ' ' + s;                     // 前置占位符，转为 1 下标
    int borderLen = getPi(s).back(); // 最长 border 的长度
    if (borderLen == 0) {            // 无任何 border，必无解
        std::cout << "Just a legend" << '\n';
        return;
    }

    std::string p = s.substr(0, borderLen + 1); // 最长 border 作为模式串 p
    auto pi = getPi(p);
    int innerLen = 0;
    // 用 KMP 在 s 的内部（终点 i <= n-1）匹配 p；
    // 匹配段长度 j <= i-1，故起点 >= 2，恰好是"中间出现"。
    // innerLen = p 的前缀在中间出现的最大长度
    for (int i = 2, j = 0; i < int(s.size()) - 1; i++) {
        while (j && s[i] != p[j + 1]) {
            j = pi[j];
        }
        if (s[i] == p[j + 1]) {
            j++;
        }
        innerLen = std::max(innerLen, j);
        if (j == int(p.size()) - 1) { // p 整个在中间出现，已是答案
            break;
        }
    }
    // 在 border 链上从长到短找第一个不超过 innerLen 的 border，即为答案
    int res = borderLen;
    while (res > innerLen) {
        res = pi[res];
    }
    if (res) {
        std::cout << s.substr(1, res) << '\n';
    } else {
        std::cout << "Just a legend" << '\n';
    }
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
