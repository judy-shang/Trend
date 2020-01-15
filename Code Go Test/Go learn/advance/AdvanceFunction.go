package main

import (
	"fmt"
	"image"
	"io"
	"math"
	"os"
	"reflect"
	"strings"
	"time"
)

// Vertex struct
type Vertex struct {
	X, Y float64
}

/*
Abs function
Go 没有类。不过你可以为结构体类型定义方法。
方法就是一类带特殊的 接收者 参数的函数。
方法接收者在它自己的参数列表内，位于 func 关键字和方法名之间。
在此例中，Abs 方法拥有一个名为 v，类型为 Vertex 的接收者。
*/
func (v *Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

// MyFloat struct
type MyFloat float64

/*
Abs float64 function
你也可以为非结构体类型声明方法。
在此例中，我们看到了一个带 Abs 方法的数值类型 MyFloat。
你只能为在同一包内定义的类型的接收者声明方法，而不能为其它包内定义的类型（包括 int 之类的内建类型）的接收者声明方法。
（译注：就是接收者的类型定义和方法声明必须在同一包内；不能为内建类型声明方法。）
*/
func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

/*
Scale function
你可以为指针接收者声明方法。
这意味着对于某类型 T，接收者的类型可以用 *T 的文法。（此外，T 不能是像 *int 这样的指针。）
例如，这里为 *Vertex 定义了 Scale 方法。
!!!=====指针接收者的方法可以修改接收者指向的值（就像 Scale 在这做的）。由于方法经常需要修改它的接收者，指针接收者比值接收者更常用。
若使用值接收者，那么 Scale 方法会对原始 Vertex 值的副本进行操作。====!!!
!!!*******
推荐使用指针作为接收者：
	1. 方法能够修改其接收者指向的值。
	2. 这样可以避免在每次调用方法时复制该值。若值的类型为大型结构体时，这样做会更加高效。
	通常来说，所有给定类型的方法都应该有值或指针接收者，但并不应该二者混用。
*/
func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

/*
Abser Interface
接口类型 是由一组方法签名定义的集合。  接口-不是太理解===https://tour.go-zh.org/methods/10
接口类型的变量可以保存任何实现了这些方法的值。
*/
type Abser interface {
	Abs() float64 // func (v Vertex) Abs() float64 //func (f MyFloat) Abs() float64
	// 可以将Vertex, MyFloat理解为一个类，他们继承了接口X,都实现的方法 Abs() float64
}

/*
I interface
接口也是值。它们可以像其它值一样传递。
接口值可以用作函数的参数或返回值。

在内部，接口值可以看做包含值和具体类型的元组：
(value, type)
接口值保存了一个具体底层类型的具体值。
接口值调用方法时会执行其底层类型的同名方法。
*/
type I interface {
	M()
}

// T struct
type T struct {
	S string
	V int
}

// M func
func (t *T) M() {
	if t == nil {
		fmt.Println("<nil>")
		return
	}
	fmt.Println(t.S, t.V)
}

// F struct
type F float64

//M function
func (f F) M() {
	fmt.Println(f)
}
func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
func describeInterface(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}

/*
interfaceType function
类型断言 提供了访问接口值底层具体值的方式。
t := i.(T)
该语句断言接口值 i 保存了具体类型 T，并将其底层类型为 T 的值赋予变量 t。

若 i 并未保存 T 类型的值，该语句就会触发一个恐慌。
为了 判断 一个接口值是否保存了一个特定的类型，类型断言可返回两个值：其底层值以及一个报告断言是否成功的布尔值。
t, ok := i.(T)
若 i 保存了一个 T，那么 t 将会是其底层值，而 ok 为 true。
否则，ok 将为 false 而 t 将为 T 类型的零值，程序并不会产生恐慌。
请注意这种语法和读取一个映射时的相同之处。===类似于判断interface i是否保存了类型T
*/
func interfaceType() {
	var i interface{} = "hello"

	s := i.(string)
	fmt.Println(s)

	s, ok := i.(string)
	fmt.Println(s, ok)

	f, ok := i.(float64)
	fmt.Println(f, ok)

	//f = i.(float64) // 报错(panic)
	//fmt.Println(f)
}

/*
do function
类型选择中的声明与类型断言 i.(T) 的语法相同，只是具体类型 T 被替换成了关键字 type。
此选择语句判断接口值 i 保存的值类型是 T 还是 S。在 T 或 S 的情况下，变量 v 会分别按 T 或 S 类型保存 i 拥有的值。
在默认（即没有匹配）的情况下，变量 v 与 i 的接口类型和值相同。
*/
func do(i interface{}) {
	switch v := i.(type) {
	case int:
		fmt.Printf("Twice %v is %v\n", v, v*2)
	case string:
		fmt.Printf("%q is %v bytes long\n", v, len(v))
	default:
		fmt.Printf("I don't know about type %T!\n", v)
	}
}

//Person struct
type Person struct {
	Name string
	Age  int
}

/*
fmt 包中定义的 Stringer 是最普遍的接口之一。
type Stringer interface {
    String() string
}
Stringer 是一个可以用字符串描述自己的类型。fmt 包（还有很多包）都通过此接口来打印值。
这里Person结构体实现String函数，fmt在打印Person结构体时，就会调用Stringer.String()进行打印了
*/
func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

/*
与 fmt.Stringer 类似，error 类型是一个内建接口：
type error interface {
    Error() string
}
*/
type MyError struct {
	When time.Time
	What string
}

func (e *MyError) Error() string {
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)
}

