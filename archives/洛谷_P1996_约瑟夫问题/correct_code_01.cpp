#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5;

int n, m;
int head, tail;
struct Node {
    int v, p, n;
} node[N];
int idx;

void init() {
    head = 0, tail = N - 1;
    node[head] = {0, N - 1, N - 1};
    node[tail] = {0, 0, 0};
}

void pushBack(int v) {
    node[++idx] = {v, node[tail].p, tail};
    node[node[tail].p].n = idx;
    node[tail].p = idx;
}

void erase(int iter) {
    node[node[iter].p].n = node[iter].n;
    node[node[iter].n].p = node[iter].p;
}

int next(int iter) {
    iter = node[iter].n;
    if (iter == tail || iter == head) {
        iter = node[head].n;
    }
    return iter;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        pushBack(i);
    }

    int iter = head;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            iter = next(iter);
        }
        std::cout << node[iter].v << ' ';
        erase(iter);
    }

    return 0;
}
