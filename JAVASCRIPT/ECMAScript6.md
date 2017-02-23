# 概要
ECMAScript6について

# 詳細

### varとletの違いについて
ES6からletによりブロックスコープが有効になったようです。ES5までは関数内のスコープしか存在しませんでした。
```
let foo = [1, 2, 3];
{
  let foo = [4, 5, 6];
  console.log(foo);
  // => 4, 5, 6
}
console.log(foo);
// => 1, 2, 3 (これがES5以前だと4, 5, 6が返ってくる)
```
- letでやっとブロックスコープが実現できるようになったとのこと
 - http://qiita.com/takeharu/items/cbbe017bbdd120015ca0

### クラスの記述方法
以下のような感じでclass extendsにより定義が可能とった。
constructorはnewするときの引数が含まれる。親コンストラクタを呼びたければsuperを使えば良い。
```
class Child extends Parent {
  constructor(name){
   super({delimiter: ":", wildcard: true}); // superで継承元を呼び出す
   this.name = name; // プロパティを持てる
  }

  ...
}
```

ES5までは次のようにクラスもどきを作成していました。  
prototypeで定義すると毎回関数が生成されないという利点があります(つまり、以下の例でHumanの中にthis.name = function(){...} を定義しても再生成される)。
```
// これまでのクラスのようなもの
function Human(name) {
  this.name = name;
}
 
Human.prototype.hello = function () {
  console.log('My name is ' + this.name);
};
```

### 名前付きexportについて
exportによってどれを外部に出すかを設定することができる。 
exportは変数や関数の前にもつけられるし、exportで{}で囲んで一括で定義することもできる。
```
export let name = 'David';
export let age  = 25;

function sumTwo(a, b) {
    return a + b;
}
 
function sumThree(a, b, c) {
    return a + b + c;
}
 
export { sumTwo, sumThree };
```

### export default classとは何か
そのクラスをimportしたときにデフォルトで呼ばれるクラスを指す。(おそらく1つに複数クラスが定義されているときなど)
```
import Comp1 from './comp/comp1';
```

defaultがもし付与されていないクラスの場合には{}で囲んで、どのくらすをインポートするかを指定する必要がある。
```
import {Comp1} from './comp/comp1';
```

### 複数のクラスを1つのファイルに定義して個別にインポートしたい
```
export class Hoge1 extends Parent {
...
}

export class Hoge2 extends Parent {
}
```

上記のファイルでHoge1とHoge2のクラスを定義していますが、個別にインポートすることが可能です。
```
import {Hoge2} from './parent';
```

注意点としてはexport default classがある場合の扱いは注意する
```
export default class DefaultPrent
export class NotDefault
```

上記のように定義されている場合
```
import DefaultPrent from '...';               // OK: DefaultPrentが呼ばれる
import {DefaultPrent, NotDefault} from '...'; // OK: DefaultPrentとNotDefaultが呼ばれる
import {NotDefault} from '...';               // OK: NotDefaultが呼ばれる
import {DefaultPrent} from '...';             // NG: defaultで指定したclassだけを個別に呼ぶことはできない
```

- 参考
 - http://qiita.com/HIGAX/items/28f3bec814928b7395da

### importについて
{}で囲む
```
import { sumTwo, sumThree } from 'math/addition';
```

次のようにすると全てをインポートできます。
```
import * as util from 'math/addition';
```

### defaultのオブジェクトをインポートする
どの機能をインポートするか選択することができます。
```
import React from 'react';
const { Component, PropTypes } = React;
```

これは次のように簡略化できます。
```
import React, { Component, PropTypes } from 'react';
```


### 分割代入
複数のvarを1行で記述できるようになりました。nameとageの例
``
var [name, age] = ['hoge', 21];
console.log(name, age) // hoge 21
```

### アロー関数
こんな感じで=>を使うやつ。関数名の"function"の文字列も省略できる。
```
let sum = (a, b) => {
   return a + b;
}
```

単一式の場合には次のように省略できる
```
let sum = (a, b) => a + b;
```

アロー関数の特徴として宣言している関数のスコープのthisを引き継ぐようです。
```
// ブラウザのグローバル空間に於いて以下を実行するとグローバルのthisであるwindowがアロー関数内のthisになる
window.setTimeout(e => {
  console.log(this === window); // => true
}, 1000);
```

### 可変長引数
```
var foo = function(...bar){  (省略) }
```

ES5までは次のように扱っていました
```
function logArguments() {
    for (var i=0; i < arguments.length; i++) {
        console.log(arguments[i]);
    }
}
```

### テンプレート文字列
```
`my name is ${this.name}`
```

### デフォルトパラメータ
```
var foo = function(name="hoge1"){ console.log(name); };
foo("hoge2");   // => hoge2
foo();          // => hoge1
```

### binaryとoctal
こんな比較が可能になった
```
0b111110111 === 503 // true
0o767 === 503       // true
```


# 参考
- BABEL
 - https://babeljs.io/learn-es2015/
- es6features(github)
 - https://github.com/lukehoban/es6features#readme
- ES2015 (ES6)についてのまとめ
 - http://qiita.com/tuno-tky/items/74ca595a9232bcbcd727
- ES6の勉強をした
 - http://shokai.org/blog/archives/10229
 - https://github.com/shokai/es6-study
