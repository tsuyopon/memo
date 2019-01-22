# 概要
centos周りに関するtips

### CentOS6とCentOS7の違いについて
詳しくは以下を参考のこと
- https://qiita.com/sion_cojp/items/115e1671fcbc8f214aee

特記事項としては
- デフォルトファイルシステムがext4からxfsになった。
- カーネルバージョンが2.x, 3.x, 4.xだったのが、3.x, 4.xになった
- GrubからGrub2になった
- ロケールの変更方法とタイムゾーンの変更方法が変わった
- iptablesからfirewalld+iptablesとなった
- serviceコマンドからsystemctlコマンドになった
- chkconfigからsystemctlコマンドになった
- 
