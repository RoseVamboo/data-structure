#include<iostream>
using namespace std;

//定义广义表的节点类型
enum NodeType{
	HEAD,//头结点类型
	VALUE,//值结点类型
	SUB,//子表类型
};
//定义广义表结点的结构体
struct GeneraNode{
	NodeType type;//结点类型
	GeneraNode* next;//存放结点的下一个元素的地址
	//一个结点要么是值结点，要么是子表
	//因此采用联合体来存放
	//若是值结点则存放值，若是表结点则存放子表的头结点地址
	union{
		char value;
		GeneraNode* subLink;
	};

	GeneraNode(NodeType nodeType = HEAD, char nodeValue = '\0') 
		:type(nodeType), next(NULL){
		if (nodeType == VALUE){
			value = nodeValue;
		}
		else if (nodeType == SUB){
			subLink = NULL;
		}
	}
};
class GeneraList{
public:
	GeneraList(const char*str) :head(NULL){
		_CreateGeneraList(head,str);
	}
	~GeneraList(){}
	void Print();//打印广义表
	int Size();//广义表中值结点的数目
	int Depth();//广义表的深度

private:
	void _CreateGeneraList(GeneraNode*& link, const char*& str);
	int _Size(GeneraNode* link);
	int _Depth(GeneraNode* link);
	void _Print(GeneraNode* link);
	bool _IsValue(const char ch);//判断指定字符是否为值结点所允许的类型

	GeneraNode* head;//用来存放广义表头结点地址
};

//创建广义表
void GeneraList::_CreateGeneraList(GeneraNode*& link, const char*& str){
	link = new GeneraNode(HEAD, NULL);
	link->next = NULL;
	GeneraNode* cur = link;
	str++;//将广义表序列后移，相当于跳过(
	while (*str != '\0'){
		if (_IsValue(*str)){
			//如果扫描到的字符为值时，则创建一个值结点
			GeneraNode* node = new GeneraNode(VALUE, *str);
			node->next = NULL;
			cur->next = node;//将新建的结点纳入到链表中
			cur = cur->next;
			str++;
		}
		else if (*str == '('){
			//如果扫描到的字符为(，则创建子结点
			GeneraNode* subLink = new GeneraNode(SUB, NULL);
			subLink->next = NULL;
			cur->next = subLink;//将子表纳入到链表中
			cur = cur->next;
			_CreateGeneraList(cur->subLink, str);//递归创建子表
		}
		else if (*str == ')'){
			//若扫描到)表示广义表创建结束
			str++;
			return;
		}
		else{
			str++;//其他无效字符跳过
		}
	}
}

int GeneraList::Size(){
	return _Size(head);
}
//计算广义表中值的结点数
int GeneraList::_Size(GeneraNode* link){
	int size = 0;
	GeneraNode* cur = link;
	while (cur != NULL){
		if (cur->type == VALUE){
			size++;
		}
		else if (cur->type == SUB){
			size += _Size(cur->subLink);
		}
		cur = cur->next;
	}
	return size;
}

int GeneraList::Depth(){
	return _Depth(head);
}
//计算广义表的深度
int GeneraList::_Depth(GeneraNode* link){
	int depth = 1;//当前表的深度
	int maxDepth = 1;//表示目前最大的深度
	GeneraNode* cur = link;
	while (cur != NULL){
		if (cur->type == SUB){
			depth += _Depth(cur->subLink);
		}
		if (depth > maxDepth){
			maxDepth = depth;
			depth = 1;
		}
		cur = cur->next;
	}
	return maxDepth;
}

void GeneraList::Print(){
	_Print(head);
	cout << endl;
}
//打印广义表
void GeneraList::_Print(GeneraNode* link){
	GeneraNode* cur = link;
	while (cur != NULL){
		if (cur->type == VALUE){
			cout << cur->value;
			if (cur->next != NULL){
				cout << ",";
			}
		}
		else if (cur->type == SUB){
			_Print(cur->subLink);//遇到子表递归打印
			if (cur->next != NULL){
				cout << ",";
			}
		}
		else if (cur->type == HEAD){
			cout << "(";
		}
		cur = cur->next;
	}
	cout << ")";
}

bool GeneraList::_IsValue(const char ch){
	if (ch >= 'a'&&ch <= 'z' ||
		ch >= 'A'&&ch <= 'Z' ||
		ch >= '0'&&ch <= '('){
		return true;
	}
	else{
		return false;
	}
}
//========测试=========//

int main(){
	//空表测试
	GeneraList generaList1("()");
	generaList1.Print();
	cout << "GeneraList1 size=" << generaList1.Size() << endl;
	cout << "GeneraList1 Depth=" << generaList1.Depth() << endl;

	//测试单层表
	GeneraList generaList2("(a,b,c)");
	generaList2.Print();
	cout << "GeneraList2 size=" << generaList2.Size() << endl;
	cout << "GeneraList2 Depth=" << generaList2.Depth() << endl;

	//测试双层表
	GeneraList generaList3("(a,b,(c,d,e))");
	generaList3.Print();
	cout << "GeneraList3 size=" << generaList3.Size() << endl;
	cout << "GeneraList3 Depth=" << generaList3.Depth() << endl;

	//测试多层表
	GeneraList generaList4("(a,b,(c,(d,(e))),((f),h))");
	generaList4.Print();
	cout << "GeneraList4 size=" << generaList4.Size() << endl;
	cout << "GeneraList4 Depth=" << generaList4.Depth() << endl;
	

	//测试多层空表表
	GeneraList generaList5("(((()),()),())");
	generaList5.Print();
	cout << "GeneraList5 size=" << generaList5.Size() << endl;
	cout << "GeneraList5 Depth=" << generaList5.Depth() << endl;
	return 0;
}