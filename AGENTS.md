# AGENTS.md

## 仓库定位
- 算法竞赛题归档仓库。
- 根目录的 `main.cpp`、`input.txt`、`output.txt` 是**临时占位文件/草稿区**，不提交。
- 已 AC 的题目归档到 `archives/<OJ前缀>_<题号>_<题名>/`，每题包含 `题解.md` + `correct_code_01.cpp`（可追加多解法）。

## 构建
- 使用 **CMake** + C++23（`CMakeLists.txt:5`），根据所在系统选择生成器：
  - **Windows**：Visual Studio 生成器，`cmake -S <项目根目录> -B <项目根目录>/build`，产物为 `build\Release\main.exe`。
  - **Linux**：**Ninja + g++**，产物为 `main`。

### Windows 示例

```powershell
cmake -S <项目根目录> -B <项目根目录>/build
cmake --build <项目根目录>/build --config Release
<项目根目录>\build\Release\main.exe < input.txt > output.txt
```

### Linux 示例

- 项目根目录的 `build/` 是旧 Visual Studio 生成文件（`.vcxproj`、`.sln`），在 Linux 下**不要用它**。
- 为避免改动仓库文件，构建目录放到项目目录外，例如 `/tmp/opencode/build`：

```bash
cmake -S <项目根目录> -B /tmp/opencode/build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build /tmp/opencode/build
/tmp/opencode/build/main < <项目根目录>/input.txt > <项目根目录>/output.txt
```

- 调试时也可以把测试输入/输出写到 `input_0N.txt` / `output_0N.txt`，但归档后应清理，不要提交。

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
