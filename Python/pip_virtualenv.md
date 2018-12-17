# 概要
Pythonのパッケージ管理システムpipの使い方とpython実行仮想環境を提供するvirtualenvについて



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

### virtualenvのインストール
pythonやpipが入っていることを前提にしてvirtualenvのインストールを行う
```
$ sudo pip install virtualenv
Collecting virtualenv
  Downloading https://files.pythonhosted.org/packages/7c/17/9b7b6cddfd255388b58c61e25b091047f6814183e1d63741c8df8dcd65a2/virtualenv-16.1.0-py2.py3-none-any.whl (1.9MB)
    100% |████████████████████████████████| 1.9MB 416kB/s 
Installing collected packages: virtualenv
Successfully installed virtualenv-16.1.0
You are using pip version 9.0.1, however version 18.1 is available.
You should consider upgrading via the 'pip install --upgrade pip' command.
```

上記ではpipも更新しろと記載されているので合わせて更新しておく
```
$ sudo pip install --upgrade pip
````

# virtualenv

### 仮想環境を作成する
virtualenvで引数を与えると仮想環境を作成します。実行後にはそのディレクトリが作成されていることが確認できます。
```
$ ls hoge
ls: cannot access hoge: No such file or directory
$ virtualenv hoge
Using base prefix '/usr'
New python executable in /home/tsuyoshi/hoge/bin/python3.6
Also creating executable in /home/tsuyoshi/hoge/bin/python
Installing setuptools, pip, wheel...
done.
$ ls -l hoge
total 0
drwxrwxr-x 2 tsuyoshi tsuyoshi 268 Dec 18 00:48 bin
drwxrwxr-x 2 tsuyoshi tsuyoshi  24 Dec 18 00:48 include
drwxrwxr-x 3 tsuyoshi tsuyoshi  23 Dec 18 00:48 lib
lrwxrwxrwx 1 tsuyoshi tsuyoshi  23 Dec 18 00:48 lib64 -> /home/tsuyoshi/hoge/lib
```

仮想環境に入るためには次のようにxxxx/bin/activateを読み込みます。
```
$ source hoge/bin/activate
(hoge) $
(hoge) $ pip list
Package    Version
---------- -------
pip        18.1   
setuptools 40.6.3 
wheel      0.32.3
```

pythonのパッケージをインストールしてみます。
```
(hoge) $ pip install test
$ pip list
Package    Version
---------- -------
pip        18.1   
setuptools 40.6.3 
test       2.3.4.5
wheel      0.32.3 
```

仮想環境から出るにはdeactivateを実行します。仮想環境から出たらpythonのパッケージ環境が汚れていないことを確認できます。
```
(hoge) $ deactivate
$
$ pip list
Package    Version
---------- -------
pip        18.1   
setuptools 39.0.1 
virtualenv 16.1.0 
```

### 現在のパッケージの状態を作成したい
pip freezeを利用することで現在の環境を作成することができます。
```
$ pip freeze -l > requirements.txt
$ cat requirements.txt 
test==2.3.4.5
virtualenv==16.1.0
```

作成したrequirements.txtを使って他の環境で同様のpython環境を作成したい。
```
$ cat requirements.txt 
test==2.3.4.5
virtualenv==16.1.0
$ sudo pip install -r requirements.txt 
...
Successfully installed test-2.3.4.5
```

### 仮想環境を実行したいpythonのバージョンを指定する
testenvという環境をpython3.7で作成したい場合には次のように実行します。
```
$ virtualenv -p python3.7 testenv
```

# pip

### パッケージをインストールする
```
$ pip install test==2.3.4.5
Collecting test==2.3.4.5
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
$ python -m pip freeze
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
