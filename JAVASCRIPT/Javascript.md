# Javascript
javascript関連のメモなど

### 一般
- 「use strict」って何の意味があるのか?
- http://linuxserver.jp/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0/javascript/use-strict
  - use strictの効果について
  - https://msdn.microsoft.com/ja-jp/library/br230269%28v=vs.94%29.aspx

- javascriptのthisは使われる場所などによって意味が異なる
  - javascriptの「this」は「4種類」？？
  - http://qiita.com/takeharu/items/9935ce476a17d6258e27

- function hoge()とvar fn = hoge()の違いがよくわからない
  - JavaScript function declaration syntax: var fn = function() {} vs function fn() {}
  - http://stackoverflow.com/questions/336859/javascript-function-declaration-syntax-var-fn-function-vs-function-fn
  - http://stackoverflow.com/questions/1013385/what-is-the-difference-between-a-function-expression-vs-declaration-in-javascrip?noredirect=1&lq=1

- Difference between == and === in JavaScript [duplicate]
  - http://stackoverflow.com/questions/523643/difference-between-and-in-javascript?rq=1

- How do JavaScript closures work?
  - http://stackoverflow.com/questions/111102/how-do-javascript-closures-work?rq=1

- What this “get” in JavaScript object means?
  - http://stackoverflow.com/questions/7401048/what-this-get-in-javascript-object-means
  - 以下はgetの使われ方で不明点なサンプル
```
var human = 
{
   firstName: 'Saeed',
   lastName: 'Neamati',
   get fullName() {
       return this.firstName + ' ' + this.lastName;
   }
}
```
- 呼び出す関数の引数が不足していたらどうなるのか?
  - 全てundefinedに定義される。javascriptではoverloadができないため
  - http://stackoverflow.com/questions/1846679/what-happens-when-i-call-a-javascript-function-which-takes-parameters-without-s


###  bind, callの違い
bindとcallはJavaScriptに「おまえのものはおれのもの、おれのものもおれのもの」というジャイアニズムを実現するための素晴らしいメソッドらしい。

bindが遅延させたいときに使用し、callとapplyが即時実行したい場合に利用する。
では、callとapplyの違いはなんだろうか?


callはthisの値を指定してその関数をcallの呼び出しと同時に実行します。
```
var hoge = new Man("Test");
steve.greet.call(hoge);
```

bindはthisの値を固定した新しい関数を作成します。  
callのようにcallを実行しただけでbindの場合には呼ばれません。そのbindを行ったtamaGreet()を呼び出すと実行されます。
```
var tama = new Cat("Tama");
var tamaGreet = steve.greet.bind(tama);
tamaGreet();
```

callのthisを強制的に書き換えるサンプル
```
var Girl = function() {
  this.name = '女の子';
  this.enterToilet = function(){
    console.log(this.name + "が女子トイレに入る");
  };
};
var Boy = function() {
  this.name = '男の子';
};

new Girl().enterToilet();                // 女の子が女子トイレに入る
new Girl().enterToilet.call(new Boy());  // 男の子が女子トイレに入る
```

### 即時関数にcallを利用する
```
"use strict"; // 『strictモード』でJavaScriptを実行させます。
 
(function(){
    console.log(this); //  // 『windowオブジェクト』が出力されます。
}).call(window); // 即時関数を『call(window)』してあげます。
 
(function(){
    console.log(this); //  // 『windowオブジェクト』が出力されます。
}).call(this); // 関数外の『this』は『windowオブジェクト』になるので『this』を渡してしまってもOKです。『CoffeeScript』でコンパイルしたJavaScriptはこの形になりますね。
```
有名ライブラリとかの中身を見てみると即時関数などに『.call(window)』とか『.call(this)』とかがくっついている事が多いのですが、これはこのためだったりします。
- http://wp-p.info/tpl_rep.php?cat=js-application&fl=r11

### applyについて
applyもthisの参照先を変更するための仕組みです。
```
var sum = function() {
  var result = 0;
  for (var i = 0; i < arguments.length; i++) {
    result += arguments[i];
  };
  return result;
};

var args = [1,2,3,4,5];

// 第1引数に渡された以下の例では、thisの参照先はwindowオブジェクトになる。
// 第2引数に添字配列を渡すと、渡された添字配列の0番目から順番に元となる関数の引数になります
sum.apply(window, args);  
```

- 参考
  - http://wp-p.info/tpl_rep.php?cat=js-application&fl=r11



