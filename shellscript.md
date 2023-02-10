# シェルスクリプトについて
よく忘れてしまって検索で引っかかりにくい特殊変数などに関するメモ

以下のリファレンスが超絶役に立つので何かあればこちらを参考するとよさそう
  - http://shellscript.sunone.me/

# /bin/shメモ

### shebangの指定方法
次の2つがあります。

- 1) bashを絶対パスで指定する方法
```
#!/bin/bash
```

- 2) envを使って指定する方法
```
#!/usr/bin/env bash
```

2)のメリットは、bashを別のパスに入れてしまった場合にも、環境情報から判断して正しく使ってくれるという利点があります。


### パターンマッチ
```
${変数名#パターン}                     前方一致でのマッチ部分削除(最短マッチ)
${変数名##パターン}                    前方一致でのマッチ部分削除(最長マッチ)
${変数名%パターン}                     後方一致でのマッチ部分削除(最短マッチ)
${変数名%%パターン}                    後方一致でのマッチ部分削除(最長マッチ)
${変数名/置換前文字列/置換後文字列}    文字列置換(最初にマッチしたもののみ)
${変数名//置換前文字列/置換後文字列}   文字列置換(マッチしたものすべて)
```

以下サンプル
```
#!/bin/sh

var="/my/path/dir/test.20161026.dat"
echo '${var#*/}  => ' ${var#*/}
echo '${var##*/} => ' ${var##*/}
echo '${var%.*}  => ' ${var%.*}
echo '${var%%.*} => ' ${var%%.*}
echo '${var%/*}  => ' ${var%/*}           # ディレクトリを切り出す
echo '${var%.*}.ext  => ' ${var%.*}.ext   # 拡張子を変更する

var2="abcdef abcdef abcdef xyz"
echo '${var2/test/XXX} => ' ${var2/test/XXX}
echo '${var2//abc/XXX} => ' ${var2//abc/XXX}
```

実行結果は次の通り
```
${var#*/}  =>  my/path/dir/test.20161026.dat
${var##*/} =>  test.20161026.dat
${var%.*}  =>  /my/path/dir/test.20161026
${var%%.*} =>  /my/path/dir/test
${var%/*}  =>  /my/path/dir
${var%.*}.ext  =>  /my/path/dir/test.20161026.ext
${var2/test/XXX} =>  abcdef abcdef abcdef xyz
${var2//abc/XXX} =>  XXXdef XXXdef XXXdef xyz
```

- 参考
  - http://d.hatena.ne.jp/ozuma/20130928/1380380390

