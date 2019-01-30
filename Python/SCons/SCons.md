# SConsとは
SCons(A Software construction tool)はPython製のMake代替となるツールです。
Autotools機能とccacheのデータ蓄積のコンパイラキャッシュの機能をあわせもっているようだ。
- 参考
  - https://github.com/SCons/scons/wiki/AboutSCons

SConsビルドエンジンは
- 参考
  - https://github.com/SCons/scons/wiki/BasicConcepts
  - https://legacy.python.org/workshops/2002-02/papers/16/index.htm#SECT-DESIGN

# インストール
pipからあっさりとインストールすることができます。
```
$ pip install scons
Collecting scons
  Downloading https://files.pythonhosted.org/packages/13/31/43b96f5b79731468a6731e4dbc71601f67fdeddad053bd4f1d1e2f0dbeec/scons-3.0.4-py2.py3-none-any.whl (829kB)
    100% |################################| 839kB 2.6MB/s 
Installing collected packages: scons
Successfully installed scons-3.0.4
```

# 基本機能

### ドライランを実行する
これから実行されるコマンドを画面上に表示してくれます。
```
$ scons . -n
```

### 実行する
```
$ scons .
```

### クリーンする
```
$ scons -c .
```
生成されたディレクトリは削除されないみたい


### ソースコード、バイナリ、コマンドなどの依存関係をtree状で表示する
```
$ scons --tree=all .
scons: Reading SConscript files ...
scons: done reading SConscript files.
Parts: Updating disk
Parts: Updating disk - Done
Parts: Loaded 1 Parts                                                                                                                                        
scons: Building targets ...
scons: building associated VariantDir targets: _build/build_debug_posix-x86_64/symlinks/__oot _build/build_debug_posix-x86_64/symlinks .                     
scons: `.' is up to date.                                                                                                                                    
+-.
  +-__rt
  | +-__rt/home
  |   +-__rt/home/tsuyoshi
  |     +-__rt/home/tsuyoshi/parts
  |       +-__rt/home/tsuyoshi/parts/samples
  +-_build
  | +-_build/build_debug_posix-x86_64
  |   +-_build/build_debug_posix-x86_64/symlinks
  |     +-_build/build_debug_posix-x86_64/symlinks/__oot
  |     +-_build/build_debug_posix-x86_64/symlinks/__rt
  |     | +-_build/build_debug_posix-x86_64/symlinks/__rt/home
  |     |   +-_build/build_debug_posix-x86_64/symlinks/__rt/home/tsuyoshi
  |     |     +-_build/build_debug_posix-x86_64/symlinks/__rt/home/tsuyoshi/parts
  |     |       +-_build/build_debug_posix-x86_64/symlinks/__rt/home/tsuyoshi/parts/samples
  |     |         +-_build/build_debug_posix-x86_64/symlinks/__rt/home/tsuyoshi/parts/samples/symlinks
  |     +-_build/build_debug_posix-x86_64/symlinks/libsymlinks.so
  |     | +-_build/build_debug_posix-x86_64/symlinks/libsymlinks.so.1
  |     | | +-_build/build_debug_posix-x86_64/symlinks/libsymlinks.so.1.0
  |     | |   +-_build/build_debug_posix-x86_64/symlinks/symlinks.pic.o
  |     | |   | +-symlinks.c
  |     | |   | +-symlinks.h
  |     | |   | +-/usr/bin/gcc
  |     | |   +-/usr/bin/gcc
  |     | |   +-/usr/bin/objcopy
  |     | |   +-/usr/bin/chmod
  |     | +-_build/build_debug_posix-x86_64/symlinks/libsymlinks.so.1.0
  |     |   +-_build/build_debug_posix-x86_64/symlinks/symlinks.pic.o
  |     |   | +-symlinks.c
  |     |   | +-symlinks.h
  |     |   | +-/usr/bin/gcc
  |     |   +-/usr/bin/gcc
  |     |   +-/usr/bin/objcopy
  |     |   +-/usr/bin/chmod
  |     +-_build/build_debug_posix-x86_64/symlinks/libsymlinks.so.1
```


### ファイルのチェック
カレントディレクトリ中にある以下のL627に記述されているファイルのチェックを行う
```
 621 def _SConstruct_exists(dirname='', repositories=[], filelist=None):
 622     """This function checks that an SConstruct file exists in a directory.
 623     If so, it returns the path of the file. By default, it checks the
 624     current directory.
 625     """
 626     if not filelist:
 627         filelist = ['SConstruct', 'Sconstruct', 'sconstruct', 'SConstruct.py', 'Sconstruct.py', 'sconstruct.py']
 628     for file in filelist:
 629         sfile = os.path.join(dirname, file)
 630         if os.path.isfile(sfile):
 631             return sfile
 632         if not os.path.isabs(sfile):
 633             for rep in repositories:
 634                 if os.path.isfile(os.path.join(rep, sfile)):
 635                     return sfile
 636     return None
