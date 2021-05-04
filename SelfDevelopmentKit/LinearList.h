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
public:
	LinearList() {
		InitializeCriticalSectionAndSpinCount(&Section, 10);
	}
	~LinearList() {
		DeleteCriticalSection(&Section);
	}
	bool InsertNode(int Index, Type& Data);
	Type& GetNode(int Index);
	bool RemoveNode(int Index);
	const int& length() { return Length; }
};

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
bool LinearList<Type>::InsertNode(int Index, Type& Data) {
	Node* CurNode = ToThatNode(Index);
	NULLPT(CurNode);
	Node* NxtNode = CurNode->NextNode;
	Node* InsNode = new Node;
	ALLOC(InsNode);
	CurNode->NextNode = InsNode;
	InsNode->NextNode = NxtNode;
	return true;
}

template<typename Type>
typename Type& LinearList<Type>::GetNode(int Index) {
	Node* CurNode = ToThatNode(Index);
	NULLPT(CurNode);
	return CurNode->Data;
}

template<typename Type>
bool LinearList<Type>::RemoveNode(int Index) {
	if (!IsIndexLegal(Index)) {
		return false;
	}
	Node* LstNode = ToThatNode(Index-1);
	NULLPT(LstNode);
	Node* DelNode = LstNode->NextNode;
	if (Index != Length - 1) {
		Node* NxtNode = DelNode->NextNode;
		LstNode->NextNode = NxtNode;
	}
	else {
		LstNode->NextNode = nullptr;
	}
	delete DelNode;

	return true;
}