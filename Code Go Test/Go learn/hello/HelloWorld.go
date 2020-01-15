/*
   Go 语言基本入门学习
   https://tour.go-zh.org/flowcontrol/1
主要内容：
   基本语法和注意事项
*/
// 包声明 同一个文件夹下的文件只能有一个包名，否则编译报错。
package main

// 引入包
import (
	"fmt"
	"math"
	"math/rand"
	"runtime"
	"strings"
	"time"
)

func sum(a int, b int) int {
	return a + b
}
func mult(a, b int) int {
	return a * b
}
func swap(src string, dst string) (string, string) {
	//注意==和python有区别，这里不需要用()括起来的
	return dst, src
}
func getStr() string {
	fmt.Println("getStr")
	return "just for testing"
}
func getStr2() string {
	fmt.Println("getStr2")
	return "just for testing2"
}

//switch 的 case 语句从上到下顺次执行，直到匹配成功时停止。
func switchCaseTest() {
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "windows":
		fmt.Println("OS: windows")
		//继续执行
		fallthrough
	case getStr():
		fmt.Println("getStr: ", getStr())
	//Go 自动提供了在这些语言中每个 case 后面所需的 break 语句
	//此处，在getStr调用后，直接break出去了，getStr2()不会被调用到了
	case getStr2():
		fmt.Println("getStr: ", getStr2())
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9
		fmt.Printf("default: %s.\n", os)
	}
}
func switchCaseFloatTest(choice float64) {
	//defer 语句会将函数推迟到外层函数返回之后执行。
	//推迟调用的函数其参数会立即求值，但直到外层函数返回前该函数都不会被调用。
	//推迟的函数调用会被压入一个栈中。当外层函数返回时，被推迟的函数会按照后进先出的顺序调用。 https://blog.go-zh.org/defer-panic-and-recover
	defer fmt.Println("Go runs on ")
	defer fmt.Println("defer FILO")
	// Go 的另一点重要的不同在于 switch 的 case 无需为常量，且取值不必为整数。
	switch choice {
	case 1.2:
		fmt.Println("1.2")
	case 1.22:
		fmt.Println("1.22")
		fallthrough
	case 1.222:
		fmt.Println("1.222")
	default:
		fmt.Printf("default: %f.\n", choice)
	}
}

//左大括号必须与 func 等关键字位于同一行而不是独占一行， 这是 Go 语言唯一允许的大括号放置风格。
func switchCaseTrueTest() {
	t := time.Now()
	//没有条件的 switch 同 switch true 一样。 这种形式能将一长串 if-then-else 写得更加清晰。
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}

/* 命名返回值
Go 的返回值可被命名，它们会被视作定义在函数顶部的变量。
返回值的名称应当具有一定的意义，它可以作为文档使用。
没有参数的 return 语句返回已命名的返回值。也就是 直接 返回。
直接返回语句应当仅用在下面这样的短函数中。在长的函数中它们会影响代码的可读性。
注意：和 C、Java、JavaScript 之类的语言不同，Go 的 if、for 语句后面的三个构成部分外没有小括号， 大括号 { } 则是必须的。
*/
// sum----[start, end)
func sumN(start int, end int) (sum int) {
	// 此处sum已经在函数中定义了，不可以再用 sum := 0这样重复初始化
	sum = 0
	if start >= end {
		return
	}
	for i := start; i < end; i++ {
		sum += i
	}
	return
}
func sumToN(start int, sumEnd int) int {
	sum := start
	end := start
	// 相当于c++中的while循环
	for sum < sumEnd {
		end++
		sum += end
	}
	// for {
	// }  //无限循环
	return end
}
func pow(x, n, lim float64) float64 {
	// 简短语句声明的变量v，只能在当前的if else语句中使用
	if v := math.Pow(x, n); v < lim {
		return v
	} else {
		fmt.Printf("%g >= %g\n", v, lim)
	}
	// 这里开始就不能使用 v 了
	return lim
}

var helloWorld string

