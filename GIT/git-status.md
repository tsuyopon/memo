


### untrackedな追跡されていないファイル除外して表示する
```
$ git status -uno
On branch master
Your branch is up-to-date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   AEAD_CHACHA20_POLY1305.md

no changes added to commit (use "git add" and/or "git commit -a")
```

上記コマンドは以下のコマンドの省略形です。
```
$ git status --untracked-files=no
```

- 参考
  - https://stackoverflow.com/questions/594757/how-do-i-do-a-git-status-so-it-doesnt-display-untracked-files-without-using


### ショートメッセージを表示する。
Mは修正されたもの、?は未追跡なファイルである。
```
$ git status -s
 M ../TLS/Cipher/AEAD_CHACHA20_POLY1305.md
?? ../CPP/memo.md
?? ../CPU/Register.md
?? ../Draft/quic/draft-ietf-quic-http.md
```


### 追跡されていないファイルを表示する
```
$ git status --ignored 
On branch master
Your branch is up-to-date with 'origin/master'.

(snip)

Ignored files:
  (use "git add -f <file>..." to include in what will be committed)

	../Draft/tls/.DS_Store
	../GDB/.TUI.md.swp
	../TLS/Cipher/TODO
	../TLS/draft/.TLSSniEncryption.md.swp
	../Virtualization/.Qemu.md.swp

no changes added to commit (use "git add" and/or "git commit -a")
```
