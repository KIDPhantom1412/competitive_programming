#include <iostream>
#include <string>
#include <unordered_set>

void solve() {
    int n, K, m;
    std::cin >> n >> K >> m;
    std::string s;
    std::cin >> s;
    std::string res;
    for (int i = 0, j = 0; i < n; i++) {
        if (j >= m) {
            std::cout << "NO" << '\n';
            res += std::string(n - res.size(), 'a');
            std::cout << res << '\n';
            return;
        }

        std::unordered_set<char> hs;
        for (; j < m; j++) {
            if (s[j] >= 'a' && s[j] < 'a' + K) {
                hs.insert(s[j]);
                if (hs.size() == K) {
                    res += s[j];
                    break;
                }
            }
        }
    }
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
