# 概要
cpplintについてのメモ

# 概要
```
$ git clone https://github.com/google/styleguide.git
$ cd styleguide
$ cpplint/cpplint.py --counting=detailed --root=src --verbose src/xxx.cc
```

cpplintへのオプションは以下のusageを参考にするのがよい
- https://github.com/google/styleguide/blob/gh-pages/cpplint/cpplint.py#L56-L187


# 参考URL
- cpplint.py本体
  - https://github.com/google/styleguide
- Google C++ Style Guide
  - http://google.github.io/styleguide/cppguide.html
