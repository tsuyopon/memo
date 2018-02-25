# 概要
Linuxなどで利用されるグラフ描画ツールgnuplotについて

# 詳細
### LinuxでなくWindowsでもgnuplotを使用したい。 †
wgnuplotというツールが存在する。(http://www.yama-ga.com/gnuplot/) wgnuplotはデフォルトでフォントが非常に小さいので、次のようにしてフォント変更する。 
ターミナル上で右クリック→Choose Fontを選択→サイズを変更

### グラフのスタイルについて
```
lines          ライン表示
points	  データポイント表示
linespoints	  データとデータポイント表示
impulses       インパルス表示(斜線表示)
dots		  ドット表示
steps	  ステップ表示
fsteps	  ステップ表示(最初の点からステップが立ち上がる)
histeps	  ステップ表示(点がステップの中心)
errorbars	  誤差グラフ
xerrorbars	  横方向の誤差グラフ
yerrorbars	  縦方向の誤差グラフ
xyerrorbars	  横及び縦方向の誤差グラフ
boxes	  棒グラフ
boxerrorbars   誤差のボックス表示
candlesticks	  変動のボックス表示
financebars	  変動の横線表示
vector	  ベクトル表示
```

### setオプション
set data style lines いちいちwith linesが面倒な場合に使用する。

### 凡例を消したり、位置を変更させたい
[凡例を消す場合] これには
```
 gnuplot>set nokey    (<=全ての凡例が消える)
 gnuplot>plot sin(x) notitle  (<=sin(x)に関する凡例が消える)
```

[凡例の位置を変更する場合] 
```
例 gnuplot>set key left bottom (<=左下になる)
```

指定できるオプションは以下のとおりである。
```
left     左側
right    右側
top	     上側
bottom   下側
outside  図の右側の外
beklow   図の下側の外
```

### 軸に日付を出したい
以下に例を示す
```
gnuplot>plot "test1.dat" using 1:2   (<=1つめのパラメータをx軸、2つめのパラメータをy軸に設定する)
gnuplot>replot "test2.dat" using 1:3 (<=1つめのパラメータをx軸、2つめのパラメータをy軸に設定する)
gnuplot>set xdata time  
gnuplot>set timefmt "%d日%H時%M分" (<=これらの詳細はdateコマンドのmanを見よ)
gnuplot>set format x "%dday\n%H:%M" (<=グラフxのフォーマットとして出力させる)
gnuplot>replot
```
(注)datファイルには文字などは#(コメントアウト)しなくてはならない

### formatで使用可能な書式
上記で日付設定などでformatを利用したが、以下ではformatで利用可能な一般的書式を載せる。
```
%f       浮動小数点表示
%e(%E)	 指数表示
%g(%G)	 %fまたは%eの簡略表示
%x(%X)	 16進数表示
%o	 8進数表示
%t	 基数が10の仮数
%T	 基数が10の指数
%l	 現在の対数の底を基数とした仮数
%L	 現在の対数の底を基数とした指数
%s	 現在の対数の底を基数とした3の倍数の仮数
%S	 現在の対数の底を基数とした3の倍数の指数
%c	 補助単位m(ミリ)、k(キロ)、M(メガ)、G(ギガ)など
%p	 πの倍数
```

### datファイルの読み込みと再読み込み
```
gnuplot>plot "testfile1.dat","testfile2.dat"
gnuplot>replot "testfile3.dat"
```

### タイトルやラベルを付ける
項目に"?????.dat using 1:3"など以外のタイトルを付ける。
```
gnuplot>plot "?????.dat" using 1:3 title "janle 1" with linespoints
```

タイトルを付ける場合
```
gnuplot>set title 'TITLENAME'
```

x軸にラベルを付ける
```
gnuplot>set xlabel 'xlablename'
```

y軸にラベルを付ける
```
gnuplot>set ylable 'ylabelname'
```

### 範囲の指定を行う
- x軸のrangeの指定
```
gnuplot>set xrange [0:100]   <=0から100まで
```
- y軸のrangeの指定
```
gnuplot>set yrange [0:100]   <=0から100まで
```

### グラフをPostscriptファイルとして出力を行なう。又、出力画面をXへ戻す
グラフを描画したら次のようにする。 
```
gnuplot> set terminal postscript eps color (<="eps color"は付けてもつけなくてもOKである。 Terminal type set to 'postscript' Options are 'landscape noenhanced monochrome dashed defaultplex "Helvetica" 14'
```

```
 gnuplot> set output "testx.eps"   <==例としてepsで出力した。psでも可能
 gnuplot> rep
 gnuplot> exit
```
これによりカレントディレクトリにtestx.epsというepsファイルが作成されている。 (ps,gif,pngなども出力可能であるらしい)

次に出力画面をXへと戻すには
```
gnuplot>set output
gnuplot>set terminal x11
```
とすればよい。

### 2つの軸を利用する
以下に設定ファイルをみて頂きたい。ここでは、y軸を2つ利用している。2つの軸を利用する場合、コマンドの順番なども重要になってくる。
しっかりとyrange,y2range,y2tics,axisの指定などを行う必要があります。
yrangeは1つ目のx軸(通常左側)の範囲を決定する。(x軸ではxrange) y2rangeはつ目のx軸(通常右側)の範囲を決定する。(x軸ではx2range) y2ticsは左側とメモリを反映させない(nomirror)を今回指定している。 axisは位置を決定するx1y2だと1つめのx軸と2つめのy軸を指定することになる。
```
<(例)test.gpl>
set title "network and cpu thermometer between server and  m1(First week)"
set xlabel "time"
set ylabel "Percentage(%)"
set xdata time
set timefmt "%d日%H時%M分"
set xrange ["08日09時00分":"12日16時00分"]
set yrange [0:70000000]
plot "m1_eth0_rtbits.dat" using 1:2  title "m1 recieve data bits/second"  with linespoints
replot "m1_eth0_rtbits.dat" using 1:3  title "m1 transfer data bits/second"  with linespoints
replot "server_eth0_rtbits.dat" using 1:2  title "server recieve data bits/second"  with linespoints
replot "server_eth0_rtbits.dat" using 1:3  title "server transfer data bits/second"  with linespoints
set y2tics nomirror
set y2range [0:60]
set y2label "Thermometer"
replot "m1_sensors_rename.dat" using 1:3 axis x1y2 title "CPU thermometer"  with linespoints
replot "server_sensors_rename.dat" using 1:5 axis x1y2 title "CPU thermometer" with linespoints
set terminal postscript eps color
set output "m1_server_mix_network_cpu_thermometer_first.eps"
rep
```

### 設定ファイルの読み込みによるコマンドラインでのgnuplot編集方法
たとえば以下のような設定ファイルを用意したとする。
```
<(例)m1_cswch.gpl>
plot "m1_cswch.dat" using 1:2  title "context switch number"  with linespoints
set xdata time
set timefmt "%d日%H時%M分"
set xrange ["16日00時00分":"17日00時00分"]
set xlabel "time"
set ylabel "context switch number per second"
set title "Context switch number about m1(1 day)"
set terminal postscript eps color
set output "m1_cswch_daily16.eps"
rep
```
上記のような設定ファイルがあれば、以下のようにしてコマンドライン上で グラフを作成することができる。これを利用すればたくさんグラフを作成しなければ ならない時など非常に便利である。
```
$gnuplot m1_cswch.gpl
```

### 項目ラベルの位置を変更する
通常はグラフ内の右上に項目ラベルがある。 以下のオプションが存在する。
```
set key top left       グラフ内左上
set key top right      グラフ内右上(デフォルト)
set key bottom left    グラフ内左下
set key bottom right   グラフ内右下
set key outside        グラフ外の右下
set key below          グラフ外の下
```

### 軸のレンジを反転する(上:値が小さいもの、下:値が大きいもの) 
```
X軸を反転   set xrange [min_value:max_value] reverse
Y軸を反転   set yrange [min_value:max_value] reverse
反転解除    set xrange [min_value:max_value] noreverse 
            set yrange [min_value:max_value] noreverse
```
