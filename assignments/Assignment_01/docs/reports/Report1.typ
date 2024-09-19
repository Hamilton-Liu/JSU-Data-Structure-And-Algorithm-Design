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
/* MODEL
#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求。为了达成这一目的，

#text(weight:"bold")[=== (2) 源代码]
```c

```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)
*/

#set align(center)
#text(16pt,weight:"black")[= 实验题第1题]
#set align(left) 
#set text(11pt)


#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求从顺序表中删除最小值，并以最后一个元素来填补该最小值的位置。为了达成这一目标，首先需要通过比较找到最小值，然后用最后一个元素覆盖它。在寻找最小值时，使用两个变量分别记录最小值及其所在位置，初始化为顺序表中的第一个元素及位置，然后从顺序表的第2个元素开始依次与该最小值比较，记录更小者，从而找到顺序表的最小值和位置。在用最后一个元素覆盖最小值时，需要注意两点：①若该最小值本身就是最后一个元素，则只需直接将之删除即可，无需进行覆盖；②在用最后一个元素覆盖最小值后，相当于将该元素移动到了最小值位置，此时需要将位于原本最后一个位置上的元素删除，以免重复存储。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//1-1 从顺序表中删除具有最小值的元素（假设顺序表中元素都不相同），并由函数返回被删元素的值，空出的位置由最后一个元素填补。
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
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)


#text(weight:"bold")[== 第2小题]

#text(weight:"bold")[=== (1)设计思路]
本题要求从顺序表中删除与给定值e相等的所有元素。为了达成这一目的，需要通过数据比对，寻找数据域与给定值e数值相同的元素的位置，并对其进行删除处理。在寻找数据域与给定值e数值相同的元素时，需要对顺序表进行遍历，一旦出现目标元素，就利用循环次数i与其序号相同的特点，立刻对其进行删除，并获取删除数据信息。整个过程需要一次完整的遍历，以删除所有数据域与给定值e相等的元素。需要注意的是，如果选择顺序（正向）遍历，在删除元素后会导致整体序号的前移，而记录循环次数的i不会前移，因此需要对此进行处理，方法有二：*(1)* 在每次删除后对计数器i进行一次自减操作(`i--`)，以保证i和数据序号的一致性（未测试）；*(2)* 对目标顺序表进行反向遍历，这样删除数据就不会影响未经遍历的数据次序，数据的序号和计数器i就不会发生错位（测试并采纳）。相较于方法1，方法2的语法更简单，执行的操作更少，操作更安全。

#text(weight:"bold")[=== (2)源代码]
```c
//1-2 从顺序表中删除与给定值e相等的所有元素。
template <class DataType>
Status DelValue(SqList<DataType> &list, int e){
	DataType tmp;
	if (list.LocateElem(e) == 0){//如果是空表，返回下溢信息
		return UNDER_FLOW;
	} else {
		for(int i = list.GetLength(); i >= 1; i--){//反向遍历顺序表，避免了顺序删除后元素相对位置改变造成的数据遗漏
			list.GetElem(i,tmp);
			if (tmp == e){//如果遇到data域数值与目标数相同的元素，则进行删除
				list.DeleteElem(i,tmp);
			}
		}
		return SUCCESS;//返回成功信息
	}
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)


#text(weight:"bold")[== 第3小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，并删除其他所有重复的元素，使表中所有元素的值均不相同。为了达成这一目的，需要对每个元素进行检测，测试是否有数据域与之相同的元素。如果发现相同元素，则进行删除，但需要留下第一个这样的元素。在检测时，需要使用一个嵌套循环，首先获取每一个元素作为目标数据，再针对这个元素进行一轮比对，并删除重复元素。需要注意的是，题目要求保留第一个这样的元素，最好的解决方法是在获取目标时采用正向遍历，而遍历比对删除时采用反向遍历，这样就可以将比对的范围锁定在i+1到length之间。这样做始终把第一次出现的重复数据作为目标数据，而又避免了与目标数据本身进行比对删除的操作。

#text(weight:"bold")[=== (2) 源代码]
```c
//1-3 在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，并删除其他所有重复的元素，使表中所有元素的值均不相同。
template <class DataType>
Status DelRepElem(SqList<DataType> &list){
	if (list.GetLength() == 0) return UNDER_FLOW;//如果为空表，返回下溢信息
	else {
		for (int i = 1; i <= list.GetLength()-1; i++){//顺序遍历，每一次循环获取一个目标数据
			int tmp,opn = 0;
			list.GetElem(i,opn);
			for (int j = list.GetLength(); j >= i+1; j--){//反向遍历，每一次循环进行一次比对
				list.GetElem(j,tmp);
				if (tmp == opn) {
					list.DeleteElem(j,tmp);//如果比对数据与目标数据的数据域相同，说明发生了重复，则删除
				}
			}
		}
		return SUCCESS;//所有循环结束，返回成功信息
	}
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)


