# 概要
グローバルプラグインとremapプラグインの見分け方

soファイルをシンボルを見る方法で簡単に見分けることができます。
```
$ nm /opt/trafficserver-7.1.x_log/libexec/trafficserver/combo_handler.so |grep -i TSPluginInit
000000000004c765 T TSPluginInit
$ nm /opt/trafficserver-7.1.x_log/libexec/trafficserver/combo_handler.so |grep -i TSRemapInit
0000000000050020 T TSRemapInit
```

- TSPluginInit
  - グローバルプラグイン
- TSRemapInit
  - Remapプラグイン
