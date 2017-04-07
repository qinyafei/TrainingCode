package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"net/http"
	//"net/url"
	"encoding/json"
	"strings"
)

/*
func httpGet() {
	resp, err := http.Get("http://www.01happy.com/demo/accept.php?id=1")
	if err != nil {
		// handle error
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))
}


func httpPostForm() {
	resp, err := http.PostForm("http://www.01happy.com/demo/accept.php",
		url.Values{"key": {"Value"}, "id": {"123"}})

	if err != nil {
		// handle error
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))

}

func httpDo() {
	client := &http.Client{}

	req, err := http.NewRequest("POST", "http://www.01happy.com/demo/accept.php", strings.NewReader("name=cjb"))
	if err != nil {
		// handle error
	}

	req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
	req.Header.Set("Cookie", "name=anny")

	resp, err := client.Do(req)

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))
}

*/

var cmdIndex int = 200
var loginSession string

var loginBody string = `{
   "id" : 1,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" : {
         "password" : "123123",
         "user" : "admin"
      },
      "call" : "Security.Session.login"
   }
   }`

type LoginResArgs struct {
	Session        string `json:"session"`
	FirstLoginFlag int    `json:"firstLoginFlag"`
}

//System.Dev.list
var devlist string = `{
   "id" : 201,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{},
      "call" : "System.Dev.list"
   }
   }`

//System.Language.get
var langet string = `{
   "id" : 202,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{},
      "call" : "System.Language.get"
   }
   }`

//System.Group.list
var usrgroup string = `{
   "id" : 203,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{},
      "call" : "System.Group.list"
   }
   }`

//System.Time.adjustIpc
var timeipc string = `{
   "id" : 204,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{
		"interval":"1",
		"correctTime": "enable"
	},
      "call" : "System.Time.adjustIpc"
   }
   }`

//Security.GroupPri.list
var scrtgr string = `{
   "id" : 205,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{
		"groupId":"1"
	},
      "call" : "Security.GroupPri.list"
   }
   }`

//Event.Plan Holiday.list
var hollist string = `{
   "id" : 206,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{},
      "call" : "Event.PlanHoliday.list"
   }
   }`

//Event.PlanHoliday.add

//Event.PlanTemplate.edit
var tempedit string = `{
   "id" : 207,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" : {
      "args" :{
		"id": "2",
		"name": "richard"
	},
      "call" : "Event.PlanTemplate.edit"
   }
   }`

//Disk.Dir.add
var diskadd string = `{
   "id" : 208,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" :{
	"dirs":[{
    "storageDirGroupId":"1",
    "dir": "/sdb1",
    "size":"100",
    "recordRatio": "1",
    "mode":"1",
    "dirType":"local"
    }],
"call": "Disk.Dir.add"
}
}`

//Disk.Dir.list
var disklist string = `{
   "id" : 209,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" :{
	 "args" :{},
"call": "Disk.Dir.list"
}
}`

//Security.GroupPri.add
var grpadd string = `{
   "id" : 209,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" :{
	"args": {
            "name": "super",
            "privilegeTag": [
                {
                    "type": "SYSTEM",
                    "Privilege": [
                        "A_DISK#B_DISKLIST",
                        "A_ALARM#B_DOOR"
                    ]
                },
                {
                    "type": "VIDEO",
                    "Privilege": "1#2#3#32"
                },
                {
                    "type": "PTZ",
                    "Privilege": "1#2#3#32"
                }
            ],
            "memo": "test"
        },
"call": "Security.GroupPri.add"
}
}`

//System.Dev.add
var devadd string = `{
   "id" : 209,
   "jsonrpc" : "2.0",
   "method" : "brest",
   "params" :{
	 "args" :{
    	"vmrChannel": "150",
	     "ip": "192.168.0.189", 
	     "name": "",
	     "devType": "" ,   
	     "model": "BSR-IPE321",
	     "port": "3721",
	     "transProtocol": "tcp",
	     "DataPort": "3720",
	     "vendor" : "bstar",
	     "userName": "admin",
	     "pwd": "123123"
},
"call": "System.Dev.add"
}
}`

func Login(args string) {
	url := "http://192.168.0.178:80/rest/2.0/lg"

	resp, err := http.Post(url,
		"",
		strings.NewReader(args))
	if err != nil {
		fmt.Println(err)
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	var data map[string]interface{}
	if err := json.Unmarshal([]byte(body), &data); err == nil {
		result := data["result"]
		//fmt.Println(result)
		if restype, ok := result.(map[string]interface{}); ok {
			//fmt.Println("result is map")
			args := restype["args"]
			if argstype, ok := args.(map[string]interface{}); ok {
				sess := argstype["session"]
				if sesstype, ok := sess.(string); ok {
					loginSession = sesstype
					fmt.Println(loginSession)
				}
			}
		}
	}
	fmt.Println(string(body))
}

func httpPost(args string, session string) {
	url := "http://192.168.0.178:80/rest/2.0/lg"
	if (strings.Count(session, "") - 1) > 0 {
		url += "/auth_none?session="
		url += session
	}
	fmt.Println(url)
	fmt.Println(args)

	resp, err := http.Post(url,
		"",
		strings.NewReader(args))
	if err != nil {
		fmt.Println(err)
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))
}

func main() {
	//func test_main() {
	for {
		//var quit *bool = flag.Bool("q", false, "is quit")
		var functest *string = flag.String("func", "login", "protocol interface testing")
		flag.Parse()

		switch *functest {
		case "login":
			fmt.Println("login test")
			Login(loginBody)
		case "devlist":
			fmt.Println("devlist test")
			Login(loginBody)
			httpPost(devlist, loginSession)
		case "langet":
			fmt.Println("langet test")
			Login(loginBody)
			httpPost(langet, loginSession)
		case "usrgroup":
			fmt.Println("usrgroup test")
			Login(loginBody)
			httpPost(usrgroup, loginSession)
		case "timeipc":
			fmt.Println("timeipc test")
			Login(loginBody)
			httpPost(timeipc, loginSession)
		case "scrtgr":
			fmt.Println("scrtgr test")
			Login(loginBody)
			httpPost(scrtgr, loginSession)
		case "hollist":
			fmt.Println("hollist test")
			Login(loginBody)
			httpPost(hollist, loginSession)
		case "tempedit":
			fmt.Println("tempedit test")
			Login(loginBody)
			httpPost(tempedit, loginSession)
		case "diskadd":
			fmt.Println("diskadd test")
			Login(loginBody)
			httpPost(diskadd, loginSession)
		case "disklist":
			fmt.Println("disklist test")
			Login(loginBody)
			httpPost(disklist, loginSession)
		case "grpadd":
			fmt.Println("grpadd test")
			Login(loginBody)
			httpPost(grpadd, loginSession)
		case "devadd":
			fmt.Println("devadd test")
			Login(loginBody)
			httpPost(devadd, loginSession)

		}
		break
	}

	fmt.Println("main exit...")

}
