# 概要
chromeブラウザに関するメモなど

# 詳細

### 再読み込み３種類

- 1) 通常読み込み
  - この方法では更新された画像が古いまま残ってしまうことがある
  - Ctrl + R  または F5
- 2) ハード再読み込み
  - Webページから直接参照されている画像ファイルやCSSなどのキャッシュを破棄してリロードする
  - Ctrl + Shift + R  または Shift + F5
- 3) キャッシュ削除とハード再読み込み
  - ハード再読み込みに加えて二時的なキャッシュも破棄してリロードする。例えば、表示中のwebページで実行されたJSから動的に読み込まれるファイルなどのキャッシュ更新が可能である。
  - ショートカットは存在しないので、Developer Toolsを起動して、ツールバー上にある「このページを再読み込みします」をクリックする。


- 参考URL
  - https://forest.watch.impress.co.jp/docs/serial/chrometips/1152903.html

### Chromeのコマンドラインオプション
以下のサイトが非常に役に立ちそう
- https://peter.sh/experiments/chromium-command-line-switches/
