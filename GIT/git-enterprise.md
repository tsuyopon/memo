# �T�v
2��ghe�T�[�o�Ԃɂ����鑀��Ȃǂɂ���

# �ڍ�
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


### ghe1����ghe2�ɍŐV��񂪍X�V���ꂽ�Bghe2��fork�������̃u�����`(testbranch)�ɑ΂��čX�V���ꂽ���e��PR�𔭍s�������ꍇ
ghe2��fork�����u�����`��ghe3�Ɖ��肷��B


ghe3��clone���āAtestbranch����u�����`��h�������č쐬����B
```
$ git clone git@ghe3:foo/bar.git
$ cd bar.git
$ git checkout testbranch
$ git branch UPDATE_testbranch
$ git checkout UPDATE_testbranch
```

upstream��ghe2��o�^���܂��B�����āAUPDATE_testbranch��upstream/testbranch�̍X�V��K�p���܂��B
```
$ git remote add upstream git@ghe2:foo/bar.git
$ git fetch upstream
$ git merge upstream/testbranch
```

���Ƃ͕K�v����΃R���t���N�g�����������āAtestbranch����h������UPDATE_testbranch�u�����`��push�����UI�ォ��PR�𔭍s�ł��܂��B
```
$ git push -u origin UPDATE_testbranch
```
