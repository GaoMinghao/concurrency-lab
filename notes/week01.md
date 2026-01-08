# week01
RAII：thread_guard 最好用 std::move 接管所有权，防止悬空引用。

Stop Token：用 std::condition_variable_any 配合 stop_token 可以实现“可中断的等待”。

Detach：除非你确定线程完全独立且不需要与主程交互（如后台日志收集），否则避免使用 detach，因为它会让你失去对线程生命周期的控制。