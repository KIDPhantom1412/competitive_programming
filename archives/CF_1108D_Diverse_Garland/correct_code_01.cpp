#include <iostream>
#include <string>
#include <vector>

void solve() {
    std::vector<char> wheel{'R', 'G', 'B'};
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    int cnt = 0;
    // 按极长同色连续段处理，段内隔位染色
    for (int i = 0; i < int(s.size());) {
        int j = i + 1;
        // 找出连续段 [i, j)：s[i..j-1] 同色
        while (j < int(s.size()) && s[j] == s[i]) {
            j++;
        }
        // 偏移 1, 3, 5, ... 的位置各染一次，共 floor(L/2) 次
        for (int k = i + 1; k < j; k += 2) {
            for (char c : wheel) {
                // 选与左右邻居都不同的颜色（三种颜色必有一个可用）
                // 左右邻居均为偶数偏移的未染色位置，保持原色；
                // 段尾还需避开下一段的段首颜色
                if ((k - 1 >= 0 && s[k - 1] == c) || (k + 1 < int(s.size()) && s[k + 1] == c)) {
                    continue;
                }
                cnt++;
                s[k] = c;
                break;
            }
        }
        i = j;
    }
    std::cout << cnt << '\n';
    std::cout << s << '\n';
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
