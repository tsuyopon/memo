# 概要
PromiseとはECMAScript6世代の機能です。以下でPromiseの対応状況が確認できます。
- http://caniuse.com/#feat=promises

非同期の受け取りにはコールバック関数を利用していましたが、大抵の場合にはライブラリで独自仕様となることが問題でした。
Promiseは、結果の受け取り方法を統一化し、非同期処理を並行・直列に実行することができるのでこの課題を解決することができます。

Promiseでつまずいたらこのmdで説明する基本事項と次のPromiseの本を読むこと
- Promiseの本
  - https://azu.github.io/promises-book/#introduction

# 詳細
### 基本事項
覚えておくべきメソッドは次のメソッドです。
- コンストラクタ
  - Promise(): Promiseオブジェクトを作成します。
- 静的メソッド
  - Promise.resolve(): 成功時に呼ぶ
  - Promise.reject():  失敗時に呼ぶ
  - Promise.all(): 配列で渡されたPromiseが全て終わった後に実行したい場合に使います
  - Promise.race(): 渡したPromiseで最初に解決されたものが呼ばれます。
- メソッド
  - then("成功時に呼び出す関数", "失敗時に呼び出す関数"):  第１引数が成功時、第２に引数が失敗時に呼ばれます。第１引数だけ定義したり、第２引数だけ定義「promise.then(undefined, onRejected)」することも可能です。
  - catch():  失敗時に呼ばれます(thenの第２引数と同じ役割です)

resolve(成功時に呼ばれる)、reject(失敗時に呼ばれる)もので次のような規則があります。!!!これは非常に重要です!!!
- Promiseの処理がresolveされた場合、thenの第１引数で登録した関数が呼び出されます。
- Promiseの処理がrejectされた場合、thenの第二引数かcatchで登録した関数が設定されている順に呼び出されます。 

rejectを定義しないとcatchの行が呼ばれません。
```
function asyncFunction() {
  return new Promise(function (resolve, reject) {
    setTimeout(function () {
      // 失敗
      reject(new Error('Error'));
    });
  });
}

asyncFunction().then(function (value) {
  console.log(value);
}).catch(function (error) {
  // 呼ばれる
  console.log(error);  // => 'Error'
});
```

サンプルとしてメソッドチェーンは次のようになります。
```
function taskA () {
  console.log("TaskA");
}

function taskB () {
  console.log("TaskB");
}

function onRejected(error) {
  console.log("error = " + error);
}

var promise = Promise.resolve();
promise
  .then(taskA)
  .then(taskB)
  .catch(onRejectted);      // taskAとtaskBの実行に失敗したらこれが呼ばれる。
```

上記２つのサンプルではthenの第２引数(catchと同様にエラー時に呼ばれる)を指定しているものはない。

### ES6-Promiseをネストしてみる
Promiseのネストに関する記事
http://qiita.com/tkrkt/items/9a04967e7779af8953bd

### Promise.all([p1, p2, ...]) 全て終わった後に実行させたい
配列で渡されたPromiseが全て終わった後に実行したい場合に使います。
```
var files = ['./a.txt', './b.txt', './c.txt'];

Promise.all(files.map(function(file){
    return readFileAsync(file);
  }))
  .then(function(results){ // 結果は配列にまとまって帰ってくる ['a', 'b', 'c']
    return results.map(function(result){
       console.log(result);
       return result;
    });
  })
  .then(...)
  .catch(onRejected); // どれか一つでも失敗すれば呼ばれる
```

### Promise.race([p1, p2, ...]) 複数登録して最初に何かresolveしたらそれを利用するといった使い方をしたい場合
Promise.raceは渡したPromiseで最初に解決されたものが呼ばれます。
Endpointが複数あった場合リクエストを同時に投げて、先に帰ってきたやつを使うとかが可能です。
```
Promise.race(files.map(function(file){
    return readFileAsync(file);
  }))
  .then(function(results){ 
    console.log(results); // 'a'
    return results;
  });
```

# 参考URL
- Promiseの本
  - https://azu.github.io/promises-book/#introduction
- 今更だけどPromise入門
  - http://qiita.com/koki_cheese/items/c559da338a3d307c9d88
