# g++周りについて
g++周りのメモなど

# 詳細

## gccバージョンによるC++バージョンサポート状況について

最新のサポート状況については以下のリンク内容を参考にすること
GNU公式資料: https://gcc.gnu.org/projects/cxx-status.html

### C++98の機能を有効にする
- GCC 6.1未満まではこのモードが何も指定しない場合のデフォルトとなっている。
- -std=c++98オプションを使用する。GNU拡張を有効にする-std=gnu++98オプションもある。

### C++11の機能を有効にする(2011)
- GCC 4.3から4.6までは、-std=c++0xオプションを使用する。GNU拡張を有効にする-std=gnu++0xオプションもある。
- GCC 4.7以降は、-std=c++11オプションを使用する(旧オプションは非推奨)。GNU拡張を有効にする-std=gnu++11オプションもある。
- GCC 4.8.1でC++11の全ての機能が補完された。

### C++14の機能を有効にする(2014)
- GCC 4.8から4.9までは、-std=c++1yオプションを使用する。GNU拡張を有効にする-std=gnu++1yオプションもある。
- GCC 5.1以降は、-std=c++14オプションを使用する(旧オプションは非推奨)。GNU拡張を有効にする-std=gnu++14オプションもある。
- GCC 6.1以降は、C++14がデフォルトとなる。デフォルトバージョンのコンパイルオプションは-std=gnu++14

### C++17の機能を有効にする(2017)
- GCC 6.1以降は、-std=c++1zオプションを使用する。GNU拡張を有効にする-std=gnu++1zオプションもある。

### c++20の機能を有効にする
- GCC 8以降は、-std=c++2aオプションを使用する。GNU拡張を有効にする-std=gnu++2aオプションもある。


## devtoolsetとgcc,g++などのバージョン対応状況について
gccやg++がサポートしてそうなバージョンはあくまで検索して見つかったものを記載しています。
- developer toolset3 環境セットアップ
  - https://www.softwarecollections.org/en/scls/rhscl/devtoolset-3/
  - gccやg++は4.9.2をサポートしてそう
- developer toolset4 環境セットアップ
  - https://www.softwarecollections.org/en/scls/rhscl/devtoolset-4/
  - gccやg++は5.2.1や5.3.1などをサポートしているのがありそう。
- developer toolset6 環境セットアップ
  - https://www.softwarecollections.org/en/scls/rhscl/devtoolset-6/
  - gccやg++は6.2.1や6.3.1などをサポートしているのがありそう。
- developer toolset7 環境セットアップ
  - https://www.softwarecollections.org/en/scls/rhscl/devtoolset-7/
  - gccやg++は7.1.1, 7.2.1, 7.3.1がありそう。
- developer toolset8
  - Centだとこの辺にパッケージがありそう
    - https://cbs.centos.org/koji/buildinfo?buildID=23600
    - https://cbs.centos.org/koji/packageinfo?packageID=7198
  - 環境セットアップはこの辺?
    - https://access.redhat.com/documentation/en-us/red_hat_developer_toolset/8/html/user_guide/chap-red_hat_developer_toolset#sect-Red_Hat_Developer_Toolset-Subscribe-RHSCL
  - StackOverflow: How to install gcc8 using devtoolset-8-gcc
    - https://stackoverflow.com/questions/53310625/how-to-install-gcc8-using-devtoolset-8-gcc
  - gccやg++は8.1.1, 8.2.1がありそう


次のコマンドでdevtoolsetに切り替えることができます。(バージョン部分は適宜変更すること)
```
$ scl enable devtoolset-4 bash
```

# 参考URL
- 各種処理系(clang, gnu, intel, microsoft)などへのポインタ
  - https://cpprefjp.github.io/implementation.html
- cpprefjp: コンパイラの実装状況
  - https://cpprefjp.github.io/implementation-status.html
- clang対応状況
  - http://clang.llvm.org/cxx_status.html
- libc対応状況
  - http://libcxx.llvm.org/cxx2a_status.html
