# 概要
次の資料に感化されたのでスタンドアロン環境でSELENIUMテストを動かせるようにすることを目的とする。
- http://decknotes.net/slides/33

自動化言語としては、Java, C#, Python, Ruby, Perl, PHPがサポートされていますが、ここではRubyを用いた例を示すことにします。

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
Xvfb というのは X (Linux 用の GUIシステム) のための仮想ディスプレイフレームバッファというもので、それは、GUI アプリが書き込むための偽のディスプレイバッファを提供します。つまり、すべてのプログラムをGUI無しのヘッドレスにすることができます。
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
- shouldの箇所をexpectに書き直す必要があります。
-- expect(@verification_errors).to eq []
- @driver.manage.timeouts.implicit_wait = 30がなぜかNot a Numberと表示されてしまうのでコメントアウトする

次のコマンドで動作させます。
```
$ bundle exec rspec mytest.rb
```

### User-Agentを偽装して実行したい
次のwebdriver-user-agentというgemを使えば良い。
- http://qiita.com/oh_rusty_nail/items/2dacfc22f06f9669cba5

### phantom.jsやchromeで実行する。

phantom.jsがインストールすればテスト用ファイルを次のように変更するだけでOK
```
#@driver = Selenium::WebDriver.for :firefox
#@driver = Selenium::WebDriver.for :phantomjs
#@driver = Selenium::WebDriver.for  :ie
#@driver = Selenium::WebDriver.for  :chrome
```

上記について補足
- ieはwindowsで動かす必要がある。
- firefox,chromeはLinux, Mac, Windowsで動作する

- 参考
-- https://www.qoosky.io/techs/71dd2d67ea


## 記述できるプログラムTIPS

- https://www.qoosky.io/techs/71dd2d67ea 

### リンクを押下する
```
element.click
```

### find_elementとfind_elementsの違い
- find_element: 該当要素がなければ例外を投げます
- find_elements: 結果を配列で返します。該当要素がなければ空の配列を返します

### waitをかける
環境によってはwaitをかける必要がります。
- https://www.qoosky.io/techs/71dd2d67ea

```
driver = Selenium::WebDriver.for :firefox
driver.get "http://google.com"

wait = Selenium::WebDriver::Wait.new(:timeout => 10) # seconds
begin
  element = wait.until { driver.find_element(:id => "testid") }
ensure
  driver.quit
end
```

### 戻る・進む
```
driver.navigate.back
driver.navigate.forward
```

### ドラッグ＆ドロップ
```
element = driver.find_element(:name => 'source')
target = driver.find_element(:name => 'target')

driver.action.drag_and_drop(element, target).perform
```

### ページ情報・タイトル・HTMLを取得する
```
driver = Selenium::WebDriver.for :firefox
driver.get "http://www.example.com/"

p driver.current_url
p driver.title
p driver.page_source
```

### スクリーンショットを撮影する
```
driver = Selenium::WebDriver.for :firefox
driver.get "http://google.com"
driver.save_screenshot "/tmp/google.png"
```

### 複数ウィンドウを開く
```
driver = Selenium::WebDriver.for :firefox
driver.get "http://www.example.com/"

driver2 = Selenium::WebDriver.for :firefox
driver2.get "http://www.example.com/"
```

# TODO
- chromeなどで動かしてみる
- phantom.jsを動かしてみる。
-- http://qiita.com/kt3k/items/cea3c6de3c2337004a84

# 参考URL
- http://decknotes.net/slides/33
- Xvfb を利用したヘッドレスブラウザテスト
-- http://qiita.com/kt3k/items/cea3c6de3c2337004a84
