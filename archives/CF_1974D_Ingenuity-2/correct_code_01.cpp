#include <iostream>
#include <string>

void solve() {
    int n;
    std::cin >> n;
    std::string instruction;
    std::cin >> instruction;

    // 总位移
    int sx = 0, sy = 0;
    for (char c : instruction) {
        sx += c == 'E';
        sx -= c == 'W';
        sy += c == 'N';
        sy -= c == 'S';
    }

    // R 与 H 位移相同，故总位移必为 2 倍，两个分量都必须是偶数
    if (sx % 2 || sy % 2) {
        std::cout << "NO" << '\n';
        return;
    }

    // 先默认全给 H
    std::string res(n, 'H');

    // 总位移为 (0, 0)：直接按需分配会把所有指令都给 H，R 为空
    // 因此先挑一对相反的指令（净位移 0）给 R，其余全给 H
    if (sx == 0 && sy == 0) {
        res[0] = 'R';
        if (instruction[0] == 'N') {
            for (int i = 1; i < n; i++) {
                if (instruction[i] == 'S') {
                    res[i] = 'R';
                    break;
                }
            }
        } else if (instruction[0] == 'E') {
            for (int i = 1; i < n; i++) {
                if (instruction[i] == 'W') {
                    res[i] = 'R';
                    break;
                }
            }
        } else if (instruction[0] == 'S') {
            for (int i = 1; i < n; i++) {
                if (instruction[i] == 'N') {
                    res[i] = 'R';
                    break;
                }
            }
        } else {
            for (int i = 1; i < n; i++) {
                if (instruction[i] == 'E') {
                    res[i] = 'R';
                    break;
                }
            }
        }
        // 找不到反向指令说明只能让同一台设备执行全部指令（如 "SN"、"WE"）
        if (res == std::string(n, 'R')) {
            std::cout << "NO" << '\n';
            return;
        }
    }

    // R 需要承担总位移的一半：sx/2 条 E（或 -sx/2 条 W），y 方向同理
    sx /= 2, sy /= 2;
    for (int i = 0; i < n; i++) {
        if (instruction[i] == 'N') {
            if (sy > 0) {
                res[i] = 'R';
                sy--;
            }
        } else if (instruction[i] == 'E') {
            if (sx > 0) {
                res[i] = 'R';
                sx--;
            }
        } else if (instruction[i] == 'S') {
            if (sy < 0) {
                res[i] = 'R';
                sy++;
            }
        } else {
            if (sx < 0) {
                res[i] = 'R';
                sx++;
            }
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
