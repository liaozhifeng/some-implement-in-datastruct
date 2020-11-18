#pragma once
#ifndef HUFFMAN_H_
#define HUFFMAN_H_
#include"heap.h"
#include"linkedqueue.h"
#include<iostream>
template<typename T>
struct HuffmanNode
{
	T data;
	HuffmanNode *parent, *leftChild, *rightChild;
	HuffmanNode():leftChild(nullptr),rightChild(nullptr),parent(nullptr)
	{}
	HuffmanNode(T d,HuffmanNode *left=nullptr,HuffmanNode *right = nullptr,HuffmanNode *p=nullptr)
		:data(d),leftChild(left),rightChild(right),parent(p) {}
	bool operator<(HuffmanNode &other) const{ return data < other.data; }
	bool operator<=(HuffmanNode &other) const{ return data <= other.data; }
	bool operator>(HuffmanNode &other) const{ return data > other.data; }
	bool operator>=(HuffmanNode &other) const{ return data >= other.data; }

};

template<typename T>
class HuffmanTree
{
public:
	HuffmanTree(T w[], int len);
	~HuffmanTree() { deleteTree(root); }
	void levelOrderPrint()const;
private:
	HuffmanNode<T> *root;
	void mergeTree(HuffmanNode<T>&h1, HuffmanNode<T> &h2, HuffmanNode<T> *&parent);
	void deleteTree(HuffmanNode<T> *r);
};
#endif // !HUFFMAN_H_

template<typename T>
HuffmanTree<T>::HuffmanTree(T w[], int len)
{
	MinHeap<HuffmanNode<T>> hp;
	HuffmanNode<T> *parent = nullptr;
	HuffmanNode<T> cur;
	for (int i = 0; i < len; i++)
	{
		cur.data = w[i];
		cur.leftChild = nullptr;
		cur.rightChild = nullptr;
		cur.parent = nullptr;
		hp.Insert(cur);//因为插入进去会存着cur的副本，所以cur发生改变也不会对后面产生什么影响
	}
	for (int i = 0; i < len - 1; i++)
	{
		HuffmanNode<T> *first = new HuffmanNode<T>;
		HuffmanNode<T> *second = new HuffmanNode<T>;
		hp.Remove(*first);
		hp.Remove(*second);
		mergeTree(*first, *second, parent);//mergeTree传进去的是引用，在函数里面给parent申请空间
		hp.Insert(*parent);
		if(i!=len-2)
			delete parent;
	}
	root = parent;
}

template<typename T>
void HuffmanTree<T>::levelOrderPrint() const
{
	LinkedQueue<HuffmanNode<T> *>q;
	q.EnQueue(root);
	HuffmanNode<T> *cur;
	while (!q.isEmpty())
	{
		q.DeQueue(cur);
		std::cout << cur->data<<' ';
		if (cur->leftChild != nullptr)
			q.EnQueue(cur->leftChild);
		if (cur->rightChild != nullptr)
			q.EnQueue(cur->rightChild);
	}
}

template<typename T>
void HuffmanTree<T>::mergeTree(HuffmanNode<T>& h1, HuffmanNode<T>& h2, HuffmanNode<T>*& parent)
{
	parent = new HuffmanNode<T>;
	parent->leftChild = &h1;
	parent->rightChild = &h2;
	parent->data = h1.data + h2.data;
	h1.parent = parent;
	h2.parent = parent;    
}

template<typename T>
void HuffmanTree<T>::deleteTree(HuffmanNode<T>* r)
{
	if (r == nullptr)
		return;
	deleteTree(r->leftChild);
	deleteTree(r->rightChild);
	delete r;
}
