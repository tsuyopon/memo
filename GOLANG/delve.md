# 概要
delveはgo言語用のデバッガです。

go言語用のデバッガにはdelveやgdb, godebugといったいくつかの候補がありますが、go言語の場合には標準のgcコンパイラを使っているのでdelveを使った方が良いらしいです。
- (参考) https://kazuhira-r.hatenablog.com/entry/2021/02/13/234024


下記資料が最速でdelveを使う為にわかりやすかった。
- https://qiita.com/minamijoyo/items/4da68467c1c5d94c8cd7

delveのコマンドラインの使い方もほとんどコマンドの使い方はgdbと同じような感じです。

# インストール方法

### MACでbrewインストールする方法
以下を参考に手元のMacにdelveを入れる。
- https://github.com/go-delve/delve/blob/master/Documentation/installation/osx/install.md


下記で簡単にインストールできます。
```
$ brew install delve
```

以下に配置されるのでPATHに入れておくと良い
```
/usr/local/Cellar/delve/1.20.1/bin/dlv
```

バージョンは下記で確認できます。
```
$ dlv version
Delve Debugger
Version: 1.20.1
Build: $Id: 96e65b6c615845d42e0e31d903f6475b0e4ece6e $
```

# delveコマンド

### delveのヘルプを確認する
下記コマンドでdelveのヘルプのサブオプションを確認することができます。
```
$  dlv help
Delve is a source level debugger for Go programs.

Delve enables you to interact with your program by controlling the execution of the process,
evaluating variables, and providing information of thread / goroutine state, CPU register state and more.

The goal of this tool is to provide a simple yet powerful interface for debugging Go programs.

Pass flags to the program you are debugging using `--`, for example:

`dlv exec ./hello -- server --config conf/config.toml`

Usage:
  dlv [command]

Available Commands:
  attach      Attach to running process and begin debugging.
  connect     Connect to a headless debug server with a terminal client.
  core        Examine a core dump.
  dap         Starts a headless TCP server communicating via Debug Adaptor Protocol (DAP).
  debug       Compile and begin debugging main package in current directory, or the package specified.
  exec        Execute a precompiled binary, and begin a debug session.
  help        Help about any command
  run         Deprecated command. Use 'debug' instead.
  test        Compile test binary and begin debugging program.
  trace       Compile and begin tracing program.
  version     Prints version.

Flags:
      --accept-multiclient               Allows a headless server to accept multiple client connections via JSON-RPC or DAP.
      --allow-non-terminal-interactive   Allows interactive sessions of Delve that don't have a terminal as stdin, stdout and stderr
      --api-version int                  Selects JSON-RPC API version when headless. New clients should use v2. Can be reset via RPCServer.SetApiVersion. See Documentation/api/json-rpc/README.md. (default 1)
      --backend string                   Backend selection (see 'dlv help backend'). (default "default")
      --build-flags string               Build flags, to be passed to the compiler. For example: --build-flags="-tags=integration -mod=vendor -cover -v"
      --check-go-version                 Exits if the version of Go in use is not compatible (too old or too new) with the version of Delve. (default true)
      --disable-aslr                     Disables address space randomization
      --headless                         Run debug server only, in headless mode. Server will accept both JSON-RPC or DAP client connections.
  -h, --help                             help for dlv
      --init string                      Init file, executed by the terminal client.
  -l, --listen string                    Debugging server listen address. (default "127.0.0.1:0")
      --log                              Enable debugging server logging.
      --log-dest string                  Writes logs to the specified file or file descriptor (see 'dlv help log').
      --log-output string                Comma separated list of components that should produce debug output (see 'dlv help log')
      --only-same-user                   Only connections from the same user that started this instance of Delve are allowed to connect. (default true)
  -r, --redirect stringArray             Specifies redirect rules for target process (see 'dlv help redirect')
      --wd string                        Working directory for running the program.

Additional help topics:
  dlv backend  Help about the --backend flag.
  dlv log      Help about logging flags.
  dlv redirect Help about file redirection.

Use "dlv [command] --help" for more information about a command.
```

