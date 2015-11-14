cscopeだとPHPのソースコードを追いかける場合に不便を感じるのでGNU GLOBALを導入するとよさそうです。

### ソースコードからのインストール
即座に導入することができます。
$ wget http://tamacom.com/global/global-6.5.tar.gz
$ tar zxvf global-6.5.tar.gz
$ cd global-6.5
$ ./configure
$ make
$ sudo make install
$ which global
/usr/local/bin/global

### 使ってみる
ソースコードがあるトップディレクトリに移動してインデックスファイルを生成します。
$ cd <path>
$ sudo gtags -v
$ file G*
GPATH:  Berkeley DB 1.85/1.86 (Btree, version 3, native byte-order)
GRTAGS: Berkeley DB 1.85/1.86 (Btree, version 3, native byte-order)
TAGS:  Berkeley DB 1.85/1.86 (Btree, version 3, native byte-order)
このgtagsを実行したディレクトリ内部でglobalコマンドを使います。
以下はcakephpのソースコードを取得して展開した結果

ネット上からDownloadします。
$ unzip cakephp-2.6.7.zip
$ cd cakephp-2.6.7
$ sudo gtags -v

execute関数が定義されているファイルを出力してみます。
$ global execute
lib/Cake/Console/Command/Task/BakeTask.php
lib/Cake/Console/Command/Task/ControllerTask.php
lib/Cake/Console/Command/Task/DbConfigTask.php
lib/Cake/Console/Command/Task/ExtractTask.php
lib/Cake/Console/Command/Task/FixtureTask.php
lib/Cake/Console/Command/Task/ModelTask.php
lib/Cake/Console/Command/Task/PluginTask.php
lib/Cake/Console/Command/Task/ProjectTask.php
lib/Cake/Console/Command/Task/TestTask.php
lib/Cake/Console/Command/Task/ViewTask.php
lib/Cake/Model/Datasource/DboSource.php

execute関数が参照されているファイルを出力します。
$ global -r execute
lib/Cake/Console/Command/AclShell.php
lib/Cake/Console/Command/BakeShell.php
lib/Cake/Console/Command/I18nShell.php
lib/Cake/Console/Command/SchemaShell.php
lib/Cake/Console/Command/Task/ControllerTask.php
lib/Cake/Console/Command/Task/DbConfigTask.php
lib/Cake/Console/Command/Task/FixtureTask.php
lib/Cake/Console/Command/Task/ModelTask.php
lib/Cake/Console/Command/Task/ProjectTask.php
lib/Cake/Console/Command/Task/TestTask.php
lib/Cake/Console/Command/Task/ViewTask.php
lib/Cake/Model/Datasource/Database/Mysql.php
(以下略)

定義されている関数名を出力します。
$ global -f lib/Cake/Controller/Component/Auth/BaseAuthorize.php
BaseAuthorize      24 lib/Cake/Controller/Component/Auth/BaseAuthorize.php abstract class BaseAuthorize {
__construct        69 lib/Cake/Controller/Component/Auth/BaseAuthorize.php 	public function __construct(ComponentCollection $collection, $settings = array()) {
authorize          83 lib/Cake/Controller/Component/Auth/BaseAuthorize.php 	abstract public function authorize($user, CakeRequest $request);
controller         92 lib/Cake/Controller/Component/Auth/BaseAuthorize.php 	public function controller(Controller $controller = null) {
action            111 lib/Cake/Controller/Component/Auth/BaseAuthorize.php 	public function action(CakeRequest $request, $path = '/:plugin/:controller/:action') {
mapActions        153 lib/Cake/Controller/Component/Auth/BaseAuthorize.php 	public function mapActions($map = array()) {

「aaa」という文字列が含まれたファイルを検索する。
$ global -g aaa
lib/Cake/Test/Case/Model/ModelIntegrationTest.php
lib/Cake/Test/Case/Utility/StringTest.php
lib/Cake/TestSuite/templates/header.php

「exec」という文字列が含まれた関数名を検索して表示します。
$ global -c exec
executable
execute

上記で出力されたexecutableは以下の様にして定義元ファイルを確認できます。
$ global -r executable
lib/Cake/Test/Case/Utility/FileTest.php

-rオプションに限りませんがglobalコマンドで詳細を見る場合には-xを付与することで確認できます。
$ global -r -x executable
executable        353 lib/Cake/Test/Case/Utility/FileTest.php 		$this->assertFalse($someFile->executable());


### GLOBALオプション一覧
global 関数名          関数名からソースコード(定義)を検索する
global -r 関数名       関数名からソースコード(参照元)を検索する
global -f ファイル名   ファイルの中の関数一覧を取得する
global -c 文字列       文字列が含まれる関数一覧を検索する
global -g 検索文字列   ソースコードのgrepを行う
上記コマンドに対して-xオプションを付与することによって、詳細情報(行番号と内容)を出力することができます。

### VIMとの連携
ソースコードからインストールした場合、以下のようにfindで検索するとgtags.vimがあります。
$ find /usr/local/share/gtags -name gtags.vim
/usr/local/share/gtags/gtags.vim

個人環境設定としてこのプラグインをコピーします。
$ mkdir -p $HOME/.vim/plugin
$ cp /usr/local/share/gtags/gtags.vim $HOME/.vim/plugin/

デフォルトのgtags.vimの設定だと使いにくい部分があるので、gtags.vimの設定を上書きするために下記設定を
$HOME/.vimrcに追加します。

map <C-g> :Gtags 
map <C-h> :Gtags -f %<CR>
map <C-j> :GtagsCursor<CR>
map <C-n> :cn<CR>
map <C-p> :cp<CR>

定義元に遷移したい場合には、カーソルを合わせて「Ctrl-J」を押下する。
ジャンプした後に定義元に戻る場合には「Ctrl-O」とする。
次の候補や前の候補の場合には「Ctrl-N」「Ctrl-P」で移動します。
grepをかけたい場合には「Ctrl-G」してgrepしたい文言を入力します。
検索をかけて画面下に候補ウィンドウが表示されますが、これを消したい場合には「Ctrl-W,O」です。


### 参考URL
GNU GLOBALとvimで巨大なコードでも快適にコードリーディング
	http://blog.matsumoto-r.jp/?p=2369

ソースコードを快適に読むための GNU GLOBAL 入門(前編・中編・後編)
	http://www.machu.jp/diary/20090307.html
	http://www.machu.jp/diary/20090308.html
	http://www.machu.jp/diary/20090309.html
