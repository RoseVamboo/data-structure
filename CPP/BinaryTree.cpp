#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;

struct Node{
	int value;
	Node* leftNode;
	Node* rightNode;
};
class BinTree{
public:
	BinTree();
	~BinTree();

	bool insert(int key);//插入节点
	Node* find(int key);//查找节点值
	void printNode(Node* leaf);//打印指定节点值
	void printTree();//打印整棵树
	void destroyTree();//销毁树结构
	int size();//获取整棵二叉树含有元素的个数
	int height();//获取二叉树节点的深度
	int leafCount();//统计二叉树的叶子节点数
	void preOrder();//先序遍历-递归
	void inOrder();//中序遍历-递归
	void postOrder();//后序遍历-递归
	void preOrder1();//先序遍历-非递归
	void inOrder1();//中序遍历-非递归
	void postOrder1();//后序遍历-非递归

private:
	bool insert(int key, Node* leaf);
	Node* find(int key, Node* leaf);
	void destroyTree(Node* leaf);
	void printTree(Node* leaf);
	int size(Node* leaf);
	int height(Node* leaf);
	int leafCount(Node* leaf);
	void preOrder(Node* leaf);//递归
	void inOrder(Node* leaf);//递归
	void postOrder(Node* leaf);//递归

	void preOrder1(Node* leaf);//非递归
	void inOrder1(Node* leaf);//非递归
	void postOrder1(Node* leaf);//非递归
	Node* root;
};

BinTree::BinTree(){
	root = NULL;
}
BinTree::~BinTree(){

}
//插入节点
bool BinTree::insert(int key, Node* leaf){
	if (key < leaf->value){
		if (leaf->leftNode != NULL){
			return insert(key, leaf->leftNode);
		}
		else{
			leaf->leftNode = new Node();
			leaf->leftNode->value = key;
			leaf->leftNode->leftNode = NULL;
			leaf->leftNode->rightNode = NULL;
			return true;
		}
	}
	else if (key > leaf->value){
		if (leaf->rightNode != NULL){
			return insert(key, leaf->rightNode);
		}
		else{
			leaf->rightNode = new Node;
			leaf->rightNode->value = key;
			leaf->rightNode->leftNode = NULL;
			leaf->rightNode->rightNode = NULL;
			return true;
		}
	}
	return false;
}
bool BinTree::insert(int key){
	if (root != NULL){
		return insert(key, root);
	}
	try{
		root = new Node;
		root->value = key;
		root->leftNode = NULL;
		root->rightNode = NULL;
		return true;
	}
	catch (...){
		return false;
	}
}
//根据值来查找节点
Node* BinTree::find(int key){
	return find(key, root);
}

