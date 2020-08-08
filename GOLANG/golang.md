# 概要
go言語のコードを読むときに必要そうな最低限の知識

以下のGo言語基礎文法最速マスターも参考のこと
- https://go-tour-jp.appspot.com/welcome/1

以下も参考のこと
- https://go-tour-jp.appspot.com/list

なお、環境構築のセットアップ方法についてはsetup.mdの方を参考のこと

# 詳細

### hello worldを試す
```
$ cat hello.go
package main

import "fmt"

func main() {
	fmt.Println("Hello, 世界")
}
```

コンパイルと実行
```
$ go build hello.go
$ ./hello
```

### 基本型とその範囲
go言語で規定されている型一覧は次の通りです。
```
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // uint8 の別名

rune // int32 の別名
     // Unicode のコードポイントを表す

float32 float64

complex64 complex128
```

それぞれの型で規定される範囲は次のようになります。
```
int         32 bit 処理系ならば int32, 64 bit 処理系ならば int64
int8        -128 ～ 127 (8 bit)
int16       -32768 ～ 32767 (16 bit)
int32       -2147483648 ～ 2147483647 (32 bit)
int64       -9223372036854775808 ～ 9223372036854775807 (64 bit)

byte        uint8 の別名

uint8       0 ～ 255 (8 bit)
uint16      0 ～ 65535 (16 bit)
uint32      0 ～ 4294967295 (32 bit)
uint64      0 ～ 18446744073709551615 (64 bit)
uint        32 bit 処理系ならば uint32, 64 bit 処理系ならば uint64

float32     ±1.1754944E-38 ～ 3.4028235E+38 (32 bit 単精度)
float64     ±2.22507E-308 ～ 1.79769E+308 (64 bit 倍精度)

complex64   float32 の実数部と虚数部を持つ複素数
complex128  float64 の実数部と虚数部を持つ複素数
```

### 関数
この例では、add関数は変数名の後ろに型名を記述します。また、戻り値の型は最後のintで表されています。
```
func add(x int, y int) int {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))
}
```

関数の２つ以上の引数が同じ型である場合には、最後の型を残して省略して記述できます。
以下の例では「x int, y int」を「x, y int」として表現しています。
```
func add(x, y int) int {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))
}
```

go言語の関数は他の言語とことなり、複数の戻り値を返すことが可能です。
```
func swap(x, y string) (string, string) {
	return y, x
}

func main() {
	a, b := swap("hello", "world")
	fmt.Println(a, b)
}
```

戻り値に名前を与える
以下の例では、split関数の戻り値にx, yという２つの戻り値の名前を予め与えています。これにより、returnしていますが、x, yの値を返しています。
```
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func main() {
	fmt.Println(split(17))
}
```

### 変数
varは最後に型を記述することで表されます。
なお、変数は何も初期化を指定しないと数値型は0, boolはfalse, stringは空文字と決まっています。
```
var c, python, java bool

func main() {
	var i int
	fmt.Println(i, c, python, java)
}
```

変数は初期化することができます。
```
var i, j int = 1, 2

func main() {
	var c, python, java = true, false, "no!"
	fmt.Println(i, j, c, python, java)
}
```

変数は:=を使って暗黙的な型宣言ができます。
なお、関数の外では、キーワードではじまる宣言( var, func, など)が必要で、 := での暗黙的な宣言は利用できません。
```
func main() {
	var i, j int = 1, 2
	k := 3
	c, python, java := true, false, "no!"

	fmt.Println(i, j, k, c, python, java)
}
```

:=を使った場合には定義された値によって型が次のように変化してくるので注意してください。
```
i := 42           // int
f := 3.142        // float64
g := 0.867 + 0.5i // complex128
```

### キャスト(型変換)
go言語のキャストは非常にシンプルです。float64()やuint()で囲むことで該当の型へと簡単にキャストしてくれます。
```
func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f)
	fmt.Println(x, y, z)
}
```

### 定数
定数はconstを使って表現できます。constは:=では宣言できません。
```
	const World = "世界"
	fmt.Println("Hello", World)
```

また、int は64-bitの整数を保持できますが、それでは足りないことが時々あります。そういったときにconstを活用できます。
次の例をみてください。constの中にBigやSamllが定義されています。
```
const (
	// Create a huge number by shifting a 1 bit left 100 places.
	// In other words, the binary number that is 1 followed by 100 zeroes.
	Big = 1 << 100
	// Shift it right again 99 places, so we end up with 1<<1, or 2.
	Small = Big >> 99
)

func needInt(x int) int { return x*10 + 1 }
func needFloat(x float64) float64 {
	return x * 0.1
}

func main() {
	fmt.Println(needInt(Small))
	fmt.Println(needFloat(Small))
	fmt.Println(needFloat(Big))
}
```

### 構造体
structのフィールドは、ドット( . )を用いてアクセスします。
```
type Vertex struct {
	X int
	Y int
}

func main() {
	v := Vertex{1, 2}
	v.X = 4
	fmt.Println(v.X)
}
```

