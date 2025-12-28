# C++ 并发训练计划 v2.0（Repo Skeleton 版，10 周 × 10 小时/周，C++20）

主教材：你提供的《C++ Concurrency in Action（2nd）》中英文版  
补充资料（仅两类）：
- cppreference：查语义（thread/mutex/condvar/atomic/<execution> 等）
- C++ Core Guidelines（并发条款）：作为 code review checklist

---

## 0. 总体规则与交付物

### 每周固定工作流（10 小时）
- **2h 阅读**：只读本周指定小节；输出“10 条卡片”（规则/坑/模板/禁忌）
- **6h 实验编码**：本周 Lab（必须可运行、可复现、可对比）
- **1h 正确性验证**：TSan + 压测（让 bug 暴露）
- **1h 性能证据链**：至少一次 profiling（perf/hotspot 等）+ 一句话结论

### 每周统一交付物（强制）
- `labs/weekXX/`：本周代码（每个 lab 独立目录）
- `notes/weekXX.md`：10 条卡片 + 复盘（本周最易错 3 件事 + 避免策略）
- `results/weekXX.txt`：TSan/bench/profiling 输出摘要（必须含命令与关键结论）

---

## 1. 仓库结构（建议直接照搬）

```
concurrency-lab/
  CMakeLists.txt
  cmake/
  include/
  src/
  tests/
  bench/
  labs/
    week00/
    week01/
    ...
    week10/
  notes/
    week00.md
    week01.md
    ...
    week10.md
    templates/
      week_notes_template.md
      lab_readme_template.md
      results_template.txt
      hb_diagram_template.md
      profiling_template.md
  results/
    week00.txt
    week01.txt
    ...
    week10.txt
  scripts/
    build_release.sh
    build_tsan.sh
    run_tests.sh
    run_bench.sh
    run_tsan.sh
    run_profile_perf.sh
    env_check.sh
  third_party/
    (optional) googletest/
    (optional) benchmark/
  README.md
```

---

## 2. 一键命令规范（脚本占位符）

> 你可以把下面这些命令写进 `scripts/`，并在每周 `results/weekXX.txt` 里粘贴“实际执行命令 + 关键输出”。

### 构建
- `scripts/build_release.sh`
  - 目标：`-O3`（或 `Release`），用于性能
- `scripts/build_tsan.sh`
  - 目标：`-fsanitize=thread -fno-omit-frame-pointer -O1/-O2`，用于正确性

### 运行
- `scripts/run_tests.sh`
- `scripts/run_bench.sh`
- `scripts/run_tsan.sh`
  - 规则：只要涉及共享状态实验，就必须跑一次 TSan
- `scripts/run_profile_perf.sh`
  - 规则：Week 0 起每周至少一次 profiling（perf/hotspot 任一）

---

## 3. 每周笔记模板（统一格式）

### `notes/templates/week_notes_template.md`
复制为：`notes/weekXX.md`

```markdown
# Week XX：<主题>

## 1) 本周阅读范围
- Book: <章节/小节>
- Supplemental: <仅当需要时填写>

## 2) 10 条卡片（必须）
1. Rule:
2. Pitfall:
3. Template:
4. ...
10.

## 3) 本周 Labs（链接到 labs/weekXX）
- Lab A: <目的> | 关键点: <...>
- Lab B: <目的> | 关键点: <...>

## 4) 正确性（TSan/单测/断言）
- 运行命令：
- 结果摘要：
- 一个“我原以为 vs 实际发生”：

## 5) 性能证据链（profiling）
- 工具：perf/hotspot/其它
- 运行命令：
- 关键发现：
- 一句话结论：<慢在锁等待/调度/缓存/计算之一>

## 6) 本周最易错 3 件事（必须）
1)
2)
3)

## 7) 下周入口（下一步我会做什么）
- <一条即可>
```

---

## 4. 结果记录模板（统一格式）

### `notes/templates/results_template.txt`
复制为：`results/weekXX.txt`

```text
Week XX Results

[Build]
- Release cmd:
- TSan cmd:

[Test]
- cmd:
- summary:

[TSan]
- cmd:
- summary:
- link/snippet:

[Bench]
- cmd:
- summary (throughput/p50/p99):

[Profiling]
- cmd:
- summary (hot functions / lock wait evidence):

[Conclusion]
- correctness:
- performance:
- next action:
```

---

## 5. 内存模型画图模板（Week 6 专用）

### `notes/templates/hb_diagram_template.md`
复制到：`notes/week06_hb_diagrams.md` 或粘入 `notes/week06.md`

```markdown
# Happens-Before Diagram Template

## Scenario
- threads:
- shared vars:
- goal:

## Events (label them)
Thread A:
- A1:
- A2:
Thread B:
- B1:
- B2:

## Relations
- synchronizes-with:
- happens-before:
- reads-from:
- allowed reorders:
- forbidden reorders:

## Explanation (plain language)
- what I expected:
- what is allowed:
- what changed after release/acquire:
```

---

## 6. Profiling 模板（Week 0 起每周使用一次）

### `notes/templates/profiling_template.md`
```markdown
# Profiling Note

## Tool & command
- tool:
- command:

## What I looked for
- lock contention?
- context switches?
- cache misses?
- cpu cycles in what function?

## Findings
- hot path:
- waiting evidence:
- change I will try next:
```

---

## 7. 10 周计划（v2.0 完整版，按 week 映射到 repo）

> 每周都要把“本周 Labs”落在 `labs/weekXX/`，把“笔记/结果”落在 `notes/` 与 `results/`。

---