func run() error {
	return &MyError{
		time.Now(),
		"it didn't work",
	}
}

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %f", float64(e))
}
func SqrtError(x float64) (float64, error) {
	if x < 0 {
		return 0, ErrNegativeSqrt(x)
	}
	switch reflect.TypeOf(x).String() {
	case "float64":
		return math.Sqrt(x), nil
	default:
		return 0, ErrNegativeSqrt(x)
	}
}

/*
io 包指定了 io.Reader 接口，它表示从数据流的末尾进行读取。
Go 标准库包含了该接口的许多实现，包括文件、网络连接、压缩和加密等等。
io.Reader 接口有一个 Read 方法：
func (T) Read(b []byte) (n int, err error)
Read 用数据填充给定的字节切片并返回填充的字节数和错误值。在遇到数据流的结尾时，它会返回一个 io.EOF 错误。
*/
func ReadTest() {
	r := strings.NewReader("Hello, Reader!")
	b := make([]byte, 8)
	for {
		n, err := r.Read(b)
		fmt.Printf("n = %v err = %v b = %v\n", n, err, b)
		fmt.Printf("b[:n] = %q\n", b[:n]) //TODO-judy  不太明白为什么第三次循环才会输出EOF，不应该第二次就可以获得EOF错误并退出了吗？
		if err == io.EOF {
			break
		}
	}
}

/*
有种常见的模式是一个 io.Reader 包装另一个 io.Reader，然后通过某种方式修改其数据流。
例如，gzip.NewReader 函数接受一个 io.Reader（已压缩的数据流）并返回一个同样实现了 io.Reader 的 *gzip.Reader（解压后的数据流）。
编写一个实现了 io.Reader 并从另一个 io.Reader 中读取数据的 rot13Reader，通过应用 rot13 代换密码对数据流进行修改。
rot13Reader 类型已经提供。实现 Read 方法以满足 io.Reader。
*/
type rot13Reader struct {
	r io.Reader
}

// 转换byte  前进13位/后退13位
func rot13Byte(b byte) byte {
	switch {
	case 'A' <= b && b <= 'M':
		b = b + 13
	case 'M' < b && b <= 'Z':
		b = b - 13
	case 'a' <= b && b <= 'm':
		b = b + 13
	case 'm' < b && b <= 'z':
		b = b - 13
	}
	return b
}

func (rot13 rot13Reader) Read(b []byte) (int, error) {
	n, err := rot13.r.Read(b)
	for i := range b {
		b[i] = rot13Byte(b[i])
	}
	return n, err
}