#set align(center)
#text(16pt,weight:"black")[= 实验题第2题]
#set align(left) 
#set text(11pt)

#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求把给定值e插入有序表中，使得插入后的表仍然有序。为了达成这一目的，需要将e按顺序与所有元素进行比较，插入到符合顺序的位置上。为与所有元素顺序比较，需要进行一次顺序遍历。一旦在遍历比对过程中发现比e大的元素，则在这个位置插入e，并跳出循环，返回成功信息，操作结束。

#text(weight:"bold")[=== (2) 源代码]
```c
//2.1 把给定值e插入有序表中，使得插入后的表仍然有序。
template <class DataType>
Status OrdListInsertElem(SqList<DataType> &list,int e){
    DataType big;//定义一个big量，作为比对数据
    for(int i = 1; i <= list.GetLength(); i++){//对顺序表元素进行顺序遍历
        list.GetElem(i,big);//获取比对元素的数据域
        if(big >= e){//如果比对元素的数据域大于等于给定值e，则进行插入
            list.InsertElem(i,e);//在序号为i的元素处插入给定值e
            return SUCCESS;//返回成功信息，结束循环
    	}
	}list.InsertElem(list.GetLength()+1,e);
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#v(2em)

#text(weight:"bold")[== 第2小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求删除值为e的所有数据元素。为了达成这一目的，需要找到所有数据域与目标值e相等的元素并全部进行删除。为此，对顺序表元素进行遍历，并获取每一个元素的数据域数据，如果与e值相等，则进行删除。与1-2相同，需要考虑到删除数据导致的序号与计数器错位问题，故采用反向（倒序）遍历来规避此问题。

#text(weight:"bold")[=== (2) 源代码]
```c
//2-2 删除值为e的所有数据元素。
template <class DataType>
Status OrdListDeleteElem(SqList<DataType> &list, int e){
    DataType tmp;//定义tmp变量，存放比对数据
    for (int i = list.GetLength(); i >= 1; i--){//反向遍历顺序表
        list.GetElem(i,tmp);//获取比对元素的数据域数据
        if(tmp == e) list.DeleteElem(i,tmp);//将tmp与给定值e比对，若相等则删除tmp对应元素
    }
    return SUCCESS;
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)

#text(weight:"bold")[== 第3小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求。为了达成这一目的，

#text(weight:"bold")[=== (2) 源代码]
```c
//2-3 合并两个有序表，得到一个新的有序表。
template <class DataType>
Status OrdListMerge(SqList<DataType> &list1, SqList<DataType> &list2, SqList<DataType> &list3){
    for(int i = 1; i <= list2.GetLength(); i++){//将list2中的元素按顺序一一复制到list3中
        DataType tmp;
        list2.GetElem(i,tmp);
        list3.InsertElem(i,tmp);
    }
    for(int j = 1; j <= list1.GetLength(); j++){//遍历list1，对其中每一个元素进行顺序插入，插入到list3中
        DataType big,tmp;
        list1.GetElem(j,tmp);
        for(int i = 1; i <= list3.GetLength(); i++){//遍历list3，将其中元素与list1中的tmp进行比较
            list3.GetElem(i,big);
            if(big >= tmp){//如果在遍历过程中出现更大的元素，则在此处插入tmp元素，并跳出循环
                list3.InsertElem(i,tmp);
				break;
            } else if(i == list3.GetLength()) {//如果在遍历完后仍未出现更大元素，则在list3的最后一位后插入tmp元素
				list3.InsertElem(list3.GetLength()+1,tmp);
				    }
        }
    }
    return SUCCESS;//返回成功信息
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)