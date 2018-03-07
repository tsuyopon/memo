# 概要
ApacheのHookについての基礎知識メモ

# 詳細

### デフォルトで読み込まれるハンドラ
DocumentRoot配下にファイルがあればそれを返すといった処理を行っているのがdefault_handlerとなる。
```
httpd-2.4.23/server/core.c: default_handler
```

### hookの順番について
```
APR_HOOK_REALLY_FIRST 	-10 	どれよりも先に実行したい
APR_HOOK_FIRST 	0 	先頭グループ
APR_HOOK_MIDDLE 	10 	中間グループ
APR_HOOK_LAST 	20 	最終グループ
APR_HOOK_REALLY_LAST 	30 	どれよりも後に実行したい
```
