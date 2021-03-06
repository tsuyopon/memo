### 木構造の用語について
- ノード
  - 接点や頂点を表す
- 根ノード
  - 木構造の頂点にあるノードを根ノードと呼ぶ
- 葉ノード
  - 木構造の最底辺にあるノードを葉ノード(leaf node)と呼ぶ。最底辺にあるため子ノードをもたない。
- 内部ノード
  - 子を持つノード、すなわち葉ノード以外のノードを意味する
- 部分木
  - 木構造の一部であり、それ自身でも完全な木構造となっている部分を指す

### 木構造探索アルゴリズム
検索アルゴリズムには、幅優先探索と深さ優先探索(Depth First Search)が存在します。
- 幅優先探索
```
	 1
	 |-- 2
	 |   |-- 4
	 |   `-- 5
	 `-- 3
	     |-- 6
	     `-- 7
```

- 深さ優先探索(これに深さ制限が付いたものを深さ制限探索といいます)
```
	 1
	 |-- 2
	 |   |-- 3
	 |   `-- 4
	 `-- 5
	     |-- 6
	     `-- 7
```

実際に深さ優先探索は主に以下の3種類に分類される
- 先行順
  - 最初にノードを訪問した際にそのノードの処理を行います。上記の図では、1234567の順番で処理します
- 中間順
  - 左部分木の処理が終わり、右部分木の処理をする前に自ノードの処理を行います。上記の図では、2345671の順番で処理します
- 後行順
  - 子どもの処理が終わり親に戻る直前に、自ノードの処理をします。上記の図では、7654321の順番で処理します

###  深さ優先探索の再帰プログラム例(以下は完全２分木で作成されていることに注意する)
```
	 void traverse(link a, void (*visit)(link) ){　
	 	if(a == NULL) return;　
	 	(*visit)(a);  // ここに入れると先行順
	 	traverse(a->l, visit);
	 	//　ここに(*visit)(a); を入れると中間順
	 	traverse(a->r, visit);
	 	//　ここに(*visit)(a); を入れると後行順
	 }
```