```


# ヘルプ
公式サイトなどのURLからでも可能だが、sconsのmanコマンドがあるのでそちらを参照にすること
```
$ man scons
```

hオプションを指定するとコマンドラインヘルプを確認することができます。
```
$ scons -h
scons: Reading SConscript files ...
scons: done reading SConscript files.
usage: scons [OPTION] [TARGET] ...

SCons Options:
  -b, -d, -e, -m, -S, -t, -w, --environment-overrides, --no-keep-going,
  --no-print-directory, --print-directory, --stop, --touch
                              Ignored for compatibility.
  -c, --clean, --remove       Remove specified targets and dependencies.
  -C DIR, --directory=DIR     Change to DIR before doing anything.
  --cache-debug=FILE          Print CacheDir debug info to FILE.
  --cache-disable, --no-cache
                              Do not retrieve built targets from CacheDir.
  --cache-force, --cache-populate
                              Copy already-built targets into the CacheDir.
  --cache-readonly            Do not update CacheDir with built targets.
  --cache-show                Print build actions for files from CacheDir.
  --config=MODE               Controls Configure subsystem: auto, force,
                                cache.
  -D                          Search up directory tree for SConstruct,
                                build all Default() targets.
  --debug=TYPE                Print various types of debugging information:
                                count, duplicate, explain, findlibs, includes,
                                memoizer, memory, objects, pdb, prepare,
                                presub, stacktrace, time.
  --diskcheck=TYPE            Enable specific on-disk checks.
  --duplicate=DUPLICATE       Set the preferred duplication methods. Must be
                                one of hard-soft-copy, soft-hard-copy,
                                hard-copy, soft-copy, copy
  --enable-virtualenv         Import certain virtualenv variables to SCons
  -f FILE, --file=FILE, --makefile=FILE, --sconstruct=FILE
                              Read FILE as the top-level SConstruct file.
  -h, --help                  Print defined help message, or this one.
  -H, --help-options          Print this message and exit.
  -i, --ignore-errors         Ignore errors from build actions.
  -I DIR, --include-dir=DIR   Search DIR for imported Python modules.
  --ignore-virtualenv         Do not import virtualenv variables to SCons
  --implicit-cache            Cache implicit dependencies
  --implicit-deps-changed     Ignore cached implicit dependencies.
  --implicit-deps-unchanged   Ignore changes in implicit dependencies.
  --interact, --interactive   Run in interactive mode.
  -j N, --jobs=N              Allow N jobs at once.
  -k, --keep-going            Keep going when a target can't be made.
  --max-drift=N               Set maximum system clock drift to N seconds.
  --md5-chunksize=N           Set chunk-size for MD5 signature computation to
                                N kilobytes.
  -n, --no-exec, --just-print, --dry-run, --recon
                              Don't build; just print commands.
  --no-site-dir               Don't search or use the usual site_scons dir.
  --profile=FILE              Profile SCons and put results in FILE.
  -q, --question              Don't build; exit status says if up to date.
  -Q                          Suppress "Reading/Building" progress messages.
  --random                    Build dependencies in random order.
  -s, --silent, --quiet       Don't print commands.
  --site-dir=DIR              Use DIR instead of the usual site_scons dir.
  --stack-size=N              Set the stack size of the threads used to run
                                jobs to N kilobytes.
  --taskmastertrace=FILE      Trace Node evaluation to FILE.
  --tree=OPTIONS              Print a dependency tree in various formats: all,
                                derived, prune, status.
  -u, --up, --search-up       Search up directory tree for SConstruct,
                                build targets at or below current directory.
  -U                          Search up directory tree for SConstruct,
                                build Default() targets from local SConscript.
  -v, --version               Print the SCons version number and exit.
  --warn=WARNING-SPEC, --warning=WARNING-SPEC
                              Enable or disable warnings.
  -Y REPOSITORY, --repository=REPOSITORY, --srcdir=REPOSITORY
                              Search REPOSITORY for source and target files.

