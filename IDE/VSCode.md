# 概要
VSCodeについて

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
- request: デバッグ実行のモード(launchかattach)
- program: デバッグ対象のプログラムのパス
- console: デバッグの結果を出力するコンソール
- cwd: 現在の作業ディレクトリ
- args: デバッグ実行時に渡される引数
- port: 


なお、事前に定義された変数を利用することが可能です。
```
${file}: 現在開いているファイルのパス
${fileBasename}: 現在開いているファイル名
${workspaceFolder}: VSCodeで開いているフォルダのパス
${workspaceFolderBasename}: VSCodeで開いているフォルダ名
${cwd}: 現在の作業ディレクトリ
```


## launch.jsonを利用した実行方法について
以下を参考のこと
- https://amateur-engineer-blog.com/vscode-launchjson/

