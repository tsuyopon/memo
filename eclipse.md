# 概要 
Eclipseで便利なショートカットについて纏めます。

# 詳細 

### ソースコード読解操作 
```
    F3
        カーソル位置のクラス、インタフェース、変数等の宣言場所へ移動
        尚、元の位置に戻るには「Alt + ←」を押下します。進むには「Alt + →」が利用できます。
    F4
        カーソル位置のクラスの継承関係を表示
    Ctrl + Space
        変数やメソッドを補完する(コンテンツアシスト)
    Ctrl + O
        カーソル位置のクラスのメソッド一覧を表示
    Ctrl + T
        カーソル位置がメソッドにあり、そのメソッドのinterfaceでなくimplementsの方を閲覧したい場合に押下する。尚、interfaceが見たい場合にはF3で閲覧できる。
    Ctrl+Alt+H
        メソッド等の使用箇所を表示する
```

### カーソル操作 
```

    Ctrl + D
        現在の行や選択された行を削除
```

### パースペクティブ移動 
```
    Ctrl + F8
        前のパースペクティブ(DDMS, Java, Debug等の移動)
    Ctrl + Shift + F8
        次のパースペクティブ(DDMS, Java, Debug等の移動)
```

### メソッド移動 
```
    Ctrl + ↓
        次のメソッド
    Ctrl + Shift + ↑
        前のメソッド
```

### デバッグ 
```
    Shift + Alt + X
        実行形式を選択(Run As)
    Shift + Alt + D
        デバッグ形式を選択(Debug As)
```

### 便利技 
```
    Ctrl + Shift + O
        必要なライブラリをimportしてくれます
    Ctrl + Shift + L
        ショートカット一覧を表示する
    Ctrl + E
        開いているウィンドウ一覧(タブになっているところ)を切り替えできます
    Ctrl + /
        Javaの場合などに行頭にコメント(//)を付与したり、削除したりを切り替えできます
```

# 参考URL 
- ニートになりたいプログラマ
  - http://fukata.org/2010/05/30/useful-eclipse-keyboard-shortcut-java/
- Eclipseコマンドリファレンス
  - http://www.geocities.jp/turtle_wide/tools/eclipse/cmd_index.htm
