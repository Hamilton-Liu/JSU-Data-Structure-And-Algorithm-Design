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
本题要求从顺序表中删除与给定值e相等的所有元素。为了达成这一目的，需要通过数据比对，寻找数据域与给定值e数值相同的元素的位置，并对其进行删除处理。在寻找数据域与给定值e数值相同的元素时，需要对顺序表进行遍历，一旦出现目标元素，就利用循环次数i与其序号相同的特点，立刻对其进行删除，并获取删除数据信息。整个过程需要一次完整的遍历，以删除所有数据域与给定值e相等的元素。需要注意的是，如果选择顺序（正向）遍历，在删除元素后会导致整体序号的前移，而记录循环次数的i不会前移，因此需要对此进行处理，方法有二：1. 在每次删除后对计数器i进行一次自减操作(```cpp i--```)，以保证i和数据序号的一致性（未测试）；2. 对目标顺序表进行反向遍历，这样删除数据就不会影响未经遍历的数据次序，数据的序号和计数器i就不会发生错位（测试并采纳）。相较于方法1，方法2的语法更简单，执行的操作更少，操作更安全。

#text(weight:"bold")[=== (2)源代码]
```cpp
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
```cpp
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
本题要求把给定值e插入有序表中，使得插入后的表仍然有序。为了达成这一目的，需要将e按顺序与所有元素进行比较，插入到符合顺序的位置上。为与所有元素顺序比较，需要进行一次顺序遍历。一旦在遍历比对过程中发现比e大的元素，则在这个位置插入e，并跳出循环，返回成功信息，操作结束。如果没有发现比e大的元素，则在表尾执行插入。
#text(weight:"bold")[=== (2) 源代码]
```cpp
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
	  }list.InsertElem(list.GetLength()+1,e);return SUCCESS;//循环结束未返回成功，在表尾插入
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#v(1em)

#text(weight:"bold")[== 第2小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求删除值为e的所有数据元素。为了达成这一目的，需要找到所有数据域与目标值e相等的元素并全部进行删除。为此，对顺序表元素进行遍历，并获取每一个元素的数据域数据，如果与e值相等，则进行删除。与1-2相同，需要考虑到删除数据导致的序号与计数器错位问题，故采用反向（倒序）遍历来规避此问题。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//2-2 删除值为e的所有数据元素。
template <class DataType>
Status OrdListDeleteElem(SqList<DataType> &list, int e){
    DataType tmp;//定义tmp变量，存放比对数据
    for (int i = list.GetLength(); i >= 1; i--){//反向遍历顺序表
        list.GetElem(i,tmp);//获取比对元素的数据域数据
        if(tmp == e) list.DeleteElem(i,tmp);//将tmp与给定值e比对，若相等则删除tmp对应元素
    }
    return SUCCESS;//返回成功信息
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)

#text(weight:"bold")[== 第3小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求合并两个有序表，得到一个新的有序表。为了达成这一目的，有两种处理方案：1. 先将一个表中的元素全部复制到新表中，再将另一个表中的每个元素有序地插入到新表中；2. 同时将两个表的数据插入到新表中，过程中通过比较数据大小来决定是否切换另一张表来插入。方法2相较于方法1，比较和插入同步进行，节约了一定的时间，总体只需要进行length1 + length2步操作，而方法1显然每次插入另一张表元素时，都要再次进行遍历，寻找应该插入的位置，整体比方法2多了一个循环。但由于没有产生新的嵌套，时间复杂度相等，故此处采用更加符合直觉的方法1。每一次插入的具体操作同2-1类似，只需添加循环即可。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//2-3 合并两个有序表，得到一个新的有序表。
template <class DataType>
Status OrdListMerge(SqList<DataType> &list1, SqList<DataType> &list2, SqList<DataType> &list3){
    for(int i = 1; i <= list2.GetLength(); i++){//将list2中的元素按顺序一一复制到list3中
        DataType tmp;
        list2.GetElem(i,tmp);
        list3.InsertElem(i,tmp);
    }
    for(int j = 1; j <= list1.GetLength(); j++){//遍历list1，获取其中每一个元素，对其进行顺序插入
        DataType big,tmp;
        list1.GetElem(j,tmp);//将获取元素存入tmp中
        for(int i = 1; i <= list3.GetLength(); i++){//遍历检索list3中元素，与tmp进行比较
            list3.GetElem(i,big);
            if(big >= tmp){//如果在遍历过程中检索出更大的元素，则在此处插入tmp元素
                list3.InsertElem(i,tmp);
				        break;//插入完成，跳出检索循环
            } else if(i == list3.GetLength()) {//如果在遍历完后仍未出现更大元素，则在list3的最后一位后插入tmp元素
				list3.InsertElem(list3.GetLength()+1,tmp);
				    }
        }
    }
    return SUCCESS;//循环结束，返回成功信息
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

*注:* 其中，在list1检索插入list3时，循环语句```cpp for(int i = 1; i <= list3.GetLength(); i++){}```可以优化。其起始值i可以用一个变量记录下来，或者将i定义为成员变量，下一次进入循环时可以利用这个标记，直接从上一次结束循环时的位次开始往后检索，以省去一部分冗余的比较操作。

#pagebreak(weak: true)

#text(weight:"bold")[== 第4小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求从有序顺序表中删除其值在给定值s与t之间（s＜t）的所有元素，即删除取值在[s,t]之间的所有元素；如果s≥t或顺序表为空，则显示出错信息，并退出运行。为了达成这一目的，需要对顺序表进行遍历，判断每一个元素是否符合题设规则，如果符合，进行删除操作。同上，使用反向遍历可以有效规避顺序删除引起的次序错位。需要注意的是，不要将返回成功信息的操作语句放在循环内，以免提前结束循环，漏删剩余符合条件的元素。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//2-4 从有序顺序表中删除其值在给定值s与t之间（s＜t）的所有元素，即删除取值在[s,t]之间的所有元素；如果s≥t或顺序表为空，则显示出错信息，并退出运行。
template <class DataType>
Status OrdListIntervalDelete(SqList<DataType> &list,int s,int t){
    DataType tmp;
    if(s >= t || list.GetLength() == 0) return FAILED;//如果为空表或s<t，返回错误信息
    else{
        for (int i = list.GetLength(); i >= 1; i--){//涉及多个删除操作，使用反向遍历
            list.GetElem(i,tmp);//获取第i位数据，存放到tmp中
            if(tmp >=s && tmp <= t){//判断tmp是否在闭区间[s,t]中
                list.DeleteElem(i,tmp);//删除第i位元素，并将数据存放到tmp中
            }
        }
        return SUCCESS;//循环结束，返回成功信息
    }
}
```
#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)