//Pointer
func pointerTest() {
	i, j := 42, 2701
	var p *int

	p = &i
	fmt.Printf("i: %d, address of i: %p, pointer value: %d\n", i, p, *p)

	p = &j
	*p = *p / 37
	fmt.Printf("j: %d, address of j: %p, pointer value: %d\n", j, p, *p)
}

// Struct
type VertexS struct {
	X int
	Y int
}

func structTest() {
	var tmp VertexS
	tmp.X = 21
	tmp.Y = 24
	fmt.Println("tmp Vertex: ", tmp)

	test := VertexS{3, 66}
	fmt.Println("test Vertex: ", test)
	//结构体字段可以通过结构体指针来访问。
	//如果我们有一个指向结构体的指针 p，那么可以通过 (*p).X 来访问其字段 X。不过这么写太啰嗦了，所以语言也允许我们使用隐式间接引用，直接写 p.X 就可以。
	p := &test
	p.X = 109
	fmt.Println("test Vertex changed: ", test)

	//Name:value的形式，仅列出部分字段（字段名与结构体声明的顺序无关），其它被隐式设置为零值
	var (
		v1  = VertexS{X: 3}
		v2  = VertexS{}
		pv3 = &VertexS{3, 4}
	)
	fmt.Println("v1 Vertex: ", v1)
	fmt.Println("v2 Vertex: ", v2)
	fmt.Println("pv3 Vertex value: ", *pv3)
	fmt.Println("pv3 Vertex pointer: ", pv3)
}

//Array    [n]T表示拥有n个T类型的值的数组
func arrayTest() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println("helloWorld array: ", a)
}

