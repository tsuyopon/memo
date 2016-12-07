# 概要
npmコマンドについてまとめておくことにする。
今回試したバージョンは次の通り
```
$ npm --version
2.1.18
```

# 参照

### インストールされているパッケージを参照する
depthは表示階層を表す。--depthのオプションがなければ全ての階層を表示する。
```
$ npm list --depth=0  [-g]
/Users/tsuyoshi/hoge
├── express@4.13.0
└── jade@1.11.0
```

### リリースされているバージョンを確認する
```
$ npm info knockout versions
 
[ '2.1.0-pre',
  '2.1.0',
  '2.2.1',
  '2.3.0-pre',
  '2.3.0-rc',
  '2.3.0',
  '3.0.0',
  '3.1.0',
  '3.2.0',
  '3.3.0',
  '3.4.0',
  '3.4.1' ]
```

### パッケージ情報を参照する
package.jsonを表示しているようだ。
```
$ npm info knockout
 
{ name: 'knockout',
  description: 'Knockout makes it easier to create rich, responsive UIs with JavaScript',
  'dist-tags': { latest: '3.4.1' },
  versions: 
   [ '2.1.0-pre',
     '2.1.0',
     '2.2.1',
     '2.3.0-pre',
     '2.3.0-rc',
     '2.3.0',
     '3.0.0',
     '3.1.0',
     '3.2.0',
     '3.3.0',
     '3.4.0',
     '3.4.1' ],
  maintainers: 
   [ 'mtscout6 <mtscout6@gmail.com>',
     'stevesanderson <steve@codeville.net>',
     'mbest <mbest@dasya.com>' ],
  time: 
   { modified: '2016-11-17T11:42:00.165Z',
     created: '2012-03-10T21:19:22.359Z',
     '2.1.0pre': '2012-03-10T21:19:24.470Z',
     '2.1.0': '2012-05-09T12:50:14.380Z',
     '2.2.1': '2013-02-27T11:25:55.841Z',
     '2.3.0pre': '2013-03-11T09:19:13.888Z',
     '2.3.0rc': '2013-06-20T01:21:12.745Z',
     '2.3.0': '2013-07-08T19:22:37.162Z',
     '3.0.0': '2013-10-25T21:36:12.157Z',
     '2.1.0-pre': '2014-03-07T21:52:13.452Z',
     '2.3.0-pre': '2014-03-07T21:52:13.452Z',
     '2.3.0-rc': '2014-03-07T21:52:13.452Z',
     '3.1.0': '2014-03-07T21:58:27.633Z',
     '3.2.0': '2014-08-17T00:28:11.936Z',
     '3.3.0': '2015-02-18T22:24:14.032Z',
     '3.4.0': '2015-11-17T00:32:57.780Z',
     '3.4.1': '2016-11-08T07:13:32.816Z' },
  author: 'The Knockout.js team',
  repository: 
   { type: 'git',
     url: 'git+https://github.com/knockout/knockout.git' },
  readmeFilename: 'README.md',
  bugs: { url: 'https://github.com/knockout/knockout/issues' },
  license: 'MIT',
  homepage: 'http://knockoutjs.com/',
  users: 
   { milutinovici: true,
     alexandermac: true,
     greendwin: true,
     asereware: true,
     levani: true,
     nickeltobias: true,
     tobiasnickel: true,
     cascadejs: true,
     keeyanajones: true,
     retorillo: true,
     mrbgit: true,
     guypeer: true,
     pkhotpanya: true,
     hueby: true,
     lavysh: true,
     deneboulton: true },
  version: '3.4.1',
  main: 'build/output/knockout-latest.debug.js',
  scripts: 
   { prepublish: 'grunt',
     test: 'node spec/runner.node.js' },
  testling: 
   { preprocess: 'build/build.sh',
     html: 'spec/runner.html?src=build/output/knockout-latest.js&testling=true',
     browsers: 
      [ 'ie/6..latest',
        'chrome/20..latest',
        'firefox/3..latest',
        'safari/5.0.5..latest',
        'opera/11.0..latest',
        'iphone/6..latest',
        'ipad/6..latest' ] },
  licenses: 
   { type: 'MIT',
     url: 'http://www.opensource.org/licenses/mit-license.php' },
  devDependencies: 
   { grunt: '~0.4.1',
     'grunt-cli': '~0.1.0',
     'closure-compiler': '~0.2.1' },
  gitHead: '7a83820efc96d47742e2f8c9b4fcd2459c81dd21',
  dist: 
   { shasum: '8bd057bde8f7d0a02b93dda433c2a8d942d8a9a0',
     tarball: 'https://registry.npmjs.org/knockout/-/knockout-3.4.1.tgz' },
  directories: {} }
```

