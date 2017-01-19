# 概要
Javascriptでのオブジェクト指向関連について

### 
```
function Foo()
{
    this.x = 1; // プロパティ
}

// クラスプロパティ
Foo.x = 2;

var foo = new Foo();
var a = foo.x; // プロパティの参照: 1が返される
var b = Foo.x; // クラスプロパティの参照: 2が返される
```
