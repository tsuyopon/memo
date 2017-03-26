# 概要
JavascriptをCLIで実行するための方法について

# 詳細

### Nodeを使った場合(確認済)
```
$ node sample.js
```

eオプションを渡すとそのまま文字列を渡して実行することができます。
```
$ node -e "console.log('hello world');"
```

### MAC用(確認済)
```
$ osascript sample.js
```

もしくは
```
$ osascript -l JavaScript sample.js
```

### Windows用(未確認)
まだ未確認ですが次のようなコマンドで実行できるとのことです。
```
$ wscript sample.js
or 
$ cscript sample.js
```
cscriptという方がコマンドライン用らしいです。

### Java(未確認)
Java8からは標準でjavascriptが実行可能となったようです。
Javaを利用した実行環境としてはPacifistaというソフトウェアがあり次のように実行できます。
```
$ pacifista sample.js
```

# JavaScript実行サンプル
適宜他のコマンドなどに置き換えてください。ここではnodeを使っていますが、osascriptなどでも確認しています。

### 即時実行してみる
```
$ cat closure.js
(function(){
  var undefined = 5; //変数作れちゃう
  console.log(undefined); // 5
})();
$ node closure.js
5
```

### 関数を試してみる。
```
$ cat sample.js
function testFunc(a, b){ 
    return a > b;
};

console.log("false: %d", testFunc(10, 20));
console.log("true:  %d", testFunc(20, 10));
$ node sample.js
false: 0
true:  1
```

### クラスの確認など。prototypeの挙動を確認したい
```
$ cat sample.js
function Cat(name) {
  this.setName(name);
};
Cat.prototype = {
  setName: function(name) {
    this._name = name;
  },
  getName: function() {
    return this._name;
  },
  walk: function() {
    console.log('My name is ' + this._name);
  }
};
 
var cat1 = new Cat('tama');
var cat2 = new Cat('jibanyan');
cat1.walk();
cat2.walk();
$ node sample.js
My name is tama
My name is jibanyan
```

### コンストラクタを確認したい

```
$ cat sample.js
function Dog(name, cry) {
  var self = {}; 
  self.name = name;
  self.bark = function() {
    console.log(cry);
  };  
  return self;
}

var dog = new Dog('yuuta', 'wanwan');
console.log(dog.name); // yuuta
dog.bark();            // wanwan
$ node sample.js 
yuuta
wanwan
```

### document.writeを使いたい
自分が試した感じだとnodeでもosascriptでもできないっぽい
```
$ cat error.js 
document.write("testwrite");
$ osascript error.js
error.js:0:28: execution error: Error on line 1: ReferenceError: Can't find variable: document (0)
$ node error.js

/Users/tsuyoshi/git/cpp/STUDY/concurrency/chap1/error.js:1
(function (exports, require, module, __filename, __dirname) { document.write("
                                                              ^
ReferenceError: document is not defined
    at Object.<anonymous> (/Users/tsuyoshi/git/cpp/STUDY/concurrency/chap1/error.js:1:63)
    at Module._compile (module.js:456:26)
    at Object.Module._extensions..js (module.js:474:10)
    at Module.load (module.js:356:32)
    at Function.Module._load (module.js:312:12)
    at Function.Module.runMain (module.js:497:10)
    at startup (node.js:119:16)
    at node.js:929:3
```


# 参考URL
- 今すぐ使えるJavaScriptを実行する環境まとめ
  - http://qiita.com/ukiuni@github/items/d077e2d450c79829a67f