# インストール
### インストール
```
$ sudo npm install npm [-g]
```

バージョンを指定してインストールする
```
$ npm install cordova@5.4.1 [-g]
```

### アンインストール
```
$ npm uninstall express
```

# pacakge.json周り
### package.jsonを生成する。
以下のコマンドを実行するとインタラクティブに質問されて、最終的にpackage.jsonを生成します。
```
$ npm init
This utility will walk you through creating a package.json file.
It only covers the most common items, and tries to guess sane defaults.

See `npm help json` for definitive documentation on these fields
and exactly what they do.

Use `npm install <pkg> --save` afterwards to install a package and
save it as a dependency in the package.json file.

Press ^C at any time to quit.
name: (sample) hoge
version: (1.0.0) 
description: sample project.
entry point: (index.js) app.js
test command: 
git repository: 
keywords: 
author: 
license: (ISC) 
About to write to /Users/my_user/Development/node.js/sample/package.json:

{
  "name": "hoge",
  "version": "1.0.0",
  "description": "sample project.",
  "main": "app.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC"
}


Is this ok? (yes) yes
```

### package.jsonからインストールする
現在いるディレクトリにpackage.jsonが存在すれば以下のコマンドでpackage.jsonを参照してインストールされる
```
$ npm install
```

### パッケージインストール時にpackage.jsonに追加する
```
$ npm install --save <package-name>
```
- 開発環境のみに追加したい場合には次のようにする
```
$ npm install --save-dev <package-name>
```

# 設定関連

### 設定を参照する
```
$ npm config ls
; cli configs
user-agent = "npm/2.1.18 node/v0.10.35 darwin x64"

; builtin config undefined
prefix = "/usr/local"

; node bin location = /usr/local/bin/node
; cwd = /Users/tsuyoshi/hoge
; HOME = /Users/tsuyoshi
; 'npm config ls -l' to show all defaults.
```

### 設定する
何かを設定するのであれば次のように
```
$ npm config set foo bar
$ npm config get foo
bar
```

上記設定はnpmから起動したスクリプトで次のように環境変数から取得することができるようになります。
```
console.log(process.env.npm_config_foo) 
```

- 参考
 - http://memo.sugyan.com/entry/20110909/1315575343

# そのほか
### 検索する
```
$ npm search express
```

