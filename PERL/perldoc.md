# perldocについて
perldocコマンドについての説明です。
perldoc自身のコマンドはperldocコマンドの引数にperldocを渡すことでできることやオプションなどを確認することが出来ます。
```
$ perldoc perldoc
```

# 詳細
### FAQを見る
例えば、配列のシャッフル(shuffle)の方法がFAQのどこかで説明されている場合 以下の様に使用する。
```
$ perldoc -q shuffle
```

perl自身のドキュメントや各種モジュールも参照することができます。
```
$ perldoc perl
$ perldoc File::Spec
```

### perlの関数名の使い方を見る
perlの組み込み関数を知るにはfオプションを利用します。
```
$perldoc -u -f 関数名[例：atan2]
```

以下は使用例です
```
$ perldoc -f atan2
$ perldoc -f substr
```

### ジュールや関数のドキュメントがみたい
関数名を知りたければ以下により、manページを確認することができる。
```
$ perldoc -f <関数名>
```

モジュールを知りたければ以下により、manページを確認することができる。
```
$ perldoc <モジュール名>
```

上記でモジュール名を指定する時にはSocketという場合socketではNGなので、しっかりと大文字、小文字 を区別して指定すること。

### インストールされているライブラリのパスが知りたい
例えば、LWP::UserAgent?がどこにあるのか知りたい場合には以下の様にすればよい。 これにより@INC中からライブラリを探し出してくれる。

```
$ perldoc -l LWP::UserAgent
/usr/share/perl5/LWP/UserAgent.pm
```

### モジュールのソースコードを読みたい
mオプションを利用すればよい。
```
$ perldoc -m File::Find
```

### 特殊変数のドキュメントが見たい
検索しても引っかかりにくい特殊変数ですが、次のようにしてそのドキュメントを確認することが出来ます。
```
$ perldoc -v '$@'
$ perldoc -v '$"'
$ perldoc -v @+
$ perldoc -v DATA
```

# 参考URL
- http://perldoc.jp/docs/
