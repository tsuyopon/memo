# 概要
Docker周りのTIPS

# 詳細

### 速攻でtcpdumpやstraceしたい。

tcpdump
```
echo 'FROM alpine\nRUN apk add --no-cache tcpdump' \
 | docker build -t debug -f - . \
 && docker run -it --rm --net container:<target> debug tcpdump -nn -X port 80
```

strace
```
$ echo 'FROM alpine\nRUN apk add --no-cache strace' \
| docker build -t debug -f - . \
&& docker run -it --rm --pid container:<target> --cap-add sys_ptrace debug strace -fp 1
```

下記ドキュメントに感謝
- 参考: https://qiita.com/minamijoyo/items/9dd59109e9fe1a35f888


### ツールが入ったコンテナ
- https://github.com/nicolaka/netshoot/blob/master/Dockerfile
