package main

import (
	"fmt"
	"math"
	"sync"
	"time"
)

/*
Go 程（goroutine）是由 Go 运行时管理的轻量级线程。
go f(x, y, z)
会启动一个新的 Go 程并执行
f(x, y, z)
f, x, y 和 z 的求值发生在当前的 Go 程中，而 f 的执行发生在新的 Go 程中。
Go 程在相同的地址空间中运行，因此在访问共享的内存时必须进行同步。
*/
func Say(s string) {
	for i := 0; i < 5; i++ {
		time.Sleep(100 * time.Microsecond)
		fmt.Println(s)

	}
}

/*
信道是带有类型的管道，你可以通过它用信道操作符 <- 来发送或者接收值。
ch <- v    // 将 v 发送至信道 ch。
v := <-ch  // 从 ch 接收值并赋予 v。
（“箭头”就是数据流的方向。）
和映射与切片一样，信道在使用前必须创建：
ch := make(chan int)
默认情况下，发送和接收操作在另一端准备好之前都会阻塞。这使得 Go 程可以在没有显式的锁或竞态变量的情况下进行同步。
*/
func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	absSum := time.Duration(math.Abs(float64(sum))) * 100 * time.Millisecond
	time.Sleep(absSum)
	fmt.Println("get result: ", sum)
	c <- sum
}

/*
信道可以是 带缓冲的。将缓冲长度作为第二个参数提供给 make 来初始化一个带缓冲的信道：
ch := make(chan int, 100)
仅当信道的缓冲区填满后，向其发送数据时才会阻塞。当缓冲区为空时，接受方会阻塞。
*/
func chainTest() {
	ch := make(chan int, 2)
	ch <- 1
	ch <- 2
	// ch <- 4  fatal error: all goroutines are asleep - deadlock!
	fmt.Println(<-ch)
	ch <- 4
	fmt.Println(<-ch)
	fmt.Println(<-ch)
}

/*
发送者可通过 close 关闭一个信道来表示没有需要发送的值了。
接收者可以通过为接收表达式分配第二个参数来测试信道是否被关闭：若没有值可以接收且信道已被关闭，那么在执行完
v, ok := <-ch
之后 ok 会被设置为 false。

循环 for i := range c 会不断从信道接收值，直到它被关闭。
*注意：* 只有发送者才能关闭信道，而接收者不能。向一个已经关闭的信道发送数据会引发程序恐慌（panic）。
*还要注意：* 信道与文件不同，通常情况下无需关闭它们。只有在必须告诉接收者不再有需要发送的值时才有必要关闭，例如终止一个 range 循环。
*/
func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	close(c) //停止
}

/*
select 语句
select 语句使一个 Go 程可以等待多个通信操作。
select 会阻塞到某个分支可以继续执行为止，这时就会执行该分支。
当多个分支都准备好时会随机选择一个执行。

当 select 中的其它分支都没有准备好时，default 分支就会执行。
为了在尝试发送或者接收时不发生阻塞，可使用 default 分支：
*/
func fibonacciChain(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x: //c是空闲的
			x, y = y, x+y
			fmt.Println("selected c")
			time.Sleep(2 * time.Second)
		case <-quit: //quit是有输入的
			fmt.Println("quit")
			return
		default:
			fmt.Println("default")
			time.Sleep(500 * time.Millisecond)
		}
	}
}

/*
Go 标准库中提供了 sync.Mutex 互斥锁类型及其两个方法：
Lock
Unlock
*/
// SafeCounter 的并发使用是安全的。
type SafeCounter struct {
	v   map[string]int // map 本身并不是并发安全的
	mux sync.Mutex     // sync.Mutex保持互斥
}

// Inc 增加给定 key 的计数器的值。
func (c *SafeCounter) Inc(key string) {
	start := time.Now()
	c.mux.Lock()
	// Lock 之后同一时刻只有一个 goroutine 能访问 c.v
	c.v[key]++
	c.mux.Unlock()
	elapsed := time.Since(start)
	fmt.Printf("App elapsed: %v\n", elapsed)
}

// Value 返回给定 key 的计数器的当前值。
func (c *SafeCounter) Value(key string) int {
	c.mux.Lock()
	// Lock 之后同一时刻只有一个 goroutine 能访问 c.v
	defer c.mux.Unlock() //用defer保证UnLock一定会执行
	return c.v[key]
}

// func main() {
// 	go Say("World")
// 	Say("Hello")

// 	//sum-信道测试
// 	s := []int{7, 2, 8, -9, 4, 0}
// 	c := make(chan int, 10) //管道传递int数据
// 	go sum(s[:len(s)/2], c)
// 	go sum(s[len(s)/2:], c)
// 	x, y := <-c, <-c //从c中接收
// 	fmt.Println("sum result: ", x, y)

// 	chainTest()

// 	fmt.Println("Cap: ", cap(c)) //如果初始化管道时，没有设置管道缓存，则默认为0。。
// 	go fibonacci(cap(c), c)
// 	for i := range c {
// 		fmt.Println("fibonacci: ", i)
// 	}

// 	fibIn := make(chan int, 2)
// 	quit := make(chan int)
// 	go func() {
// 		for i := 0; i < 10; i++ {
// 			fmt.Println("fib chain: ", <-fibIn)
// 			time.Sleep(3 * time.Second)
// 		}
// 		quit <- 0
// 	}()
// 	fibonacciChain(fibIn, quit)

// 	//mutex--共享变量
// 	counter := SafeCounter{v: make(map[string]int)}
// 	for i := 0; i < 10; i++ {
// 		go counter.Inc("somekey")
// 	}

// 	time.Sleep(time.Second) // 必须要等待一会，不然go程中的Inc还没有执行完成，主进程就已经print并退出了
// 	fmt.Println("counter: ", counter.Value("somekey"))
// }

type Fetcher interface {
	// Fetch 返回 URL 的 body 内容，并且将在这个页面上找到的 URL 放到一个 slice 中。
	Fetch(url string) (body string, urls []string, err error)
}
type fetched struct {
	urls  map[string]int
	mutex sync.Mutex
}

func (f fetched) find(s string) bool {
	f.mutex.Lock() //并发读写操作go语言的任何一个map都需要加锁，这样才能防止冲突
	defer f.mutex.Unlock()
	_, ok := f.urls[s]
	return ok
}
func (f fetched) insert(s string) {
	f.mutex.Lock()
	defer f.mutex.Unlock()
	f.urls[s] = 1
	return
}

// Crawl 使用 fetcher 从某个 URL 开始递归的爬取页面，直到达到最大深度。
func Crawl(url string, depth int, fetcher Fetcher) {
	// TODO: 并行的抓取 URL。
	// TODO: 不重复抓取页面。
	// 下面并没有实现上面两种情况：
	if depth <= 0 {
		return
	}

	body, urls, err := fetcher.Fetch(url)

	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		if fetchedUrls.find(u) {
			continue
		}
		fetchedUrls.insert(u)
		go Crawl(u, depth-1, fetcher)
	}
	return
}

var fetchedUrls fetched

func main() {
	fetchedUrls = fetched{urls: make(map[string]int)}
	go Crawl("https://golang.org/", 4, fetcher)
	time.Sleep(20 * time.Second)
}

// fakeFetcher 是返回若干结果的 Fetcher。
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher 是填充后的 fakeFetcher。
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}
