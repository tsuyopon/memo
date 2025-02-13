# 概要
Moleculeのセットアップ (python3.6以上、Ansible2.8以上が必要です。)

# インストール(MacOS)
下記でパッケージをインストールします。
```
$ pip3 install molecule[docker,lint]
$ python3 -m pip install ansible-lint molecule molecule-plugins[docker] docker flake8 flake8-bugbear flake8-docstrings flake8-import-order flake8-pylint pytest pytest-testinfra yamllint
```

今回インストールしたバージョンは下記の通りです
```
$ molecule --version
molecule 6.0.2 using python 3.10 
    ansible:2.15.2
    default:6.0.2 from molecule
```

# Molecule利用までの準備作業

コレクションの雛形を生成してくれるコマンドがあります。
foo.barは「[namespace].[collection]」の書式である必要があり、fooだけや、foo.bar.piyoだとエラーになります。
```
$ ansible-galaxy collection init foo.bar
- Collection foo.bar was created successfully
$ tree .
.
└── foo
    └── bar
        ├── README.md
        ├── docs
        ├── galaxy.yml
        ├── meta
        │   └── runtime.yml
        ├── plugins
        │   └── README.md
        └── roles

6 directories, 4 files
```

次に、roleの雛形を作ってくれるコマンドがありますので、それを実行します。
```
$ cd foo/bar/
$ ansible-galaxy role init my_role
- Role my_role was created successfully
$ tree ~/ansibletest/
/home/tsuyoshi/ansibletest/
└── foo
    └── bar
        ├── README.md
        ├── docs
        ├── galaxy.yml
        ├── meta
        │   └── runtime.yml
        ├── my_role
        │   ├── README.md
        │   ├── defaults
        │   │   └── main.yml
        │   ├── files
        │   ├── handlers
        │   │   └── main.yml
        │   ├── meta
        │   │   └── main.yml
        │   ├── tasks
        │   │   └── main.yml
        │   ├── templates
        │   ├── tests
        │   │   ├── inventory
        │   │   └── test.yml
        │   └── vars
        │       └── main.yml
        ├── plugins
        │   └── README.md
        └── roles
15 directories, 12 files
```

次に、foo.barのロールを実行させるためにplaybookを作成します。
```
$ mkdir playbooks
$ vim playbooks/my_playbook.yml
---
- name: Test new role from within this playbook
  hosts: localhost
  gather_facts: false
  tasks:
    - name: Testing role
      ansible.builtin.include_role:
        name: foo.bar.my_role
        tasks_from: main.yml
```

続いて、Moleculeを実行するために必要なファイルを生成します。「molecule init scenario」により生成します。
```
$ mkdir extensions
$ cd extensions/
$  molecule init scenario
INFO     Initializing new scenario default...

PLAY [Create a new molecule scenario] ******************************************

TASK [Check if destination folder exists] **************************************
changed: [localhost]

TASK [Check if destination folder is empty] ************************************
ok: [localhost]

TASK [Fail if destination folder is not empty] *********************************
skipping: [localhost]

TASK [Expand templates] ********************************************************
changed: [localhost] => (item=molecule/default/create.yml)
changed: [localhost] => (item=molecule/default/converge.yml)
changed: [localhost] => (item=molecule/default/molecule.yml)
changed: [localhost] => (item=molecule/default/destroy.yml)

PLAY RECAP *********************************************************************
localhost                  : ok=3    changed=2    unreachable=0    failed=0    skipped=1    rescued=0    ignored=0

INFO     Initialized scenario in /home/tsuyoshi/molecule/foo/bar/extensions/molecule/default successfully.
$ tree .
.
└── molecule
    └── default
        ├── converge.yml
        ├── create.yml
        ├── destroy.yml
        └── molecule.yml

2 directories, 4 files
```

生成後の全体的なディレクトリレイアウトは下記の通りです。
```
$ cd ~/molecule/
$ tree .
.
├── foo
│ └── bar
│     ├── README.md
│     ├── docs
│     ├── extensions
│     │ └── molecule
│     │     └── default
│     │         ├── converge.yml
│     │         ├── create.yml
│     │         ├── destroy.yml
│     │         └── molecule.yml
│     ├── galaxy.yml
│     ├── meta
│     │ └── runtime.yml
│     ├── my_role
│     │ ├── README.md
│     │ ├── defaults
│     │ │ └── main.yml
│     │ ├── files
│     │ ├── handlers
│     │ │ └── main.yml
│     │ ├── meta
│     │ │ └── main.yml
│     │ ├── tasks
│     │ │ └── main.yml
│     │ ├── templates
│     │ ├── tests
│     │ │ ├── inventory
│     │ │ └── test.yml
│     │ └── vars
│     │     └── main.yml
│     ├── plugins
│     │ └── README.md
│     └── roles
└── playbooks
  └── my_playbook.yml

19 directories, 17 files
```

雛形作成が何度かありましたが、やっとここまでで準備作業が完了です。


# Moleculeを使ってみる。
TBD