Local Options:
  --console-stream=CONSOLE-STREAM
                              Control how Parts maps the console stream.
                                Values can be none, tty, con:, stdout, stderr
  --show-progress=SHOW_PROGRESS
                              Controls if progress state is shown
  --hide-progress             Controls if progress state is shown
  --build-branch=BUILD_BRANCH, --bb=BUILD_BRANCH
                              Controls which Branch to used by smart SVN
                                logic.
  --use-parts-site=USE_PART_SITE
                              User provided part-site path. Overides all
                                default location.
  --disable-global-parts-site
                              Disable Parts from using the part-site location
                                in the system or user areas.
  --use-env                   Force use of shell environment. Overrides normal
                                tools path setup
  --verbose=VERBOSE           Control the level of detailed verbose
                                information printed
  --trace=TRACE               Control the level of trace information printed
  --log=LOGGER                True to use default logger, else name of logger
                                to use
  --build-config=BUILD_CONFIG, --buildconfig=BUILD_CONFIG,
  --bldcfg=BUILD_CONFIG, --bcfg=BUILD_CONFIG, --cfg=BUILD_CONFIG
                              The configuration to use
  --tool-chain=TOOL_CHAIN, --toolchain=TOOL_CHAIN, --tc=TOOL_CHAIN
                              Tool chains to use for build
  --mode=MODE                 Values used to control different build mode for
                                a given part
  --disable-parts-cache       Disable Parts data cache from being used
  --load-logic=LOAD_LOGIC, --ll=LOAD_LOGIC
                              Tells Parts what logic to use when loading
                                files. Options are "all", "target", "min",
                                "unsafe", "default"
  --disable-color=USE_COLOR   Controls if console color support is used
  --enable-color=USE_COLOR, --use-color=USE_COLOR, --color=USE_COLOR
                              Controls if console color support is used
  --ccopy=CCOPY_LOGIC, --ccopy-logic=CCOPY_LOGIC, --copy-logic=CCOPY_LOGIC
                              Control how Parts copy logic will work must be
                                hard-soft-copy,soft-hard-copy, soft-copy,
                                hard-copy, copy
  --vcs-update=UPDATE, --update=UPDATE
                              Controls if Parts should update the Vcs object,
                                and which Parts to update.
  --enable-vcs-clean=VCS_CLEAN, --vcs-clean=VCS_CLEAN
                              Controls if VCS update should ensure a clean,
                                unmodifed, factory defaults update.
  --enable-vcs-retry=VCS_RETRY, --vcs-retry=VCS_RETRY
                              Controls if an failure with a VCS update or
                                checkout is allow to retry the update by
                                removing the existing code
  --vcs-logic=VCS_LOGIC       Control logic of how Parts will automatically do
                                vcs up date checks. Values must be none,
                                exists, check, force
  --vcs-job=VCS_JOBS, --vcsj=VCS_JOBS, --vj=VCS_JOBS
                              Level of concurrent VCS checkouts/updates that
                                can happen at once. Defaults to -j value if
                                not set
  --disable-section-suppression
                              Disable process suppression of any sections
                                defined in a Part via the SUPPRESS_SECTION
                                variable
  --per-thread-logging=THREAD_LOGGING_PATH
                              Enable per-thread task logging to the specified
                                directory
  --cfg-file=CFG_FILE, --config-file=CFG_FILE
                              Configuration file used to store common settings
  --vcs-policy=VCS_POLICY     Policy in how Parts should react if the
                                automatic vcs check find that it is out of
                                date. The policy values can be warning, error,
                                message_update, warning-update, update,
                                checkout-warning, checkout-error
  --target=TARGET_PLATFORM, --target-platform=TARGET_PLATFORM
                              Sets the default TARGET_PLATFORM use for cross
                                builds
```

# 公式関連資料
- 公式サイト
  - https://www.scons.org/
- 公式ドキュメント
  - https://scons.org/documentation.html
  - https://scons.org/docversions.html
    - バージョンごとに様々な形式のmanpageのファイルが用意されているようです。
    - 例えば、3.0.4のHTMLバージョンだと
      - https://scons.org/doc/3.0.4/HTML/scons-man.html
- github
  - https://github.com/SCons/scons
- The SCons Wiki:
  - https://github.com/SCons/scons/wiki
  - チュートリアル
    - https://github.com/SCons/scons/wiki/SconsTutorial1
    - https://github.com/SCons/scons/wiki/SconsTutorial2

# 実装詳細資料
- SCons Design and Implementation
  - クラス間の関係図なども記載しているのでとっても貴重な資料
  - https://legacy.python.org/workshops/2002-02/papers/16/index.htm

# 日本語関連資料
- SCons: wikipedia
  - https://ja.wikipedia.org/wiki/SCons
- SCons入門(1) 〜 (3)
  - http://d.hatena.ne.jp/pashango_p/20110226/1298733157
  - http://d.hatena.ne.jp/pashango_p/20110228/1298857832
  - http://d.hatena.ne.jp/pashango_p/20110301/1298993461
- SConsチートシート
  - http://m5knt.hatenablog.com/entry/2013/03/29/000157