#set align(center)
#text(16pt,weight:"black")[= 实验题第3题]
#set align(left) 
#set text(11pt)

#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求在LinkList类中增加一个定位函数：在单链表中寻找第i个元素节点。若找到，则返回第i个元素节点的地址，否则返回空指针。为了达成这一目的，需要对链表中的元素进行遍历，直到次序为i，获取此节点并返回。因此需要创建一个计数器变量count，从1开始随循环次数自增，同时伴随着指针后移，直到count与i相等，结束循环，此时p正好存放目标节点的地址，返回p即可。如果遍历完全部元素，count都没有与i相等而结束循环，则p已经后移到了尾指针位置上，存放的地址为NULL，此时返回NULL即可。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//3-1 定位函数：在单链表中寻找第i个元素节点。若找到，则返回第i个元素节点的地址，否则返回空指针。
template <class DataType>
Node<DataType>* LinkList<DataType>::LocateAddress(const int i) {
	Node<DataType> *p = head->next;//p指向第一个元素节点
	int count = 1;//初始化计数器为1
	while(p != NULL && count != i) {//从第一个元素节点开始依次进行比较元素的值，直到到第i个元素或遍历结束(P=NULL)为止
		p = p->next;//移动指针p使之指向后继节点
		count++;//计数器进行自增
	}
	return p ? p : NULL;//使用三元运算符判断，如果找到第i个元素的地址(p不为NULL)，返回p,否则返回NULL
} 
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)

#text(weight:"bold")[== 第2小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求增加一个统计函数：统计单链表中等于给定值e的元素个数。为了达成这一目的，需要对链表所有元素进行比较，如果与目标值相等，曾记录一次，最终返回总记录次数。使用一个for循环遍历整个链表，利用LinkList的类函数GetElem逐个获取数据并记录即可。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//3-2 统计函数：统计单链表中等于给定值e的元素个数。
template <class DataType>
int Frequency(LinkList<DataType> &list, DataType &e){
	int count = 0;//初始化计数器为0
	DataType tmp;
	for(int i = 1; i <= list.GetLength(); i++){//遍历整个链表
		list.GetElem(i,tmp);//将第i个元素存放到tmp中
		if(tmp == e) count++;//将给定值e与tmp进行比对，如果相等，计数加1
	}
	return count;//循环结束，返回计数器count的值
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)

#set align(center)
#text(16pt,weight:"black")[= 实验题第4题]
#set align(left) 
#set text(11pt)

#text(weight:"bold")[== 第1小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求插入函数：把元素值e作为数据元素插入表中，使得插入后的表仍然有序。为达成这一目的，需要找到符合要求的位次，并将给定值e插入其中。利用for循环遍历，获取节点数据与e比较，如果大于等于e则在此处执行插入。循环结束无返回值，则在链表尾部插入。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//4-1 插入函数：把元素值e作为数据元素插入表中，使得插入后的表仍然有序。
template <class DataType>
Status OrdListInsertElem(LinkList<DataType> &list,DataType e){
    DataType tmp;
    for(int i = 1; i <= list.GetLength(); i++){//循环遍历数组
        list.GetElem(i,tmp);//获取第i个元素数据存放到tmp中
        if(e <= tmp){//判断给定值e是否小于等于tmp
            list.InsertElem(i,e);//在第i个节点处插入给定值e
            return SUCCESS;//退出循环，返回成功信息
        }
    }list.InsertElem(list.GetLength()+1,e);//循环结束，在链表尾插入给定值e
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#v(2em)

#text(weight:"bold")[== 第2小题]

#text(weight:"bold")[=== (1) 设计思路]
本题要求删除数据元素等于e的节点。为了达成这一目的，需要判断每个元素是否与e相同，相同的执行删除操作。为此，使用一个for循环进行反向遍历，获取第i个节点数据至tmp，与e比较，相等则进行删除。循环结束，执行完全部删除操作，返回成功信息。

#text(weight:"bold")[=== (2) 源代码]
```cpp
//4-2 删除数据元素等于e的节点。
template <class DataType>
Status OrdListDeleteElem(LinkList<DataType> &list, DataType e){
    DataType tmp;
    for(int i = list.GetLength(); i >= 1; i--){//涉及多个删除，反向遍历
        list.GetElem(i,tmp);//获取第i个节点的数据，存放在tmp中
        if(tmp == e){//判断tmp是否与e相等
            list.DeleteElem(i,tmp);//删除第i个节点数据并存放在tmp中
        }
    }
    return SUCCESS;//循环结束，返回成功信息
}
```

#text(weight:"bold")[=== (3)说明]
上述代码可以应用测试程序进行测试并得到正确结果。

#pagebreak(weak: true)