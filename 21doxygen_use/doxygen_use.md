# Doxygen & Graphviz #
------

> Graphviz是一个图形可视化软件。Doxygen使用Graphviz生成各种图形

> Doxygen 是代码注释生成器。

# 参考web #

> https://blog.51cto.com/ticktick/188672

> https://www.cnblogs.com/chenyang920/p/5732643.html

> https://www.jianshu.com/p/9464eca6aefe

**download**

> hhc.exe
> 
> http://www.create-chm.com/chm-help-compiler/


# demo #

## 文件头 ##

	/**
	 * @file 文件名
	 * @brief 简介
	 * @details 细节
	 * @mainpage 工程概览
	 * @author 作者
	 * @email 邮箱
	 * @version 版本号
	 * @date 年-月-日
	 * @license 版权
	 */

## 类定义注释 ##

	 /**
	 * @brief 类的简单概述
	 * 类的详细概述
	 */

## 常量/变量的注释 ##

	/// 注释
	常量/变量
	
	常量/变量 ///< 注释

	常量/变量 /**< 注释 */   
## 函数注释 ##

	/**
	 * @brief 函数简介
	 *
	 * @param 形参 参数说明
	 * @param 形参 参数说明
	 * @return 返回说明
	 *   @retval 返回值说明
	 */

**详细注释**

	/**
	 * @brief 函数简介
	 * @detail 详细说明
	 * 
	 * @param 形参 参数说明
	 * @param 形参 参数说明
	 * @return 返回说明
	 *   @retval 返回值说明
	 * @note 注解
	 * @attention 注意
	 * @warning 警告
	 * @exception 异常
	 */

## 其他 ##

|其他命令|解释|
|--|--|
|@class	|引用类|
|@var|引用变量|
|@enum|引用枚举|

# note #

**GB2312 有中文**
