#import "@preview/cuti:0.2.1": show-cn-fakebold
#show: show-cn-fakebold
#set text(16pt,font:("STIX Two Text","SimSun"))
#let indent()={ box(width: 3em) }
#let space()={ box(width: 0.2em) }
#set align(center)
#text(weight:"black")[= 实验题第1题]

#set align(left) 
#set text(11pt)

#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求从顺序表中删除最小值，并以最后一个元素来填补该最小值的位置。为了达成这一目标，首先需要通过比较找到最小值，然后用最后一个元素覆盖它。在寻找最小值时，使用两个变量分别记录最小值及其所在位置，初始化为顺序表中的第一个元素及位置，然后从顺序表的第2个元素开始依次与该最小值比较，记录更小者，从而找到顺序表的最小值和位置。在用最后一个元素覆盖最小值时，需要注意两点：①若该最小值本身就是最后一个元素，则只需直接将之删除即可，无需进行覆盖；②在用最后一个元素覆盖最小值后，相当于将该元素移动到了最小值位置，此时需要将位于原本最后一个位置上的元素删除，以免重复存储。

#text(weight:"bold")[=== (2) 源代码]
```cpp
template <class DataType>
DataType DelMinElem(SqList<DataType> &list){
  DataType min,tmp;//min标记当前的最小值，tmp为临时变量
  if (list.GetLength() == 0) return UNDER_FLOW;//如果是空表，返回下溢信息
	list.GetElem(1, min);//初始化min
	int flag = 1;//定义标记变量flag来标记最小值的序号
	for (int i = 2 ; i <= list.GetLength(); i++){//遍历顺序表，如果有更小值，则更新min，并记录其序号
    list.GetElem(i,tmp);//获取第i个数据的值，记录到tmp中
		if (tmp < min){//比较min与tmp，进行最小值的更新并标记其序号
			min=tmp;
			flag = i;
		}
	}
  list.GetElem(list.GetLength(),tmp);//获取最后一个元素的值
	list.SetElem(flag,tmp);//用最后一个元素的值替换最终标记的最小值
	list.DeleteElem(list.GetLength(),tmp);//删除最后一个元素
    return min;//返回最小值
}
```

#text(weight:"bold")[=== (3) 说明]