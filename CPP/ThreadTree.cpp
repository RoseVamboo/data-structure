#include<iostream>
using namespace std;
enum PointerTag{ THREAD, LINK };

typedef int DataType;
/*
缺少后序遍历，因为线索二叉树的后序遍历需要借助父节点来操作，
所以线索二叉树的后序遍历在ThreadTree1.cpp中单独处理
*/
struct Node{
	DataType data;
	Node* left;
	Node* right;
	PointerTag leftTag;//左孩子线索标记
	PointerTag rightTag;//右孩子线索标记
	Node(DataType x){
		data = x;
		left = NULL;
		right = NULL;
		leftTag = LINK;
		rightTag = LINK;
	}
};
class ThreadTree{
public:
	ThreadTree();
	ThreadTree(DataType val);
	bool insert(int key);
	void InOrder();
	//先序遍历-递归
	void PreOrder();
	void InOrderThreading();
	void InOrderThd();
	void PreOrderThreading();
	void PreOrderThd();

	//打印二叉树
	void printTree();
protected:
	//插入节点
	bool insert(int key, Node* root);
	Node* Create(DataType val);
	void InOrder(Node* root);
	void PreOrder(Node* root);
	void InOrderThread(Node* root, Node*& pre);
	void InOrderThd(Node* root);
	void PreOrderThread(Node* root, Node*& pre);
	void PreOrderThd(Node* root);
	void printTree(Node* root);
private:
	Node* _root;
};
ThreadTree::ThreadTree(){
	_root = NULL;
}
ThreadTree::ThreadTree(DataType val){
	_root = Create(val);
}
//插入节点
bool ThreadTree::insert(int key){
	if (_root != NULL){
		return insert(key, _root);
	}
	try{
		_root = new Node(key);
		return true;
	}
	catch (...){
		return false;
	}
}

bool ThreadTree::insert(int key, Node* leaf){
	if (key < leaf->data){
		if (leaf->left != NULL){
			return insert(key, leaf->left);
		}
		else{
			leaf->left = new Node(key);
			return true;
		}
	}
	else if (key > leaf->data){
		if (leaf->right != NULL){
			return insert(key, leaf->right);
		}
		else{
			leaf->right = new Node(key);
			return true;
		}
	}
	return false;
}


//先序遍历-递归
void ThreadTree::PreOrder(){
	PreOrder(_root);
}
void ThreadTree::PreOrder(Node* leaf){
	if (leaf != NULL){
		cout << leaf->data << " ";
		PreOrder(leaf->left);
		PreOrder(leaf->right);
	}
}
//创建root
Node* ThreadTree::Create(DataType val){
	Node* root = new Node(val);
	return root;
}
void ThreadTree::InOrder()	{
	InOrder(_root);
	cout << endl;
}
//中序遍历
void ThreadTree::InOrder(Node* root){
	if (root != NULL){
		InOrder(root->left);
		cout << root->data << " ";
		InOrder(root->right);
	}
}

//前序遍历线索化
void ThreadTree::PreOrderThreading(){
	Node* prev = NULL;
	PreOrderThread(_root, prev);
}

void ThreadTree::PreOrderThread(Node* root, Node*& pre){
	if (root == NULL){
		return;
	}
	if (root->left == NULL){
		root->leftTag = THREAD;
		root->left = pre;
	}
	if (pre != NULL&&pre->right == NULL){
		pre->right = root;
		pre->rightTag = THREAD;
	}
	pre = root;
	//防止重复线索化
	if (root->leftTag == LINK){
		PreOrderThread(root->left, pre);
	}
	if (root->rightTag == LINK){
		PreOrderThread(root->right, pre);
	}
}
//前续遍历输出
void ThreadTree::PreOrderThd(){
	PreOrderThd(_root);
}

void ThreadTree::PreOrderThd(Node* root){
	Node* cur = root;
	while (cur != NULL){
		while (cur != NULL&&cur->leftTag == LINK){
			cout << cur->data << " ";
			cur = cur->left;
		}
		cout << cur->data << " ";
		//访问连续的后继结点
		while (cur->rightTag == THREAD){
			cur = cur->right;
			cout << cur->data << " ";
		}
		cur = cur->right;
	}
	cout << endl;
}
//中序遍历线索化
void ThreadTree::InOrderThreading(){
	Node* prev = NULL;
	InOrderThread(_root, prev);
}
void ThreadTree::InOrderThread(Node* root, Node*& pre){
	if (root == NULL){
		return;
	}
	InOrderThread(root->left, pre);
	//线索化
	if (root->left == NULL){
		root->leftTag = THREAD;
		root->left = pre;
	}
	//右孩子在访问完下一个后在线索化
	if (pre != NULL&&pre->right == NULL){
		pre->right = root;
		pre->rightTag = THREAD;
	}
	pre = root;
	InOrderThread(root->right, pre);
}
//打印中序遍历
void ThreadTree::InOrderThd(){
	InOrderThd(_root);
}
void ThreadTree::InOrderThd(Node* root){
	Node* cur = root;
	while (cur != NULL){
		while (cur != NULL&&cur->leftTag == LINK){
			cur = cur->left;
		}
		cout << cur->data << " ";
		while (cur->rightTag == THREAD){
			cur = cur->right;
			cout << cur->data << " ";
		}
		cur = cur->right;
	}
	cout << endl;
}

//打印树
//打印二叉树
void ThreadTree::printTree(){
	printTree(_root);
	cout << endl;
}

void ThreadTree::printTree(Node* root){
	if (root != NULL){
		printTree(root->left);
		cout << root->data << " ";
		printTree(root->right);
	}
}

int main(){
	int i;
	ThreadTree* binTree = new ThreadTree();
	cout << binTree->insert(5) << endl;
	cout << binTree->insert(3) << endl;
	cout << binTree->insert(7) << endl;
	cout << binTree->insert(5) << endl;
	cout << binTree->insert(2) << endl;
	cout << binTree->insert(8) << endl;
	cout << binTree->insert(9) << endl;
	binTree->printTree();
	cout << endl;
	
	binTree->PreOrder();
	cout << endl;
	binTree->PreOrderThreading();
	binTree->PreOrderThd();
	cout << endl;
	
	/**/
	/*
	binTree->InOrder();
	cout << endl;
	binTree->InOrderThreading();
	binTree->InOrderThd();
	cout << endl;
	*/

	cin >> i;
	return 0;
}