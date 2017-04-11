# 概要
PHPパッケージ管理ツールのcomposerについてです。
composerはPHPには同梱されていませんが、php標準パッケージ管理ツールとしての地位を築きつつあります。

パッケージは次の箇所から探すようです。
- https://packagist.org/

# 詳細
### composerの導入について

composerをcurl経由で取得します。
```
$ curl -sS https://getcomposer.org/installer | php
Downloading...

Composer (version 1.4.1) successfully installed to: /home/tsuyoshi/php/composer.phar
Use it: php composer.phar

Some settings on your machine may cause stability issues with Composer.
If you encounter issues, try to change the following:

The OpenSSL library (1.0.0k-fips) used by PHP does not support TLSv1.2 or TLSv1.1.
If possible you should upgrade OpenSSL to version 1.0.1 or above.

$ ls
composer.phar
```

続いて、composer.jsonを作成します。ここにパッケージの依存などを記述します。
```
$ vim composer.json
$ cat composer.json
{
    "require": {
        "mockery/mockery": "*",
        "facebook/php-sdk": "v3.2.3"
    }
}
```

インストールを行います。更新したければinstallをupdateに変更します。
```
$ ./composer.phar install
Your version of PHP, 5.4.17, is affected by CVE-2013-6420 and cannot safely perform certificate validation, we strongly suggest you upgrade.
Loading composer repositories with package information
Updating dependencies (including require-dev)
Package operations: 3 installs, 0 updates, 0 removals
  - Installing facebook/php-sdk (v3.2.3): Downloading (100%)         
  - Installing hamcrest/hamcrest-php (v1.2.2): Downloading (100%)         
  - Installing mockery/mockery (0.9.9): Downloading (100%)         
Package facebook/php-sdk is abandoned, you should avoid using it. Use facebook/graph-sdk instead.
Writing lock file
Generating autoload files
```

composer.lockの現在インストールされたパッケージが記述されたファイルやvendorディレクトリが作成されます。
```
$ ls
composer.json  composer.lock  composer.phar  vendor
$ ls vendor/
autoload.php  composer  facebook  hamcrest  mockery
```

この後、パッケージを更新したい場合にはcomposer.jsonを更新して次のコマンドを実行するとvendorに新しいバージョンのパッケージが依存関係も含めてupdateされる。また、composer.lockファイルも更新される。
```
$ ./composer.phar update
```

### レポジトリに含めるファイルについて
次の3つを含めるのが一般的なレポジトリ生成の作法のようです。
- composer.phar
- composer.json
- composer.lock 

### オートローダーの機能について(vendor/autoload.php)
vendor/autoload.phpはcomposer.phar installした時に生成されるphpファイルです。
このファイルをrequireすることによってvendor/配下に配置されたライブラリをautoloadしてくれます。

また、次のようにcomposer.jsonに記載して実行すると、Moge\で始まる名前空間のautoloadをpsr-4に従ってsrc/配下で行います。
どういうことかというと、Moge\Model\Classという名前に対してsrc/model/Class.phpをオートロードするようになります。
```
    "autoload": {
        "psr-4": {
            "Moge\\": "src/"
        }
    },
```

このautoloadに関するcomposer.jsonの設定を後から付け加えた場合には、次のコマンドを実行するとvendor/autoload.phpに設定を加えることができます。
```
composer dump-autoload
```

# 参考URL
- composer公式サイト
  - https://packagist.org/
  - https://getcomposer.org/doc/01-basic-usage.md#package-versions

# TODO
ちゃんと全体をまとめたい
- composer 導入をまじめに考える
  - http://qiita.com/notona/items/c5a087d8dd446d315e6e
- PHP開発でComposerを使わないなんてありえない！基礎編
  - http://qiita.com/niisan-tokyo/items/8cccec88d45f38171c94