構造体フィールドへのアクセスでは以下のようにp.Xと簡単にアクセスできます。
```
type Vertex struct {
	X int
	Y int
}

func main() {
	v := Vertex{1, 2}
	p := &v
	p.X = 1e9            // (*p).X のように書くことができますが、これは面倒なのでp.Xと記述できます。
	fmt.Println(v)
}
```

構造体の宣言方法の例を以下に示します。
```
type Vertex struct {
	X, Y int
}

var (
	v1 = Vertex{1, 2}  // has type Vertex
	v2 = Vertex{X: 1}  // Y:0 is implicit
	v3 = Vertex{}      // X:0 and Y:0
	p  = &Vertex{1, 2} // has type *Vertex
)
```


### 配列
配列は次の例で示します。
```
func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)

	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)
}
```

intで10個の配列であるmyarrを宣言するには次のようにします。
```
var myarr [10]int
```

### 配列のスライス
スライスを指定することで必要な配列のみを取り出すことができます。これは参照のようなものなので、値の変更には注意してください。
```
func main() {
	primes := [6]int{2, 3, 5, 7, 11, 13}

	var s []int = primes[1:4]
	fmt.Println(s)
}
```

### スライスリテラル
[]の中に値を指定しないことも可能です。
```
func main() {
	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println(r)

	s := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}
	fmt.Println(s)
}
```

スライスの上限や下限は省略することができます。
```
	s := []int{2, 3, 5, 7, 11, 13}

	s = s[1:4]
	fmt.Println(s)

	s = s[:2]
	fmt.Println(s)

	s = s[1:]
	fmt.Println(s)
}
```

スライスの長さの変更、要素の切り詰め、伸張について
```
func main() {
	s := []int{2, 3, 5, 7, 11, 13}
	printSlice(s)

	// Slice the slice to give it zero length.
	s = s[:0]
	printSlice(s)

	// Extend its length.
	s = s[:4]
	printSlice(s)

	// Drop its first two values.
	s = s[2:]
	printSlice(s)
}
```

スライスに何も値が入っていない場合にはnilになります。
```
func main() {
	var s []int
	fmt.Println(s, len(s), cap(s))
	if s == nil {
		fmt.Println("nil!")
	}
}
```

### スライスとRange文
for ループに利用する range は、スライスや、マップ( map )をひとつずつ反復処理するために使います。
rangeでは最初にindexを、次にインデックスが指定する値を返します。
```
var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

func main() {
	for i, v := range pow {                // iはindex, vは要素の値
		fmt.Printf("2**%d = %d\n", i, v)
	}
}
```


### rangeで不要な要素をアンダーバーで捨てる
indexや値は不要であればアンダーバーで捨てることができます。
```
func main() {
	pow := make([]int, 10)
	for i := range pow {
		pow[i] = 1 << uint(i) // == 2**i
	}
	for _, value := range pow {
		fmt.Printf("%d\n", value)
	}
}
```

### 無限ループ
ループ条件を省略すれば無限ループになります。
```
func main() {
	for {
	}
}
```

### if文
通常のif文の他に、if文では簡単なステートメントを記述することができます。
```
func pow(x, n, lim float64) float64 {
	if v := math.Pow(x, n); v < lim {     // ここに v<limであれば return vする条件が記載されている。
		return v
	}
	return lim
}

func main() {
	fmt.Println(
		pow(3, 2, 10),
		pow(3, 3, 20),
	)
}
```

### switch文
switch文は通常と変わらないように見えますが、大きな注意点があります。
それは、「Go では選択された case だけを実行してそれに続く全ての case は実行されません。 」ということです。必ず覚えておきましょう。
```
func main() {
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.", os)
	}
}
```

以下のようにswitch文の後に条件がない場合には、switch trueと記述することと同じで常にswitchが実行されます。
```
func main() {
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}
```

### Defer文

defer ステートメントは、 defer へ渡した関数の実行を、呼び出し元の関数の終わり(returnする)まで遅延させるものです。
defer へ渡した関数の引数は、すぐに評価されますが、その関数自体は呼び出し元の関数がreturnするまで実行されません。

以下の関数は実行されるとworldの出力は関数の終わりまで遅延されるので「hello world」と表示されます。
```
func main() {
	defer fmt.Println("world")

	fmt.Println("hello")
}
```

なお、deferが複数指定されている場合、LIFOの順番で出力されます。
```
func main() {
	defer fmt.Println("world")
	defer fmt.Println("world2")
	defer fmt.Println("world3")	
	fmt.Println("hello")
}
```

上記関数の出力は次のようになります。
```
hello
world3
world2
world
```


### ポインタ
注意点としては、C言語とは異なりポインタ演算はありません。

```
func main() {
	i, j := 42, 2701

	p := &i         // point to i
	fmt.Println(*p) // read i through the pointer
	*p = 21         // set i through the pointer
	fmt.Println(i)  // see the new value of i

	p = &j         // point to j
	*p = *p / 37   // divide j through the pointer
	fmt.Println(j) // see the new value of j
}
```

### 受信演算子
次のような記法を受信演算子と呼ぶ
```
v1 := <-ch
```


# 参考URL
- Tour of Go
  - https://go-tour-jp.appspot.com/welcome/1