### 文字列長の取得
文字列長の取得をするには${#変数}とすればよい。
```
${#変数}
```

サンプルは次の通り。expr lengthでも可能なので一緒にのせている
```
STRING=helloworld
echo LENGTH ${#STRING}       # 「LENGTH 10」

STRLEN=$(expr length "$STRING")   # 上と同じ出力
echo LENGTH $STRLEN
```

### 文字列から一部を抽出する
文字列の抽出もできる次の例を見た方がわかりやすい
```
STRING=helloworld
REPLACESTR="${STRING:5:3}"   # 5+1文字目から3文字取得する
echo $REPLACESTR             # "wor"を表示する
```

### 準変数
書式と意味が次の通り
```
${VAR:-expression} 	    値がセットされていない(NULL)場合、:-以降の式を評価結果を返す。
${VAR:+expression} 	    値がセットされている(NONE-NULL)場合、:+以降の式を評価結果を返す。
${VAR:=expression} 	    値がセットされていない(NULL)場合、:=以降の式を評価結果を返し変数に代入。
${VAR:?[expression]}    値がセットされていない(NULL)場合、式が標準エラーに出力。
```

サンプルは次の通り
```
#!/bin/sh
 
echo "[ null variable ]"
VAR=
EXPAND=${VAR:-blue}
echo "-var    : $VAR"
echo "-expand : $EXPAND"
EXPAND=${VAR:+yellow}
echo "+var    : $VAR"
echo "+expand : $EXPAND"
EXPAND=${VAR:=green}
echo "=var    : $VAR"
echo "=expand : $EXPAND"
echo ""
echo "[ non-null variable ]"
VAR=red
EXPAND=${VAR:-blue}
echo "-var    : $VAR"
echo "-expand : $EXPAND"
EXPAND=${VAR:+yellow}
echo "+var    : $VAR"
echo "+expand : $EXPAND"
EXPAND=${VAR:=green}
echo "=var    : $VAR"
echo "=expand : $EXPAND"
exit 0
```

実行結果は次の通り
```
$ ./var.sh
[ null variable ]
-var    :
-expand : blue
+var    :
+expand :
=var    : green
=expand : green
 
[ non-null variable ]
-var    : red
-expand : red
+var    : red
+expand : yellow
=var    : red
=expand : red
```

この辺も参考にすると良い
- http://shellscript.sunone.me/variable.html#%E5%A4%89%E6%95%B0%E3%81%AE%E7%89%B9%E6%AE%8A%E3%81%AA%E5%8F%82%E7%85%A7%E6%96%B9%E6%B3%95

上記サイトでは以下の違いについて詳細に説明している。
```
${VAR=aaa}
${VAR:=aaa}
${VAR-aaa}
${VAR:-aaa}
${VAR+aaa}
${VAR:+aaa}
```

### 特殊記号

<table>
    <tr>
        <td>$?</td>
        <td>直前に実行されたコマンドの終了ステータスが設定される変数</td>
    </tr>
    <tr>
        <td>$!</td>
        <td>バックグラウンドで実行されたコマンドのプロセスID が設定される変数</td>
    </tr>
    <tr>
        <td>$-</td>
        <td>set コマンドで設定されたフラグ、もしくはシェルの起動時に指定されたフラグの一覧が設定される変数。「abc」ならば「-abc」が指定されたことになる</td>
    </tr>
    <tr>
        <td>$$</td>
        <td>コマンド自身の PID (プロセスID)が設定される変数</td>
    </tr>
    <tr>
        <td>$#</td>
        <td>シェル変数の数</td>
    </tr>
    <tr>
        <td>$@</td>
        <td>実行時に指定された引数の数が設定される変数。"$@"とダブルクォートで囲むと"$1" "$2" ...と等価。</td>
    </tr>
    <tr>
        <td>$*</td>
        <td>シェルスクリプト実行時、もしくは set コマンド実行時に指定された全パラメータが設定される変数。"$*"とダブルクォートで囲むと"$1 $2 ... $n"と等価。IFS環境変数で区切り文字を指定可能</td>
    </tr>
    <tr>
        <td>$LINENO</td>
        <td>この変数を使用している行の行番号が設定される変数</td>
    </tr>
    <tr>
        <td>${PIPESTATUS[@]}</td>
        <td>パイプで連結した各コマンドの終了ステータスが設定される変数(配列)</td>
    </tr>
    <tr>
        <td>$0</td>
        <td>実行したシェルスクリプト名が設定される。</td>
    </tr>
    <tr>
        <td>$1から$9、${10}から${100}</td>
        <td>N番目の引数。10以上はカッコで囲む必要がある。</td>
    </tr>
</table>

### 環境変数
<table>
    <tr>
        <td>$PS1</td>
        <td>プロンプトに使用される文字列が設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PS2</td>
        <td>コマンドが複数行にわたった場合のプロンプトに使用される文字列が設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PATH</td>
        <td>コマンドが格納されているディレクトリのパスが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$TZ</td>
        <td>タイムゾーンが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PWD</td>
        <td>カレントディレクトリのパスが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$IFS</td>
        <td>デリミタ(区切り文字)として使用される値が設定されている環境変数。デフォルトではタブ、スペース、改行が設定されている。for 文の値リストの区切りや、read コマンドで読み込む値の区切りなどに使用される。</td>
    </tr>
</table>

### 数値比較
```
-eq 	test num1 -eq num2 	        num1 と num2 が等しければ真となる(num1=num2)
-ne 	test num1 -ne num2 	        num1 と num2 が等しくなければ真となる(num1≠num2)
-lt 	test num1 -lt num2 	        num1 が num2 より小ならば真となる(num1<num2)
-le 	test num1 -le num2 	        num1 が num2 以下ならば真となる(num1≦num2)
-gt 	test num1 -gt num2 	        num1 が num2 より大ならば真となる(num1>num2)
-ge 	test num1 -ge num2 	        num1 が num2 以上ならば真となる(num1≧num2)
```

- 参考
  - http://shellscript.sunone.me/if_and_test.html

### ファイルが新しいか古いかでの評価
```
オプション  使用例                         オプションの意味
-nt         test ファイル1 -nt ファイル2   ファイル1 is newer than ファイル2
-ot         test ファイル1 -ot ファイル2   ファイル1 is older than ファイル2
```

### testコマンドによるファイルや文字列の評価
```
オプション  使用例             オプションの意味
-z 	        test -z string     string の文字列長が 0 ならば真となる。
-n 	        test -n string     string の文字列長が 0 より大ならば真となる。
-d 	        test -d file       file がディレクトリならば真となる。
-f 	        test -f file       file が普通のファイルならば真となる。
-s 	        test -s file       file が 0 より大きいサイズならば真となる。
-e 	        test -e file       file が存在するならば真となる。
-r 	        test -r file       file が読み取り可能ならば真となる。
-w 	        test -w file       file が書き込み可能ならば真となる。
-x 	        test -x file       file が実行可能ならば真となる。
```

- 参考
  - http://shellscript.sunone.me/if_and_test.html

### 計算

```
x=10
echo $x # 10
echo $x+2 # 10+2
echo `expr $x + 2` # 12
echo `expr \($x + 5\) \* 2` # 30 

readonly y=20
y=25 # y: readonly variableというエラーが出る
```

ポイントは次の通り
- 計算したい時は`(バッククォート)を使う
- 数値として展開したい変数の前にexprを使う。（この時計算する四則演算記号の前後にスペースを入れる）
- 掛け算やカッコを使う場合は \* のように、記号の前にバックスラッシュが必要（エスケープ）
- readonly とすると変数の上書きができなくなる


$(())も利用することができるようです。
```
// $(())も利用することができる。
$ echo $(( (x + 5) * 2 ))
30
```

- 参考: http://qiita.com/katsukii/items/383b241209fe96eae6e7

### オプション解析
オプションの使い方としては次の通りでdは値を取り、aとhは値を取りません。
```
usage_exit() {
        echo "Usage: $0 [-a] [-d dir] item ..." 1>&2
        exit 1
}

while getopts ad:h OPT
do
    case $OPT in
        a)  FLAG_A=1
            ;;
        d)  VALUE_D=$OPTARG
            ;;
        h)  usage_exit
            ;;
        \?) usage_exit
            ;;
    esac
