# 概要
rpmspecコマンドを使うとspecfileの情報やパースが可能です。

# 詳細

### specファイルから生成されるバイナリパッケージを取得する。
```
$ rpmspec -q poltest.spec 
poltest-1.0-2.x86_64
poltest-policy-1.0-2.x86_64
```

### specファイルから情報を指定して抽出する
specfileから特定の情報をフォーマットを指定して出力することができます。
以下の例の場合、1つのspecfile中に2つのパッケージ情報(foo, foo-sub)が定義してあることがわかります。
```
$ rpmspec -q --qf "%{name} ===> %{summary}\n" foo.spec 
foo ===> foo
foo-sub ===> foo
```

### 指定したspecファイルをパースする (rpm4.9以上で利用可能)

例えば、次のようなspecファイルにおいて、マクロも合わせて展開したい場合
```
$ cat foo.spec 
Summary: foo
Name: foo
Version: 1.0
Release: 1
Source: hello-2.0.tar.gz
Patch1: hello-1.0-modernize.patch
Group: Testing
License: GPLv2+
BuildArch: noarch

%description
Simple rpm demonstration.

%package sub
Summary: %{summary}
Requires: %{name} = %{version}-%{release}

%description sub
%{summary}

%files

%files sub
```

specァイルをparseするにはPオプションを利用します。
```
$ rpmspec -P foo.spec 
Summary: foo
Name: foo
Version: 1.0
Release: 1
Source: hello-2.0.tar.gz
Patch1: hello-1.0-modernize.patch
Group: Testing
License: GPLv2+
BuildArch: noarch

%description
Simple rpm demonstration.

%package sub
Summary: foo
Requires: foo = 1.0-1

%description sub
foo

%files

%files sub
```