Node* BinTree::find(int key, Node* leaf){
	if (leaf != NULL){

		if (key == leaf->value){
			return leaf;
		}
		else if (key < leaf->value){
			find(key, leaf->leftNode);
		}
		else{
			find(key, leaf->rightNode);
		}
	}
	else{
		return NULL;
	}
}
//打印指定节点
void BinTree::printNode(Node* leaf){
	if (leaf != NULL){
		cout << "value=" << leaf->value << endl;
	}
	else{
		cout << "NULL" << endl;
	}
}
//销毁二叉树
void BinTree::destroyTree(){
	destroyTree(root);
}
void BinTree::destroyTree(Node* leaf){
	if (leaf != NULL){
		destroyTree(leaf->leftNode);
		destroyTree(leaf->rightNode);
		delete leaf;
	}
}
//打印二叉树
void BinTree::printTree(){
	printTree(root);
	cout << endl;
}
void BinTree::printTree(Node* leaf){
	if (leaf != NULL){
		printTree(leaf->leftNode);
		cout << leaf->value << " ";
		printTree(leaf->rightNode);
	}
}
//获取整棵二叉树含有元素的个数
int BinTree::size(){
	return size(root);
}
int BinTree::size(Node* leaf){
	if (leaf == NULL){
		return 0;
	}
	else{
		return (1 + size(leaf->leftNode) + size(leaf->rightNode));
	}
}
//获取二叉树节点的深度
int BinTree::height(){
	return height(root);
}
int BinTree::height(Node* leaf){
	if (leaf != NULL){
		int dep1 = height(leaf->leftNode);
		int dep2 = height(leaf->rightNode);
		if (dep1 < dep2){
			return 1 + dep2;
		}
		else{
			return 1 + dep1;
		}
	}
	else{
		return 0;
	}
}
//统计二叉树的叶子节点数
int BinTree::leafCount(){
	return leafCount(root);
}
int BinTree::leafCount(Node* leaf){
	static int count = 0;
	if (leaf != NULL){
		if (leaf->leftNode == NULL&&leaf->rightNode == NULL){
			count++;
		}
		leafCount(leaf->leftNode);
		leafCount(leaf->rightNode);
	}
	return count;
}
//先序遍历-递归
void BinTree::preOrder(){
	preOrder(root);
}
void BinTree::preOrder(Node* leaf){
	if (leaf != NULL){
		cout << leaf->value << " ";
		preOrder(leaf->leftNode);
		preOrder(leaf->rightNode);
	}
}
//中序遍历-递归
void BinTree::inOrder(){
	inOrder(root);
}
void BinTree::inOrder(Node* leaf){
	if (leaf != NULL){
		inOrder(leaf->leftNode);
		cout << leaf->value << " ";
		inOrder(leaf->rightNode);
	}
}
//后序遍历-递归
void BinTree::postOrder(){
	postOrder(root);
}
void BinTree::postOrder(Node* leaf){
	if (leaf != NULL){
		postOrder(leaf->leftNode);
		postOrder(leaf->rightNode);
		cout << leaf->value << " ";
	}
}
//先序遍历-非递归
void BinTree::preOrder1(){
	preOrder1(root);
}
void BinTree::preOrder1(Node* leaf){
	if (leaf == NULL){
		return;
	}
	else{
		Node *p = leaf;
		stack<Node*> nodeStack;
		while (p != NULL || !nodeStack.empty()){
			while (p != NULL){
				nodeStack.push(p);
				cout << p->value << " ";
				p = p->leftNode;
			}
			if (!nodeStack.empty()){
				p = nodeStack.top();
				nodeStack.pop();
				p = p->rightNode;
			}
		}
	}
}
//中序遍历-非递归
void BinTree::inOrder1(){
	inOrder1(root);
}
void BinTree::inOrder1(Node* leaf){
	if (leaf != NULL){
		return;
	}
	else{
		Node* p = leaf;
		stack<Node*> nodeStack;
		while (p != NULL || !nodeStack.empty()){
			while (p!=NULL){
				nodeStack.push(p);
				p = p->leftNode;
			}
			if (!nodeStack.empty()){
				p = nodeStack.top();
				cout << p->value << " ";
				nodeStack.pop();
				p = p->rightNode;
			}
		}
	}
}
//后序遍历-非递归
void BinTree::postOrder1(){
	postOrder1(root);
}
typedef struct BNode{
	Node* btnode;
	bool isfirst;
};
void BinTree::postOrder1(Node* leaf){
	if (leaf == NULL){
		return;
	}
	else{
		stack<BNode*> bnodeStack;
		Node* p = leaf;
		BNode* temp;
		while (p != NULL || !bnodeStack.empty()){
			while (p != NULL){
				BNode* btn=new BNode;
				btn->btnode = p;
				btn->isfirst = true;
				bnodeStack.push(btn);
				p = p->leftNode;
			}
			if (!bnodeStack.empty()){
				temp = bnodeStack.top();
				bnodeStack.pop();
				if (temp->isfirst == true){
					temp->isfirst = false;
					bnodeStack.push(temp);
					p = temp->btnode->rightNode;
				}
				else{
					cout << temp->btnode->value << " ";
					p = NULL;
				}
			}
		}
	}
}

int main(){
	int i;
	BinTree* binTree = new BinTree();
	cout << binTree->insert(6) << endl;
	cout << binTree->insert(4) << endl;
	cout << binTree->insert(7) << endl;
	cout << binTree->insert(5) << endl;
	cout << binTree->insert(2) << endl;
	cout << binTree->insert(8) << endl;
	cout << binTree->insert(9) << endl;
	Node* pp = binTree->find(7);
	binTree->printNode(binTree->find(7));
	binTree->printTree();
	cout << binTree->size() << endl;
	cout << binTree->height() << endl;
	cout << binTree->leafCount() << endl;
	binTree->preOrder1();
	cout << endl;
	binTree->preOrder();
	cout << endl;
	binTree ->postOrder();
	cout << endl;
	binTree -> postOrder1();
	cout << endl;
	binTree->destroyTree();

	cin >> i;
	return 0;
}