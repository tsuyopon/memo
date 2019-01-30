# 概要
Python実行仮想環境を提供するvirtualenvを利用することでプロジェクト毎にクリーンな仮想環境を作成することができます。

# virutualenvのインストールの種類
システムへvirtualenvをインストールするにはいくつかの方法があります。
```
$ sudo apt-get install python-virtualenv
$ sudo easy_install virtualenv
$ sudo pip install virtualenv
```

### virtualenvのインストール from pip
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


### virtualenvのアップグレード from pip
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

作成したvirtualenv環境が不要であれば削除してしまえば良いです。
```
$ rm -rf hoge/
```

### 現在のパッケージの状態を作成したい
pip freezeを利用することで現在の環境を作成することができます。
```
$ pip freeze -l > requirements.txt
$ cat requirements.txt 
test==2.3.4.5
virtualenv==16.1.0
```

### パッケージリストからインストールしたい
上記で作成したrequirements.txtを使って他の環境で同様のpython環境を作成したい。
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


### 仮想環境からグローバルなsite-packages(ライブラリ)を参照できるようにする。
```
$ virtualenv --system-site-packages ENV
```

昔のバージョンはグローバルも参照できたようですが、最近のだとデフォルトではグローバルなsite-packageは参照できないようになっているようです。

### 現在のバージョン・ヘルプを確認する
```
$ virtualenv --version
16.1.0
$ virtualenv -h
Usage: virtualenv [OPTIONS] DEST_DIR

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -v, --verbose         Increase verbosity.
  -q, --quiet           Decrease verbosity.
  -p PYTHON_EXE, --python=PYTHON_EXE
                        The Python interpreter to use, e.g.,
                        --python=python3.5 will use the python3.5 interpreter
                        to create the new environment.  The default is the
                        interpreter that virtualenv was installed with
                        (/usr/bin/python3.6)
  --clear               Clear out the non-root install and start from scratch.
  --no-site-packages    DEPRECATED. Retained only for backward compatibility.
                        Not having access to global site-packages is now the
                        default behavior.
  --system-site-packages
                        Give the virtual environment access to the global
                        site-packages.
  --always-copy         Always copy files rather than symlinking.
  --relocatable         Make an EXISTING virtualenv environment relocatable.
                        This fixes up scripts and makes all .pth files
                        relative.
  --no-setuptools       Do not install setuptools in the new virtualenv.
  --no-pip              Do not install pip in the new virtualenv.
  --no-wheel            Do not install wheel in the new virtualenv.
  --extra-search-dir=DIR
                        Directory to look for setuptools/pip distributions in.
                        This option can be used multiple times.
  --download            Download preinstalled packages from PyPI.
  --no-download, --never-download
                        Do not download preinstalled packages from PyPI.
  --prompt=PROMPT       Provides an alternative prompt prefix for this
                        environment.
  --setuptools          DEPRECATED. Retained only for backward compatibility.
                        This option has no effect.
  --distribute          DEPRECATED. Retained only for backward compatibility.
                        This option has no effect.
  --unzip-setuptools    DEPRECATED.  Retained only for backward compatibility.
                        This option has no effect.
```

# 参考URL
- ドキュメント
  - https://virtualenv.pypa.io/en/latest/
