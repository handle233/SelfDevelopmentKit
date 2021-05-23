/**
* project : SelfDevelopmentKit
* file    : LinearList.h
* Copyright 2021 handle All rights reserved.
**/
#pragma once
#include "CommonHead.h"
#include "Exception.h"

/*
* Linear List
* which is a GP can easily manage the linear data.
* It has its memory surviving,
* all data send in would have a copy.
*/
template<typename Type>
class _declspec(dllexport)  LinearList {
private:
	/*Node is a single part of all the list.
	* It`s for saving and linking.
	*/
	struct Node {
		Type* Data;//The p of Data
		Node* NextNode;//The p to NextNode
	};
	/*Length is the length*/
	int Length;
	/*The thread protection.*/
	CRITICAL_SECTION Section;
	/*The Root Node*/
	Node* Root;
	/*To Check if index is legal */
	bool IsIndexLegal(int Index) {
		if (Index < 0) {
			OCC_ERROR("Index too small.");
		}
		if (Index >= Length) {
			OCC_ERROR("Index overflow.");
		}
		return true;
	}
	inline void InSection() {
		EnterCriticalSection(&Section);
	}
	inline void OutSection() {
		LeaveCriticalSection(&Section);
	}
	Node* ToThatNode(int Index);
	Node* AllocNewNode(const Type &Data);
public:
	LinearList() {
		InitializeCriticalSectionAndSpinCount(&Section, 10);
		Root = nullptr;
		Length = 0;
	}
	~LinearList() {
		DeleteCriticalSection(&Section);
	}
	bool InsertNode(int Index,const Type& Data);
	bool GetNode(int Index,Type &Recv);
	bool SetData(int Index,const Type& Data);
	bool RemoveNode(int Index);
	const int length() { return Length; }
};

template<typename Type>
typename LinearList<Type>::Node* LinearList<Type>::AllocNewNode(const Type &Data) {
	Node* pNode = new Node;

	ALLOC(pNode);
	pNode->NextNode = nullptr;

	pNode->Data = new Type;
	ALLOC(pNode->Data);
	memcpy(pNode->Data, &Data, sizeof(Type));

	return pNode;
}
template<typename Type>
typename LinearList<Type>::Node* LinearList<Type>::ToThatNode(int Index) {
	if (!IsIndexLegal(Index)) {
		return nullptr;
	}
	Node* CurNode = Root;
	for (int a = 0; a < Index; a++) {
		CurNode = CurNode->NextNode;
	}
	return CurNode;
}

template<typename Type>
bool LinearList<Type>::InsertNode(int Index,const Type& Data) {
	InSection();
	Node* CurNode = ToThatNode(Index);
	if (CurNode == nullptr && Length == 0 && Index == 0) {
		//针对从零开始的链表的插入
		Root = AllocNewNode(Data);
		Length++;
		OutSection();
		return true;
	} else {
		//常规内存检查
		NULLPT(CurNode);
	}
	//常规加入
	Node* NxtNode = CurNode->NextNode;
	Node* InsNode = AllocNewNode(Data);

	CurNode->NextNode = InsNode;
	InsNode->NextNode = NxtNode;
	Length++;
	OutSection();
	return true;
}

template<typename Type>
bool LinearList<Type>::GetNode(int Index,Type &Recv) {
	Node* CurNode = ToThatNode(Index);
	NULLPT(CurNode);
	Recv = *CurNode->Data;
	return true;
}

template<typename Type>
bool LinearList<Type>::SetData(int Index,const Type& Data) {
	Node* CurNode = ToThatNode(Index);
	NULLPT(CurNode);

	memcpy(CurNode->Data, &Data, sizeof(Type));

	return true;
}

template<typename Type>
bool LinearList<Type>::RemoveNode(int Index) {
	if (!IsIndexLegal(Index)) {
		return false;
	}
	if (Index == 0) {
		Node* NxtNode = Root->NextNode;
		delete Root->Data;
		delete Root;
		Root = NxtNode;
	}
	else {
		Node* LstNode = ToThatNode(Index - 1);
		Node* DelNode = LstNode->NextNode;
		Node* NxtNode = DelNode->NextNode;

		delete DelNode->Data;
		delete DelNode;
		LstNode->NextNode = NxtNode;
	}

	Length--;
	return true;
}