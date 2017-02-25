# 概要
rubyのUnittestフレームワークであるrspecについて

以下に文法があるので参考にすること
- https://github.com/rspec/rspec-expectations


## はじめてのRspec
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

## unittestファイルの説明
rspecのテストコードに出てくる以下の意味を押さえておきます。
- describe / it / expect の役割
- context の使い方
- before の使い方


### describe, expect, itについて
describeはテストのグループ化を宣言すること、itはテストを実行することです。
rspec2.10以前はexpectではなくshouldというものを使っていました。
```
describe '四則演算' do
  it '1 + 1 は 2 になること' do
    expect(1 + 1).to eq 2
  end

  it '1 - 1, 2 - 2 は 0 になること' do
    expect(1 - 1).to eq 0
    expect(2 - 2).to eq 0
  end
end
```

describeのネストも可能です
```
describe '四則演算' do
  describe '足し算' do
    it '1 + 1 は 2 になること' do
      expect(1 + 1).to eq 2
    end
  end
  describe '引き算' do
    it '10 - 1 は 9 になること' do
      expect(10 - 1).to eq 9
    end
  end
end
```

### contextについて
describeとあまり違いがよくわかりませんがcontextというものでグルーピングできるようです。  
contextの部分をdescribeと書いてもいいようなきもするが、、、　 
一応記事などをみると、describe はテストする対象をあらわし、 context はテストする時の状況(特定の条件)をあらわしているようだ。contextはdescribeのエイリアスらしい。
```
describe User do
  describe '#greet' do
    context '12歳以下の場合' do
      it 'ひらがなで答えること' do
        user = User.new(name: 'たろう', age: 12)
        expect(user.greet).to eq 'ぼくはたろうだよ。'
      end
    end
    context '13歳以上の場合' do
      it '漢字で答えること' do
        user = User.new(name: 'たろう', age: 13)
        expect(user.greet).to eq '僕はたろうです。'
      end
    end
  end
end
```

### beforeについて
事前に共通する項目や事前条件などがあればbeforeを記述します。  
以下の例では太郎を変数@paramに入れています。
```
describe User do
  describe '#greet' do
    before do
      @params = { name: 'たろう' }
    end
    context '12歳以下の場合' do
      it 'ひらがなで答えること' do
        user = User.new(@params.merge(age: 12))
        expect(user.greet).to eq 'ぼくはたろうだよ。'
      end
    end
    context '13歳以上の場合' do
      it '漢字で答えること' do
        user = User.new(@params.merge(age: 13))
        expect(user.greet).to eq '僕はたろうです。'
      end
    end
  end
end
```


## カバレッジテストを追加する
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

# 参考URL
- RSpec公式ドキュメント
 - https://www.relishapp.com/rspec
- はじめてのRSpec - まずテスト書いてからコード書くシンプルなチュートリアル
 - http://qiita.com/luckypool/items/e3662170033347510c3c
- https://github.com/rspec/rspec-expectations
 - expect関連のAPIについて役に立つページ
- カバレッジテスト結果を生成するための仕組みです。HTML用に加工してくれます。
 - https://github.com/colszowka/simplecov

# TODO
- let / let! / subject の使い方
- shared_examples の使い方
- shared_context の使い方
- pending と skip の使い分け
