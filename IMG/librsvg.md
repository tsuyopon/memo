# 概要
librsvgは、SVG形式のファイルを画像に変換する為の仕組みです。
- rsvg-convertコマンドにより以下の事ができます。
  - SVG形式のファイルからPNG, PDF, PSに変換可能
  - DPI指定(X座標、Y座標)可能
  - ズーム指定(X座標、Y座標、全体)可能
  - 幅、高さ指定可能
  - 出力ファイル名指定可能
  - アスペクト比指定可能

# 詳細

### パッケージ名称とコマンド一覧について(私の環境CentOS5で確認) 
- パッケージ名称
```
$ rpm -qf /usr/bin/rsvg-convert
librsvg2-2.16.1-1.el5
```
- パッケージ一覧(コマンドのみ抜粋)
```
$ rpm -ql librsvg2 | grep -i bin
/usr/bin/rsvg
/usr/bin/rsvg-convert
/usr/bin/rsvg-view
```
3つのコマンドが存在しているようですが、このページではrsvg-convertについて説明します。

### rsvg-convertコマンド
ヘルプは以下で確認することができます。
```
$ rsvg-convert --help
Application Options:
 -d, --dpi-x=<float>                  pixels per inch [optional; defaults to 90dpi]
 -p, --dpi-y=<float>                  pixels per inch [optional; defaults to 90dpi]
 -x, --x-zoom=<float>                 x zoom factor [optional; defaults to 1.0]
 -y, --y-zoom=<float>                 y zoom factor [optional; defaults to 1.0]
 -z, --zoom=<float>                   zoom factor [optional; defaults to 1.0]
 -w, --width=<int>                    width [optional; defaults to the SVG's width]
 -h, --height=<int>                   height [optional; defaults to the SVG's height]
 -f, --format=[png, pdf, ps, svg]     save format [optional; defaults to 'png']
 -o, --output                         output filename [optional; defaults to stdout]
 -a, --keep-aspect-ratio              whether to preserve the aspect ratio [optional; defaults to FALSE]
 -v, --version                        show version information
 -b, --base-uri                       base uri
```

### rsvg-convertコマンドサンプル
- (例1) hoge.svgをサイズを1/10にし、PNG形式でhoge.pngという名称で保存する
```
$ rsvg-convert hoge.svg -z 0.1 -f png -o hoge.png
```

- (例2) hoge.svgの高さを100にし知恵して、PDF形式でhoge.pdfという名称で保存する
```
$ rsvg-convert hoge.svg -h 100 -f pdf -o hoge.pdf
```

# 詳細
- https://wiki.gnome.org/action/show/Projects/LibRsvg?action=show&redirect=LibRsvg
