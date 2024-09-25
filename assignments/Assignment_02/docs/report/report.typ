#import "@preview/cuti:0.2.1": show-cn-fakebold
#show: show-cn-fakebold
#let indent()={ box(width: 3em) }
#set text(font:("STIX Two Text","SimSun"))
#let space()={ box(width: 0.2em) }
#set page(
  numbering: (..numbers) => {
  return numbering("1", counter(page).get().at(0) - 0)
},
)
#set table(
    stroke: none,
    align: center + horizon,
    inset:(x: 20pt, y: 2.5pt),
)
#let boldline()=table.hline(stroke: 1pt);
#let thinline()=table.hline(stroke: .5pt);
#let redbold(it) = text(fill: red, weight: "bold", it)

/* MODEL
#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求。为了达成这一目的，

#text(weight:"bold")[=== (2) 源代码]
```cpp

```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)
*/

#set align(center)
#text(16pt,weight:"black")[= 实验题第1题]
#set align(left) 
#set text(11pt)

#text(weight:"bold")[=== (1) 设计思路]
本题要求设计共享栈的类定义，实现判断栈空、入栈和出栈的函数。此时，两个栈的栈底分别设置在数组的两端，入栈时栈顶向数组中间移动，当两个栈的栈顶位置相遇时才是栈满状态。为了实现这一目的，可以在一个存储空间里设置两个栈顶指针，分别向后与向前移动。可以利用指针数值与容量的代数关系，找到栈满时两指针满足的条件，从而实现判空、入栈、出栈等操作。


#text(weight:"bold")[=== (2) 源代码]


#line(length: 100%, stroke: 2pt)
#v(-1em)
= SqStack(int size = DEFAULT_SIZE)`                  //构造函数`
  #line(length: 100%,stroke: 1pt)
```cpp
template<class DataType>
SqStack<DataType>::SqStack(int size)		//构造一个容量为size的共享栈
{	
	elems = new DataType[size];   //开辟存储空间，创建共享栈
	maxSize = size;
	top1 = -1;					          //构造栈1
	top2 = size;				          //构造栈2
}
```
#v(-.5em)
#line(length: 100%, stroke: 2pt)


#line(length: 100%, stroke: 2pt)
#v(-1em)
= Status Push(int id, const DataType &e)`                  //入栈`
  #line(length: 100%,stroke: 1pt)
```cpp
template<class DataType>
Status SqStack<DataType>::Push(int id, const DataType &e)
{
	if(id == 1)             
  {                       //如果id为1，对栈1执行入栈
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)			//判断栈1是否已满
			return OVER_FLOW;		//栈已满，返回上溢信息
		else                  //栈未满，执行入栈
    {								
			elems[++top1] = e;	//top1+1即为新的栈顶位置，将元素e放入该位置
			return SUCCESS; 		//返回成功信息
		}
	}
	else
  {                       //如果id不为1，对栈2执行入栈
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)			//判断栈2是否已满
			return OVER_FLOW;		//栈已满，返回上溢信息
		else                  //栈未满，执行入栈
    {								
			elems[--top2] = e;	//top2-1即为新的栈顶位置，将元素e放入该位置
			return SUCCESS; 		//返回成功信息
		}
	}
}
```
#v(-.5em)
#line(length: 100%, stroke: 2pt)
#pagebreak(weak: true)


#line(length: 100%, stroke: 2pt)
#v(-1em)
= Status Pop(int id, DataType &e)`                         //出栈`
  #line(length: 100%,stroke: 1pt)
```cpp
template<class DataType>
Status SqStack<DataType>::Pop(int id, DataType &e)	//若出栈成功，用e返回栈顶元素的值
{	
	if (id == 1)              //判断对栈1还是栈2进行出栈
  {
		if (IsEmpty(id))		    //判断栈1是否为空
			return UNDER_FLOW;	  //栈空，返回下溢信息
		else {								  //栈不为空，执行出栈
			e = elems[top1--];		//获取当前栈顶元素的值，并删除该元素，栈顶指针前移
			return SUCCESS; 			//返回成功信息
		}
	}
	else
  {
		if (IsEmpty(id))				//判断栈2是否为空
			return UNDER_FLOW;		//栈空，返回下溢信息
		else {								  //栈不为空，执行出栈
			e = elems[top2++];		//获取当前栈顶元素的值，并删除该元素，栈顶指针后移
			return SUCCESS; 			//返回成功信息
		}
	}
}
```
#v(-.5em)
#line(length: 100%, stroke: 2pt)


#line(length: 100%, stroke: 2pt)
#v(-1em)
= bool IsEmpty(int id) const`                           //判断栈空`
  #line(length: 100%,stroke: 1pt)
```cpp
template<class DataType>
bool SqStack<DataType>::IsEmpty(int id) const		//利用共享栈两边为栈顶的特性，分别判断栈空
{
	if(id == 1)               //判断对栈1还是栈2进行操作
  {
		return top1 == -1;      //如果栈顶指针1指向-1，则栈1空
	}
	return top2 == maxSize;   //如果栈顶指针2指向maxSize，则栈2空
}
```
#v(-.5em)
#line(length: 100%, stroke: 2pt)


#text(weight:"bold")[=== (3) 说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)
