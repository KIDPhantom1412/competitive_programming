# 树形DP

## 普通树形DP

### 树上独立集(Independent Set on Tree)

> 在树中选出若干节点构成独立集，要求任意两个被选节点之间没有边直接相连，目标是最大化（或最小化）某种权值。
>
> 常用状态：
>
> - `f[u][0]`：不选节点 $u$ 时，以 $u$ 为根的子树内的最优值。
> - `f[u][1]`：选节点 $u$ 时，以 $u$ 为根的子树内的最优值。
>
> 转移要点：若选 $u$，则所有子节点都不能选；若不选 $u$，则子节点可选可不选，取更优者。

#### 没有上司的舞会

题目：

* [www.acwing.com/problem/content/description/287](https://www.acwing.com/problem/content/description/287/)

题解：

+ [无向树解法](../archives/AcWing_285_没有上司的舞会/题解.md)

### 树上点覆盖集(Vertex Cover on Tree)

> 在树中选出若干节点构成点覆盖集，要求每条边至少有一个端点被选中，目标是最小化（或最大化）某种权值。
>
> 常用状态：
>
> - `f[u][0]`：不选节点 $u$ 时，以 $u$ 为根的子树内的最优值。此时 $u$ 到每个子节点的边都必须由子节点覆盖，因此每个子节点都必须被选。
> - `f[u][1]`：选节点 $u$ 时，以 $u$ 为根的子树内的最优值。此时子节点可选可不选，取更优者。
>
> 转移要点：$u$ 不选时所有子节点必须选；$u$ 选时子节点自由。

#### 战略游戏

题目：

* [www.acwing.com/problem/content/325/](https://www.acwing.com/problem/content/325/)

题解：

* [最小点覆盖](../archives/AcWing_323_战略游戏/题解.md)

### 树上支配集(Dominating Set on Tree)

> 在树中选出若干节点构成支配集，要求每个节点要么自己被选中，要么至少与一个被选中的节点相邻，目标是最小化（或最大化）某种权值。
>
> 常用状态（三态模型）：
>
> - `f[u][0]`：节点 $u$ 被选中，此时 $u$ 已被自己支配，子节点可被自己或父节点（即 $u$）支配。
> - `f[u][1]`：节点 $u$ 未被选中，但至少有一个子节点被选中，从而 $u$ 被子节点支配。
> - `f[u][2]`：节点 $u$ 未被选中，且当前没有子节点被选中，$u$ 等待被父节点支配。
>
> 转移要点：状态 1 要求至少选一个子节点；状态 2 要求父节点最终被选，因此常与父节点的状态 0 配合使用。

#### 皇宫看守

题目：

* [www.acwing.com/problem/content/description/1079](https://www.acwing.com/problem/content/description/1079/)

题解：

* [最小权支配集](../archives/AcWing_1077_皇宫看守/题解.md)

### 树形染色 / 约束传播

> 在树上为每个节点赋予一个颜色/状态，父子之间（或兄弟之间）满足某种约束，求某种颜色/状态的最优数量。这类 DP 通常只和节点相邻状态有关，转移时枚举当前节点状态并合并子树状态。

#### 三色二叉树

题目：

* [vjudge.net/problem/洛谷-P2585](https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2585)

题解：

* [栈模拟后序遍历 + 节点绿/非绿状态转移](../archives/洛谷_P2585_三色二叉树/题解.md)

### 树上最大连通子树和

> 在树中保留一个以某节点为根的连通子树，使得子树中节点权值和最大。每个节点做后序 DP：若子节点的贡献为正，则把该子树合并进来；否则剪断该边。

#### 最大子树和

题目：

* [vjudge.net/problem/洛谷-P1122](https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P1122)

题解：

* [后序 DFS，正贡献合并](../archives/洛谷_P1122_最大子树和/题解.md)

### 树上路径问题

#### 树的最长路径

题目：

* [www.acwing.com/problem/content/1074](https://www.acwing.com/problem/content/1074/)

题解：

* [维护单链长度和双链长度](../archives/AcWing_1072_树的最长路径/题解.md)
* [维护最长链长度和次长链长度](../archives/AcWing_1072_树的最长路径/题解.md)

#### 数字转换

题目：

* [www.acwing.com/problem/content/description/1077](https://www.acwing.com/problem/content/description/1077/)

题解：

* [建模为树的最长路径](../archives/AcWing_1075_数字转换/题解.md)

## 换根DP

> 换根DP（Rerooting DP）用于求解"以每个节点作为整棵树的根时，与树结构相关的某个状态值"。
>
> 基本思想：先任选一个根（通常为 1）做一次树形 DP，求出每个节点在**其子树内**的答案；然后再做一次 DFS，利用父节点已经计算好的信息，把根从父节点"换"到子节点，从而推出每个节点作为**整棵树**的根时的答案。
>
> 核心状态：
>
> - `down[u]`：以 $u$ 为根的子树内的答案（第一遍 DFS 自下而上计算）。
> - `up[u]`：$u$ 通过父节点能到达的**子树外部**的答案（第二遍 DFS 自上而下计算）。
> - 最终答案：`f(u) = combine(down[u], up[u])`，即将子树内与子树外信息合并。
>
> 关键细节：换根时需要判断子节点是否是当前父节点向下最优路径的来源；若是，则不能重复使用该子节点，需改用次优路径或向上路径，避免同一条边被经过两次。

### 树的中心

题目：

* [www.acwing.com/problem/content/description/1075](https://www.acwing.com/problem/content/description/1075/)

题解：

* [换根DP](../archives/AcWing_1073_树的中心/题解.md)

### Computer

题目：

* [vjudge.net/problem/HDU-2196](https://vjudge.net/problem/HDU-2196)

题解：

* [换根DP求每个节点最远距离](../archives/HDU_2196_Computer/题解.md)

### Nearby Cows G

题目：

* [vjudge.net/problem/洛谷-P3047](https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3047)

题解：

* [换根DP求每个节点距离K以内权和](../archives/洛谷_P3047_Nearby_Cows_G/题解.md)

## 树形背包DP

> 在有根树上做背包：每个子树可视为一个物品组，从中选择若干节点会获得收益并付出代价，要求在某个限制下的最优值。
>
> 常用状态：
>
> - `f[u][j]`：以 $u$ 为根的子树中，共选择 / 保留 $j$ 个节点（或用户）时的最优值。
>
> 按实现方式可分为两类：
> 1. 按子树合并：逐个合并子节点的 DP 表，适合“把容量分配给各个子树”的问题。
> 2. 拍平为 DFS 序：利用后序遍历中子树连续的性质，用一维 DP 做“选择节点 / 跳过子树”的转移。

### 树上依赖背包（按子树合并）

> 转移要点：按后序 DFS 顺序处理每个子树，将每个子树视为一个物品组，枚举在子树中选择的数量，做类似依赖背包合并的转移。注意合并顺序和容量上限。

#### Rebuilding Roads

题目：

* [vjudge.net/problem/OpenJ_Bailian-1947](https://vjudge.net/problem/OpenJ_Bailian-1947)

题解：

* [删边得到孤立子树](../archives/OpenJ_Bailian_1947_Rebuilding_Roads/题解.md)

#### Apple Tree

题目：

* [vjudge.net/problem/OpenJ_Bailian-2486](https://vjudge.net/problem/OpenJ_Bailian-2486)

题解：

* [步数限制与返回状态](../archives/OpenJ_Bailian_2486_Apple_Tree/题解.md)

#### 小 Q 的棋盘

题目：

* [vjudge.net/problem/洛谷-P3698](https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3698)

题解：

* [步数限制 + 返回状态 + 贪心对比](../archives/洛谷_P3698_小Q的棋盘/题解.md)

#### Find Metal Mineral

题目：

* [vjudge.net/problem/HDU-4003](https://vjudge.net/problem/HDU-4003)

题解：

* [机器人覆盖子树](../archives/HDU_4003_Find_Metal_Mineral/题解.md)

### 可拍平为 DFS 序的树上依赖背包

> 当“选择当前节点”等价于“允许进入该子树”，“不选当前节点”等价于“跳过整棵子树”时，可以把后序 DFS 序列拍平成一维区间，用 `f[i][j]` 表示前 i 个节点中选 j 个的最优值。利用子树在 DFS 序中连续、大小为 `size[u]` 的性质，不选 u 时直接跳过 `size[u]` 个位置。拍平后就是一个普通 0/1 背包。
>
> 以下题目在结构上都满足该条件（题解中的经典写法可能是按子树合并，但同样可拍平）。

#### 有线电视网

题目：

* [www.luogu.com.cn/problem/P1273](https://www.luogu.com.cn/problem/P1273)

题解：

* [后序DFS序树形背包](../archives/洛谷_P1273_有线电视网/题解.md)

#### The more, The Better

题目：

* [vjudge.net/problem/HDU-1561](https://vjudge.net/problem/HDU-1561)

题解：

* [树形背包 + 依赖背包 + 虚拟根](../archives/HDU_1561_The_more_The_Better/题解.md)

#### Starship Troopers

题目：

* [vjudge.net/problem/HDU-1011](https://vjudge.net/problem/HDU-1011)

题解：

* [子树至少 1 士兵 + m=0 特判](../archives/HDU_1011_Starship_Troopers/题解.md)

#### 最佳团体

题目：

* [www.luogu.com.cn/problem/P4322](https://www.luogu.com.cn/problem/P4322)

题解：

* [DFS 序 + 0/1 背包 + 分数规划](../archives/洛谷_P4322_最佳团体/题解.md)

#### 选课

题目：

* [vjudge.net/problem/洛谷-P2014](https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2014)

题解：

* [DFS 序 + 0/1 背包 + 虚拟根](../archives/洛谷_P2014_选课/题解.md)
