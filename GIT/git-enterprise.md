### ghe1���̃��|�W�g����ghe2���̓������|�W�g���Ƀ~���[����

���炩����ghe2���ŐV���������̃��|�W�g��bar���쐬���Ă����܂��B���̍ۂ�README.md���쐬���Ȃ��悤�ɂ��܂��B

���O�������s���܂��B
```
git clone --bare git@ghe1:foo/bar.git
cd bar.git
git remote add ghe2 git@ghe2:foo/bar.git
```

�������@��git-fetch��origin��ghe1�̕ύX����荞�݂܂��B����git-push��ghe2�֌�����push���܂�.
```
git fetch --prune origin 'refs/heads/*:refs/heads/*'
git push ghe2 --mirror
```

- �Q�l
  - http://qiita.com/satoruk/items/186af9d095d744d15c76
