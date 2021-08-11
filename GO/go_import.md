# 概要
goのモジュール周りについて

# 詳細

### import記法

- 相対パスを指定して(NOT RECOMMEND)
```
import "./model"
```


- 絶対パスを指定
```
import "shorturl/model"
```

- 単一行で指定
```
import "fmt"
import "string"
```

- グループ化して指定する
```
import (
    "fmt"
    "string"
)
```

- ドットを指定する
  - ドットを指定すると、以下の例ではfmt.PrintをPrintと省略することが可能です
```
import (
    . "fmt"
    "string"
)
```

- エイリアスを指定する
  - エイリアスを指定すると、以下の例ではfmt.Printをf.Printとして呼び出すことが可能です。
```
import (
    f "fmt"
)
```

- 直接使わないが依存関係により指定が必要な場合
```
import (
    "database/sql"
    _ "github.com/ziutek/mymysql/godrv"
)
```

