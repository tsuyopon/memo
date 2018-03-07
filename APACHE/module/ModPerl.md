# 概要
mod_perlは、ApacheにPerlインタプリタを組み込んだものです。
以下の特徴があります。
- CGIを使用せずに済む
- パフォーマンスを向上させることができる。
- mod_perlを組み込んだApache環境では、以下の2つのモジュール用命令を利用することができます。
  - Apache::Registry
    - Perlで作成したモジュールを実行する際に１度だけモジュールがコンパイルされ、メモリに常駐する。
  - Apache::PerlRun
    - Perlで作成したモジュールが呼び出されるたびにコンパイルされる。

# 詳細
### 拡張子が.cgiのものはmod_perlで実行するように設定する
こんな感じ
```
<IfModule mod_perl.c>
  <Files *.cgi>
    SetHandler perl-script
    PerlHandler Apache::Registry
    PerlSendHeader On
  </Files>
</IfModule> 
```

### PERL5LIBの設定
```
PerlSetEnv PERL5LIB /usr/local/apache2/site_perl
```

# 参考URL
- mod_perl公式サイト
  -  http://perl.apache.org/
