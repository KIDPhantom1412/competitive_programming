# AGENTS.md

## 仓库定位

对算法竞赛题进行调试、归档和笔记仓库。已 AC 的题目归档到 `archives/`，学习笔记放在 `notes/`，调试通过`main.cpp`、`run.sh`等进行。

## 目录说明

| 目录/文件                            | 用途                                                                      |
| ------------------------------------ | ------------------------------------------------------------------------- |
| `archives/<OJ前缀>_<题号>_<题名>/` | 已 AC 题目的归档目录，每个目录包含`题解.md` 与 `correct_code_*.cpp`。 |
| `notes/`                           | 算法与数据结构学习笔记、题型总结，按主题组织。                            |
| `templates/`                       | 常用算法与数据结构代码模板，按主题组织。                                  |
| `main.cpp`                         | 调试用的临时代码，不提交。                                                |
| `input.txt`                        | 调试用的临时输入文件，不提交。                                            |
| `output.txt`                       | 调试用的临时输出文件，不提交。                                            |
| `tmp/`                             | Agent的工作台，用于存储脚本、输入输出等临时文件，不提交。                 |
| `.env`                             | 编译配置（`CXX`、`CXXFLAGS` 等），不提交。                            |
| `.agents/skills/`                  | 本仓库使用的 agent skill 定义。                                           |

## 代码格式

使用 `.clang-format`（LLVM 风格）。格式化命令：`clang-format -i main.cpp`。

## git 规范

### 权限与推送

- 除非用户明确要求提交某个文件，否则禁止直接执行 `git commit` / `git push` / `git reset` / `git rebase` 等 git 变更操作。
- 用户明确说“提交”“commit”“保存”等仅表示允许执行本地 `git commit`，**不等于允许推送**。`git push` 属于独立操作，每次执行前必须单独获得用户明确同意。

### 提交信息格式

所有提交信息统一使用如下结构：

```
<type>(<scope>): <subject>

<body>

<footer>
```

- `subject` 必填，使用中文，简洁描述本次改动，结尾不加句号。
- `body` 可选，用于补充背景、改动细节或迁移说明。
- `footer` 可选，用于引用 issue、标注 BREAKING CHANGE 等（本仓库很少使用）。

### 类型（type）

| 类型       | 含义                                 | 典型场景                                              |
| ---------- | ------------------------------------ | ----------------------------------------------------- |
| `feat`     | 新增功能、题目归档、模板、笔记章节等 | 新增归档目录、新增模板文件、新增 notes 章节           |
| `docs`     | 文档/笔记内容更新                    | 修改题解、补充笔记例题、更新 skill 文档、更新 AGENTS  |
| `fix`      | 修复错误                             | 修正代码 bug、修复样例输出、修复格式错误              |
| `refactor` | 重构，不改变外部功能                 | 调整归档结构、重命名文件、重构模板/笔记章节           |
| `chore`    | 杂项/工具链/配置                     | 更新 `.vscode`、`.clangd`、`.env`、构建脚本等         |

### 作用域（scope）

| 作用域        | 对应内容                                        |
| ------------- | ----------------------------------------------- |
| `archive`     | `archives/` 目录下的题目归档                    |
| `notes`       | `notes/` 目录下的学习笔记                       |
| `templates`   | `templates/` 目录下的代码模板                   |
| `skills`      | `.agents/skills/` 目录下的 skill 定义           |
| `AGENTS`      | `AGENTS.md` 文件                                |
| `build`       | `run.sh` / `run.bat` / `.env` 等构建/运行脚本   |
| `vscode`      | `.vscode/` 编辑器配置                           |
| `lsp`         | `.clangd` 等 LSP 配置                           |
| `debugger`    | `cp-debugger` skill 的文档或逻辑调整            |
| `archiver`    | `cp-archiver` skill 的文档或逻辑调整            |
| （省略 scope) | 仓库根级改动或涉及多个 scope，建议尽量明确 scope  |

### 主题（subject）规范

- 用动词或动作开头，例如“新增”“修复”“重构”“补充”“更新”“迁移”。
- 归档提交：`feat(archive): <OJ前缀>_<题号>_<题名> - <一句话题解>`。
  - 首次归档：`feat(archive): 洛谷_P6242_线段树3 - 吉司机线段树维护区间加/chmin/和/最大值/历史最大值`
  - 追加解法：`feat(archive): 洛谷_P3372_线段树_1 - 追加解法2：线段树（懒标记）`
- 笔记提交：`docs(notes): <主题> - <说明>`。
  - 示例：`docs(notes): 线段树 - 新增 Segment Tree Beats 章节`
  - 示例：`docs(notes): 树状数组 - 补充单点修改区间查询（HDU 1754，max 型 BIT）`
- 模板提交：`docs(templates): <主题> - <说明>`。
  - 示例：`docs(templates): 树状数组新增二维「矩形修改，矩形查询」模板（洛谷 P4514）`
- 配置/工具提交：`chore(<scope>): <说明>` 或 `fix(<scope>): <说明>`。
  - 示例：`chore(vscode): 移除 clangd 默认格式化工具配置`
  - 示例：`fix(build): 修复 .env 读取空行导致编译失败的问题`

### 应避免的情况

- 禁止无意义提交信息，如 `--amend`、空提交、`update` 等。
- 避免用题目号单独作为 scope（如 `fix(P4322):`），应改为 `fix(archive): 洛谷_P4322_最佳团体 - 修复建图方向`。
- 避免完全省略 type（如 `改为通用的vscode格式`），应改为 `chore(vscode): 改为通用的 VS Code 格式`。
- 同类改动尽量合并为一个提交，不要把一个完整改动的中间状态分成多次提交。

### Merge 提交

由 Git 自动生成的 `Merge branch 'xxx' ...` 可保留默认格式，无需手动改写。
