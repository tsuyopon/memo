# 概要
runcはDocker社が発表した新しいコンテナランタイムのCLIツールでOCI(Open Container Initiative)のコンテナ技術標準仕様を満たしています。
runC という CLI ツールだけでコンテナの起動が可能になった。コンテナは、runC の子プロセスとして起動される。

runC はコンテナの定義情報が書かれたJSONファイルに従いコンテナを作成します。
デフォルトでは、カレントディレクトリにある config.json というファイルが読み込まれるので、その点注意してください。

# 詳細

### runc経由でコンテナを作成してみる

あらかじめROOT配下にファイルシステムを生成しておく必要があります。
```
$ mkdir /mycontainer
$ cd /mycontainer
```

config.jsonはrun specでスケルトンを生成すると、そのスケルトンの中にはrootfsディレクトリをルートとして読み込むように設定が記述されています。
ですので、あらかじめrootfsディレクトリをさくせいしておきます。
```
$ mkdir rootfs
```

自分の場合、手元のdocker imageにnginxがありましたのでこれをそのまま流用します。
docker exportでtarにしたものを、パイプで展開してrootfs配下に配置します。
```
$ sudo sh -c "docker export `sudo docker create nginx` | tar -C rootfs -xvf -"
```

rootfsディレクトリの中にはnginxのイメージが展開できたことを確認できます
```
$ ls rootfs/
bin  boot  dev  docker-entrypoint.d  docker-entrypoint.sh  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
```

runc経由でコンテナを起動するためにあらかじめconfig.jsonというファイルを作成しておく必要があります。このファイルはrun specを実行するとconfig.jsonを生成してくれます。
```
$ ls
$ runc spec
$ ls
config.json
```

このconfig.jsonは何も修正しなくてもそのままコンテナ起動に使えます。では起動してみます。runc runの引数にはROOT配下のディレクトリを指定する必要があります。
```
$ sudo runc run mycontainer
# pwd
/
```

今度はconfig.jsonがrunc runに与える影響を確認するために少しだけ修正してみます。config.jsonでpwdを変えてみてください。
```
< 		"cwd": "/",
---
> 		"cwd": "/tmp",
```

再度、コンテナを起動してみると、カレントディレクトリは/tmpに変化したことが確認できます。
```
$ sudo runc run mycontainer
# pwd
/tmp
```


- 参考: https://blog.selectel.com/managing-containers-runc/

### runc specで作成したデフォルトのconfig.json
参考までにデフォルトで生成されるrunc specの雛形を添付しておきます。
```
$ cat config.json 
{
	"ociVersion": "1.0.1-dev",
	"process": {
		"terminal": true,
		"user": {
			"uid": 0,
			"gid": 0
		},
		"args": [
			"sh"
		],
		"env": [
			"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			"TERM=xterm"
		],
		"cwd": "/",
		"capabilities": {
			"bounding": [
				"CAP_AUDIT_WRITE",
				"CAP_KILL",
				"CAP_NET_BIND_SERVICE"
			],
			"effective": [
				"CAP_AUDIT_WRITE",
				"CAP_KILL",
				"CAP_NET_BIND_SERVICE"
			],
			"inheritable": [
				"CAP_AUDIT_WRITE",
				"CAP_KILL",
				"CAP_NET_BIND_SERVICE"
			],
			"permitted": [
				"CAP_AUDIT_WRITE",
				"CAP_KILL",
				"CAP_NET_BIND_SERVICE"
			],
			"ambient": [
				"CAP_AUDIT_WRITE",
				"CAP_KILL",
				"CAP_NET_BIND_SERVICE"
			]
		},
		"rlimits": [
			{
				"type": "RLIMIT_NOFILE",
				"hard": 1024,
				"soft": 1024
			}
		],
		"noNewPrivileges": true
	},
	"root": {
		"path": "rootfs",
		"readonly": true
	},
	"hostname": "runc",
	"mounts": [
		{
			"destination": "/proc",
			"type": "proc",
			"source": "proc"
		},
		{
			"destination": "/dev",
			"type": "tmpfs",
			"source": "tmpfs",
			"options": [
				"nosuid",
				"strictatime",
				"mode=755",
				"size=65536k"
			]
		},
		{
			"destination": "/dev/pts",
			"type": "devpts",
			"source": "devpts",
			"options": [
				"nosuid",
				"noexec",
				"newinstance",
				"ptmxmode=0666",
				"mode=0620",
				"gid=5"
			]
		},
		{
			"destination": "/dev/shm",
			"type": "tmpfs",
			"source": "shm",
			"options": [
				"nosuid",
				"noexec",
				"nodev",
				"mode=1777",
				"size=65536k"
			]
		},
		{
			"destination": "/dev/mqueue",
			"type": "mqueue",
			"source": "mqueue",
			"options": [
				"nosuid",
				"noexec",
				"nodev"
			]
		},
		{
			"destination": "/sys",
			"type": "sysfs",
			"source": "sysfs",
			"options": [
				"nosuid",
				"noexec",
				"nodev",
				"ro"
			]
		},
		{
			"destination": "/sys/fs/cgroup",
			"type": "cgroup",
			"source": "cgroup",
			"options": [
				"nosuid",
				"noexec",
				"nodev",
				"relatime",
				"ro"
			]
		}
	],
	"linux": {
		"resources": {
			"devices": [
				{
					"allow": false,
					"access": "rwm"
				}
			]
		},
		"namespaces": [
			{
				"type": "pid"
			},
			{
				"type": "network"
			},
			{
				"type": "ipc"
			},
			{
				"type": "uts"
			},
			{
				"type": "mount"
			}
		],
		"maskedPaths": [
			"/proc/acpi",
			"/proc/asound",
			"/proc/kcore",
			"/proc/keys",
			"/proc/latency_stats",
			"/proc/timer_list",
			"/proc/timer_stats",
			"/proc/sched_debug",
			"/sys/firmware",
			"/proc/scsi"
		],
		"readonlyPaths": [
			"/proc/bus",
			"/proc/fs",
			"/proc/irq",
			"/proc/sys",
			"/proc/sysrq-trigger"
		]
	}
}
```

### config.jsonの仕様はどこにあるのか?
以下で定義されています。
- https://github.com/opencontainers/runtime-spec

### runcで管理されているリストを表示する
```
$ sudo runc list
ID            PID         STATUS      BUNDLE         CREATED                          OWNER
mycontainer   5774        running     /mycontainer   2020-08-05T02:35:23.719325608Z   root
```

# 公式資料
- github runc
  - https://github.com/opencontainers/runc/blob/master/README.md
- OCI標準config.jsonの仕様
  - https://github.com/opencontainers/runtime-spec
- 公式ブログ
  - https://www.docker.com/blog/runc/

# 参考参考
- コンテナ作成で参考にした資料
  - https://blog.selectel.com/managing-containers-runc/
- youtube: runC: The little engine that could (run Docker containers) - Black Belt Track
  - https://www.youtube.com/watch?v=ZAhzoz2zJj8