done
```

getoptは外部コマンドのため、バージョンや環境によって差異があります。それが、BSD 系と GNU 系の違いです。
- http://qiita.com/b4b4r07/items/dcd6be0bb9c9185475bb

### ユーザーからの入力
readで読み込みを行う。
```
while : 
do
    read key
    echo "you pressed $key"
    if [ $key = "end" ]; then
        break
    fi
done
```

### 選択肢で選ばせたい場合
```
select option in CODE DIE
do
    echo "you pressed $option"
    break;
done
```

こうすると次のように表示され、数字で選択することができる。
```
1) CODE
2) DIE
#? 1
you pressed CODE
```

### データを読み込ませる
以下はwhile read lineで読み込ませる場合の４パターンです

- パターン1
```
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<END
hoge
fuga
piyo
END
```
- パターン2: コマンド実行と同時に利用する(パイプ以降プロセスが変わることに注意)
```
cnt=0
cat /tmp/test.txt | while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done
```
- パターン3: 変数から読み込ませる
```
DATA=`cat /tmp/test.txt`
 
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<END
$DATA
END
```
- パターン4: 標準入力からファイルを読み込ませる
```
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done < /tmp/test.txt
```
- 参考
  - http://server.etutsplus.com/sh-while-read-line-4pattern/

パターン2のcatで読み込みパイプでwhile read lineなどを実行するときにはパイプ以降は別プロセスとして動作します。
このため、以下のようにwhileで定義された変数をwhile文で参照することができません。
- http://www.atmarkit.co.jp/bbs/phpBB/viewtopic.php?topic=15886&forum=10

この場合はパイプを使わない方法で行いましょう

### while read lineとevalを組み合わせてみる

コマンドを実行してその結果を変数に格納して、while read lineで処理したい場合は次のようにします。先ほどのパターン３の例で記述します。
```
CMD="cat /etc/hosts | egrep -ie \"^127.0.0.1\" -ie \"localhost6$\""
RET=`eval ${CMD}`

