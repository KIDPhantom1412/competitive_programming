#include <algorithm>
#include <cstring>
#include <iostream>

using LL = long long;

const int N = int(5e5) + 5;

int n;
char S[N];          // 每个节点上的括号
int fa[N];          // 父节点
int H[N];           // 邻接表头
struct EdgeNode {
    int v, n;
} E[N];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int stk[N], top;    // 维护当前路径中未匹配的左括号节点
int last[N];        // 以当前节点结尾的合法子串数量
LL sum[N];          // 根到当前节点路径中合法子串总数

void dfs(int u) {
    int t = 0;      // 若发生匹配，记录被弹出的左括号，用于回溯恢复
    if (S[u] == '(') {
        stk[++top] = u;            // 左括号入栈
    } else {
        if (top > 0) {
            t = stk[top--];        // 右括号匹配栈顶
            // 以 u 结尾的合法串数 = 以匹配左括号父节点结尾的合法串数 + 1
            last[u] = last[fa[t]] + 1;
        }
    }
    sum[u] = sum[fa[u]] + last[u]; // 前缀和累加
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
    }
    if (t) {            // 恢复现场：重新把匹配掉的左括号压回栈
        stk[++top] = t;
    } else if (S[u] == '(') {
        top--;          // 恢复现场：撤销本次入栈
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    std::cin >> S;
    std::memmove(S + 1, S, n); // 将字符串下标从 1 开始

    for (int i = 2; i <= n; i++) {
        int j;
        std::cin >> j;
        add(j, i);      // 建图
        fa[i] = j;
    }

    dfs(1);

    LL res = 0;
    for (int i = 1; i <= n; i++) {
        res ^= i * sum[i]; // 计算答案
    }
    std::cout << res << '\n';

    return 0;
}