## Week 0：基线工程 + 正确性/性能闭环
### 目标
- 一键跑通：Release（性能）+ TSan（正确性）+ profiling（证据链）

### Labs（在 `labs/week00/`）
- Lab 00A：故意制造 data race → TSan 报告 → 修复到 clean
- Lab 00B：perf/hotspot 跑通：能生成一个热点视图

### 验收
- [ ] TSan 能报、能修
- [ ] profiling 能出图/出热点

---

## Week 1：线程生命周期（Ch2）+ C++20 `jthread/stop_token`
### Labs（`labs/week01/`）
- Lab 01A：`thread_guard` + 异常路径反例
- Lab 01B：`std::jthread` 重写并对比
- Lab 01C：`stop_token` 可控停止最小例

### 验收
- [ ] 能区分 join/detach/jthread 的责任与风险

---

## Week 2：共享数据与接口竞态（Ch3.1–3.2.3）
### Labs（`labs/week02/`）
- Lab 02A：data race 最小复现（TSan）
- Lab 02B：接口竞态（check-then-act / 泄露引用）
- Lab 02C：线程安全容器雏形（不返回引用/指针；try_* 接口）

### 验收
- [ ] 能解释“保护对象不变量”的边界

---

## Week 3：死锁与 `unique_lock`（Ch3.2.4–3.2.7）
### Labs（`labs/week03/`）
- Lab 03A：ABBA 死锁复现（naive swap）
- Lab 03B：`std::lock + defer_lock` 修复版
- Lab 03C：`scoped_lock` 简化版
- Lab 03D：缩短临界区（锁内快照→锁外重活→锁内回写）
- Lab 03E：`unique_lock` 所有权转移（move）

### 验收
- [ ] 能列出 unique_lock 灵活点及代价

---

## Week 4：阻塞同步（Ch4）+ C++20 `atomic::wait/notify`
### Labs（`labs/week04/`）
- Lab 04A：`blocking_queue<T>`（wait(predicate)+压力测试）
- Lab 04B：busy-wait 起跑门 → `atomic<bool>::wait/notify_all`
- Lab 04C：队列关闭 + `stop_token` 退出语义

### 验收
- [ ] 能解释 wait 的 unlock/睡眠/唤醒/再 lock 流程与原因

---

## Week 5：任务抽象与并行算法（thread pool + `<execution>`)
### Labs（`labs/week05/`）
- Lab 05A：最小 thread pool + `packaged_task/future`（含异常透传）
- Lab 05B：并行算法对比：seq vs pool vs `execution::par`
  - 记录：代码量/可控性/是否真的并行/性能趋势

### 验收
- [ ] 形成“优先高抽象，必要时下沉”的工程策略

---

## Week 6：内存模型与原子（Ch5）两段式（预警周）
### Labs（`labs/week06/`）
- Lab 06A（必须）：message passing（relaxed vs release/acquire vs seq_cst）
- Lab 06B（必须）：画 happens-before 图（用模板）
- Lab 06C（选做）：RMW（fetch_add 等）与 `acq_rel` 的必要性实验
- Lab 06D（选做）：可视化辅助材料（如演讲）对应到你的图与代码

### 验收
- [ ] 能复述：relaxed 原子性；release/acquire 发布订阅；seq_cst 最强

---

## Week 7：锁式并发数据结构（Ch6）+ Profiling（锁竞争证据）
### Labs（`labs/week07/`）
- Lab 07A：threadsafe queue（粗锁）
- Lab 07B：threadsafe queue（细锁：头尾分离或分段锁）
- Lab 07C（强制）：perf/hotspot 对比两版，给出“等待锁证据”

### 验收
- [ ] 能用证据解释：细锁为何不一定更快

---

## Week 8：并发设计与性能（Ch8 前半）+ False Sharing 强制 Lab
### Labs（`labs/week08/`）
- Lab 08A（强制）：False Sharing 计数器
  - 相邻变量写 → 慢
  - alignas(64)/hardware interference size 修复 → 快
- Lab 08B：任务划分实验（数据并行 vs 任务并行）

### 验收
- [ ] 能解释“写不同变量也互相拖慢”的一致性机制原因

---

## Week 9：无锁入门（Ch7）——锁定 SPSC
### Labs（`labs/week09/`）
- Lab 09A：SPSC ring buffer（固定容量，无锁）
- Lab 09B：对比 blocking_queue：吞吐/尾延迟趋势 + 解释差异来源

### 验收
- [ ] 能解释无锁代价：cache coherence + 原子序 + 回收复杂度

---

## Week 10：Capstone（量化风格流水线工程）
### 项目（`labs/week10/`）
三阶段流水线（mock 数据即可）：
- Stage A：producer（模拟行情）
- Stage B：workers（rolling/VWAP/统计）
- Stage C：collector（聚合输出/落盘/日志）

### 强制要求
- [ ] 至少一段用 `blocking_queue`（condvar）
- [ ] 至少一段用 SPSC ring buffer（无锁）
- [ ] 停止机制贯穿：`stop_token` + 队列关闭语义
- [ ] TSan clean + 压测跑通
- [ ] profiling 给出热点/等待证据 + 一句话结论

### 验收
- [ ] 能完整解释：无 data race/无死锁；内存序为何足够；瓶颈在哪里

---

## 8. 从现在开始的接入建议（你当前在 Ch3.2.6）
建议直接从 **Week 3** 执行：
- 阅读：3.2.4–3.2.7（重点 3.2.6）
- 编码：swap 三版 + 临界区缩短 + 所有权转移
- 正确性：TSan / 死锁复现与修复对比
- 复盘：`notes/week03.md`（10 条卡片 + 3 个坑）
