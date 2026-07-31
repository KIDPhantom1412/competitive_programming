#include <algorithm>
#include <iostream>
#include <vector>

using LL = long long;

const int N = int(5e5) + 5;

int n;
int A[N];
LL tr[N];

void update(int x, LL d) { // 单点修改：A[x] += d
    for (int i = x; i <= n; i += i & -i) {
        tr[i] += d;
    }
}

LL sum(int x) { // 前缀和查询：A[1..x]
    LL res = 0;
    for (int i = x; i; i -= i & -i) {
        res += tr[i];
    }
    return res;
}

LL sum(int l, int r) { // 区间查询：A[l..r]
    return sum(r) - sum(l - 1);
}

std::vector<int> disc;

int find(int x) {
    return std::lower_bound(disc.begin(), disc.end(), x) - disc.begin() + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        disc.push_back(A[i]);
    }

    // 离散化：排序去重后，用 lower_bound 映射到秩 [1, 不同值个数]
    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    LL res = 0; // 逆序对总数最大约 1.25e11，必须用 long long
    for (int i = n; i >= 1; i--) {
        int x = find(A[i]);
        // 关键：逆序对要求 a_i > a_j（严格大于），
        // 只能查 sum(x - 1)，排除右侧等于自身的元素
        res += sum(x - 1);
        update(x, 1);
    }

    std::cout << res << '\n';

    return 0;
}
