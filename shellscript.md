# シェルスクリプト関連のメモ
よく忘れてしまって検索で引っかかりにくい特殊変数などに関するメモ

# メモ 


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


### 特殊記号

<table>
    <tr>
        <td>$?</td>
        <td>$!</td>
        <td>$-</td>
        <td>$$</td>
        <td>$#</td>
        <td>$@</td>
        <td>$*</td>
        <td>$LINENO</td>
        <td>${PIPESTATUS[@]}</td>
        <td>$0</td>
        <td>$1から$9、${10}から${100}</td>
    </tr>
    <tr>
        <td>直前に実行されたコマンドの終了ステータスが設定される変数</td>
        <td>バックグラウンドで実行されたコマンドのプロセスID が設定される変数</td>
        <td>set コマンドで設定されたフラグ、もしくはシェルの起動時に指定されたフラグの一覧が設定される変数。「abc」ならば「-abc」が指定されたことになる</td>
        <td>コマンド自身の PID (プロセスID)が設定される変数</td>
        <td>実行時に指定された引数の数が設定される変数。"$@"とダブルクォートで囲むと"$1" "$2" ...と等価。</td>
        <td>シェルスクリプト実行時、もしくは set コマンド実行時に指定された全パラメータが設定される変数。"$*"とダブルクォートで囲むと"$1 $2 ... $n"と等価。IFS環境変数で区切り文字を指定可能</td>
        <td>この変数を使用している行の行番号が設定される変数</td>
        <td>パイプで連結した各コマンドの終了ステータスが設定される変数(配列)</td>
        <td>実行したシェルスクリプト名が設定される。</td>
        <td>N番目の引数。10以上はカッコで囲む必要がある。</td>
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

### 配列
- http://shellscript.sunone.me/array.html

### 変数の解釈関連
- http://shellscript.sunone.me/variable.html
