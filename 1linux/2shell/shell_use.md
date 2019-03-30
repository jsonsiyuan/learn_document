# shell base use #
------
## BASE 环境设置 ##

BASH 的环境配置文件


1. 系统设置 
> BASH 的系统配置主要存储在 /etc/profilr,/etc/bashrc (ubuntu 上是/etc/bash.bashrc)。

2. 用户设置

> .bash_history
> .bash_logout
> .bashrc 

## 重点命令 ##

	export [-fnp][变量名称]=[变量设置值]
	-f 代表[变量名称]中为函数名称。
	-n 删除指定的变量。变量实际上并未删除，只是不会输出到后续指令的执行环境中。
	-p 列出所有的shell赋予程序的环境变量。
	
	export PATH=/bin/bash:$PATH

---
	sh，bash，./:
	
	这三种形式都是用来打开一个子shell来读取并执行FileName中命令.而对于./命令，filename文件必须要有执行权限.

------

	source 和 .
	在当前bash环境下读取并执行FileName中的命令。. 是source 别名。