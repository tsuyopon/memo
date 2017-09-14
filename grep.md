# 概要
grepコマンドに関するtipsなど

# 詳細
### 特定のディレクトリや特定のファイルを検索対象から除外する場合
```
$ export GREP_OPTIONS="--exclude-dir=.git --exclude-dir=doc --exclude-dir=experimental --exclude=cscope.out --exclude=tags"
```