/*
image 包定义了 Image 接口：
package image

type Image interface {
    ColorModel() color.Model
    Bounds() Rectangle
    At(x, y int) color.Color
}
注意: Bounds 方法的返回值 Rectangle 实际上是一个 image.Rectangle，它在 image 包中声明。
（请参阅文档了解全部信息。）
color.Color 和 color.Model 类型也是接口，但是通常因为直接使用预定义的实现 image.RGBA 和 image.RGBAModel 而被忽视了。
这些接口和类型由 image/color 包定义。
*/
func imageTest() {
	m := image.NewRGBA(image.Rect(0, 0, 100, 100))
	fmt.Println(m.Bounds())
	fmt.Println(m.At(0, 0).RGBA())
}

func main() {
	v := Vertex{3, 4}
	fmt.Println(v.Abs())

	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs())
	/*
		带指针参数的函数必须接受一个指针：
			var v Vertex
			ScaleFunc(v, 5)  // 编译错误！
			ScaleFunc(&v, 5) // OK

		而以指针为接收者的方法被调用时，接收者既能为值又能为指针：
			var v Vertex
			v.Scale(5)  // OK
			p := &v
			p.Scale(10) // OK
			对于语句 v.Scale(5)，即便 v 是个值而非指针，带指针接收者的方法也能被直接调用。
			也就是说，由于 Scale 方法有一个指针接收者，为方便起见，Go 会将语句 v.Scale(5) 解释为 (&v).Scale(5)。

		反之，接受一个值作为参数的函数必须接受一个指定类型的值：
			var v Vertex
			fmt.Println(AbsFunc(v))  // OK
			fmt.Println(AbsFunc(&v)) // 编译错误！

		而以值为接收者的方法被调用时，接收者既能为值又能为指针：
			var v Vertex
			fmt.Println(v.Abs()) // OK
			p := &v
			fmt.Println(p.Abs()) // OK
			这种情况下，方法调用 p.Abs() 会被解释为 (*p).Abs()。
	*/
	v.Scale(10)
	fmt.Println(v.Abs())

	var a Abser
	a = f
	fmt.Println("Abser f: ", a.Abs())
	a = &v
	fmt.Println("Abser v: ", a.Abs())
	// cannot use v (type Vertex) as type Abser in assignment:
	// Vertex does not implement Abser (Abs method has pointer receiver)
	//a = v
	fmt.Println("v.Abs()", v.Abs())
	// TODO-judy 但是为什么这个可以呢？
	a = &f
	fmt.Println("Abser &f ", a.Abs())

	// 接口作为参数值
	var i I
	i = &T{"Hello", 2}
	describe(i)
	i.M()
	// 接口的底层值为nil====[接口本身不是nil]
	var t *T
	i = t
	describe(i)
	i.M()
	// 接口值为nil
	// nil 接口值既不保存值也不保存具体类型。
	// 为 nil 接口调用方法会产生运行时错误，因为接口的元组内并未包含能够指明该调用哪个 具体 方法的类型。
	// var err error = nil ----ok
	// err := nil --- error, nil需要指定type类型
	var iNil I
	describe(iNil)
	// invalid memory address or nil pointer dereference
	// iNil.M()

	i = F(math.Pi)
	describe(i)
	i.M()

	/*
		指定了零个方法的接口值被称为 *空接口：*
		interface{}
		空接口可保存任何类型的值。（因为每个类型都至少实现了零个方法。）
		空接口被用来处理未知类型的值。例如，fmt.Print 可接受类型为 interface{} 的任意数量的参数。
		TODO-judy 但是空接口的话，有什么用途呢？也没法调用啊？
	*/
	var interfaceI interface{}
	describeInterface(interfaceI)

	interfaceI = 42
	describeInterface(interfaceI)

	interfaceI = "hello"
	describeInterface(interfaceI)

	interfaceType()
	do(21)
	do("hello")
	do(true)

	x := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(x, z) //单步运行时，会走到Person的String()

	if err := run(); err != nil {
		fmt.Println(err)
	}

	_, err := SqrtError(-2)
	if err != nil {
		fmt.Println(err)
	}
	_, err2 := SqrtError(5)
	if err != nil {
		fmt.Println(err2)
	}

	ReadTest()
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)

	imageTest()
	//FuncParameterCaseTest()
}
