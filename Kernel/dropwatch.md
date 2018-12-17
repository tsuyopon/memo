# dropwatchとは
カーネルでドロップされたパケットを監視するユーティリティです。
次のコマンドで簡単にパッケージインストールすることができます。
```
$ sudo yum install dropwatch
```

# 使い方
使い方もここに載せているのがほとんどですごいシンプルです。
リアルタイムにカーネルでパケットが
ドロップされたことを通知する表示が出力されますので、終了する場合にはCtrl+Cで終了します。その後、stopでインタラクティブモードから抜けます。　
```
$ dropwatch
Initalizing null lookup method
dropwatch> start
Enabling monitoring...
Kernel monitoring activated.
Issue Ctrl-C to stop monitoring
1 drops at location 0xffffffff81572ec8
2 drops at location 0xffffffff815d3371
2 drops at location 0xffffffff8163c638
1 drops at location 0xffffffff815d3371
^CGot a stop message
dropwatch> stop
Deactivation requested, turning off monitoring
Got a stop message
```

上記だとdropされたことがわかるだけで、どこでパケットがドロップされたのかわかりません。
そこで/proc/kallsymを参照してどのアドレスがどのカーネルシンボルと一致するのかを示してくれるオプションがあります。それが「-l kas」です。
```
$ dropwatch -l kas
Initalizing kallsyms db
dropwatch> start
Enabling monitoring...
Kernel monitoring activated.
Issue Ctrl-C to stop monitoring
1 drops at skb_queue_purge+18 (0xffffffff81572ec8)
2 drops at ip_recv_error+81 (0xffffffff815d3371)
1 drops at ip_recv_error+81 (0xffffffff815d3371)
^CGot a stop message
```

