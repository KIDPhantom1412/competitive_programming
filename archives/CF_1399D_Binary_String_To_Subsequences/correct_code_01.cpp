#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int cnt = 0;
    std::vector<int> A(n);
    std::stack<int> zeros, ones; // 以 0 / 1 结尾的子序列，栈中存末尾下标

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            if (ones.empty()) {
                A[i] = ++cnt; // 没有以 1 结尾的子序列可接，新开一条
            } else {
                A[i] = A[ones.top()]; // 接到最近的以 1 结尾的子序列，沿用其编号
                ones.pop();
            }
            zeros.push(i); // 该子序列现在以 0 结尾
        } else {
            if (zeros.empty()) {
                A[i] = ++cnt; // 没有以 0 结尾的子序列可接，新开一条
            } else {
                A[i] = A[zeros.top()]; // 接到最近的以 0 结尾的子序列，沿用其编号
                zeros.pop();
            }
            ones.push(i); // 该子序列现在以 1 结尾
        }
    }

    std::cout << cnt << '\n';
    for (int a : A) {
        std::cout << a << ' ';
    }
    std::cout << '\n';
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
