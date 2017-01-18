# 概要
ECMAScript6について

# 詳細

### varとletの違いについて
- letでやっとブロックスコープが実現できるようになったとのこと
 - http://qiita.com/takeharu/items/cbbe017bbdd120015ca0

### 分割代入
複数のvarを1行で記述できるようになりました。nameとageの例
``
var [name, age] = ['hoge', 21];
console.log(name, age) // hoge 21
```

### アロー演算子
こんな感じで=>を使うやつ。関数名の"function"の文字列も省略できる。
```
var sum = (a, b) => {
   return a + b;
}
```

### 可変長引数
```
var foo = function(...bar){  (省略) }
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


# 参考
- BABEL
 - https://babeljs.io/learn-es2015/
- es6features(github)
 - https://github.com/lukehoban/es6features#readme
- ES2015 (ES6)についてのまとめ
 - http://qiita.com/tuno-tky/items/74ca595a9232bcbcd727
- ES6の勉強をした
 - http://shokai.org/blog/archives/10229
