# Javascript
javascript関連のメモなど

# 一般
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

# Angular関連

### $$や$などの変数の意味について
- What is the $$ (double dollar sign) used for in angular?
 - Angularのソースコードでは$や$$がつかわれている。これは一体なんだろうか？
  - https://github.com/angular/angular.js/blob/v1.5.8/src/AngularPublic.js#L219-L260
 - http://stackoverflow.com/questions/19338493/what-is-the-double-dollar-sign-used-for-in-angular
 - $はpublic identifier, $$はprivate identiferとのこと

### this.$getとかの意味が不明
以下のサイトを参考にする。
- http://qiita.com/Quramy/items/2ef4dba5e29b3148be50

サービスプロバイダのコンストラクタは、 $get メソッドを実装しなくてはならない(こいつが無い場合、Angularがエラーを吐く).  
$get メソッドは関数であり、AngularのDI($inject)経由でインジェクションされる際に呼び出される関数を実装する。

```
var module = angular.module('myModule', []);
module.provider('myService', function(){
  var opt = {message: 'Hello, world'};
  this.configure = function(options){
    opt = angular.extend(opt, options);
  };
  this.$get = function(){
    return {
      hello: function(){
        return opt.message;
      }
    };
  };
});
```



