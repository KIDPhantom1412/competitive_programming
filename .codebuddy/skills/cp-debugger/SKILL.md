---
name: cp-debugger
description: 算法竞赛题代码调试助手。当用户上传算法竞赛题目图片或文字描述，并检查 main.cpp / input.txt 的代码错误时使用。适用于用户需要诊断算法题代码为什么不对、WA/TLE/RE 等问题排查的场景。
---

# CP Debugger - 算法竞赛题代码调试 Skill

## 目的

本 skill 帮助诊断算法竞赛题代码错误。用户提供题目（图片或文字）后，分析 `main.cpp`、`input.txt`，找出代码错误原因。标准答案以题目截图中的样例输出为准。

## 使用流程

### 1. 获取题目信息

- 如果用户上传了**题目图片**，使用 OCR 或视觉能力读取题目内容
- 如果用户提供了**文字描述**，直接读取描述
- 如果用户提供了**参考题解**（网址、截图、或文字描述）：
  - **网址**：尝试访问链接，获取题解内容（算法思路、代码等）
  - **截图**：使用视觉能力读取截图中的题解内容
  - **文字**：直接读取用户提供的题解描述
  - 将参考题解与用户自己的 `main.cpp` 进行对比分析，帮助定位错误
- 提取关键信息：
  - 题目名称
  - 输入格式
  - 输出格式
  - 数据范围（n 的大小、数值范围等）
  - 样例输入/输出
  - 时间限制、内存限制

### 2. 读取代码文件并备份原始代码

读取当前工作目录下的文件：
- `main.cpp` - 待检查的代码
- `input.txt` - 输入数据
- `CMakeLists.txt` - 构建配置（确认编译方式）

如果文件不存在，提示用户确认文件路径。

**备份原始错误代码**（重要！调试过程中会反复修改 `main.cpp`，备份原始版本便于后续对比和归档）：

```powershell
Copy-Item "main.cpp" "main.cpp.orig" -Force
```

- 备份文件 `main.cpp.orig` 保存的是用户最初的错误代码
- 调试过程中**不要修改** `main.cpp.orig`
- 后续归档时如需错误代码，从 `main.cpp.orig` 读取
- 调试完成后可删除 `main.cpp.orig`（已归档则无需保留）

### 3. 编译与运行

**本项目使用 CMake 构建，编译步骤如下：**

#### 第一步：CMake 配置（仅首次或 CMakeLists.txt 变更后需要）

```powershell
cmake -S "<项目根目录>" -B "<项目根目录>/build"
```

示例（当前项目）：
```powershell
cmake -S "d:\workspace\qt\competitive_programming" -B "d:\workspace\qt\competitive_programming\build"
```

- 如果已经配置过（build 目录已存在），可跳过此步骤
- 配置成功后会显示 `-- Configuring done` 和 `-- Generating done`

#### 第二步：编译

```powershell
cmake --build "<项目根目录>/build" --config Release
```

示例：
```powershell
cmake --build "d:\workspace\qt\competitive_programming\build" --config Release
```

- 编译成功后，可执行文件位于：`build\Release\competitive_programming.exe`
- 如果只改了 `main.cpp`，此步骤增量编译很快

#### 第三步：运行与比对

```powershell
cmd /c "\"<项目根目录>\build\Release\competitive_programming.exe\" < \"<项目根目录>\input.txt\""
```

示例：
```powershell
cmd /c "d:\workspace\qt\competitive_programming\build\Release\competitive_programming.exe < d:\workspace\qt\competitive_programming\input.txt"
```

**注意：** PowerShell 不支持 `<` 重定向，必须用 `cmd /c` 包裹命令。

**输出比对：** 将程序输出与题目截图中的样例输出对比。

#### 编译错误速查

| 现象 | 处理方式 |
|------|---------|
| `cmake` 不是内部命令 | 提示用户安装 CMake 并加入 PATH |
| `No CMAKE_CXX_COMPILER could be found` | 提示用户安装 Visual Studio 或 MinGW |
| 编译警告（warning） | **不要忽略**，逐条检查，往往是潜在 bug |
| 编译错误（error） | 复制完整错误信息，进入步骤 4A（CE 诊断） |

#### 运行后观察

| 现象 | 下一步 |
|------|--------|
| 程序崩溃 / 报系统错误 | 进入步骤 4B（RE 诊断） |
| 程序长时间无输出 | 可能是 TLE，用 Ctrl+C 终止，进入步骤 4C |
| 有输出但答案不对 | 进入步骤 4D（WA 诊断） |
| 输出与题目样例一致 | 代码正确，无需进一步诊断 |

### 4. 诊断分析

根据步骤 3 的运行结果，针对问题类型（CE/RE/TLE/WA/MLE）进行诊断。诊断时给出**具体行号**和**精准修复建议**，不要直接重写整个代码。

### 5. 输出诊断报告

以清晰的结构输出：

```
## 诊断报告

### 题目信息
- 题目：xxx
- 数据范围：xxx

### 代码分析
- 算法思路：xxx
- 时间复杂度：xxx
- 编译：✅/❌（有警告则列出）

### 问题定位
[具体指出问题所在，附上行号]

### 修复建议
[给出具体的修改方案和理由]

### 修正代码
[如需要，给出修正后的关键代码片段]
```

## 注意事项

- 如果用户提供了题目图片，先仔细读取图片中的题目内容
- 如果用户提供了在线评测链接，可以尝试获取题目
- 如果用户提供了参考题解（网址/截图/文字），将其作为辅助诊断依据，对比参考题解的思路与用户代码，帮助定位错误
- 诊断时给出具体行号，方便用户定位
- 不要直接重写整个代码，而是给出精准的修复建议
- **每次修改代码后，都要重新执行编译（步骤3）→ 运行 → 比对，确认问题是否解决**
- 编译命令直接用 CMake，不要手写 g++ 命令
