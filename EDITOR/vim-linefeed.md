# 概要
vimでの改行コードの取り扱いについて

# 詳細

### 開いたファイルの改行コードを確認する
```
:set fileformat?
:set ff?
```

### 改行コードを変換する
```
:set ff=dos
:set ff=mac
:set ff=unix
```

### 改行コードを指定して開く
- LF
```
:edit ++fileformat=unix
```
- CRLF
```
:e ++ff=dos
```
- CR
```
:e ++ff=mac
```

### 改行コードを削除する
```
:%s/\r//g
```
