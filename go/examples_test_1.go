package main

import (
	"fmt"
	"strconv"
	"time"
)

/**
测试要点：
1 函数
2 类对象构造
3 指针对象
4 返回多个返回值
5 if
6 map
7 go channel
8 interface
9 select
10 goroutine
11 standard library
os
strings
log
encoding/json
flag
context
testing
12 reflect
*/

//------------------------
//test class
type WorkInfo struct {
	name string
	ip   string
	port int
}

func (w *WorkInfo) Print() {
	fmt.Println(w.name, w.ip, w.port)
}

func Test_classConstruct() {
	work := WorkInfo{
		name: "workinfo",
		ip:   "localhost",
		port: 3310,
	}
	work.name = "changed"
	fmt.Println(work.name)

	pwork := &WorkInfo{
		name: "a",
		ip:   "127.0.0.1",
		port: 3721,
	}
	fmt.Println(pwork.ip)
}

func Test_class2() {
	info := new(WorkInfo)
	info.name = "1"

	info2 := WorkInfo{}
	info2.ip = "1.1.1.1"

	//info3 := &WorkInfo{}
	//info3 = info

	info4 := &WorkInfo{"a", "1.1.1.1", 1234}
	fmt.Println(info4.name, info4.ip, info4.port)

	//info5 := &WorkInfo{name: "a", port: 4333}

}

//---------------------------end

//------------------------
//test function

//-------------------------end

//------------------------
//test map array string
func Test_map_getvalue(key string) (WorkInfo, error) {
	var workmap map[string]WorkInfo
	workmap = make(map[string]WorkInfo)
	info := WorkInfo{
		ip:   "1.1.1.1",
		name: "qinyafei",
		port: 3333,
	}

	workmap["qinyafei"] = info

	//
	map2 := make(map[string]string)
	map2["a"] = "123"
	map2["b"] = "456"

	//
	map3 := map[string]string{
		"a": "aa",
		"b": "bb",
		"c": "cc",
	}

	//
	if v, ok := map3["a"]; ok {
		fmt.Println("find key a", v)
	} else {
		fmt.Println("key not found")
	}
	//
	for k, v := range map3 {
		fmt.Println(k, v)
	}

	return info, nil

}

func Test_array() {
	var arr = [5]string{"a", "b", "c"}
	fmt.Println(arr[0])
	arr2 := [...]string{"c", "d", "j", "l"}
	fmt.Println(arr2[3])
	arr2[0] = "cdjl"
	arrint := [5]int{1: 4, 3: 10, 4: 11}
	for index, val := range arrint {
		fmt.Println(index, val)
	}

}

func Test_for() {
	for {
		//while(true)
		break
	}

	for i := 0; i < 5; i++ {
		fmt.Println("test_for", i)
	}

	var sum int
	sum = 1
	for sum < 20 {
		sum += 5
	}
}

//-------------------------end

//------------------
//go channel
func Test_channel2() {
	ch := make(chan bool)
	close(ch)
	//close(ch) //twice panic
	bok := <-ch

	ch2 := make(chan string)
	close(ch2)
	//ch2 <- "bad" //panic
	str, bok := <-ch2
	if bok {
		fmt.Println(str)
	} else {
		fmt.Println("chan closed")
	}

	ch3 := make(chan int)
	go func() {
		for {
			msg, ok := <-ch3
			if ok {
				fmt.Println(msg, ok)
			} else {
				fmt.Println("goroutine break")
				break
			}
			fmt.Println("goroutine...")
		}
	}()

	ch3 <- 1
	fmt.Println("chan3 wait lock1")
	ch3 <- 2
	fmt.Println("chan3 wait lock2")
	ch3 <- 3
	fmt.Println("chan3 wait lock3")
	//for v := range ch3 {
	//	fmt.Print(v)
	//}
}

func Test_channel_timeout() {
	ch2 := make(chan int64, 5)
	defer close(ch2)

	timeout := make(chan bool)
	defer close(timeout)

	go func() {
		time.Sleep(time.Second * 5)
		timeout <- true
	}()

	select {
	case <-timeout:
		fmt.Println("timeout...")
	case <-ch2:
		fmt.Println("read chan")
	}
}

func Test_channel_deadlock() {
	ch := make(chan string, 2)
	ch <- "wa"
	ch <- "wb"
	select {
	case ch <- "wc":
		fmt.Println("ch<-wc ok")
	default:
		fmt.Println("channel if full")
	}

	close(ch)
	//when ch close,for range break
	for v := range ch {
		fmt.Println(v)
	}

	//
	ch2 := make(chan int)
	select {
	case num := <-ch2:
		fmt.Println(num)
	case <-time.After(time.Second * 2):
		fmt.Println("ch2 read timeout")
	}

}

//-------------------------end

//------------------
//standard library

//-------------------------end

//------------------
//interface
func Test_interface() {
	var inter interface{}
	var num int = 5
	str := "interface"
	inter = str
	fmt.Println(inter)

	inter = num
	fmt.Println(inter)

}

type Person struct {
	name  string
	age   int
	phone string
}

func (p Person) String() string {
	return "(" + p.name + "," + strconv.Itoa(p.age) + "," + p.phone + ")"
}

func Test_interface2() {
	MrQin := Person{"qinyafei", 32, "12334556"}
	fmt.Println("the person is:", MrQin)

	//
	type Base interface {
		Read() string
	}

	type Derive interface {
		Write(str string)
		Base
	}
}

func Test_interface3() {
	type Element interface{}
	type List []Element

	alist := make(List, 5)
	alist[0] = 4
	alist[1] = "string"
	alist[2] = Person{"qyf", 22, "343532"}

	for _, ele := range alist {
		if val, bok := ele.(int); bok {
			fmt.Println("ele is int:", val)
		} else if val, bok := ele.(string); bok {
			fmt.Println("ele is string:", val)
		} else if val, bok := ele.(Person); bok {
			fmt.Println("ele is Person:", val)
		}
	}
}

//-------------------------end

func main() {
	fmt.Printf("hello golang \n")
	fmt.Println("hello golang", 1)
	fmt.Printf("hello golang:%s", "world")

	Test_classConstruct()
	Test_class2()
	key := "qinyafei"
	Test_map_getvalue(key)
	Test_array()
	Test_for()
	Test_channel2()
	Test_channel_timeout()
	Test_channel_deadlock()
	Test_interface()
	Test_interface2()
	Test_interface3()
}
