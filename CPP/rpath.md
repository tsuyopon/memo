# 概要
rpathを設定するプログラムについて

# 詳細
```
$ cat main.cpp 
#include <iostream>

int main(int argc, char const* argv[])
{
        std::cout << "aaa" << std::endl;
        return 0;
}
```

次のようにしてrpathを設定したビルドが可能である。
```
$ g++ -Wl,-rpath=/tmp main.cpp 
```

バイナリにrpathが設定されているかどうかを確認することもできる。
```
$ readelf -d -w ./a.out | grep -i rpath
 0x000000000000000f (RPATH)              Library rpath: [/tmp]
$ objdump -x ./a.out | grep RPATH
  RPATH                /tmp

```

# 参考URL
- https://qiita.com/koara-local/items/2c26e249e02994230324
