# 概要
Knockout.jsについて

次の３つの視点からKnockout.jsを理解しておくと理解しやすいです。
- データのバインディング
 - (例) APIからデータを取得して特定の要素のdata-bind属性にバインディングできること
- データ双方向のバインディング
 - ロジックからHTMLを変更するためにはko.computedを利用する
 - (例) HTML上からデータをフォームにデータを入力すると、変更等同時に合計も計算される仕組み。
- データの受け取り
 - data-bindで設定されたデータを受け取ることができること(フォームから送信ボタンを押下されるような場合)

### チュートリアル
この辺にあるようです。
- http://learn.knockoutjs.com/#/?tutorial=intro

### ko.observableについて
以下の違いを押さえておくことが重要です。
- 引数があるとsetterとして値をセットします
 - (例) http://learn.knockoutjs.com/#/?tutorial=collections
- 引数がないとgetterとして値を取得できるようになります。
 - (例) http://learn.knockoutjs.com/#/?tutorial=loadingsaving
```
this.newTaskText = ko.observable();
とすると
this.newTaskText()として関数のように値が取得できます。
```

### ko.computedについて
ko.computedはデータの双方向のやりとりなどに利用する仕組みのようです。
- viewにdata-bindをattributeに記述するdata-bind="text: hoge"
- this.hoge = ko.observable(true); などとして対象の監視をする
- this.hogeを使ってデータを書き出したい場合にはko.computedを使う。
- ko.computedは最初に実行された際に依存する変数を保存しておく。これによって対象が変更された場合にはその関数を実行することになる。


条件分岐などで参照されなかった変数は依存として保存されない。つまり、変更があってもそのko.computedが実行されることはないので注意すること

- この辺の記事がわかりやすい。
- http://qiita.com/opengl-8080/items/2b0fb26be865bd5d1890

### データの条件分岐について

幾つか方法があるので記載しておく。

- (1) 次のように2つ一気に書いてしまうとif文などを記述しなくてもよさそう
```
<span data-bind="visible: isTrue">isTrue</span>
<span data-bind="visible: isFalse">isFalse</span>
```

- (2) 次の表にviewModelの値によってDOMを切り替えることもできる。
```
window.onload = function() {
    var viewModel = {
        isTrue: true,
        isFalse: false
    };

    ko.applyBindings(viewModel);
};
```

ifやifnotバインディングを使うことができる。
```
<span data-bind="if: isTrue">isTrue</span>
<span data-bind="if: isFalse">isFalse</span>

<span data-bind="ifnot: isTrue">isTrue</span>
<span data-bind="ifnot: isFalse">isFalse</span>
```

- (3) コンテナレス構文というのもある
先ほどの(2)であればこんな感じ。elseはknockout.jsのデフォルト機能ではなさそうだ。
```
<!-- ko if: isTrue -->
  isTrue
<!-- /ko -->

<!-- ko if: isFalse-->
  isFalse
<!-- /ko -->
```



# 参考URL
- http://qiita.com/opengl-8080/items/2b0fb26be865bd5d1890
