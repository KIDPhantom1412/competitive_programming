# OJ 前缀规范

归档目录命名格式：`<OJ前缀>_<题号>_<题名>`

## 前缀对照表

| OJ | 前缀 | 题号格式 | 示例 |
|----|------|---------|------|
| 洛谷 | 洛谷 | Pxxxx | 洛谷_P1040_加分二叉树 |
| HDU | HDU | xxxx | HDU_1561_The_more_The_Better |
| Codeforces | CF | xxxx(字母) | CF_1234C |
| OpenJ_Bailian | OpenJ_Bailian | xxxx | OpenJ_Bailian_1234 |
| POJ | POJ | xxxx | POJ_1234 |
| AtCoder | AC | abcxxx | AC_abc123 |
| SPOJ | SPOJ | xxxxx | SPOJ_PROBNAME |
| UVa | UVa | xxxxx | UVa_10000 |
| ZOJ | ZOJ | xxxx | ZOJ_1234 |
| 蓝桥杯 | 蓝桥杯 | xxxxx | 蓝桥杯_12345 |
| AcWing | AcWing | xxx | AcWing_285_没有上司的舞会 |

## 注意事项

- 遇到表中没有的 OJ 时，先确认前缀（优先用 OJ 官方缩写或通用中文称呼），然后**在此文件添加一行**
- 前缀保持稳定，不要随意更改（影响检索）
- 题名部分用英文缩写或中文，不要有空格，空格用 `_` 替换
- 目录名非法字符 `/\:*?"<>|` 删除，空格→`_`
