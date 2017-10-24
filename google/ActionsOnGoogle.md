# 概要
Actions On Googleとはサードパーティデベロッパー向けのプラットフォームです。
このプラットフォームを利用することによって、Googleアシスタントに対応したアプリの開発が可能になります。  

これらのアプリはGoogle Home, Android, iOSなど多くの環境でサービスを提供します。
- https://developers-jp.googleblog.com/2017/10/google-assistant-app-ja.html?m=1

上記アナウンスで2017/10/24から日本語対応が行われたとのこと。上記アナウンスページに

# 詳細
- 開発者向けドキュメント
  - https://developers.google.com/actions/
- サンプルプログラム
  - https://github.com/actions-on-google
- JSON データの解析を行ったり、抽出したユーザーの入力情報を形態素解析して、それに応じた条件分岐を書く必要を軽減するツールを以下に用意している
  - https://developers.google.com/actions/building-your-apps
- アシスタントに対応したアプリが実装できたら次の箇所から登録する必要があります。登録するとシミュレータや実機テストができるようになる。
  - https://developers.google.com/actions/console/publishing
- 一般公開されたアシスタント対応アプリはAssistant Directoryから検索することができます。
  - https://developers.google.com/actions/discovery/directory