//切片 切片返回的范围是[low:high)
/* 切片就像数组的引用
切片并不存储任何数据，它只是描述了底层数组中的一段。
更改切片的元素会修改其底层数组中对应的元素。
与它共享底层数组的切片都会观测到这些修改。
在进行切片时，你可以利用它的默认行为来忽略上下界。

切片下界的默认值为 0，上界则是该切片的长度。
对于数组
var a [10]int
来说，以下切片是等价的：
a[0:10]
a[:10]
a[0:]
a[:]
*/
/*
切片拥有 长度 和 容量。
切片的长度就是它所包含的元素个数。
切片的容量是从它的第一个元素开始数，到其底层数组元素末尾的个数。
切片 s 的长度和容量可通过表达式 len(s) 和 cap(s) 来获取。
切片类型的写法是 []T ， T 是切片元素的类型。和数组不同的是，切片类型并没有给定固定的长度。
https://blog.go-zh.org/go-slices-usage-and-internals
*/
func arraySliceTest() {
	primes := [6]int{2, 4, 6, 8, 10, 12}
	fmt.Println("primes array: ", primes)
	var s []int = primes[1:4]
	var t []int = primes[2:5]
	fmt.Println("slice primes 1:4 result is: ", s)
	fmt.Println("slice primes 2:5 result is: ", t)
	s[1] = 3
	fmt.Println("s[1] changed to 3")
	fmt.Println("primes array changed: ", primes)
	fmt.Println("slice primes 1:4 changed result is: ", s)
	fmt.Println("slice primes 2:5 changed result is: ", t)

	//不设定长度的初始化--切片文法= =
	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println("q array: ", q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println("r array: ", r)
	//这种方法还挺奇特的
	s2 := []struct {
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
	fmt.Println("s2 array: ", s2)

	s = []int{2, 3, 5, 7, 11, 13}
	printSlice("s", s)

	// 截取切片使其长度为 0
	s = s[:0]
	printSlice("s slice to nil", s)

	// 拓展其长度
	s = s[:4]
	printSlice("s expand len", s)

	// 舍弃前两个值
	s = s[2:]
	printSlice("s disgard first 2", s)
	var s3 []int
	printSlice("s3", s3)
	if s3 == nil {
		fmt.Println("s3 nil!")
	}

	//用 make 创建切片
	a := make([]int, 5)
	printSlice("a", a)
	b := make([]int, 0, 5)
	printSlice("b", b)
	c := b[:2]
	printSlice("c", c)
	d := c[2:5]
	printSlice("d", d)

	//切片的切片
	// 创建一个井字板（经典游戏）
	board := [][]string{
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
		[]string{"_", "_", "_"},
	}

	// 两个玩家轮流打上 X 和 O
	board[0][0] = "X"
	board[2][2] = "O"
	board[1][2] = "X"
	board[1][0] = "O"
	board[0][2] = "X"
	for i := 0; i < len(board); i++ {
		fmt.Printf("%s\n", strings.Join(board[i], " "))
	}

	//向切片追加元素 append 的结果是一个包含原切片所有元素加上新添加元素的切片。
	//当 s 的底层数组太小，不足以容纳所有给定的值时，它就会分配一个更大的数组。返回的切片会指向这个新分配的数组。
	var sliceAppend []int
	printSlice("sliceAppend", sliceAppend)
	// 添加一个空切片
	sliceAppend = append(sliceAppend, 0)
	printSlice("sliceAppend", sliceAppend)
	// 这个切片会按需增长
	sliceAppend = append(sliceAppend, 1)
	printSlice("sliceAppend", sliceAppend)
	// 可以一次性添加多个元素
	sliceAppend = append(sliceAppend, 2, 3, 4)
	printSlice("sliceAppend", sliceAppend)

	//range遍历--as pos,value
	var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}
	for i, v := range pow {
		fmt.Printf("2**%d = %d\n", i, v)
	}

	pow1 := make([]int, 10)
	for i := range pow1 {
		pow1[i] = 1 << uint(i) // == 2**i
	}
	for _, value := range pow1 {
		fmt.Printf("%d\n", value)
	}
}

func printSlice(s string, x []int) {
	fmt.Printf("%s len=%d cap=%d %v\n",
		s, len(x), cap(x), x)
}
func Pic(dx, dy int) [][]uint8 {
	if dx <= 0 || dy <= 0 {
		return nil
	}
	//var ret [][]uint8
	ret := make([][]uint8, dy)
	for i := 0; i < dy; i++ {
		//var row []uint8
		row := make([]uint8, dx)
		for j := 0; j < dx; j++ {
			//-****-如果是没有初始化，则需要使用append进行添加，而不能直接获取index操作
			//row = append(row, uint8(float64(i)*math.Log(float64(j))))
			// 注意: row didn't init===make, can't get index
			row[j] = uint8(float64(i) * math.Log(float64(j)))
		}
		ret = append(ret, row)
	}
	for _, value := range ret {
		for _, valuej := range value {
			fmt.Printf("%d\n", valuej)
		}

	}
	return ret
}

//映射
/*
在映射 m 中插入或修改元素：
m[key] = elem

获取元素：
elem = m[key]

删除元素：
delete(m, key)

通过双赋值检测某个键是否存在：
elem, ok = m[key]
若 key 在 m 中，ok 为 true ；否则，ok 为 false。
若 key 不在映射中，那么 elem 是该映射元素类型的零值。
同样的，当从映射中读取某个不存在的键时，结果是映射的元素类型的零值。
*/
type VertexFloat struct {
	Lat, Long float64
}

func mapCaseTest() {
	var m map[string]VertexFloat
	//make 函数会返回给定类型的映射，并将其初始化备用。必须先初始化，再使用
	m = make(map[string]VertexFloat)
	m["Bell Labs"] = VertexFloat{
		40.68433, -74.39967,
	}
	m["Judy test"] = VertexFloat{
		2020, 1.00,
	}
	fmt.Println(m["Bell Labs"])
	fmt.Println(m["Judy test"])

	var m2 = map[string]VertexFloat{
		"Bell Labs": VertexFloat{
			40.68433, -74.39967,
		},
		"Google": VertexFloat{
			37.42202, -122.08408,
		},
	}
	fmt.Println(m2)
	//若顶级类型只是一个类型名，你可以在文法的元素中省略它。
	var m3 = map[string]VertexFloat{
		"Bell Labs": {
			40.68433, -74.39967,
		},
		"Google": {
			37.42202, -122.08408,
		},
	}
	fmt.Println(m3)
	//增改
	m4 := make(map[string]int)

	m4["Answer"] = 42
	fmt.Println("The value:", m4["Answer"])

	m4["Answer"] = 48
	fmt.Println("The value:", m4["Answer"])

	delete(m4, "Answer")
	fmt.Println("The value:", m4["Answer"])

	v, ok := m4["Answer"]
	fmt.Println("The value:", v, "Present?", ok)
}
func WordCount(s string) map[string]int {
	arrayS := strings.Fields(s) // https://go-zh.org/pkg/strings/#Fields
	ret := make(map[string]int)
	for _, val := range arrayS {
		_, in := ret[val]
		if in {
			ret[val] = ret[val] + 1
		} else {
			ret[val] = 1
		}
	}
	fmt.Println(ret)
	return ret
}

//函数作为参数进行传递
/*
Go 函数可以是一个闭包。闭包是一个函数值，它引用了其函数体之外的变量。
该函数可以访问并赋予其引用的变量的值，换句话说，该函数被这些变量“绑定”在一起。
例如，函数 adder 返回一个闭包。每个闭包都被绑定在其各自的 sum 变量上。
*/
func compute(fn func(float64, float64) float64) float64 {
	return fn(3, 4)
}
func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}
func FuncParameterCaseTest() {
	hypot := func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}
	fmt.Println("hypot: ", hypot(5, 12))

	fmt.Println("compute: ", compute(hypot))
	fmt.Println("compute: ", compute(math.Pow))

	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		fmt.Println("adder: ",
			pos(i),
			neg(-2*i),
		)
	}
}