### npmのヘルプを表示する。
どのようなオプションがあるのかは以下で確認することができる。
ここには載せきれないほどのたくさんのオプションがある。
```
$ npm -l

Usage: npm <command>

where <command> is one of:

    adduser     npm adduser
                Then enter stuff at the prompts

    bin         npm bin
                npm bin -g
                (just prints the bin folder)

    bugs        npm bugs <pkgname>

    cache       npm cache add <tarball file>
                npm cache add <folder>
                npm cache add <tarball url>
                npm cache add <git url>
                npm cache add <name>@<version>
                npm cache ls [<path>]
                npm cache clean [<pkg>[@<version>]]

    completion  npm completion >> ~/.bashrc
                npm completion >> ~/.zshrc
                source <(npm completion)

    config      npm config set <key> <value>
                npm config get [<key>]
                npm config delete <key>
                npm config list
                npm config edit
                npm set <key> <value>
                npm get [<key>]

    dedupe      npm dedupe [pkg pkg...]

    deprecate   npm deprecate <pkg>[@<version>] <message>

    docs        npm docs <pkgname>
                npm docs .

    edit        npm edit <pkg>

    explore     npm explore <pkg> [ -- <cmd>]

    faq         npm faq

    get         npm get <key> <value> (See `npm config`)

    help        

    help-search npm help-search <text>

    init        npm init [--force/-f]

    install     npm install
                npm install <pkg>
                npm install <pkg>@<tag>
                npm install <pkg>@<version>
                npm install <pkg>@<version range>
                npm install <folder>
                npm install <tarball file>
                npm install <tarball url>
                npm install <git:// url>
                npm install <github username>/<github project>
                
                Can specify one or more: npm install ./foo.tgz bar@stable /some/folder
                If no argument is supplied and ./npm-shrinkwrap.json is 
                present, installs dependencies specified in the shrinkwrap.
                Otherwise, installs dependencies from ./package.json.

    link        npm link (in package dir)
                npm link <pkg> (link global into local)

    ls          npm ls

    outdated    npm outdated [<pkg> [<pkg> ...]]

    owner       npm owner add <username> <pkg>
                npm owner rm <username> <pkg>
                npm owner ls <pkg>

    pack        npm pack <pkg>

    prefix      npm prefix
                npm prefix -g
                (just prints the prefix folder)

    prune       npm prune

    publish     npm publish <tarball>
                npm publish <folder>
                
                Publishes '.' if no argument supplied

    rebuild     npm rebuild [<name>[@<version>] [name[@<version>] ...]]

    repo        npm repo <pkgname>

    restart     npm restart [-- <args>]

    root        npm root
                npm root -g
                (just prints the root folder)

    run-script  npm run-script <command> [-- <args>]

    search      npm search [some search terms ...]

    set         npm set <key> <value> (See `npm config`)

    shrinkwrap  npm shrinkwrap

    star        npm star <package> [pkg, pkg, ...]
                npm unstar <package> [pkg, pkg, ...]

    stars       npm stars [username]

    start       npm start [-- <args>]

    stop        npm stop [-- <args>]

    tag         npm tag <project>@<version> [<tag>]

    test        

    uninstall   npm uninstall <name>[@<version> [<name>[@<version>] ...]
                npm rm <name>[@<version> [<name>[@<version>] ...]

    unpublish   npm unpublish <project>[@<version>]

    update      npm update [pkg]

    version     npm version [<newversion> | major | minor | patch | prerelease | preminor | premajor ]
                
                (run in package dir)
                'npm -v' or 'npm --version' to print npm version (2.1.18)
                'npm view <pkg> version' to view a package's published version
                'npm ls' to inspect current package/dependency versions

    view        npm view pkg[@version] [<field>[.subfield]...]

    whoami      npm whoami
                (just prints username according to given registry)

npm <cmd> -h     quick help on <cmd>
npm -l           display full usage info
npm faq          commonly asked questions
npm help <term>  search for help on <term>
npm help npm     involved overview

Specify configs in the ini-formatted file:
    /Users/tsuyoshi/.npmrc
or on the command line via: npm <command> --key value
Config info can be viewed via: npm help config

npm@2.1.18 /usr/local/lib/node_modules/npm
```

### 特定のヘルプを表示する。
たとえば、expressのヘルプを表示したい場合
```
$ npm help express
Top hits for "express"
————————————————————————————————————————————————————————————————————————————————
npm apihelp view                                                       express:4
npm help view                                                          express:4
npm help package.json                                                  express:4
npm help search                                                        express:2
npm apihelp npm                                                        express:1
npm help coding-style                                                  express:1
————————————————————————————————————————————————————————————————————————————————
(run with -l or --long to see more context)

$ npm help express -l
npm apihelp view                                                       express:4
————————————————————————————————————————————————————————————————————————————————
all of the values from the objects in the list.  For example, to get all
the contributor names for the "express" project, you can do this:
    npm.commands.view(["express", "contributors.email"], callback)


npm help view                                                          express:4
————————————————————————————————————————————————————————————————————————————————
all of the values from the objects in the list.  For example, to get all
the contributor names for the "express" project, you can do this:
    npm view express contributors.email


npm help package.json                                                  express:4
————————————————————————————————————————————————————————————————————————————————
"dependencies": {
        "express": "visionmedia/express",
        "mocha": "visionmedia/mocha#4727d357ea"
(省略)
```

# TODO
- npm -lしたときのいろいろなオプションを試せていないので時間があるときに試してもいいかもしれない


# 参考URL
- github npm
 - https://github.com/npm/npm
- リリースバージョンなどはこちら
 - https://github.com/nodejs/node/releases
- https://docs.npmjs.com/
 - npm公式サイトでビデオ講義などもあるようだ
