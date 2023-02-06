# 概要
VSCodeについて

# ショートカットについて

### 基本ショートカット
- https://skillhub.jp/blogs/234

### ソースコードを読む際のショートカット
- F12: カーソル上にある名前を持つクラスや関数、変数などの定義元に移動する

### デバッガ実行の際のショートカット

- F9:  停止したい行で押下することでブレークポイントを設定できる
  - ブレークポイントにはいくつか種類があり、ソースコードの左側を右クリックで選択できます。
- F10: 現在の行の処理を実行し、次の行で停止する(step over)
- F11: 現在の行の実行が関数の場合、その関数の中でステップ実行に進む(step in)
- Shift + F11: 現在実行中の関数が終わるまで進み、呼び出し元関数で停止する(step out)
- Cmd + Shift + F5: 再実行する。つまり、デバッグ実行しているプログラムを再起動する。
- Shift + F5: デバッグ実行しているプログラムを停止する。


# launch.jsonについて
launch.jsonはVSCodeでデバッグ実行するための設定ファイルです。

詳細は下記の公式ドキュメントを参照してください。
```
https://code.visualstudio.com/docs/editor/debugging#_launch-configurations
```

プロジェクトの作業ディレクトリやworkspace直下に.vscode/launch.jsonを配置することが一般的です。

## launch.jsonに記載する項目について

- name: デバッグ実行の名前です。画面に表示するわかりやすい識別子を付与します。
- type: 使用するDebugger
- request: デバッグ実行のモード。以下の重要な値を指定する。
  - launch: デバッグ時にプログラムを起動するか
  - attach: 既に起動しているプログラムにデバッガーをアタッチするか
- program: デバッグ対象のプログラムのパス
- console: デバッグの結果を出力するコンソール。以下の値が指定できる。
  - internalConsole: デバッグコンソールタブで実行される
  - integratedTerminal: ターミナルタブで実行される
- cwd: 現在の作業ディレクトリ
- args: デバッグ実行時に渡される引数
- port: 


なお、事前に定義された変数を利用することが可能です。
```
${workspaceFolder}: VSCodeで開いているフォルダのパス(フルパスが含まれる)
${workspaceFolderBasename}: VSCodeで開いているディレクトリ名
${file}: 現在開いているファイルのパス(フルパスを指定)
${fileBasename}: 現在開いているファイル名${file}のファイル名情報(パスは含まない)
${relativeFile}: ワークスペース(${workspaceFolder})から${file}へのパス
${fileBasenameNoExtension}: ${file}から拡張子を除外したもの
${fileDirname}: ${file}のディレクト名
${fileExtname}: ${file}の拡張子
${cwd}: 現在の作業ディレクトリ
```

### request属性が「launch」の場合にサポートされる属性
- program: 起動するプログラムのパス
- args: デバッグ実行時にプログラムに渡す引数
- cwd: デバッグ実行を行うディレクトリ
- env: 環境変数の指定
- envFile: 環境関数を定義したファイル
- console: プログラムを起動するコンソールの種類を指定
- runtimeExecutable: 使用するランタイム環境
- runtimeArgs: ランタイム環境に渡す引数


### request属性が「attach」の場合にサポートされる属性
- processId: アタッチするプロセスのプロセスID


## launch.jsonを利用した実行方法について
以下を参考のこと
- https://amateur-engineer-blog.com/vscode-launchjson/


### ステップイン実行時に除外したいファイルを指定する
skipFilesにglob形式でステップインで参照してほしくないファイルを記載することができます。
- 参考: https://github.com/isaacs/node-glob
```
{
  "version": "0.2.0",
  "configurations": [
    {
      …… 省略 ……
      "skipFiles": [
        "<node_internals>/**/*.js"
      ]
    },
    {
      …… 省略 ……
    }
  ]
}
```

なお、上記で使っている「<node_internals>」はNode.jsの組み込みコアモジュールを参照する「マジックネーム」となっている。


# 外部資料参考
- Visual Studio Codeデバッグ入門
  - https://atmarkit.itmedia.co.jp/ait/subtop/features/dotnet/all.html#xe789b9e99b86efbc9aVisualStudioCodee38387e38390e38383e382b0e585a5e99680
