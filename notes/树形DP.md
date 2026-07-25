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

## 树形背包DP

> 在有根树上做分组背包（或依赖背包）：每个子树可视为一个物品组，从中选择若干节点（或保留若干用户）会获得一定收益并付出代价，要求在某个限制下的最优值。
>
> 常用状态：
>
> - `f[u][j]`：以 $u$ 为根的子树中，共选择 / 保留 $j$ 个节点（或用户）时的最优值。
>
> 转移要点：按后序 DFS 顺序处理每个子树，将每个子树视为一个物品组，枚举在子树中选择的数量，做类似 0/1 背包或分组背包的转移。注意合并顺序和容量上限。

### 有线电视网

题目：

* [www.luogu.com.cn/problem/P1273](https://www.luogu.com.cn/problem/P1273)

题解：

* [后序DFS序树形背包](../archives/洛谷_P1273_有线电视网/题解.md)

### Rebuilding Roads

题目：

* [vjudge.net/problem/OpenJ_Bailian-1947](https://vjudge.net/problem/OpenJ_Bailian-1947)

题解：

* [树上背包：删边得到孤立子树](../archives/OpenJ_Bailian_1947_Rebuilding_Roads/题解.md)

### Apple Tree

题目：

* [vjudge.net/problem/OpenJ_Bailian-2486](https://vjudge.net/problem/OpenJ_Bailian-2486)

题解：

* [树上背包：步数限制与返回状态](../archives/OpenJ_Bailian_2486_Apple_Tree/题解.md)