echo "============================"
echo ${RET}

echo "============================"
while read line
do
    echo $line
done << END
$RET
END
```

結果は次の通りです。${RET}だと改行コードなく表示され、while read lineだと正しく表示されるようです。(なぜかはまだ不明)
```
============================
127.0.0.1 localhost.localdomain localhost ::1 localhost6.localdomain6 localhost6
============================
127.0.0.1 localhost.localdomain localhost
::1 localhost6.localdomain6 localhost6
```

### 配列
ループして実行する場合
```
#!/bin/sh

a=(1 2 3 4 5)
for i in ${a[@]}
do
    echo $i
done
```

全要素、配列数を取得するには次のようにする
```
VAR[@] - 配列の全要素
VAR[#] - 配列の要素数
```

- http://shellscript.sunone.me/array.html


### 変数の解釈関連
- http://shellscript.sunone.me/variable.html

${VAR}とか


## テクニック

### 引数を取得する
以下は引数を解析する際のサンプルです。
引数が想定よりも少なければusageを表示します。OKなら取得します
```
if [ $# -lt 2]; then
  echo "Usage:"
  echo "  $(basename ${0}) <arg1> <arg2>"
  exit1
fi

ARG1=${1}
ARG2=${2}
```

### $1が存在しない場合に


### ステータス情報の退避
次のようにしておけば、$?のコマンドステータスが他のコマンドを実行する前に退避しておくことが可能である。
```
echo "$var" | grep -sq "hoge"; CMDRESULT=$?
if [ $CMDRESULT -eq 0 ]; then
	echo "hoge が見つかりました。"
fi
```


### スクリプト自身のパスを知る
```
BASEDIR=$(cd $(/usr/bin/dirname $0); pwd)
```

### 変数がNULLかどうかのチェック
変数が null だった場合、以下の条件式ではエラーになります。
```
if [ $answer = yes ]; then
```
これは $answer がから文字列だった場合、 if [ = yes ]; then と評価されエラーになります。 ではダブルクォーテーションで囲めばよいのか？
```
if [ "$answer" = yes ]; then
```

実はこれでもまだ安全ではありません。もし $answer が -f だった場合 if [ -f = yes ]; then となりエラーと判断されるかもしれません。
最も安全場記述方法は以下のように確実に文字列として評価されるように記述することです。
```
if [ x"$answer" = xyes ]; then
```

### "[]"と"[[]]"の違いについて
[はテストコマンドで、[[はbash組み込みコマンドとなる。
動作上の違いとして次の違いがある。
```
$ unset hoge
$ [ $hoge = "HOGE" ]
-bash: [: =: unary operator expected
$ [[ $hoge = "HOGE" ]]
$
```

加えて終了ステータスにも次の違いがある。
```
$ [ $hoge = "HOGE" ]
-bash: [: =: unary operator expected
$ echo $?
2
$ [[ $hoge = "HOGE" ]]
$ echo $?
1
```

変数展開後の条件式が「= “HOGE”」となるため [] の場合にはエラーメッセージが出力されている。
一方で [[ ]] ではエラーメッセージは表示されないのでこの辺は使い分けると良いかも

- 参考
  - https://fumiyas.github.io/2013/12/15/test.sh-advent-calendar.html

### setコマンドについて
シェルスクリプトでよく使われるのがsetコマンド
一般的に「set -eu」などとつけておくと便利らしいので、このオプションの意味を確認してみる

- 未定義の変数を使おうとしたときに打ち止めにしてくれる。Perlでいうuse strict 'vars';的なもの
```
set -u
```

- エラーがあったらそこで打ち止めにしてくれる
```
set -e
```

その後、上記をある段階になったら無効にする場合には次のコマンドを実行すればいい
```
set +e
```

また、パイプライン内のコマンドがエラーとなった時に中断するオプションは以下です。
```
set -o pipefall
```

これは、例えば以下のスクリプトの場合に有効です。
```
set -e

FOO=$(wc --liens "$0" | cut -d' ' -f1)
echo "lines: $FOO"
```

実行結果としてwcコマンドのエラーとなっていて、wcエラー時に本来停止して欲しい処理なのに実行されてしまっています。
```
$ ./my_script.sh; echo ?=$?
wc: unrecognized option '--liens'
Try `wc --help' for more information.
lines:
?=0
```

set -xやset +xなどについてはデバッグオプションで後述する。


上記をふまえて、シェルスクリプトでは特に理由がなければ次の様に設定しておくのが良さそうである。
```
set -ue -o pipefail
```

- 参考
  - http://qiita.com/youcune/items/fcfb4ad3d7c1edf9dc96
  - https://moneyforward.com/engineers_blog/2015/05/21/bash-script-tips/

###
```
$ cat ./hoge.sh 
#!/bin/sh

set -o
[tsuyoshi@localhost ~]$ ./hoge.sh 
allexport      	off
braceexpand    	on
emacs          	off
errexit        	off
errtrace       	off
functrace      	off
hashall        	on
histexpand     	off
history        	off
ignoreeof      	off
interactive-comments	on
keyword        	off
monitor        	off
noclobber      	off
noexec         	off
noglob         	off
nolog          	off
notify         	off
nounset        	off
onecmd         	off
physical       	off
pipefail       	off
posix          	on
privileged     	off
verbose        	off
vi             	off
xtrace         	off
```

### shとbashの違い
set -oすると以下の出力が取得できる
```
allexport      	off
braceexpand    	on
emacs          	off
errexit        	off
errtrace       	off
functrace      	off
hashall        	on
histexpand     	off
history        	off
ignoreeof      	off
interactive-comments	on
keyword        	off
monitor        	off
noclobber      	off
noexec         	off
noglob         	off
nolog          	off
notify         	off
nounset        	off
onecmd         	off
physical       	off
pipefail       	off
posix          	on
privileged     	off
verbose        	off
vi             	off
xtrace         	off
```

shとbashではこれらに差異がある。
```
$ cat binsh.sh 
#!/bin/sh
set -o
$ cat binbash.sh 
#!/bin/bash
set -o
$ ./binsh.sh > sh.sh   
$ ./binbash.sh > bash.sh
$ diff sh.sh bash.sh 
23c23
< posix          	on
---
> posix          	off
```

bashはshを真似ようとしているだけであり、上記の違いがある。
違いを示すソースコードを載せます。

```
$ cat test.sh 
diff <(ls /home) <(ls /homuhomu)
$ sh test.sh
test.sh: line 1: syntax error near unexpected token `('
test.sh: line 1: `diff <(ls /home) <(ls /homuhomu)'
$ bash test.sh
ls: cannot access /homuhomu: No such file or directory
1d0
< tsuyoshi
```

また、bashじゃないと配列が使えない場合もあるので注意が必要です。

- 参考
  - http://sechiro.hatenablog.com/entry/20120806/1344267619

## デバッグ


### -v

### -xオプションで実行したら、その時の変数の値なども同時に出力する
bashの場合には-xオプションによってコマンド実行時の変数の値なども出力することができる。
```
#!/bin/bash -x
# ↑ここで「-x」オプションを指定する。(bashであることに注意!!)

var1=`date +%M`
var2=`ls -1 | wc -l`

if [ $var1 -ge 30 ]; then
  var3="BIG"
else
  var3="SMALL"
fi

exit 0
```

実行すると結果は次のようになる。
```
$ ./script.sh
++ date +%M
+ var1=47
++ ls -1
++ wc -l
+ var2=26
+ '[' 47 -ge 30 ']'
+ var3=BIG
+ exit 0
```



### 特定の箇所から特定の箇所までをデバッグモードにしたい
次のようにset -xやset +xを使い分けすれば良い。
```
#!/bin/sh

デバッグが必要ない部分

set -x　←実行状況の出力を開始

デバッグが必要な部分

set +x　←実行状況の出力を終了

デバッグが必要ない部分
```

なお、/usr/bin/envでは「#!/usr/bin/env bash -x」や「#!/usr/bin/env "bash -x"」などとしても効かないで実行時にエラーとなってしまうので、デバッグ時には「set -x」を利用する。
以下のようなサンプルがある場合
```
$ cat test.sh 
#!/usr/bin/env bash

set -x

hostname="MOGE"
debug_variable_name="T3C_DEBUG_COMPONENT_${hostname}"
echo $debug_variable_name

debug_binary="${!debug_variable_name}"

echo $debug_binary
```

実行すると以下のように変数情報や実行結果が展開されて表示されます。
```
$ ./test.sh 
+ hostname=MOGE
+ debug_variable_name=T3C_DEBUG_COMPONENT_MOGE
+ echo T3C_DEBUG_COMPONENT_MOGE
T3C_DEBUG_COMPONENT_MOGE
+ debug_binary=
+ echo
```

### 間違ってファイルの上書きをしないように禁止する
間違ってファイルの上書きをしたりしないように禁止するには
```
$ set -C
```
やめるときには+Cとなる。

### コマンドが実行可能かどうか
```
CMD=foo
type -p "$CMD" 1>/dev/null 2>&1 || echo "command not found: $CMD" >&2
```

## TIPS


### grepするときにハイフンをコマンドラインオプションとして解釈しないようにする
"-hoge"という文字列をgrepしようとするとエラーとなる
```
$ echo "-hoge" > hoge
$ cat hoge 
-hoge
$ grep "-hoge" hoge 
grep: invalid option -- 'g'
Usage: grep [OPTION]... PATTERN [FILE]...
Try 'grep --help' for more information.
```

"--"をコマンドの後に付与するとそれ以降をコマンドラインオプションとして解釈しないようになる
```
$ grep -- "-hoge" hoge 
-hoge
```

### パスワード文字列を入力させたい
-sで文字のechoをoffにする
```
$ read -s -p "MSG " PASSWD
```

ユーザー入力の後に改行が表示できないので次のを入れて回避するのが一般的となる
```
printf "%b" "\n"
```

ただし、パスワードは/proc/coreから覗くことは可能である。

### timeコマンドをファイルに出力させたい。
実は組み込みコマンドのtimeは標準出力や標準エラー出力にやってもファイルにリダイレクトされない
- https://stackoverflow.com/questions/2408981/how-can-i-redirect-the-output-of-the-time-command

こんな感じで指定しなければならない　
```
(time ls) &> file
```

### カンマ区切り2つは何?
カンマ区切り２つは「Parameter Expansion」と呼ばれているもののようでbash4以降で利用できるようです。
```
${reportName,,}
```
サンプル出力はこちら
```
var=HeyThere
echo ${var,,}
heythere
```

- 参考
  - https://stackoverflow.com/questions/41166026/what-does-2-commas-after-variable-name-mean-in-bash

# 参考URL
- UNIX&LINUXコマンド・シェルスクリプトリファレンス
  - 今後もリファレンスとして非常によさそう
  - http://shellscript.sunone.me/debug.html
- シェルスクリプトの基礎知識まとめ
  - http://qiita.com/katsukii/items/383b241209fe96eae6e7
- UNIX&LINUXコマンド・シェルスクリプトリファレンス
  - http://shellscript.sunone.me/variable.html
- 割りと便利だけど微妙に忘れがちなbashのコマンド・チートシート
  - http://qiita.com/jpshadowapps/items/d6f9b55026637519347f

