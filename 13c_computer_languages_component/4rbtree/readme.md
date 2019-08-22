# Linux kernel rbtree#

> Red-black trees（rbtree）是一种自平衡的二叉搜索树，用于存储可分类的key/value数据对。
> 它不同于radix trees或者hash tables。
> radix trees用于有效存储稀疏数组（使用长整型索引进行节点的插入、查询和删除），其索引值太大无法用数组直接存储。
> hash tables用于散列索引缩小查询的范围，但它没有做排序，因此不能快速的定位。

## rbtree code ##

	lib/rbtree.c
	linux/rbtree.h

## rbtree使用方法 ##

### web ###

	https://www.cnblogs.com/jimbo17/p/8298163.html
### rbtree.txt 官方使用介绍 ###





