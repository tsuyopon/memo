# 概要
editorconfigとは、Indent、改行コード、文字コード、コーディングスタイルに関するエディタの設定を異なるエディタ間で共有するための規格です。
.editorconfigという設定ファイルをプロジェクトのディレクトリに配置しておくだけで、自動的にエディタの設定として反映されます。
これは複数人で関わるプロジェクトの場合でも同じ設定で開発できるという利点があります。

以下の様なエディタにも対応しています。エディタによってはプラグインをインストールする必要があります。
- Vim
- Emacs
- Atom
- Sublime Text
- Brackets
- WebStorm
- Coda
- Apache Ant
- Gradle
- Maven
- (他にもたくさん)

上記は一例ですが、どのエディタに対応しているかは下記の公式サイトで確認してください。
- https://editorconfig.org/#download

最初に入門として読むべきとしては下記が良いと思います。
- https://qiita.com/yama-github/items/f4af3b3a0c00306bbb17

# 詳細

### .editorconfigサンプル

```
# 最上位のEditorConfigファイル (.editorconfigは上位ディレクトリを探索するが、「root=true」があるとそこで探索を終了する)
root = true

# 各ファイルの末尾に改行を入れるUnixスタイルの改行
[*]
end_of_line = lf
insert_final_newline = true

# 波括弧展開記法を使用して複数のファイルに一致
# デフォルトの文字セットを設定
[*.{js,py}]
charset = utf-8

# 4スペースのインデント
[*.py]
indent_style = space
indent_size = 4

# タブによるインデント（サイズは指定されていない）
[Makefile]
indent_style = tab

# libディレクトリ内のすべてのJSファイルのインデントオーバーライド
[lib/**.js]
indent_style = space
indent_size = 2

# package.jsonまたは.travis.ymlという正確なファイル名に一致した場合に適用される
[{package.json,.travis.yml}]
indent_style = space
indent_size = 2
```

- \[\]はセクション名です。ファイルパスのグロブパスとして記述され、大文字と小文字を区別します。
- コメントは独立した行に記述が必要です。
- UTF-8エンコードで記述します、改行区切りはCRLF、またはLFを使用します。

### .editorconfigはどこに配置すべきか?
エディタでファイルを開くと、EditorConfigプラグインは開いたファイルのディレクトリおよびすべての親ディレクトリ内の.editorconfigを探索します。
.editorconfigの探索は最上位のディレクトリに到達するか、「root=true」と指定された.editorconfigファイルが見つかると探索を停止します。


### ワイルドカード
ワイルドカード記法については下記を参照のこと
```
*              パスセパレータ（/）を除く任意の文字列に一致
**             パスセパレータ（/）も含めた任意の文字列に一致。下層のディレクトリも含めたマッチング
?              任意の1文字に一致
[name]         n,a,m,e の任意の1文字に一致
[!name]        n,a,m,e に含まれない任意の1文字に一致
{s1,s2,s3}     指定された文字列のいずれかに一致（カンマで区切られる） (EditorConfig Core 0.11.0以降で利用可能)
{num1..num2}   num1とnum2の間の任意の整数に一致。 num1とnum2は正または負のいずれか
```

複数の場合には中カッコで囲む必要があります。以下の例を見てください。
```
[*.{css,scss,js,ts}]        正しい書き方
[{*.css,*.scss,*.js,*.ts}]  正しい書き方
[*.css,*.scss,*.js,*.ts]    認識されない書き方
```


### プロパティ
正式な資料は下記を参照してください。
- https://github.com/editorconfig/editorconfig/wiki/EditorConfig-Properties

エディタによってプロパティがサポートされないこともあるらしいので注意してください。
- indent_style
  - ハードタブまたはソフトタブを使用するために tab または space を設定します。
- indent_size
  - 各インデントレベルに使用される列数とソフトタブの幅を定義する整数。 tab に設定すると、tab_width（指定されている場合）の値が使用されます。
- tab_width
  - タブ文字を表すために使用される列数を定義する整数。これはデフォルトで indent_size の値となり、通常は指定する必要はありません。
- end_of_line
  - 改行の表現方法を制御するために lf、cr、または crlf を設定します。
- charset
  - 文字セットを制御するために latin1、utf-8、utf-8-bom、utf-16be、または utf-16le を設定します。
- trim_trailing_whitespace
  - 改行文字の前にある空白文字を削除するために true を設定し、削除しないようにするために false を設定します。
- insert_final_newline
  - ファイルを保存する際に末尾に改行を追加するために true を設定し、追加しないようにするために false を設定します。
- root
  - 親ディレクトリの .editorconfig ファイルの検索を停止するために root=true を設定します。これを指定しないと親ディレクトリを探索し続けます。


以下、特記事項
- プロパティとその値は大文字と小文字を区別しない。
- 任意のプロパティに対して「unset」という値を設定することで、そのプロパティ効果を削除できます。


# 公式資料
- 公式サイト
  - https://editorconfig.org/
- 公式ドキュメント
  - https://spec.editorconfig.org/
- プロパティに関する説明
  - https://github.com/editorconfig/editorconfig/wiki/EditorConfig-Properties

# 参考資料
- https://qiita.com/yama-github/items/f4af3b3a0c00306bbb17
