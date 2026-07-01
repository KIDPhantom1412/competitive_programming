#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(5e5) + 10;

std::string preOrder;
int stk[N], top;
int mn[N][2], mx[N][2]; // 0: 根非绿, 1: 根绿

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> preOrder;
    for (int i = preOrder.size() - 1; i >= 0; i--) {
        int x = preOrder[i] - '0';
        if (x == 0) {
            mn[i][0] = mx[i][0] = 0; // 非绿：0 个绿
            mn[i][1] = mx[i][1] = 1; // 绿：1 个绿
            stk[++top] = i;
        } else if (x == 1) {
            int child = stk[top--];
            mn[i][0] = std::min(mn[child][0], mn[child][1]); // 父非绿，子可绿或非绿
            mn[i][1] = mn[child][0] + 1;                      // 父绿，子必须非绿
            mx[i][0] = std::max(mx[child][0], mx[child][1]);
            mx[i][1] = mx[child][0] + 1;
            stk[++top] = i;
        } else if (x == 2) {
            int lc = stk[top--], rc = stk[top--];
            // 父非绿：两个儿子必须一绿一非绿
            mn[i][0] = std::min(mn[lc][0] + mn[rc][1], mn[lc][1] + mn[rc][0]);
            mx[i][0] = std::max(mx[lc][0] + mx[rc][1], mx[lc][1] + mx[rc][0]);
            // 父绿：两个儿子必须都非绿（且颜色不同，红/蓝各一）
            mn[i][1] = mn[lc][0] + mn[rc][0] + 1;
            mx[i][1] = mx[lc][0] + mx[rc][0] + 1;
            stk[++top] = i;
        }
    }
    // 注意：先输出最多，再输出最少
    std::cout << std::max(mx[0][0], mx[0][1]) << ' ' << std::min(mn[0][0], mn[0][1]) << '\n';
    return 0;
}
