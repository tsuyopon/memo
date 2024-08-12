# shellcheckについて
shellcheckはシェルスクリプトの静的解析のlintツールです。

# 試してみる
MacOSなので下記でインストール可能です
```
brew install shellcheck
```

実行するには下記の様に引数にシェルスクリプト与えるだけです。
```
$ shellcheck foo.sh

In foo.sh line 3:
x = 10
  ^-- SC2283 (error): Remove spaces around = to assign (or use [ ] to compare, or quote '=' if literal).


In foo.sh line 4:
echo ${x}
     ^--^ SC2154 (warning): x is referenced but not assigned.
     ^--^ SC2086 (info): Double quote to prevent globbing and word splitting.

Did you mean:
echo "${x}"

For more information:
  https://www.shellcheck.net/wiki/SC2283 -- Remove spaces around = to assign ...
  https://www.shellcheck.net/wiki/SC2154 -- x is referenced but not assigned.
  https://www.shellcheck.net/wiki/SC2086 -- Double quote to prevent globbing ...
```

なお、特定のエラーを無視するにはeオプションで指定できます。
```
$ shellcheck -e SC2154 foo.sh
```

毎回当てるのが面倒な場合には環境変数でも指定することが可能です。
```
$ export SHELLCHECK_OPTS="-e SC2059 -e SC2034 -e SC1090"
$ shellcheck foo.sh
```


# 詳細

### 深刻度について
深刻度によって以下の4種類が定められています。
- error
- warning
- info
- style


検出される深刻度のレベルを指定する場合には--sevirityオプション(-Sオプション)を指定します。
```
$ shellcheck script.sh -S warning
```

### shellcheckが検出するエラーメッセージ一覧
以下を参照してください
- https://www.shellcheck.net/wiki/

### 出力フォーマットを指定する
--formatオプションで指定できる。選べるフォーマットは「tty、json、checkstyle、gcc」だ。
```
$ shellcheck --format=gcc xxx.sh
```

- ttyの場合のエラーメッセージ例
```
In example.sh line 1:
echo $0
^-- SC2148: Tips depend on target shell and yours is unknown. Add a shebang.
     ^-- SC2086: Double quote to prevent globbing and word splitting.
```
- jsonの場合のエラーメッセージ例(jq補正しています)
```
[
  {
    "file": "example.sh",
    "line": 1,
    "endLine": 2,
    "column": 1,
    "endColumn": 1,
    "level": "error",
    "code": 2148,
    "message": "Tips depend on target shell and yours is unknown. Add a shebang."
  },
  {
    "file": "example.sh",
    "line": 1,
    "endLine": 1,
    "column": 6,
    "endColumn": 8,
    "level": "info",
    "code": 2086,
    "message": "Double quote to prevent globbing and word splitting."
  }
]
```
- checkstyleの場合のエラーメッセージ例
```
<?xml version='1.0' encoding='UTF-8'?>
<checkstyle version='4.3'>
<file name='example.sh' >
<error line='1' column='1' severity='error' message='Tips depend on target shell and yours is unknown. Add a shebang.' source='ShellCheck.SC2148' />
<error line='1' column='6' severity='info' message='Double quote to prevent globbing and word splitting.' source='ShellCheck.SC2086' />
</file>
</checkstyle>
```
- gccの場合のエラーメッセージ例
```
example.sh:1:1: error: Tips depend on target shell and yours is unknown. Add a shebang. [SC2148]
example.sh:1:6: note: Double quote to prevent globbing and word splitting. [SC2086]
```

# 公式資料
- 公式ポータル
  - https://www.shellcheck.net/
- github
  - https://github.com/koalaman/shellcheck