よくあるものを確認します。
- attach: 実行中のプロセスにアタッチする
- connect: ヘッドレスデバッグサーバーに接続する
- debug: カレントディレクトリまたは指定パッケージをコンパイルしてmainパッケージのデバッグを開始する
- exec: コンパイル済みのバイナリをデバッグする
- test: テストバイナリをコンパイルしてデバッグする
- trace: コンパイルしてトレーシングを始める


インタラクティブなインターフェイス側の利用可能なコマンドも表示できます。
```
(dlv) help
The following commands are available:

Running the program:
    call ------------------------ Resumes process, injecting a function call (EXPERIMENTAL!!!)
    continue (alias: c) --------- Run until breakpoint or program termination.
    next (alias: n) ------------- Step over to next source line.
    rebuild --------------------- Rebuild the target executable and restarts it. It does not work if the executable was not built by delve.
    restart (alias: r) ---------- Restart process.
    step (alias: s) ------------- Single step through program.
    step-instruction (alias: si)  Single step a single cpu instruction.
    stepout (alias: so) --------- Step out of the current function.

Manipulating breakpoints:
    break (alias: b) ------- Sets a breakpoint.
    breakpoints (alias: bp)  Print out info for active breakpoints.
    clear ------------------ Deletes breakpoint.
    clearall --------------- Deletes multiple breakpoints.
    condition (alias: cond)  Set breakpoint condition.
    on --------------------- Executes a command when a breakpoint is hit.
    toggle ----------------- Toggles on or off a breakpoint.
    trace (alias: t) ------- Set tracepoint.
    watch ------------------ Set watchpoint.

Viewing program variables and memory:
    args ----------------- Print function arguments.
    display -------------- Print value of an expression every time the program stops.
    examinemem (alias: x)  Examine raw memory at the given address.
    locals --------------- Print local variables.
    print (alias: p) ----- Evaluate an expression.
    regs ----------------- Print contents of CPU registers.
    set ------------------ Changes the value of a variable.
    vars ----------------- Print package variables.
    whatis --------------- Prints type of an expression.

Listing and switching between threads and goroutines:
    goroutine (alias: gr) -- Shows or changes current goroutine
    goroutines (alias: grs)  List program goroutines.
    thread (alias: tr) ----- Switch to the specified thread.
    threads ---------------- Print out info for every traced thread.

Viewing the call stack and selecting frames:
    deferred --------- Executes command in the context of a deferred call.
    down ------------- Move the current frame down.
    frame ------------ Set the current frame, or execute command on a different frame.
    stack (alias: bt)  Print stack trace.
    up --------------- Move the current frame up.

Other commands:
    config --------------------- Changes configuration parameters.
    disassemble (alias: disass)  Disassembler.
    dump ----------------------- Creates a core dump from the current process state
    edit (alias: ed) ----------- Open where you are in $DELVE_EDITOR or $EDITOR
    exit (alias: quit | q) ----- Exit the debugger.
    funcs ---------------------- Print list of functions.
    help (alias: h) ------------ Prints the help message.
    libraries ------------------ List loaded dynamic libraries
    list (alias: ls | l) ------- Show source code.
    source --------------------- Executes a file containing a list of delve commands
    sources -------------------- Print list of source files.
    transcript ----------------- Appends command output to a file.
    types ---------------------- Print list of types

Type help followed by a command for full documentation.
```

### 基本コマンド
以下に基本的なコマンドを
- 実行開始
  - r
- ブレークポイントの作成
  - break 関数名
  - break ファイル名:行数
  - b ファイル名:行数
- ブレークポイントの確認
  - breakpoints
  - bp
- 次のブレークポイントへの移動
  - continue
  - c
- 次の行へ移動する
  - next
  - n
- ステップイン
  - step
  - s
- ステップアウト
  - stepout
- ローカル変数の表示
  - locals
- 変数の表示
  - print 変数
- 変数の値の変更
  - set 変数 = 値
- スタックトレースの表示
  - stack
- スタックトレース上でデバッグを実行
  - frame 番号 コマンド
- コードの表示
  - ls 関数名
  - ls パッケージ.関数名
- 終了
  - exit
  - quit
  - q

上記以外にもヘルプ側に記載していますので、そちらも併せて参照してください。

### 非常に簡単な使い方
下記のソースコードmain.goがあるとする。
```
$ nl -b a main.go 
     1	package main
     2	
     3	import "fmt"
     4	
     5	func main() {
     6		msg := "hello world"
     7		fmt.Println(msg)
     8	}
```

