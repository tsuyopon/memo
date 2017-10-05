# 概要
Red Hat Software Collections (SCL)としてのdevtoolsetを用いるとコンパイラ(gcc, g++, fortranなど)及びbinutilsを切り替えることができるようになります。

# 詳細

### devtoolset-1.1(gcc-4.7)
```
$ cd /etc/yum.repos.d
$ wget http://people.centos.org/tru/devtools-1.1/devtools-1.1.repo 
$ yum --enablerepo=testing-1.1-devtools-6 install devtoolset-1.1-gcc devtoolset-1.1-gcc-c++
````

- 参考
  - https://superuser.com/questions/381160/how-to-install-gcc-4-7-x-4-8-x-on-centos

### devtoolset-2(gcc-4.8.2)
devtoolset-2ではgcc-4.8系がインストールされるらしいのでC++11にも対応しています。
```
$ cd /etc/yum.repos.d
$ wget http://people.centos.org/tru/devtools-2/devtools-2.repo -O /etc/yum.repos.d/devtools-2.repo
$ yum install devtoolset-2-gcc devtoolset-2-binutils
$ yum install devtoolset-2-gcc-c++ devtoolset-2-gcc-gfortran
```

以上によりgcc-4.8.2がインストールされる
```
$ /opt/rh/devtoolset-2/root/usr/bin/gcc --version
gcc (GCC) 4.8.2 20140120 (Red Hat 4.8.2-15)
Copyright (C) 2013 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

次のコマンドを実行するとdevtoolset-2に切り替えができる。
```
$ scl enable devtoolset-2 bash
```

シェルを再起動すると元に戻ってしまうので、.bashrcや.bash_profilesに以下を入れるのがよい。
```
source /opt/rh/devtoolset-2/enable
```

- 参考
  - https://qiita.com/giwa/items/28c754d8fc2936c0f6d2
  - https://people.centos.org/tru/devtools-2/readme

### devtoolset-3
```
$ cd /etc/yum.repos.d
$ wget https://copr.fedorainfracloud.org/coprs/rhscl/devtoolset-3/repo/epel-6/rhscl-devtoolset-3-epel-6.repo
$ yum install scl-utils devtoolset-3-toolchain devtoolset-3-perftools devtoolset-3-gcc devtoolset-3-binutils 
$ yum install devtoolset-3-gcc-c++ devtoolset-3-gcc-gfortran
```


切り替えを行う
```
$ scl enable devtoolset-3 bash
```

- 参考
  - http://www.task-notes.com/entry/20151114/1447492231

### devtoolset-4(gcc-5.2.1)

```
$ sudo yum install centos-release-scl
$ sudo yum install scl-utils
$ sudo yum install devtoolset-4-gcc devtoolset-4-gcc-c++ devtoolset-4-binutils
```

切り替えを行う
```
$ scl enable devtoolset-4 bash
```
