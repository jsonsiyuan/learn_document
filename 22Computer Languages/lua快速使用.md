# lua 快速使用查询文档 #

## 注释 ##

两个减号是单行注释:

	--

多行注释：

	--[[
	 多行注释
	 多行注释
 	--]]

## 关键词 ##

| :---: |:---:| :---:| :---:|
|and|break|do|else|
|elseif|end|false|for|
|function|if|in|local|
|nil|not|or|repeat|
|return|then|true|until|
|while||||

## Lua 数据类型 ##
|数据类型|描述|
| :---: |:---:| 
|nil|这个最简单，只有值nil属于该类，表示一个无效值（在条件表达式中相当于false）。|
|boolean|包含两个值：false和true。|
|number|表示双精度类型的实浮点数|
|string|字符串由一对双引号或单引号来表示|
|function|由 C 或 Lua 编写的函数|
|userdata|表示任意存储在变量中的C数据结构|
|thread|表示执行的独立线路，用于执行协同程序|
|table|Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字、字符串或表类型。在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。|

### ## type ## ###

	type(a) --类型查看

### string（字符串） ###

	string1 = "this is string1"

2 个方括号 "[[]]" 来表示"一块"字符串

	html = [[
		<html>
		<head></head>
		<body>
    		<a href="http://www.runoob.com/">菜鸟教程</a>
		</body>
		</html>
		]]


### table（表） ###

demo：

	-- 创建一个空的 table
	local tbl1 = {}
	
	-- 直接初始表
	local tbl2 = {"apple", "pear", "orange", "grape"}

----

	a = {}
	a["key"] = "value"
	key = 10
	a[key] = 22
	a[key] = a[key] + 11
	for k, v in pairs(a) do
	    print(k .. " : " .. v)
	end

--

	-- table_test2.lua 脚本文件
	local tbl = {"apple", "pear", "orange", "grape"}
	for key, val in pairs(tbl) do
	    print("Key", key)
	end


### function（函数） ###

	-- function_test.lua 脚本文件
	function factorial1(n)
	    if n == 0 then
	        return 1
	    else
	        return n * factorial1(n - 1)
	    end
	end
	print(factorial1(5))
	factorial2 = factorial1
	print(factorial2(5))

## Lua 变量 ##

Lua 变量有三种类型：全局变量、局部变量、表中的域

	a = 5               -- 全局变量
	local b = 5         -- 局部变量

	function joke()
    	c = 5           -- 全局变量
    	local d = 6     -- 局部变量
	end

### 索引 ###

	t[i]
	t.i                 -- 当索引为字符串类型时的一种简化写法

### 可变参数 ###

在函数参数列表中使用三点 ... 表示函数有可变的参数

那么就可以用 select 函数来访问变长参数了：select('#', …) 或者 select(n, …)

	select('#', …) 返回可变参数的长度
	select(n, …) 用于访问 n 到 select('#',…) 的参数


## Lua 迭代器 ##

	for k, v in pairs(t) do
	print(k, v)
	end

-----

	demo：
	array = {"Google", "Runoob"}
	
	for key,value in ipairs(array) 
	do
		print(key, value)
	end