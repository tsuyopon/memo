# 概要
ftraceとはLinuxカーネルに組み込まれているトレース機能です。  
動作中のカーネルイベントを記録してログを採取することができます。

# 使い方
debugfsにマウントします。
```
# sudo mount -t debugfs nodev debugTest/
# ls debugTest/
# ls
```

これによって/sys/kernel/debug/tracing配下に、traceで使用するファイルがマウントされる。
```
# ls /sys/kernel/debug/tracing/
available_events            buffer_total_size_kb   events                    kprobe_events   printk_formats       set_event           snapshot            trace          trace_pipe           tracing_on
available_filter_functions  current_tracer         free_buffer               kprobe_profile  README               set_ftrace_filter   stack_max_size      trace_clock    trace_stat           tracing_thresh
available_tracers           dyn_ftrace_total_info  function_profile_enabled  options         saved_cmdlines       set_ftrace_notrace  stack_trace         trace_marker   tracing_cpumask      uprobe_events
buffer_size_kb              enabled_functions      instances                 per_cpu         saved_cmdlines_size  set_ftrace_pid      stack_trace_filter  trace_options  tracing_max_latency  uprobe_profile
```

利用可能なトレーサー種別を確認する。
```
# cat /sys/kernel/debug/tracing/available_tracers
blk mmiotrace wakeup_dl wakeup_rt wakeup function nop
```

current_tracerにトレーサを登録する
```
# echo function > /sys/kernel/debug/tracing/current_tracer
```

トレース開始、トレースするプログラムの実行、トレース終了まで
```
トレース開始
# echo 1 > /sys/kernel/debug/tracing/tracing_on

トレースするコマンド実行
# ls

トレース終了
# echo 0 > /sys/kernel/debug/tracing/tracing_on
```

トレースログを採取して確認する。
```
# cat /sys/kernel/debug/tracing/trace_pipe > trace.log
```

# 参考URL
- ftrace関連でやくにたつカーネルオプション
  - http://qiita.com/mhiramat/items/c73edd8f9d3f15a6adca
- ftraceでカーネルの一部をおいかける方法
  - http://qiita.com/mhiramat/items/42a6af4f3c289ad37095
