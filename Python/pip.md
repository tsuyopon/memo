# 概要
Pythonのパッケージ管理システムpipの使い方について説明します。

# インストール・セットアップ
### python3.6 + pipのインストール

python3.6系+3.6対応のpipはyumのデフォルトレポジトリに含まれていないので以下をインストールしておく
```
$ sudo yum install -y https://centos7.iuscommunity.org/ius-release.rpm
```

pythonとpipをインストールします。
```
$ sudo yum install -y python36u python36u-devel python36u-libs
$ sudo yum install -y python36u-pip
$ which /usr/bin/python3.6
/usr/bin/python3.6
$ which /usr/bin/pip3.6
/usr/bin/pip3.6
```

シンボリックリンクを貼っておきます。
```
$ sudo ln -s /usr/bin/python3.6 /usr/bin/python3
$ sudo ln -s /usr/bin/pip3.6 /usr/bin/pip
```

pipについてはeasy_installやpython get-pip.pyでインストールする方法もありますが、ここでは割愛します。

# pip

### パッケージをインストールする
```
$ pip install test
```

バージョンを固定としたいのであれば次のようにして指定できます。
```
$ pip install test==2.3.4.5
Collecting test==2.3.4.5
Installing collected packages: test
Successfully installed test-2.3.4.5
```

次のようなバージョン指定も可能です
```
$ pip install 'test==0.16.2'
$ pip install 'test>=0.16.2'
$ pip install 'test>=0.16'        # 0.16.*が対象です
$ pip install 'test<0.16.2
$ pip install "test~=0.16.2"
```

複合パターンも指定できます。
```
$ pip install "test>=1,<2"     # バージョン1系のみ許容する。
```

### VersionControlSystem(VCS)からインストールする
```
$ pip install -e git+https://git.repo/some_pkg.git#egg=SomeProject          # from git
$ pip install -e hg+https://hg.repo/some_pkg#egg=SomeProject                # from mercurial
$ pip install -e svn+svn://svn.repo/some_pkg/trunk/#egg=SomeProject         # from svn
$ pip install -e git+https://git.repo/some_pkg.git@feature#egg=SomeProject  # from a branch
```

### 入っているパッケージを再度インストールする
パッケージが入っている場合にはIオプションを付与する必要があります。
```
(hoge2) $ pip install test
Requirement already satisfied: test in ./hoge2/lib/python3.6/site-packages (2.3.4.5)
(hoge2) $ pip install test -I
Collecting test
Installing collected packages: test
Successfully installed test-2.3.4.5
```

### pipモジュールの検索を行う
```
$ pip search curl
couchdb-python-curl (1.1.6)  - CouchDB-python wrapper (using cURL library)
django-test-curl (0.1.1)     - Write Django test requests using curl syntax
pytest-curl-report (0.5.4)   - pytest plugin to generate curl command line report
curl-http (0.1.2)            - curl_http is a wrapper for PyCUrl
Curl-Multi-stro (0.2)        - 
ccurl (0.0.3)                - A wrapper around curl to continually curl an endpoint over time
PyOTA-CCurl (1.0.9)          - C Curl extension for PyOTA
...
```

以下のコマンドも上記と同様です
```
$ python -m pip search curl
```

### パッケージ一覧の確認
```
$ pip list
Package    Version
---------- -------
pip        18.1   
setuptools 40.6.3 
test       2.3.4.5
```

### インストール済みパッケージを確認する
```
$ python -m pip freeze | tee requirements.txt
test==2.3.4.5
```

### パッケージのアップグレードを行う
```
$ pip install --upgrade test
```

### パッケージの削除を行う
```
$ pip uninstall test
Uninstalling test-2.3.4.5:
  Would remove:
    /home/tsuyoshi/hoge2/lib/python3.6/site-packages/test-2.3.4.5.dist-info/*
    /home/tsuyoshi/hoge2/lib/python3.6/site-packages/test.py
Proceed (y/n)? y
  Successfully uninstalled test-2.3.4.5
```

不要なパッケージをrequirements.txtに記載して次のようにしてパッケージ削除することも可能です
```
$ pip uninstall -r requirements.txt
```

### インストール済みライブラリが最新版かどうかをチェックする
```
$ pip list --outdated
```

### パッケージに依存するパッケージを調べる
以下ではRequiresやRequired-byが依存状態を表す表記です。
```
$ pip show requests
Name: requests
Version: 2.21.0
Summary: Python HTTP for Humans.
Home-page: http://python-requests.org
Author: Kenneth Reitz
Author-email: me@kennethreitz.org
License: Apache 2.0
Location: /home/tsuyoshi/hoge2/lib/python3.6/site-packages
Requires: urllib3, chardet, idna, certifi
Required-by: 
```

### プロキシを設定する
```
$ pip install pycrypto --proxy=http://user@proxy.example.jp:8080
```

### パッケージをダウンロードする
```
$ pip download scons
Collecting scons
  Using cached https://files.pythonhosted.org/packages/13/31/43b96f5b79731468a6731e4dbc71601f67fdeddad053bd4f1d1e2f0dbeec/scons-3.0.4-py2.py3-none-any.whl
  Saved ./scons-3.0.4-py2.py3-none-any.whl
Successfully downloaded scons
You are using pip version 18.1, however version 19.0.1 is available.
You should consider upgrading via the 'pip install --upgrade pip' command.
$ ls scons*
scons-3.0.4-py2.py3-none-any.whl
```

### 互換性のあるパッケージが問題なく入っていることを確認する
```
$ pip check virtualenv
No broken requirements found.
```


### ヘルプを表示
```
$ pip help

Usage:   
  pip <command> [options]

Commands:
  install                     Install packages.
  download                    Download packages.
  uninstall                   Uninstall packages.
  freeze                      Output installed packages in requirements format.
  list                        List installed packages.
  show                        Show information about installed packages.
  check                       Verify installed packages have compatible dependencies.
  config                      Manage local and global configuration.
  search                      Search PyPI for packages.
  wheel                       Build wheels from your requirements.
  hash                        Compute hashes of package archives.
  completion                  A helper command used for command completion.
  help                        Show help for commands.

General Options:
  -h, --help                  Show help.
  --isolated                  Run pip in an isolated mode, ignoring environment variables and user configuration.
  -v, --verbose               Give more output. Option is additive, and can be used up to 3 times.
  -V, --version               Show version and exit.
  -q, --quiet                 Give less output. Option is additive, and can be used up to 3 times (corresponding to WARNING, ERROR, and CRITICAL logging
                              levels).
  --log <path>                Path to a verbose appending log.
  --proxy <proxy>             Specify a proxy in the form [user:passwd@]proxy.server:port.
  --retries <retries>         Maximum number of retries each connection should attempt (default 5 times).
  --timeout <sec>             Set the socket timeout (default 15 seconds).
  --exists-action <action>    Default action when a path already exists: (s)witch, (i)gnore, (w)ipe, (b)ackup, (a)bort).
  --trusted-host <hostname>   Mark this host as trusted, even though it does not have valid or any HTTPS.
  --cert <path>               Path to alternate CA bundle.
  --client-cert <path>        Path to SSL client certificate, a single file containing the private key and the certificate in PEM format.
  --cache-dir <dir>           Store the cache data in <dir>.
  --no-cache-dir              Disable the cache.
  --disable-pip-version-check
                              Don't periodically check PyPI to determine whether a new version of pip is available for download. Implied with --no-index.
  --no-color                  Suppress colored output
```


# 参考資料
- PyPA: Installing Packages
  - https://packaging.python.org/tutorials/installing-packages/
