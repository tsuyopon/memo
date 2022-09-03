# 概要
IntelliJについてのメモ

# MAC
以下のメモ。動画を見ないとUIからどの様に操作すれば良いのかがわからないので非常に良い。
- https://www.udemy.com/course/poco-tech-intellij/

## 超基本(セクション1
- なんでも検索対象とする (これだとクラスだけ、ファイル名だけなどは絞れないので別途ショートカットを学ぶ必要があります)
  - Shiftを２回連続で押下する
- 左のプロジェクトのファイルレイアウト部分を閉じる
  - Command + 1
    - クラス側にカーソルがあるときには一度「Command + 1」を押下するとプロジェクト側にカーソルが移り、再度「Command + 1」を押下するとプロジェクトが閉じる
    - なお、カーソルをクラスに戻す場合には「ESC」を押すと良い
- 選択したファイルが左側のプロジェクトのレイアウトでフォーカスされる様になっていてほしい
  - 「歯車マーク」 -> 「Always Select Opened File」をクリック
  - これはデフォルトで有効になっていて欲しい機能ですが、有効になっていないので注意が必要です。

## ソースコードを読むために必要なショートカット(セクション2)
- メソッドやクラスの定義に移動する。呼び出し箇所に移動する。
  - Command + B
- 実装に移動する
  - Command + Option + B
- 先ほどの場所に戻る
  - Command + [
- 先ほどの場所に進
  - Command + ]
- 最近開いたファイル
  - Command + E
  - さらに最近編集したファイルを表示するには"もう一度"「Command + E」を押すことで表示される
- テストクラスとテスト対象クラスを行き来する
  - Shift + Command + T

## コーディング時に便利なショートカット(セクション3)
- コメントアウトをする・解除する(HTMLなどもHTML記法でコメントしてくれる)
  - Command + /
- 行の削除
  - Command + delete
- 行の複製
  - Command + D
- マルチカーソル (by クリック)
  - Option + Shift + マウスでクリック
  - で複数操作したい箇所にクリックする。その後、文字入力等を１度行うことで複数行に対しておこなうことができる。
- マルチカーソル (by キーボード)
  - Option を２度押して、２度目を押しっぱなしにする。その後、上矢印キーや下矢印キーでどこの行までを対象とするかを指定し、その後文字の入力や削除を一括で行うことができる様になります。
- Postfix Completion (後方置換) 
  - 後ろから記述することでifやnotなどの補完を行ってくれる (Udemyの動画を見た方がわかるかも)
  - どのようなものがあるかは以下で確認できる
    - 「Preferences」 -> 「Editor」 ->「General」->「Postfix Completion」でどのような後方置換が利用できるのかを確認することができます。
    - if, not, opt, return, soutあたりは便利らしい
    - 参考: https://qiita.com/chenglin/items/3c5380187bac263f13b3
- メソッドへの引数パラメータ情報を表示する
  - Command + P
- 現在扱っている型情報を表示する
  - Ctrl + Shift + P
    - 特にメソッドチェーンを扱っている場合などに自分が何の型を操作しているのかわからなくなるような場合に利用する
- Auto Importの自動追加を行う
  - Opt + Enter
    - インポートされていないライブラリの文字列が記載された箇所に移動して上記コマンドを実行します。
- Optimize Import
  - Ctrl + Option + O
    - コードをコメントアウト等すると不要になったライブラリは自動でコメントになりますが、これらを削除したい場合に利用します。
- コードフォーマッターを適用する
  - Option + Command + L
    - カーソルで範囲を絞ればその範囲だけ適用となります。通常はクラス全体が対象となります。
- コードフォーマット対象外のコードを指定する
  - 「Preferences」 -> 「Editor」 ->「Code Style」をクリック、「Formatter」タブをクリックして「Turn formatter on/off with markers in code comments」をonにしておきます。
  - 「//@formatter:on」というコメント行と「//@formatter:off」というコメント行で囲むことでその行はコードフォーマッターからの対象外となります。

## リファクタリング(セクション5)
- リファクタリングポップアップ(まずはこれだけ覚えると良い)
  - Ctrl + T
- 名前の変更
  - Shift + F6
  - クラス名や変数名を変更することで、他の参照箇所も一括で変更することができます。

以下は必要に応じて参照すれば良い。
- 変数の抽出
  - Option + Command + V
- 定数の抽出
  - Option + Command + C
- メソッドの抽出
  - Option + Command + M
- フィールドの抽出
  - Option + Command + F
- パラメータの抽出
  - Option + Command + P
- インライン化(メソッドを展開する)
  - Option + Command + N
- シグネチャーの変更
  - Option + Enter + Update usages..


## バージョン管理(セクション6)
- VCS Operation ポップアップ
  - Ctrl + V
- ブランチの作成
  - Ctrl + V -> 「Branches」 -> New Branch からブランチ名入力する
- ブランチのチェックアウト
  - Ctrl + V -> 「Branches」 -> ブランチを選択 -> Checkout
- ブランチ名の変更と削除
  - Ctrl + V -> 「Branches」 -> ブランチを選択 -> Rename or Delete
- 変更差分を確認する
  - Command + 0 -> Command + D
  - 前の差分に移動する
    - Shift + F7
  - 次の差分に移動する
    - F7
- 変更差分をロールバックする
  - Option + Command + Z
- コミットする
  - Command + K
  - コミットウィンドウを閉じる場合には Command + 0を押下する。Escを押すとクラス側にカーソルのフォーカスが切り替わる
- 直前のコミットを修正する
  - 1. コミットツールウィンドウを開く
  - 2. Amendにチェックを入れる
  - 3. Amend Commitを押下する
- コミットを修正する
  - Command + Shift + K
- ログを確認する
  - Command + 9
  - 上記でログウィンドウが表示されます。
- 特定の行の直近の変更を確認する
  - Ctrl + V -> 「Annotate with Git Blame」
  - ログウィンドウを閉じたい場合には右クリックをして、「Close Annotation」すれば良い。戻したい場合は、数字で右クリックして「Annotate with Git Blame」をすればよい
- 特定コミットをチェックアウトする
  - 「Command + 9」でログウィンドウが表示されて、チェックアウトしたいログを指定します。その後、右クリックで「Checkout revision 'hash'」とします。
- 選択範囲の変更履歴を表示する (不具合調査などに利用できる)
  - 1. 範囲を選択する
  - 2. 右クリック -> Git -> Show history for selection
- マージする
  - Shift + Command + A -> Mergeを検索
- コンフリクトを解消する
  - Shift + Command + A -> Resolve Conflictを検索


## 影響範囲の調査(セクション7)
- 使用箇所の調査 (Command + Bよりも調査向き)
  - Option + F7
- 呼び出し階層の表示
  - Ctrl + Option + H

# ショートカット関連
- 公式
  - https://pleiades.io/help/idea/mastering-keyboard-shortcuts.html
- ショートカットPDF
  - https://qiita.com/cypher256/items/8ce0527a46bd7cfe43eb

# 参考
- Udemy
  - https://www.udemy.com/course/poco-tech-intellij/
