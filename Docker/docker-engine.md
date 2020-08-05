# 概要
Docker Engineを直接操作して、dockerコマンドが行なっている裏側への理解を深めます。

v1.40のリファレンスは以下に存在しています。
- https://docs.docker.com/engine/api/v1.40/#

# 詳細

### Docker Engineのバージョンを確認する方法
docker versionコマンドを実行すると「API Version」が確認できます。このバージョンを参考にして該当のリファレンスを参照します。
```
$ docker version
Client: Docker Engine - Community
 Version:           19.03.12
 API version:       1.40
 Go version:        go1.13.10
 Git commit:        48a66213fe
 Built:             Mon Jun 22 15:41:33 2020
 OS/Arch:           darwin/amd64
 Experimental:      false

Server: Docker Engine - Community
 Engine:
  Version:          19.03.12
  API version:      1.40 (minimum version 1.12)
  Go version:       go1.13.10
  Git commit:       48a66213fe
  Built:            Mon Jun 22 15:49:27 2020
  OS/Arch:          linux/amd64
  Experimental:     false
 containerd:
  Version:          v1.2.13
  GitCommit:        7ad184331fa3e55e52b890ea95e65ba581ae3429
 runc:
  Version:          1.0.0-rc10
  GitCommit:        dc9208a3303feef5b3839f4323d9beb36df0a9dd
 docker-init:
  Version:          0.18.0
  GitCommit:        fec3683
```

unix domain socketを通じて上記の情報を取得することもできます。
```
$ curl --unix-socket /var/run/docker.sock http:/localhost/version
{"Platform":{"Name":"Docker Engine - Community"},"Components":[{"Name":"Engine","Version":"19.03.12","Details":{"ApiVersion":"1.40","Arch":"amd64","BuildTime":"2020-06-22T15:49:27.000000000+00:00","Experimental":"false","GitCommit":"48a66213fe","GoVersion":"go1.13.10","KernelVersion":"4.19.76-linuxkit","MinAPIVersion":"1.12","Os":"linux"}},{"Name":"containerd","Version":"v1.2.13","Details":{"GitCommit":"7ad184331fa3e55e52b890ea95e65ba581ae3429"}},{"Name":"runc","Version":"1.0.0-rc10","Details":{"GitCommit":"dc9208a3303feef5b3839f4323d9beb36df0a9dd"}},{"Name":"docker-init","Version":"0.18.0","Details":{"GitCommit":"fec3683"}}],"Version":"19.03.12","ApiVersion":"1.40","MinAPIVersion":"1.12","GitCommit":"48a66213fe","GoVersion":"go1.13.10","Os":"linux","Arch":"amd64","KernelVersion":"4.19.76-linuxkit","BuildTime":"2020-06-22T15:49:27.000000000+00:00"}
```

### コンテナに関する情報を取得する
「http:/localhost」や「http://v1.40」のようにバージョンを指定する方法でもいいようです。
```
$ curl --unix-socket /var/run/docker.sock http:/v1.40/containers/json?all=1
[{"Id":"1fb337af7fce551181dcc8b4470bb76b45e3c9e69ecc7cb58d0625d74782c742","Names":["/attack"],"Image":"golang","ImageID":"sha256:a794da9351a3b2f860cc9d8859f75c7722ea0eb3d482ceac2c44e20780743018","Command":"/bin/sh","Created":1596570739,"Ports":[],"Labels":{},"State":"created","Status":"Created","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[{"Type":"bind","Source":"/","Destination":"/host","Mode":"","RW":true,"Propagation":"rslave"}]},{"Id":"aa72f1c2e0a885d17b7007083bfc7fc6a87016082f5482ce213feacd8c1f9dfa","Names":["/jolly_raman"],"Image":"mbrt/golang-vim-dev","ImageID":"sha256:729a2bcc6dc64ed999ee4a0dcb1fbbc2b99c3029a8b221d221ead5e4a0e89157","Command":"bash","Created":1596482871,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (0) 25 hours ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"7df9bdd917a212f36a0b9aba1a269cd184185df0b0b526b2e1ff55850597a185","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[{"Type":"bind","Source":"/Users/tsuyoshi/SOURCE","Destination":"/go","Mode":"","RW":true,"Propagation":"rprivate"}]},{"Id":"60c4042fd1a655f81ab67259c2a9db7212e041ae99c7e31de57be083e47baddc","Names":["/frosty_hofstadter"],"Image":"golang","ImageID":"sha256:a794da9351a3b2f860cc9d8859f75c7722ea0eb3d482ceac2c44e20780743018","Command":"bash","Created":1596482819,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (0) 25 hours ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"7df9bdd917a212f36a0b9aba1a269cd184185df0b0b526b2e1ff55850597a185","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[]},{"Id":"5a486c35a825f683a632921aeb3e0b31b19af15a73afd6ad8944d8f679222730","Names":["/funny_gates"],"Image":"golang","ImageID":"sha256:a794da9351a3b2f860cc9d8859f75c7722ea0eb3d482ceac2c44e20780743018","Command":"bash","Created":1596482811,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (0) 25 hours ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"7df9bdd917a212f36a0b9aba1a269cd184185df0b0b526b2e1ff55850597a185","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[]},{"Id":"e0c1f3850bd7c383789ccb3302ea66de7f97369a7e80c47ccd589e3e2a79da65","Names":["/amazing_jones"],"Image":"a794da9351a3","ImageID":"sha256:a794da9351a3b2f860cc9d8859f75c7722ea0eb3d482ceac2c44e20780743018","Command":"/bin/bash","Created":1595771231,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (127) 9 days ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"c090cb71ebddd2c135833f85825ebb002394e12ef8da05ec8ba35bb4a5873114","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[]},{"Id":"42a1b2fed60f40e2ea2136bf57d1c8ea23e8f725bfd1fdc2acff8a15b9252bd7","Names":["/bold_keldysh"],"Image":"a794da9351a3","ImageID":"sha256:a794da9351a3b2f860cc9d8859f75c7722ea0eb3d482ceac2c44e20780743018","Command":"/bin/bash","Created":1595771213,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (0) 9 days ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"c090cb71ebddd2c135833f85825ebb002394e12ef8da05ec8ba35bb4a5873114","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[]},{"Id":"6cf83cd7e2f14bfeee534807a3e39c8ca00f7c48cc0ee79b0b4fd9a560489f91","Names":["/adoring_panini"],"Image":"sha256:7e5e8028e8ecb43c45b9928ab4561de171b28b9a8add11e575405133e4f408e5","ImageID":"sha256:7e5e8028e8ecb43c45b9928ab4561de171b28b9a8add11e575405133e4f408e5","Command":"bash","Created":1590432692,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (128) 2 months ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"3f6db96f8b24be7a82c84e344b4b69c864fa15cc1710da5852654c4574c4fbbd","EndpointID":"","Gateway":"","IPAddress":"","IPPrefixLen":0,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"","DriverOpts":null}}},"Mounts":[]},{"Id":"7918a8c0d2759bb66c0cc966436b8110a3251262203c1772d039c6bd88f115c2","Names":["/great_hypatia"],"Image":"sha256:7e5e8028e8ecb43c45b9928ab4561de171b28b9a8add11e575405133e4f408e5","ImageID":"sha256:7e5e8028e8ecb43c45b9928ab4561de171b28b9a8add11e575405133e4f408e5","Command":"bash","Created":1590313614,"Ports":[],"Labels":{},"State":"exited","Status":"Exited (255) 2 months ago","HostConfig":{"NetworkMode":"default"},"NetworkSettings":{"Networks":{"bridge":{"IPAMConfig":null,"Links":null,"Aliases":null,"NetworkID":"3f6db96f8b24be7a82c84e344b4b69c864fa15cc1710da5852654c4574c4fbbd","EndpointID":"b30a163fcb6695ec3bf7422ae95ad917340b5626174e3bcfd6f62a41e4e8d1fa","Gateway":"172.17.0.1","IPAddress":"172.17.0.2","IPPrefixLen":16,"IPv6Gateway":"","GlobalIPv6Address":"","GlobalIPv6PrefixLen":0,"MacAddress":"02:42:ac:11:00:02","DriverOpts":null}}},"Mounts":[]}]
```

