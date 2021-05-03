/**
* project : SelfDevelopmentKit
* file    : Exception.h
* Copyright 2021 handle All rights reserved.
**/
#pragma once
#include "CommonHead.h"

class _declspec(dllexport) Exception {
private:
	static FILE* fLog;

	static char* MakeDateString();
	static void AddItem(const char* MsgStr);
public:
#define INFO_EXCEPTION 0
#define WARNING_EXCEPTION 1
#define ERROR_EXCEPTION 2
#define PANIC_EXCEPTION 3

	static void InitLog(char* sfLog);

	Exception(int Level, char* Description);
};