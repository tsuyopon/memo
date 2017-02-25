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



# 参考URL
- はじめてのRSpec - まずテスト書いてからコード書くシンプルなチュートリアル
 - http://qiita.com/luckypool/items/e3662170033347510c3c
- https://github.com/rspec/rspec-expectations
 - expect関連のAPIについて役に立つページ