### 新規コンテナをunix domain socket経由で作成する。

たとえば、次のgolanイメージのコンテナをunix domain socket経由で作成します。
```
$ sudo docker images
REPOSITORY                              TAG                 IMAGE ID            CREATED             SIZE
golang                                  latest              a794da9351a3        12 days ago         810MB
```

では、unix domain socket経由でのリクエストを出してみます。
```
$ curl -X POST -H "Content-Type: application/json" --unix-socket /var/run/docker.sock http://localhost/containers/create?name=attack -d '{
>   "Image": "golang",
>   "Cmd": ["/bin/sh"],
>   "OpenStdin":true,
>   "Mounts": [
>     {
>       "Type": "bind",
>       "Source": "/",
>       "Target": "/host"
>     }
>   ]
> }'
{"Id":"1fb337af7fce551181dcc8b4470bb76b45e3c9e69ecc7cb58d0625d74782c742","Warnings":[]}
```

コンテナを確認するとちゃんと生成できています。
```
$ sudo docker ps -a
CONTAINER ID        IMAGE                 COMMAND             CREATED             STATUS                      PORTS               NAMES
1fb337af7fce        golang                "/bin/sh"           11 seconds ago      Created                                         attack
```

- 参考
  - https://docs.docker.com/engine/api/v1.40/#operation/ContainerCreate


### 作成したコンテナを起動する
作成した状態だとSTATUSが「Created」となっています。
```
$ docker ps -a
CONTAINER ID        IMAGE                 COMMAND             CREATED             STATUS                      PORTS               NAMES
1fb337af7fce        golang                "/bin/sh"           18 minutes ago      Created                                         attack
```

「attack」を起動してみて、STATUSを確認すると「Up」と変化してることが確認できます。
```
$ curl -X POST --unix-socket /var/run/docker.sock http://localhost/containers/attack/start
$ docker ps -a
CONTAINER ID        IMAGE                 COMMAND             CREATED             STATUS                      PORTS               NAMES
1fb337af7fce        golang                "/bin/sh"           18 minutes ago      Up 2 seconds                                    attack
```

### コンテナにアタッチする
詳細は引用元の参考URLを参照した方がいいですが、インタラクティブ操作をしようとするとcurlだとうまい方法がないので、socatで試せます。
```
(cat <<EOF
POST /containers/attack/attach?stream=1&stdin=1&stdout=1&stderr=1 HTTP/1.1
Host:
Connection: Upgrade
Upgrade: tcp
EOF
cat - ) | socat - UNIX-CONNECT:/var/run/docker.sock
```

- 参考: https://knqyf263.hatenablog.com/entry/2018/11/01/113508


### コンテナのログを確認する
以下はname「attack」の操作ログを出力しています。
```
$ curl --unix-socket /var/run/docker.sock http:/localhost/containers/attack/logs?stdout=1
root@golang2:/go# ls
bin  src
root@golang2:/go# vim src/
bash: vim: command not found
root@golang2:/go# ls sr
ls: cannot access 'sr': No such file or directory
root@golang2:/go# ls src/
root@golang2:/go# ls
bin  src
```
