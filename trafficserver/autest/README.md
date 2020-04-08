# 概要
trafficserver内部の仕組みでautestが利用されています。
ここではautestの使い方について記載します。

# 基本事項
- trafficserver/tests/autest.shを呼び出すことで実行します。 
- 以下のコマンドでも実行できます。
- autestコマンド実行時の際にはautestの拡張プラグイン(拡張子.test.ext)が読み込まれます。
  - trafficserverであれば、trafficserver/tests/gold_test/autest-site/配下に拡張プラグインである
- テストファイルは拡張子がtest.pyや.testでなければなりません(ハードコード)。autestはディレクトリ配下にこの拡張子のファイルが配置されていても実行してくれます。
- 最低限の起動に必要なファイルはtrafficserver/tests/gold_test/autest-site/min_cfg/に含まれています。
- 設定ファイルは基本的にはtraffic_layoutに配置されたconfigをコピーしたものから変更を行うことができます。records.configへの設定のoverrideやそれ以外の指定されている設定ファイル(内部でハードコード)への設定行追加が可能です。
- ログのチェックはデフォルトで「ERROR:」、「FATAL:」はチェックされるようにハードコードされています。


# autestコマンド

### autestで指定できる引数

- 参考: autestのソースコード
  - https://bitbucket.org/dragon512/reusable-gold-testing-system/src/4251b68398b0604b1d646e352f14a4963151130b/src/autest/__main__.py#lines-32
```
    run = setup.add_command("run", help='(Default Option) Runs tests')
    list = setup.add_command("list", help='Lists all the test available to Autest')

    setup.path_argument(
        ["-D", "--directory"],
        default=os.path.abspath('.'),
        help="The directory with all the tests in them")

    setup.path_list_argument(
        ["--autest-site"],
        help="A user provided autest-site director(y)ies to use instead of the default.")

    setup.path_argument(
        ["--sandbox"],
        default=os.path.abspath('./_sandbox'),
        exists=False,
        help="The root directory in which the tests will run")

    setup.list_argument(
        ["--env"],
        metavar="Key=Value",
        help="Set a variable to be used in the local test environment. Replaces value inherited from shell.")

    setup.list_argument(
        ["-f", "--filters"],
        dest='filters',
        default=['*'],
        help="Filter the tests run by their names")

    setup.add_argument(
        ['-V', '--version'], action='version',
        version='%(prog)s {0}'.format(autest.__version__))

    run.list_argument(
        ["-R", "--reporters"],
        default=['default'],
        help="Names of Reporters to use for report generation")

    run.add_argument(
        ["-j", "--jobs"],
        default=1,
        type=JobValues,
        help="The number of test to try to run at the same time")

    run.string_argument(
        ['-C', '--clean'],
        default='passed',
        help='''
        Level of cleaning for after a test is finished.
        all > exception > failed > warning > passed > skipped > unknown> none
        Defaults at passed
        ''')

    run.int_argument(
        ['--normalize-kill'],
        default=None,
        help='Normalizes the exit code when a process is given SIGKILL'
    )

    list.add_argument(
        ['--json'],
        action='store_true',
        help="outputs the list of available tests in JSON format"
    )
```

ats側のオプションは以下に指定されている
- 参考: trafficserverのinit.cli.extのソースコード
  - https://github.com/apache/trafficserver/blob/master/tests/gold_tests/autest-site/init.cli.ext#L31-L33
```
Settings.path_argument(["--ats-bin"],
                       required=True,
                       help="A user provided directory to ATS bin")
```


# 基本的な使い方
ここではテストファイルに指定できるロジックについて記載します。


### テストで利用するtrafficserverの起動
ATSサーバの起動は以下で行います。
```
ts = Test.MakeATSProcess("ts")
```

引数を指定することも可能なようです。
```
p = Test.MakeATSProcess("ts", select_ports=False)
```

### テストで利用するオリジンサーバの起動

オリジンサーバの起動はマイクロサーバという仕組みを使って行います。
```
server = Test.MakeOriginServer("server")
```

以下でテストのレスポンスを追加することができます。
```
request_header = {'timestamp': 100, "headers": "GET /test-1 HTTP/1.1\r\nHost: test-1\r\n\r\n", "body": ""} 
response_header = {'timestamp': 100,
                   "headers": "HTTP/1.1 200 OK\r\nTest: 1\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n", "body": "Test 1"}
server.addResponse("sessionlog.json", request_header, response_header)
server.addResponse("sessionlog.json",
                   {'timestamp': 101, "headers": "GET /test-2 HTTP/1.1\r\nHost: test-2\r\n\r\n", "body": ""},
                   {'timestamp': 101, "headers": "HTTP/1.1 200 OK\r\nTest: 2\r\nContent-Type: application/jason\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n", "body": "Test 2"}
                   )
server.addResponse("sessionlog.json",
                   {'timestamp': 102, "headers": "GET /test-3 HTTP/1.1\r\nHost: test-3\r\n\r\n", "body": ""},
                   {'timestamp': 102, "headers": "HTTP/1.1 200 OK\r\nTest: 3\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n", "body": "Test 3"}
                   )
server.addResponse("sessionlog.json",
                   {'timestamp': 103, "headers": "GET /test-4 HTTP/1.1\r\nHost: test-4\r\n\r\n", "body": ""},
                   {'timestamp': 103, "headers": "HTTP/1.1 200 OK\r\nTest: 4\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n", "body": "Test 4"}
                   )
server.addResponse("sessionlog.json",
                   {'timestamp': 104, "headers": "GET /test-5 HTTP/1.1\r\nHost: test-5\r\n\r\n", "body": ""},
                   {'timestamp': 104, "headers": "HTTP/1.1 200 OK\r\nTest: 5\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n", "body": "Test 5"}
                   )
```

