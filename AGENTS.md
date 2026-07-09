# AGENTS.md

## 仓库定位
- 算法竞赛题归档仓库。
- 根目录的 `main.cpp`、`input.txt`、`output.txt` 是**临时占位文件/草稿区**，不提交。
- 已 AC 的题目归档到 `archives/<OJ前缀>_<题号>_<题名>/`，每题包含 `题解.md` + `correct_code_01.cpp`（可追加多解法）。

## 构建

- 统一通过 `run.sh`（Linux）或 `run.bat`（Windows）脚本编译运行，**不要直接调用 `g++`**；编译选项通过项目根目录的 `.env` 配置：
  - `CXX`：编译器路径
  - `CXXFLAGS`：编译 flag，例如 `-std=c++23 -O2 -Wall -Wextra`
- `run.sh` / `run.bat` 自动编译并运行：
  - Linux 默认：`./run.sh` 等价于读取 `.env` 后编译 `main.cpp` 并运行：`tmp/main < input.txt > output.txt`
  - Linux 带参数：`./run.sh input_01.txt output_01.txt`
  - Windows 默认：`run.bat` 等价于读取 `.env` 后编译 `main.cpp` 并运行：`tmp\main.exe < input.txt > output.txt`
  - Windows 带参数：`run.bat input_01.txt output_01.txt`
- 编译产物放在 `tmp/main`（Linux）或 `tmp\main.exe`（Windows），不污染项目目录。

### Linux 示例

```bash
./run.sh
```

### Windows 示例

```cmd
run.bat
```

### 调试示例

```bash
./run.sh input_01.txt output_01.txt
```

```cmd
run.bat input_01.txt output_01.txt
```

## 代码格式
- 按 `.clang-format`：LLVM 风格，4 空格缩进，列宽 100，左指针对齐。
- 格式化命令：`clang-format -i main.cpp`。

## 工作流
- 调试题目 → 使用 `cp-debugger` skill；它会把原始 `main.cpp` 备份为 `main.cpp.orig`。
- 归档题目 → 使用 `cp-archiver` skill；目录命名规范见 `.agents/skills/cp-archiver/references/oj_prefixes.md`。
- 归档后清理 `main.cpp.orig`、`input_0N.txt`、`output_0N.txt` 等调试中间文件。
- 归档提交时只 `add archives/<题目>/`，**不要提交 `main.cpp`、`input.txt`、`output.txt`**。

## 约束
- 不要修改项目目录下已有文件，除非用户明确要求。
- 不要使用 `bits/stdc++.h`（skill 要求）。
