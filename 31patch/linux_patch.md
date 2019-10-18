#patch 使用 #

## liunx patch ##

### 语法 ###


	patch [-bceEflnNRstTuvZ][-B <备份字首字符串>][-d <工作目录>][-D <标示符号>][-F <监别列数>][-g <控制数值>][-i <修补文件>][-o <输出文件>][-p <剥离层级>][-r <拒绝文件>][-V <备份方式>][-Y <备份字首字符串>][-z <备份字尾字符串>][--backup-if -mismatch][--binary][--help][--nobackup-if-mismatch][--verbose][原始文件 <修补文件>] 或 path [-p <剥离层级>] < [修补文件]

### demo ###
	
	$ cat testfile1                 #查看testfile1的内容  
	Hello,This is the firstfile!  
	$ cat testfile2                 #查看testfile2的内容  
	Hello,Thisisthesecondfile!  
	$ diff testfile1 testfile2          #比较两个文件  
	1c1  
	<Hello,Thisisthefirstfile!  
	---  
	>Hello,Thisisthesecondfile!  
	#将比较结果保存到tetsfile.patch文件  
	$ diff testfile1 testfile2>testfile.patch     
	$ cat testfile.patch                #查看补丁包的内容  
	1c1  
	<Hello,Thisisthefirstfile!  
	---  
	>Hello,Thisisthesecondfile!  
	#使用补丁包升级testfile1文件  
	$ patch -p0 testfile1 testfile.patch      
	patching file testfile1  
	$cat testfile1                  #再次查看testfile1的内容  
	#testfile1文件被修改为与testfile2一样的内容  
	Hello,This is the secondfile!   
## git patch ##

### 参考web ###
	https://www.jianshu.com/p/4166e97ece87

### git patch使用 ###

#### 1.生成patch ####

	git format-patch HEAD^                                 //最近一次提交节点的patch
	git format-patch  节点A   节点B //两个节点之间的patch
	git format-patch HEAD^^　　　　　　　　　　　　　  #生成最近的2次commit的patch

#### 2.使用patch ####

	git apply --check patch  //检测patch是否可以正常打入
	git apply patch //将patch文件内容差分到本地 