### テストを追加する
テストの追加はTest.AddTestRunで指定します。
```
t = Test.AddTestRun("Test traffic server started properly")

p = t.Processes.Default
p.Command = "curl http://127.0.0.1:8080"
p.ReturnCode = 0
p.StartBefore(Test.Processes.ts, ready=When.PortOpen(8080))
```

### テスト実行後も起動しておいて欲しいプロセスを指定する。
一般的によく記述されるのが、trafficserverのインスタンス(ts)とオリジンサーバのインスタンス(server)の２つを指定します。
これによって、テスト実行後にこれら２つのプロセスが起動していることをチェックします。
```
t.StillRunningAfter = ts
t.StillRunningAfter = server
```

### 条件を指定して、条件がなければテストをskipさせる
以下の条件はテストの先頭に記載されることが多いです。


以下の例ではcurlが存在してなければテストをskipします。
```
Test.SkipUnless(Condition.HasProgram("curl", "Curl need to be installed on system for this test to work"))
```

以下の例ではプラグインが存在しなければテストをskipします。
```
Test.SkipUnless(
    Condition.PluginExists('a-plugin.so'),
)
```

コンパイル時に指定された機能をskip条件に指定することもできます。
```
Test.SkipUnless(
    Condition.HasATSFeature('TS_USE_TLS_ALPN'),
)
```

### recoreds.configの更新
配列で指定できます。
keyとして設定の識別子を指定して、右側にはその値を指定します。
```
ts.Disk.records_config.update({
    'proxy.config.net.connections_throttle': 100,
    'proxy.config.http.cache.http': 0
})
```

records.configはINT, STRING BOOLEANなどが指定されますが、それは配列の値として指定した型がint型、string型、bool型かを内部でハードコードで判定しています。


### remap.configの更新処理
```
ts.Disk.remap_config.AddLine(
    'map / http://localhost:{}/'.format(server.Variables.Port)
)
```

### ログに文言が含まれているかどうかのチェック
デフォルトではWARNやCRITのログはエラー扱いとなるが、ts.Disk.diags_log.Contentを+=ではなく=で定義することで上書き扱いとなる。
正規表現も指定できる
```
ts.Disk.diags_log.Content = Testers.ContainsExpression("ERROR: HTTP/2", "h2spec tests should have error log")
```

### ログに文言が含まれていないことをチェック
以下は+=でデフォルトのFATALやERROR文言の監視を含んでいる。=にすればこれらのデフォルト値は上書きされる。
```
ts.Disk.diags_log.Content += Testers.ExcludesExpression("loading", "should not contain loading")
```


# TIPS

### 同一ファイルに複数のテストが存在していた場合、テストが途中で失敗してもその後のテストを実行し続ける
```
Test.ContinueOnFail = True
```

### テストを遅延させて実行する
tr.DelayStartで指定した秒数を遅延させることができます。
```
tr = Test.AddTestRun()
tr.DelayStart = 10
tr.Processes.Default.Command = 'echo "Delay"'
tr.Processes.Default.ReturnCode = 0
```

### タイムアウト関連
TBD: 以下の2つの違いは...???
```
tr.Processes.Default.TimeOut = 5
tr.TimeOut = 5
```

### logging.yamlへの追加
以下に例を示す。
```
ts.Disk.logging_yaml.AddLines(
    '''
formats:
  - name: custom
    format: '%<{Content-Type}essh>'
logs:
  - filename: field-test
    format: custom
'''.split("\n")
)
```

### ATSでHTTPSを起動させたい

HTTPSの起動は少し面倒です。
予め秘密鍵(ssl/server.key)と対応する公開鍵(ssl/server.pem)を作成して、records.configに適切なHTTPS
```
ts.addSSLfile("ssl/server.pem")
ts.addSSLfile("ssl/server.key")

ts.Variables.ssl_port = 4443
ts.Disk.records_config.update({
    'proxy.config.diags.debug.enabled': 1,
    'proxy.config.diags.debug.tags': 'ssl_hook_test',
    'proxy.config.ssl.server.cert.path': '{0}'.format(ts.Variables.SSLDir),
    'proxy.config.ssl.server.private_key.path': '{0}'.format(ts.Variables.SSLDir),
    # enable ssl port
    'proxy.config.http.server_ports': '{0}:ssl'.format(ts.Variables.ssl_port),
    'proxy.config.ssl.client.verify.server':  0,
    'proxy.config.ssl.TLSv1_3': 0,
    'proxy.config.
```

なお、上記で指定する場合には4443ポートを指定しているので、Test.MakeATSProcessの引数で指定するselect_portsはfalseを指定しておいてください。
```
ts = Test.MakeATSProcess("ts", select_ports=False)
```

- https://github.com/apache/trafficserver/blob/8.0.7/tests/gold_tests/tls_hooks/tls_hooks.test.py


### 全部の出力をチェックする
```
ts.Streams.All = Testers.ContainsExpression(
    "\A(?:(?!{0}).)*{0}.*({0})?(?!.*{0}).*\Z".format(preacceptstring), "Pre accept message appears only once or twice", reflags=re.S | re.M)
```

### テストを追加する

### httpsを起動させる


### DNSサーバを起動する


### httpbinサーバを起動する
```
httpbin = Test.MakeHttpBinServer("httpbin")
```


# 資料
- autestの公式ドキュメント
  - https://autestsuite.bitbucket.io/
- autest (pypi.org)
  - https://pypi.org/project/autest/
- trafficserverのtestディレクトリは以下のREADME.md
  - https://github.com/apache/trafficserver/tree/8.0.7/tests
