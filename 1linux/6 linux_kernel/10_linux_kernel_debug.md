# 调试和性能优化 #

## printk ##

## 动态输出 ##
在内核配置时打开 **CONFIG_DYNAMIC_DEBUG**

## proc，sys，debugfs ##

都是内核的虚拟文件

proc ：用户和内核内部数据结构进行交互，比如获得进程的有用信息
sys  ：对计算机上的所有设备进行统一的表示和操作
debugfs：私有的调试信息可以显示在这个虚拟文件中

## kernelshark图形化分析 ##

备注：具体遇到再使用