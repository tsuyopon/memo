# 概要
vimのpluginであるproject.vimに関する説明

### インストール
インストールは次の通り
```
$ wget http://www.vim.org/scripts/download_script.php?src_id=6273
$ tar zxvf download_script.php?src_id=6273 -C $HOME/.vim/
```

起動方法
```
:Project
```

project.vimは起動後に
```
$HOME/.vimprojects
```
という設定ファイルを読み込みます。 この設定ファイルは以下で述べるインタラクティブな操作により作成することが可能です。

### 指定したディレクトリのファイルを登録する
起動後に
```
\c(小文字のC)  又は \C(大文字のc)
```
をタイプするとインタラクティブなウィザードが開始されます。 COLOLR(red): 指定したディレクトリ配下を再帰的に取得するのは\C(大文字のc)の方で、\c(小文字のc)は指定した階層のファイルしか取得しない。\Cの方が一般的によく利用するだろう。
- プロジェクト名
- プロジェクト配下とするディレクトリ(絶対パス)
- gmake等を実行する際に移動するディレクトリ
- 取得するファイル名 以上の４項目を指定します。


### ディレクトリ内部を更新する
ディレクトリ部分にカーソルをあて、下記コマンドをタイプすることによりファイルを更新することが可能です。
```
\r(小文字のR) 又は \R(大文字のR)
```
尚、\R(大文字のR)の方は再帰的にディレクトリ内部のファイルを更新してくれます。

### 検索機能
再帰的に一括grepをするのは\Gで、カレントディレクトリからgrepするのは\gです。
```
\g(小文字のG) 又は \G(大文字のG)
```

# 参考URL
- project.vimダウンロード
 - http://www.vim.org/scripts/script.php?script_id=69
- project.vimを導入する
 - http://blog.kaihatsubu.com/?p=1438
 - http://onlineconsultant.jp/pukiwiki/?vim%20Project%E3%82%92%E5%B0%8E%E5%85%A5%E3%81%99%E3%82%8B
