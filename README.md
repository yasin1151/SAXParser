# SAXParser

> 从cocos2dx-3.9中提取的一个小组件

SAX (simple API for XML) 它是一种逐行扫描文档，
一边扫描一边解析的解析方法		
相比于DOM，SAX速度更快，更有效



自带例子的测试：
```
<?xml version="1.0" encoding="utf-8"?>
<resourse>
  <string name="first">
  hello
  <stringChild name="firstChild">child</stringChild>
  world
  </string>
  <string name="second">hey</string>
</resourse>
```

解析后:

```
< resourse >
< string atts[0] : 'name' atts[1] : 'first'  >
hello
< stringChild >
child
</ stringChild>
world
</ string>
< string atts[0] : 'name' atts[1] : 'second'  >
hey
</ string>
</ resourse>

name set:
name 1 = first
name 2 = second
```