コマンドラインでdlvの開始、ブレークポイント、continueやプロセスの終了までの簡単な流れを以下に示します。
```
$ dlv debug main.go 
Type 'help' for list of commands.
(dlv) b main.go:6
Breakpoint 1 set at 0x10ad058 for main.main() ./main.go:6
(dlv) r
Process restarted with PID 67387
(dlv) c
> main.main() ./main.go:6 (hits goroutine(1):1 total:1) (PC: 0x10ad058)
     1:	package main
     2:	
     3:	import "fmt"
     4:	
     5:	func main() {
=>   6:		msg := "hello world"
     7:		fmt.Println(msg)
     8:	}
     9:	
(dlv) n
> main.main() ./main.go:7 (PC: 0x10ad06d)
     2:	
     3:	import "fmt"
     4:	
     5:	func main() {
     6:		msg := "hello world"
=>   7:		fmt.Println(msg)
     8:	}
     9:	
(dlv) c
hello world
Process 67387 has exited with status 0
(dlv) q
```

### ローカル変数の確認
```
(dlv) locals
hoge = (unreadable could not read string at 0x1 due to protocol error E08 during memory read for packet $m1,6)
fuga = ""
```

### スタックトレースの表示とframeの表示
```
(dlv) bt
0  0x00000000010cb8cd in main.greeting
   at ./main.go:9
1  0x00000000010cb976 in main.main
   at ./main.go:14
2  0x000000000103b6e3 in runtime.main
   at /usr/local/Cellar/go/1.16.3/libexec/src/runtime/proc.go:225
3  0x000000000106eb01 in runtime.goexit
   at /usr/local/Cellar/go/1.16.3/libexec/src/runtime/asm_amd64.s:1371

(dlv) frame 1 locals # ./main.go:14 で localsを実行
name = "Bob"
```

### ブレークポイントを残したままでプロセスの再実行をしたい場合
```
(dlv) restart
Process restarted with PID 55704
(dlv) c
> main.main() ./hoge.go:6 (hits goroutine(1):1 total:1) (PC: 0x1087122)
     1:    package main
     2: 
     3:    import "fmt"
     4: 
     5:    func main() {
=>   6:     fmt.Println("start")
     7: 
     8:        a := Hoge("main")
     9: 
    10:        fmt.Println(a)
    11: 
```

# 単体テストでのデバッグ

### 簡単なテストをデバッグしてみる。
以下のテストコードをdelveでデバッグすることを考えます。
```
func TestHoge(t *testing.T) {
    tests := []struct {
        in  string
        out string
    }{
        {"1", "1hogefuga"},
        {"tmp", "tmphogefuga"},
    }

    for _, v := range tests {
        out := Hoge(v.in)
        if out != v.out {
            t.Errorf("input %s\n, get %s\n, want %s\n", v.in, out, v.out)
        }
    }
}
```

上記のテストコードをデバッグする場合にはdlv testを実行します。
テストを実行する場合には「go test -run TestHoge」と実行しますが、デバッガで実行する場合には「-test.run」オプションを付与してください。
```
$ dlv test -- -test.run TestHoge
(dlv) 
```

(参考) https://christina04.hatenablog.com/entry/2017/07/16/094140


# トラブルシュート

### バイナリに対して実行したら変数が表示されない

delveはdlv exec <binary>と実行すればバイナリに対してもデバッグできます。
しかしgoのビルドは通常だと最適化され、実行された関数や変数の値はレジスタへ保存されるためにそのままでは下記のように表示できません。
```
(dlv) locals
(no locals)
```

バイナリ生成のビルド時には最適化を無効にするために下記オプションを付与することで、生成されたELFが最適化されることもありません。
```
$ go build -gcflags '-N -l' 
```


# 公式ドキュメント
- delveソースコード(github) ドキュメントの記載もあり
  - https://github.com/go-delve/delve
- delve(v1.20.1)
  - https://github.com/go-delve/delve/blob/v1.20.1/Documentation/usage/dlv.md
- Debugging Go Code with GDB (こちらはGDBについてです。一応、リンクを載せておきます)
  - https://go.dev/doc/gdb
 
