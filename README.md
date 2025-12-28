# concurrency-lab (C++20)

这是一个用于《C++ Concurrency in Action》配套训练的工程骨架（支持：Release / TSan / 单测 / 基准 / profiling 记录）。

## 目录结构
- `labs/weekXX/`：每周实验代码（你按计划填充）
- `notes/`：每周笔记（10 条卡片 + 复盘）
- `results/`：每周结果摘要（TSan / bench / profiling）
- `scripts/`：一键构建与运行脚本
- `src/`：可复用的基础代码（可选）
- `tests/`：可复用的单测基建（可选）
- `bench/`：可复用的基准基建（可选）

## 快速开始（Linux / macOS）
1) Release 构建
```bash
./scripts/build_release.sh
./scripts/run_tests.sh
```

2) TSan 构建（抓 data race）
```bash
./scripts/build_tsan.sh
./scripts/run_tsan.sh
```

3) 运行基准（可选）
```bash
./scripts/run_bench.sh
```

4) Profiling（perf 示例；需要 Linux + perf）
```bash
./scripts/run_profile_perf.sh build/release/bin/example_app
```

## 依赖策略
- 本骨架默认不强制拉取第三方依赖。
- 如果你希望启用 gtest / google benchmark，可在 `third_party/` 放入源码或改为 FetchContent（见 `CMakeLists.txt` 的注释）。
