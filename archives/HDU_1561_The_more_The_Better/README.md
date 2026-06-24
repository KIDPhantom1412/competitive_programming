# HDU 1561 - The more, The Better

- **来源**：HDU 1561
- **难度**：中等
- **标签**：树形 DP、依赖背包、背包问题
- **日期**：2026-06-24

## 一句话题解

建立虚拟根节点 0，将依赖关系转化为树，然后在树上做分组背包 / 依赖背包，最终答案为 `f[0][M+1]`。

## 文件说明

| 文件 | 说明 |
|------|------|
| problem.md | 题目描述 |
| solution.md | 详细题解 |
| wrong_code.cpp | 错误代码（本次未记录） |
| correct_code.cpp | 正确代码（AC） |
| pitfalls.md | 坑点总结 |
| samples.md | 样例输入输出（Markdown，便于复习） |
| input.txt | 典型输入（标题式格式，可直接用于测试） |
| output.txt | 典型输出（标题式格式，可直接用于测试） |
