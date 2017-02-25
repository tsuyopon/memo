# 概要
rubyのUnittestフレームワークであるrspecについて

以下に文法があるので参考にすること
- https://github.com/rspec/rspec-expectations


### はじめてのRspec
あらかじめrspecをインストールしておきます
```
$ gem install rspec
```

雛形を作成するにはinitを実行します。  
.rspecとspecディレクトリはレポジトリ直下に置かれる事が多いですのでレポジトリ直下で実行するのがいいかもしれません。
```
$ rspec --init
  create   .rspec
  create   spec/spec_helper.rb
```

.rspecファイルはrspecコマンドを実行した時に必ず追加されるオプションが格納されたファイルです。内部でspec_helperを呼び出します。
```
$ cat .rspec 
--color
--require spec_helper
```

大元のライブラリを配置します。
```
$ cat lib/dog.rb 
class Dog
  attr_accessor :name, :fangs

  def initialize(name="Pochi")
    @name = name
    @fangs = 2
  end

  def alived?
    true
  end
end
```

lib配下にライブラリを配置します。
```
$ cat spec/lib/dog_spec.rb 
require "spec_helper"
require "dog"

describe Dog do
  it "is named 'Pochi'" do
    dog = Dog.new
    expect(dog.name).to eq 'Pochi'
  end

  it "has fangs" do
    dog = Dog.new
    expect(dog.fangs).to eq 2
  end

  it "is alived" do
    dog = Dog.new
    expect(dog).to be_alived
  end
end
```

以上で次のディレクトリレイアウトになります。
```
$ tree .
.
|-- lib
|   `-- dog.rb
`-- spec
    |-- lib
    |   `-- dog_spec.rb
    `-- spec_helper.rb
```

レポジトリ直下でrspecコマンドを実行すればrspecテストを実行してくれます。
```
$ rspec 
...

Finished in 0.00555 seconds (files took 0.15489 seconds to load)
3 examples, 0 failures
```

以下に簡単な雛形(forkさせてもらったもの)を配置しています。
- https://github.com/tsuyopon/testing-with-rspec


### カバレッジテストを追加する
次のパッケージを利用します。
- https://github.com/colszowka/simplecov

パッケージをインストールします。
```
$ gem install simplecov
```


spec_helper.rbに以下のrequreとSimpleCov.startを追加する。
```
$ vim spec/spec_helper.rb
require 'simplecov'          #<=この行を追加

SimpleCov.start 'rails'      #<=この行を追加
RSpec.configure do |config|
```

rpsecを実行する。coverageを生成した旨がひょうじされる
```
$ bundle exec rspec spec/
...

Finished in 0.00582 seconds (files took 0.14344 seconds to load)
3 examples, 0 failures

Coverage report generated for RSpec to /home/tsuyoshi/gemtest/a/testing-with-rspec/spec/a/coverage. 0.0 / 0.0 LOC (100.0%) covered.
```

treeでcoverage配下のディレクトリ構造を見てみる。
```
$ tree  coverage/
coverage/
|-- assets
|   `-- 0.10.0
|       |-- application.css
|       |-- application.js
|       |-- colorbox
|       |   |-- border.png
|       |   |-- controls.png
|       |   |-- loading.gif
|       |   `-- loading_background.png
|       |-- favicon_green.png
|       |-- favicon_red.png
|       |-- favicon_yellow.png
|       |-- loading.gif
|       |-- magnify.png
|       `-- smoothness
|           `-- images
|               |-- ui-bg_flat_0_aaaaaa_40x100.png
|               |-- ui-bg_flat_75_ffffff_40x100.png
|               |-- ui-bg_glass_55_fbf9ee_1x400.png
|               |-- ui-bg_glass_65_ffffff_1x400.png
|               |-- ui-bg_glass_75_dadada_1x400.png
|               |-- ui-bg_glass_75_e6e6e6_1x400.png
|               |-- ui-bg_glass_95_fef1ec_1x400.png
|               |-- ui-bg_highlight-soft_75_cccccc_1x100.png
|               |-- ui-icons_222222_256x240.png
|               |-- ui-icons_2e83ff_256x240.png
|               |-- ui-icons_454545_256x240.png
|               |-- ui-icons_888888_256x240.png
|               `-- ui-icons_cd0a0a_256x240.png
`-- index.html

5 directories, 25 files
```

coverageディレクトリ直下にhtmlファイルがあるのでウェブサーバを起動すれば良い。
```
$ python -m SimpleHTTPServer 8080
```

あとはブラウザで以下のURLにアクセスすればOK
- http://localhost:8080/


### モックを作成する


# 参考URL
- はじめてのRSpec - まずテスト書いてからコード書くシンプルなチュートリアル
 - http://qiita.com/luckypool/items/e3662170033347510c3c
- https://github.com/rspec/rspec-expectations
 - expect関連のAPIについて役に立つページ
- カバレッジテスト結果を生成するための仕組みです。HTML用に加工してくれます。
 - https://github.com/colszowka/simplecov
