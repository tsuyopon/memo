# 概要
外部キー制約周りについて

# 詳細


### INSERTを先に済ませてあとで外部キー関連を直したい場合
```
SET FOREIGN_KEY_CHECKS = 0;
```
とすれば外部キー制約無しでデータの更新や削除が出来ます。

また、終わったら以下を実行して制約を元に戻すこと
```
SET FOREIGN_KEY_CHECKS = 1;
```

