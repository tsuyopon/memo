# 概要
rubyのデバッグについて

### rubyのデバッガを使ってみる
次のようなサンプルプログラムを用意する。
```
$ cat test.rb 
require 'open-uri'
f = open("http://0xcc.net/", "r")
puts f.read
```

ちょっとだけ使ってみる
```
$ ruby -rdebug test.rb
Debug.rb
Emacs support available.

test.rb:1:require 'open-uri'
(rdb:1) b 2
Set breakpoint 1 at test.rb:2
(rdb:1) c
Breakpoint 1, toplevel at test.rb:2
test.rb:2:f = open("http://0xcc.net/", "r")
(rdb:1) s
/usr/share/ruby/open-uri.rb:28:    if name.respond_to?(:open)
(rdb:1) l
[23, 32] in /usr/share/ruby/open-uri.rb
   23    # Since open-uri.rb provides URI::HTTP#open, URI::HTTPS#open and
   24    # URI::FTP#open, Kernel[#.]open can accept URIs and strings that begin with
   25    # http://, https:// and ftp://.  In these cases, the opened file object is
   26    # extended by OpenURI::Meta.
   27    def open(name, *rest, &block) # :doc:
=> 28      if name.respond_to?(:open)
   29        name.open(*rest, &block)
   30      elsif name.respond_to?(:to_str) &&
   31            %r{\A[A-Za-z][A-Za-z0-9+\-\.]*://} =~ name &&
   32            (uri = URI.parse(name)).respond_to?(:open)
(rdb:1) p name
"http://0xcc.net/"
(rdb:1) w
--> #1 /usr/share/ruby/open-uri.rb:28:in `open'
    #2 test.rb:2
```

### 起動中のプロセスにアタッチする
参考になりそうなのはこの辺?
- http://weblog.jamisbuck.org/2006/9/22/inspecting-a-live-ruby-process
- http://axonflux.com/inspect-a-live-running-ruby-process
- https://spin.atomicobject.com/2013/08/19/debug-ruby-processes/

# 参考URL
- http://0xcc.net/blog/archives/000162.html
