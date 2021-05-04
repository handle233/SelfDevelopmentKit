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
/*The enum show all the pobably error type.*/
enum ErrorCode {
	/*Just put a info.*/
	INFO_EXCEPTION=0,
	/*Command can process,but some var check is failure.*/
	WARNING_EXCEPTION=1,
	/*Command can`t be done,but program should return and repair.*/
	ERROR_EXCEPTION=2, 
	/*Serious error,whole program should be close.*/
	PANIC_EXCEPTION=3, 
};

	static void InitLog(char* sfLog);
	static void CloseLog();

	Exception(ErrorCode Level, char* Description);
};

/*定义一些异常抛出宏*/
#define OCC_INFO(sM) {Exception(INFO_EXCEPTION,sM);}
#define OCC_WARNING(sM) {Exception(WARNING_EXCEPTION,sM);}
#define OCC_ERROR(sM) {Exception(ERROR_EXCEPTION,sM);return FALSE;}
#define OCC_PANIC(sM) {Exception(PANIC_EXCEPTION,sM);ExitProcess(-65535);}
//常用宏
#define NULLPT(p) {if(!p){OCC_ERROR("null pointer.")}}
#define ALLOC(p) {if(!p){OCC_PANIC("alloc error.")}}