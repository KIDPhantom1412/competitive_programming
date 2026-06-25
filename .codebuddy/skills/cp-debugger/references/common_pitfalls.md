# 算法竞赛常见坑点参考

## 整数溢出

| 场景 | 错误写法 | 正确写法 |
|------|---------|---------|
| n ≤ 10^5, 求和 | `int sum` | `long long sum` |
| n ≤ 10^9 | `int` | `long long` |
| 乘法 | `a * b` | `(long long)a * b` 或 `1LL * a * b` |

经验法则：
- 10^5 以内的 int 求和可能溢出，用 long long
- 涉及乘法一律用 long long
- `int` 最大值约 2×10^9，`long long` 约 9×10^18

## 数组越界

```cpp
// 错误：n 最大 10^5，但数组只开了 1000
int a[1000];

// 错误：下标从 1 开始但访问了 a[n]
for (int i = 1; i <= n; i++) { ... }

// 错误：string 下标越界
string s;
cin >> s;
for (int i = 0; i <= s.length(); i++)  // 应该是 <

// 正确：数组至少开 maxN + 5 或更大
const int MAXN = 100005;
int a[MAXN];
```

## 多测试用例未重置

```cpp
// 错误：全局数组在多组 case 间有残留数据
int vis[1000];
for (int i = 0; i < n; i++) { vis[i] = 0; }  // 只清了 n 个

// 正确：每个 case 前完整重置
int vis[1000];
for (int t = 0; t < T; t++) {
    memset(vis, 0, sizeof(vis));  // 或只清用到的部分
    // ...
}
```

## 浮点数精度

```cpp
// 错误：直接比较
if (a == b) ...

// 正确：用 eps
const double eps = 1e-9;
if (fabs(a - b) < eps) ...

// 错误：输出精度不够
cout << ans;

// 正确：控制精度
cout << fixed << setprecision(6) << ans;
```

## I/O 效率

```cpp
// 必须加：加速 cin/cout
ios::sync_with_stdio(false);
cin.tie(nullptr);

// 大数据量时用 scanf/printf 或快读
```

## 边界条件

常见需要检查的边界：
- n = 0, n = 1
- 空字符串、空数组
- 最小值、最大值（如 min element in array）
- 图：n = 1（只有一个节点）
- 树：只有根节点

## STL 常见错误

```cpp
// 错误：vector 下标访问越界
vector<int> v;
cout << v[0];  // 未检查 size

// 正确：用 .at() 或先检查
if (!v.empty()) cout << v[0];

// 错误：遍历时修改 vector
for (auto it = v.begin(); it != v.end(); it++) {
    v.push_back(*it);  // 可能 invalid iterator
}
```
