# 概要
inspecはChefが開発したテスト用フレームワークで、環境構築が正しく行われているかをテストするためのフレームワークです。
Rubyで記述されており環境構築ツールで有名なChefが開発しています。


InSpec と同系のツールに serverspec というフレームワークがあります。
もともと InSpec は serverspec の拡張として作られていたため、テストコードの記述の仕方もよく似ています。しかし InSpec の方がセキュリティやコンプライアンスのテストなど serverspec よりも幅広いテストが可能となっています。

- 参考: マイグレーションガイド
  - https://docs.chef.io/inspec/migration/


# inspecを使ってみる
以下のコマンドで雛形を作成することができます。
```
$ inspec init profile server01 

 ─────────────────────────── InSpec Code Generator ─────────────────────────── 

Creating new profile at /Users/tsuyoshi/git/memo/Chef/test/server01
 • Creating file README.md
 • Creating directory controls
 • Creating file controls/example.rb
 • Creating file inspec.yml
```

```
$ tree .
.
└── server01
    ├── README.md
    ├── controls
    │   └── example.rb
    └── inspec.yml

2 directories, 3 files
```

デフォルトのテストを見てみます。/tmpディレクトリに関するテストが存在しています。
```
$ cat controls/example.rb 
# copyright: 2018, The Authors

title "sample section"

# you can also use plain tests
describe file("/tmp") do
  it { should be_directory }
end

# you add controls here
control "tmp-1.0" do                        # A unique ID for this control
  impact 0.7                                # The criticality, if this control fails.
  title "Create /tmp directory"             # A human-readable title
  desc "An optional description..."
  describe file("/tmp") do                  # The actual test
    it { should be_directory }
  end
end
```

ではinspec initで作成したテスト雛形を実行してみます。
```
$ inspec exec ../server01/

Profile: InSpec Profile (server01)
Version: 0.1.0
Target:  local://

  ✔  tmp-1.0: Create /tmp directory
     ✔  File /tmp is expected to be directory

  File /tmp
     ✔  is expected to be directory

Profile Summary: 1 successful control, 0 control failures, 0 controls skipped
Test Summary: 2 successful, 0 failures, 0 skipped
```


# inspecコマンドについて

### inspecテストを実行する
ファイルを指定する場合
```
$ inspec exec xxxx.rb -t ssh://<user>:<pass>@<host>:<port>
```

テストディレクトリを指定する場合(再帰的にテストが実行される)
```
$ inspec exec testdir/ -t ssh://<user>:<pass>@<host>:<port>
```


# 公式資料
- github: 本家ソースコード
  - https://github.com/inspec/inspec
- InSpec Resources Reference
  - 基本的にはここを参照すること
  - https://docs.chef.io/inspec/resources/
