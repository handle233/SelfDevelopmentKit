/**
* project : SelfDevelopmentKit
* file    : LinearList.h
* Copyright 2021 handle All rights reserved.
**/
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
	/*The Root Node*/
	Node* Root;
	/*To Check if index is legal */
	bool IsIndexLegal(int Index) {
		if (Index < 0) {
			Exception(PANIC_EXCEPTION, "Index too small.");
		}
	}
public://Will be removed
	Node* ToThatNode(int Index);
public:
	bool InsertNode(int Index, Type& Data);
	Type& GetNode(int Index);
	bool RemoveNode();
	int& length() { return Length; }
};

template<typename Type>
typename LinearList<Type>::Node* LinearList<Type>::ToThatNode(int Index) {
	Node* CurNode = Root;
	for (int a = 0; a < Index; a++) {
		CurNode = CurNode->NextNode;
	}
	return CurNode;
}