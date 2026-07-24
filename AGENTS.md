# AGENTS.md

## 仓库定位

对算法竞赛题进行调试、归档和笔记仓库。已 AC 的题目归档到 `archives/`，学习笔记放在 `notes/`，调试通过`main.cpp`、`run.sh`等进行。

## 目录说明

| 目录/文件                            | 用途                                                                      |
| ------------------------------------ | ------------------------------------------------------------------------- |
| `archives/<OJ前缀>_<题号>_<题名>/` | 已 AC 题目的归档目录，每个目录包含`题解.md` 与 `correct_code_*.cpp`。 |
| `notes/`                           | 算法与数据结构学习笔记、题型总结，按主题组织。                            |
| `main.cpp`                         | 调试用的临时代码，不提交。                                                |
| `input.txt`                        | 调试用的临时输入文件，不提交。                                            |
| `output.txt`                       | 调试用的临时输出文件，不提交。                                            |
| `tmp/`                             | Agent的工作台，用于存储脚本、输入输出等临时文件，不提交。                 |
| `.env`                             | 编译配置（`CXX`、`CXXFLAGS` 等），不提交。                            |
| `.agents/skills/`                  | 本仓库使用的 agent skill 定义。                                           |

## 代码格式

使用 `.clang-format`（LLVM 风格）。格式化命令：`clang-format -i main.cpp`。

## git 规范

- 除非用户明确要求提交某个文件，否则禁止直接执行 `git commit` / `git push` / `git reset` / `git rebase` 等 git 变更操作。
- 用户明确说“提交”“commit”“保存”等仅表示允许执行本地 `git commit`，**不等于允许推送**。`git push` 属于独立操作，每次执行前必须单独获得用户明确同意。
- `git commit` 的提交信息必须遵循仓库已有的提交风格（如 `feat(archive): <题目> - <一句话题解>`、`docs(notes): <说明>` 等），保持简洁一致。