// 斐波那契数列  https://studygolang.com/articles/7884
func fibonacci() func() int {
	//函数文字是闭包：它们可能引用周围函数中定义的变量。这些变量然后在周围的函数和函数文字之间共享，并且只要它们是可访问的，它们就存活。
	// 类似于静态局部变量
	fib1 := 0
	fib2 := 1
	return func() int {
		fib1, fib2 = fib2, fib1+fib2
		return fib1
	}
}

// 入口函数
func main() {

	fmt.Println("Hello, World!")
	fmt.Println(time.Now())
	rand.Seed(time.Now().Unix())
	fmt.Println("My favorite number is", rand.Intn(10))
	//导出名，必须是大写字母开头
	fmt.Println(math.Pi)
	fmt.Println("2 + 5 = ", sum(2, 5))
	fmt.Println("2 * 5 =", mult(2, 5))
	//注意==函数外的每个语句都必须以关键字开始（var, func 等等），因此 := 结构不能在函数外使用
	//编译器自动识别类型
	a := "123"
	b := "456"
	a, b = swap(a, b)
	fmt.Println("swap '123', '456': ", a, ", ", b)
	fmt.Println("sum from 2 to 46: ", sumN(2, 46))
	fmt.Println("sum from 3 to 2: ", sumN(3, 2))
	// var var_name type形式的初始化
	var name string = "Judy"
	helloWorld = "Good Day~"
	fmt.Println(name + ", " + helloWorld)

	var x, y int = 3, 4
	//T() 类型转换
	var f float64 = math.Sqrt(float64(x*x + y*y))
	//var f float64 = math.Sqrt(x*x + y*y)
	// error, go中不同类型的变量不可以直接赋值，需要显式转换
	fmt.Printf("sqrt(x*x+y*y): x: %d, y: %d, z: %f\n", x, y, f)

	start := 2
	sumEnd := 1000
	fmt.Printf("start: %d, sum up to sumEnd: %d, we should add to: %d\n", start, sumEnd, sumToN(start, sumEnd))

	switchCaseTest()
	switchCaseFloatTest(1.22)
	switchCaseTrueTest()

	pointerTest()
	structTest()
	arrayTest()
	arraySliceTest()
	Pic(5, 4)
	mapCaseTest()
	WordCount("judy testing hello world in 2020 year.")

	FuncParameterCaseTest()
	fib := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(i, " fib: ", fib())
	}

}
