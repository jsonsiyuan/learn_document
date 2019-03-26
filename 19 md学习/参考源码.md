# 公牛智脑协议 sig-mesh 部分报文交互参考

----------

| 版本号 |更新内容|记录人|记录时间|
| :---: |:---:| :---:| :---:|
| V0.0.1 |初步整理文档|缪观山|2019/3/25 18:45:43 |
| V0.0.2 |修改 `5.1.2` 报文解析|缪观山|2019/3/26 10:35:07  |
| V0.0.1 |增加节点心跳机制|缪观山|2019/3/26 11:35:12  |
注：

- 本文档以节点灯作为实例
- 数据报文链路是 APP<->云端<->Gateway<->Node

目录：

* [指令示例部分](#a)
	* [1. 开灯](#1)
		* [1.1 指令下发](#1.1)
			* [1.1.1 手机APP -> 云端](#1.1.1)
			* [1.1.2 云端-> Gateway](#1.1.2)
		* [1.2节点响应](#1.2)
			* [1.2.1 node->Gateway->云端](#1.2.1)
			* [1.2.2 云端-> 手机app](#1.2.2)
	* [2. 关灯](#2)
		* [2.1 指令下发](#2.1)
			* [2.1.1 手机APP -> 云端](#2.1.1)
			* [2.1.2 云端-> Gateway](#2.1.2)
		* [2.2节点响应](#2.2)
			* [2.2.1 node->Gateway->云端](#2.2.1)
			* [2.2.2 云端-> 手机app](#2.2.2)
	* [3. 广播开灯](#3)
		* [3.1 指令下发](#3.1)
			* [3.1.1 手机APP -> 云端](#3.1.1)
			* [3.1.2 云端-> Gateway](#3.1.2)
		* [3.2节点响应](#3.2)
			* [3.2.1 node->Gateway->云端](#3.2.1)
			* [3.2.2 云端-> 手机app](#3.2.2)
	* [4. 广播关灯](#4)
		* [4.1 指令下发](#1.1)
			* [4.1.1 手机APP -> 云端](#4.1.1)
			* [4.1.2 云端-> Gateway](#4.1.2)
		* [4.2节点响应](#1.2)
			* [4.2.1 node->Gateway->云端](#4.2.1)
			* [4.2.2 云端-> 手机app](#4.2.2)
	* [5. 亮度调节](#5)
		* [5.1 指令下发](#5.1)
			* [1.1.1 手机APP -> 云端](#5.1.1)
			* [1.1.2 云端-> Gateway](#5.1.2)
		* [5.2节点响应](#5.2)
			* [5.2.1 node->Gateway->云端](#5.2.1)
			* [5.2.2 云端-> 手机app](#5.2.2)
	* [6. 色温调节](#6)
		* [6.1 指令下发](#6.1)
			* [6.1.1 手机APP -> 云端](#6.1.1)
			* [6.1.2 云端-> Gateway](#6.1.2)
		* [6.2节点响应](#6.2)
			* [6.2.1 node->Gateway->云端](#6.2.1)
			* [6.2.2 云端-> 手机app](#6.2.2)
	* [7. 节点固件版本查询](#7)
		* [7.1 指令下发](#7.1)
			* [7.1.1 手机APP -> 云端](#7.1.1)
			* [7.1.2 云端-> Gateway](#7.1.2)
		* [7.2节点响应](#7.2)
			* [7.2.1 node->Gateway->云端](#7.2.1)
			* [7.2.2 云端-> 手机app](#7.2.2)
	* [8. 节点 kick out ](#8)
		* [8.1 指令下发](#8.1)
			* [8.1.1 手机APP -> 云端](#8.1.1)
			* [8.1.2 云端-> Gateway](#8.1.2)
		* [8.2节点响应](#8.2)
			* [8.2.1 node->Gateway->云端](#8.2.1)
			* [8.2.2 云端-> 手机app](#8.2.2)
	* [9. 节点固件升级](#9)
		* [9.1 指令下发](#1.1)
			* [9.1.1 手机APP -> 云端](#9.1.1)
			* [9.1.2 云端-> Gateway](#9.1.2)
		* [9.2节点响应](#1.2)
			* [9.2.1 node->Gateway->云端](#9.2.1)
			* [9.2.2 云端-> 手机app](#9.2.2)
	* [10.灯亮度状态上报 ](#10)
		* [10.1 指令下发](#10.1)
			* [10.1.1 手机APP -> 云端](#10.1.1)
			* [10.1.2 云端-> Gateway](#10.1.2)
		* [10.2节点响应](#10.2)
			* [10.2.1 node->Gateway->云端](#10.2.1)
			* [10.2.2 云端-> 手机app](#10.2.2)
* [节点心跳机制](#a) 

<h2 id="a">指令示例部分</h2>	
<h3 id="1">1. 开灯</h3>	
<h4 id="1.1">1.1 指令下发</h4>	
<h5 id="1.1.1">1.1.1 手机APP -> 云端</h5>

云端收到的数据如下：

	{
	"serial":1,
	"devices":[{
		"gwDeviceUUID":"ea2a2b661fd0bcc15b51ab86d7804940",
		"hexCmd":["0000000002010A00820201000000"]
	}]
	}	

**`hexCmd` 的 `value` 是 `sig-mesh` 的标准报文，此报文云端下发给网关。
由于此文档关注的是 sig-mesh 报文的解析说明，所以后续的实例不再重复 手机APP-> 云端 这部分报文内容，只是在这里展示一下手机app->云端的通讯报文框架。**

<h5 id="1.1.2">1.1.2 云端-> Gateway</h5>

云端发送的数据如下：

	00 00 00 00 02 01 0A 00 82 02 01 00 00 00

`sig-mesh` 指令解析如下： 
	
| 0000 |0000|02|01|0A00|8202|01|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|OnOff|TID|Transition time |Delay|

部分注解：

- `nk_idx`：`network key index`
- `ak_idx`:`app key index`
- `reliable retry cnt`:应用层 `retry` (发出命令后如果收不到回复则重发次数)
- `eliable rsp_max`:设置回复的节点的个数
- `dst`:目的地址填充
- `op`:sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.1 Messages summary >`
- 剩余部分：传参部分，`generic onoff` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<3.2.1.2 Generic OnOff Set >`

<h4 id="1.2">1.2 节点响应</h4>	
<h5 id="1.2.1">1.2.1 node->Gateway->云端</h5>

云端收到的数据如下：

	91 81 0A 00 FF 0F 82 04 01


| 91 |81|0A 00|FF 0F|82 04|01|
| :---: |:---:| :---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|OnOff|

- `dir_rsp`: 芯片厂商定义的响应命令类型
- `rsp`: 芯片厂商定义的 返回 `gateway` 收到的rsp包命令类型
- `src`: 节点地址
- `dst`:目的地址填充，这里指的是 `Gateway unicast addr` 
- `op`:sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.1 Messages summary >`
- `OnOff`:传参部分，`generic onoff ACK` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<3.2.1.2 Generic OnOff Set >`

<h5 id="1.2.2">1.2.2 云端-> 手机app</h5>

云端发送的数据如下：

	[{
	"deviceUUID": "9e4e2bed3e0fc4df0424707660b092ab",
	"elements": [{
		"elementIndex": 0,
		"meshAddress": 10,
		"models": [{
			"modelId": 4096,
			"opCode": 33284,
			"value": 1
		}]
	}],
	"onLine": 1
	}]	

- `meshAddress`: `node  meshAddress`
- `modelId`: sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.3 Models summary >`
- `opCode`:暂未使用。
- `value`: 表示开关状态，`0 - off ， 1 - on`
- `online` : `node` 是否在线


<h3 id="2">2.关灯</h3>	
<h4 id="2.1">2.1 指令下发</h4>	
<h5 id="2.1.1">2.1.1 手机APP -> 云端</h5>

略。

<h5 id="2.1.2">2.1.2 云端-> Gateway</h5> 

云端发送的数据如下：

	00 00 00 00 02 01 0A 00 82 02 00 00 00 00

`sig-mesh` 指令解析如下： 
	
| 0000 |0000|02|01|0A00|8202|00|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|OnOff|TID|Transition time |Delay|

部分注解：

- `nk_idx`：`network key index`
- `ak_idx`:`app key index`
- `reliable retry cnt`:应用层 `retry` (发出命令后如果收不到回复则重发次数)
- `eliable rsp_max`:设置回复的节点的个数
- `dst`:目的地址填充
- `op`:sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.1 Messages summary >`
- 参数部分：传参部分，`generic onoff` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<3.2.1.2 Generic OnOff Set >`

<h4 id="2.2">2.2 节点响应</h4>	
<h5 id="2.2.1">2.2.1 node->Gateway->云端</h5>

云端收到的数据如下：

	91 81 0A 00 FF 0F 82 04 00


| 91 |81|0A 00|FF 0F|82 04|00|
| :---: |:---:| :---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|OnOff|

- `dir_rsp`: 芯片厂商定义的响应命令类型
- `rsp`: 芯片厂商定义的 返回 `gateway` 收到的rsp包命令类型
- `src`: 节点地址
- `dst`:目的地址填充，这里指的是 `Gateway unicast addr` 
- `op`:sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.1 Messages summary >`
- `OnOff`:传参部分，`generic onoff ACK` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<3.2.1.2 Generic OnOff Set >`

<h5 id="2.2.2">2.2.2 云端-> 手机app</h5>

云端发送的数据如下：

	[{
	"deviceUUID": "9e4e2bed3e0fc4df0424707660b092ab",
	"elements": [{
		"elementIndex": 0,
		"meshAddress": 10,
		"models": [{
			"modelId": 4096,
			"opCode": 33284,
			"value": 0
		}]
	}],
	"onLine": 1
	}]	

- `meshAddress`: `node  meshAddress`
- `modelId`: sig-mesh 规范定义的标准命令码，可以参考 `<Mesh_Model_Specification v1.0>` ，命令码不是固定长度
文档里的 `<7.3 Models summary >`
- `opCode`:暂未使用。
- `value`: 表示开关状态，`0 - off ， 1 - on`
- `online` : `node` 是否在线



<h3 id="3">3.广播开灯</h3>	
<h4 id="3.1">3.1 指令下发</h4>	
<h5 id="3.1.1">3.1.1 手机APP -> 云端</h5>

略。

<h5 id="3.1.2">3.1.2 云端-> Gateway</h5> 

云端发送的数据如下：
	
	00 00 00 00 02 00 FF FF 82 02 01 00 00 00

| 0000 |0000|02|00|FFFF|8202|01|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|OnOff|TID|Transition time |Delay|

- `dst`:目的地址填充，FFFF 是广播地址
-其他字段解析参考[1.1.2 云端-> Gateway ](#1.1.2) 

<h4 id="3.2">3.2 节点响应 </h4>	
<h5 id="3.2.1">3.2.1 node->Gateway->云端</h5>

当前 Mesh 网络下的 Node 收到广播开灯的消息之后，都会响应ACk.响应的ACk格式可以参考[1.2.1 node->Gateway->云端 ](#1.1.2)

<h5 id="3.2.2">3.2.2 云端->手机app</h5>

参考[1.2.1 云端-> 手机app ](#1.2.2)


<h3 id="4">4.广播关灯</h3>	
<h4 id="4.1">4.1 指令下发</h4>	
<h5 id="4.1.1">4.1.1 手机APP -> 云端</h5>

略。
<h5 id="4.1.2">4.1.2 云端-> Gateway</h5>

云端发送的数据如下：
	
	00 00 00 00 02 00 FF FF 82 02 00 00 00 00

| 0000 |0000|02|00|FFFF|8202|00|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|OnOff|TID|Transition time |Delay|

- `dst`:目的地址填充，FFFF 是广播地址
-其他字段解析参考 关灯-指令下发-云端-> Gateway **2.1.2**

<h4 id="4.2">4.2 节点响应 </h4>	
<h5 id="4.2.1">4.2.1 node->Gateway->云端</h5>

当前 Mesh 网络下的 Node 收到广播开灯的消息之后，都会响应ACk.响应的ACk格式可以参考[1.2.1 node->Gateway->云端](#2.2.1)


<h5 id="4.2.2">4.2.2 node->Gateway->云端</h5>

参考[1.2.1 云端->手机app](#2.2.2)

<h3 id="5">5.亮度调节</h3>	
<h4 id="5.1">5.1 指令下发</h4>	
<h5 id="5.1.1">5.1.1 手机APP -> 云端</h5>

略。

<h5 id="5.1.2">5.1.2 云端-> Gateway</h5>

云端发送的数据如下：
	
	00 00 00 00 02 01 0A 00 82 4D 4B 4F 00 00 00

| 0000 |0000|02|01|0A00|824D|4B4F|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|Lightness|TID|Transition Time|Delay|

传参部分，`Light Lightness Linear Set Unacknowledged` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<6.3.1.3 Light Lightness Linear Set Unacknowledged >`
 
<h4 id="5.2">5.2 节点响应</h4>

**Unackonwledged**


<h3 id="6">6.色温调节</h3>	
<h4 id="6.1">6.1 指令下发</h4>	
<h5 id="6.1.1">6.1.1 手机APP -> 云端</h5>

略。
 
<h5 id="6.1.2">6.1.2 云端-> Gateway</h5>

云端发送的数据如下：
	
	00 00 00 00 02 01 0B 00 82 65 20 21 00 00 00 00 00

| 0000 |0000|02|01|0A00|8265|2021|0000|00|00|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|:---:|:---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|CTL Temperature|CTL Delta UV|TID|Transition Time|Delay|

传参部分，`Light CTL Temperature Set Unacknowledged` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<6.3.2.7 Light CTL Temperature Set Unacknowledged >`
 
<h4 id="1">6.2 节点响应</h4>	

**Unackonwledged**


<h3 id="7">7.节点固件版本查询</h3>	
<h4 id="7.1">7.1 指令下发</h4>	
<h5 id="7.1.1">7.1.1 手机APP -> 云端</h5>

略。
<h5 id="7.1.2">7.1.2 云端-> Gateway</h5>
 
云端发送的数据如下：
	
	00 00 00 00 02 01 0A 00 B6 01 00

| 0000 |0000|02|01|0A00|B601|00|
| :---: |:---:| :---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|TID|

此指令的 `TID` 可以不携带。

<h4 id="7.2">7.2 节点响应 </h4>	
<h5 id="7.2.1">7.2.1 node->Gateway->云端	</h5>

云端收到的数据如下：
	91 81 0A 00 FF 0F B6 02 12 07 56 31 2E 37

| 91 |81|0A 00|FF 0F|B6 02|12 07|56 31 2E 37|
| :---: |:---:| :---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|CID|Version str|

- `dir_rsp`: 芯片厂商定义的响应命令类型
- `rsp`: 芯片厂商定义的 返回 `gateway` 收到的rsp包命令类型
- `src`: 源地址
- `dst`:目的地址填充，这里指的是 `Gateway unicast addr` 
- `op`: 查询版本 回复cmd
- `CID`: 公司ID在sig-mesh公司身份认证代号
- `version str`：` v1.7`(ASCII)

<h5 id="7.1.1">7.2.2 云端-> 手机app</h5>

略。


<h3 id="8"> 8. 节点kick out</h3>	
<h4 id="8.1">8.1 指令下发</h4>	
<h5 id="8.1.1">8.1.1 手机APP -> 云端</h5>

略。
<h5 id="8.1.2">8.1.2 手机APP -> 云端</h5>

云端发送的数据如下：
	
	00 00 00 00 02 01 0A 00 80 49

| 0000 |0000|02|01|0A00|80 49|
| :---: |:---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|dst|op|

参考文档 `<Mesh Profile v1.0>`的 `<4.3.4.1 Alphabetical summary of opcodes >`

<h4 id="8.2">8.2 节点响应</h4>	
<h5 id="8.2.1">8.2.1 node->Gateway->云端</h5>
	
云端收到的数据如下：
	91 81 0A 00 FF 0F 80 4A

| 91 |81|0A 00|FF 0F|82 4A|
| :---: |:---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|

参考文档 `<Mesh Profile v1.0>`的 `<4.3.4.1 Alphabetical summary of opcodes >`
成功 kict out 才会收到此指令，如果失败，则接收不到。

<h5 id="8.2.2">8.2.2 云端-> 手机app</h5>

略。


<h3 id="9"> 9. 节点固件升级</h3>	
<h4 id="9.1">9.1 指令下发</h4>	
<h5 id="9.1.1">9.1.1 手机APP -> 云端</h5>

略。

<h5 id="9.1.2">9.1.2 云端-> Gateway</h5>
 
云端发送的数据如下：
	
	00 00 00 00 02 00 FF 0F B6 0A 12 07 56 31 2E 37 00 C0 4A 00 

| 0000 |0000|02|01|FF0F|B60A|1207|56 31 2E 37| 00 C0| 4A 00|
| :---: |:---:| :---:| :---:| :---:| :---:|
| nk_idx |ak_idx|reliable retry cnt|eliable rsp_max|src|op|CID|Version str|group|dst|
 
- `op`: start ota cmd
- `CID`: 公司ID在sig-mesh公司身份认证代号
- `version str`：` v1.7`(`ASCII`)
- `group`: `group addr`
- `dst`:目的地址填充，这里指的是 `node unicast addr`


<h4 id="9.2">9.2 节点响应</h4>	
<h5 id="9.2.1">9.2.1 node->Gateway->云端</h5>

云端收到的数据如下：
	91 81 FF 0F FF 0F B6 0C 01 12 07 56 31 2E 37

| 91 |81|0A 00|FF 0F|B6 0C|01|12 07| 56 31 2E 37|
| :---: |:---:| :---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|ota status|CID|Vsrsion str|

- `op`: start ota cmd
- `CID`: 公司ID在sig-mesh公司身份认证代号
- `version str`：` v1.7`(`ASCII`)

<h5 id="9.2.2">9.2.2 云端-> 手机app端</h5>

略。


<h3 id="10"> 10灯亮度上报(节点刚上电)</h3>	
<h4 id="10.1">10.1 指令下发</h4>	
无。
<h4 id="10.2">10.2 节点主动上报</h4>

<h5 id="10.2.1">10.2.1 node->Gateway->云端</h5>

云端收到的数据如下：
	91 81 0C 00 FF FF 82 4E 88 C1 66 E6 01

| 91 |81|0A 00|FF 0F|82 4E|88 C1| 66 E6| 01|
| :---: |:---:| :---:| :---:| :---:| :---:|
| dir_rsp |rsp|src|dst|op|Present Lightness|Target Lightness|Remaining Time|

传参部分，`Light Lightness Status` 控制命令填充数据为参考文档 `<Mesh_Model_Specification v1.0>`
的 `<6.3.1.4 Light Lightness Status >`

<h5 id="10.2.1">10.2.1 云端-> 手机app</h5>

略。


<h2 id="b">节点心跳机制</h2>

节点正常场景下，如果没有接收到指令(携带 `ACK` 的报文)控制是每隔 `30s`，主动上报一次节点开关状态的报文，接收到控制指令(携带 `ACK` 的报文)的情况下，重新计时，到下一个 `30s` 主动上报一次开关状态报文。

判断节点在/离线机制：
- 当前离线状态下，收到控制指令响应(携带 `ACK` 的报文)或者节点主动上报开关状态报文则将状态切换到在线状态；
- 当前在线状态下，`keepalive * 3 s`没有收到节点主动上报开关状态报文则切换为离线状态；	