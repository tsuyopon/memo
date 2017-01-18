# Angular関連

### 変数名の前に$や$$が付いている場合などについて
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
