# 概要
次の資料に感化されたのでスタンドアロン環境でSELENIUMテストを動かせるようにすることを目的とする。
- http://decknotes.net/slides/33

# Rspec経由でSelenium Web Driverを稼働させる(Firefoxを想定)

```
$ cat Gemfile
source 'https://rubygems.org'
gem "rspec"
gem "selenium-webdriver"
gem "pry"
gem "gechodriver-helper"
$ bundle install --path vendor --jobs=3 --retry=3
```

続いて、firefoxをインストールしてそのままだとfirefoxを起動できないので、仮想ディスプレイを動かします。

```
$ yum install firefox -y
$ yum install xorg-x11-server-Xvfb -y
```

以下のコマンドで仮想Xを起動して、DISPLAY 1番を使うように環境変数を指定する。
```
$ Xvfb :1 -screen 0 1024x768x24 -nolisten inet6 &
$ export DISPLAY=1
```

以上によりfirefoxを起動できる。
```
$ firefox &
Xlib: extension "RANDR" missing on display ":1".
$ ps auxww | grep -i firefox
```

最初にレポジトリ直下でrspecを動かすのであれば次のコマンドで.rspecファイルとspecディレクトリを生成します。
```
$ bundle exec rspec --init
$ cd spec
```

つづいて、FirefoxプラグインのSelenium IDEなどでテストをぽちぽちして生成したらRspec形式でエクスポートできるのでエクスポートしたらspecディレクトリに配置します。これをmytest.rbという名称と仮定します。

ただし、mytest.rbにはそのままだといくつかの不具合があります。自分の場合には次の３つも不具合がありました。
- vim上で:%s/${receiver}/@driver/gとして${receiver}を@driverに変換しましょう。
- sholdの箇所をexpectに書き直す必要があります。
-- expect(@verification_errors).to eq []
- @driver.manage.timeouts.implicit_wait = 30がなぜかNot a Numberと表示されてしまうのでコメントアウトする

次のコマンドで動作させます。
```
$ bundle exec rspec mytest.rb
```

### User-Agentを偽装して実行したい
次のwebdriver-user-agentというgemを使えば良い。
- http://qiita.com/oh_rusty_nail/items/2dacfc22f06f9669cba5

# 参考URL
- http://decknotes.net/slides/33
