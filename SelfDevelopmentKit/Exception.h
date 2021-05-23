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

	/*Initalize the log file*/
	static void InitLog(const char* sfLog);
	/*End up the Log*/
	static void CloseLog();

	/*throw a exception message*/
	static void ThrowException(ErrorCode Level,const char* Description);
};

/*����һЩ�쳣�׳���*/

/*���һ����Ϣ*/
#define OCC_INFO(sM) {Exception::ThrowException(Exception::ErrorCode::INFO_EXCEPTION,sM);}
/*���һ������*/
#define OCC_WARNING(sM) {Exception::ThrowException(Exception::ErrorCode::WARNING_EXCEPTION,sM);}
/*���һ������*/
#define OCC_ERROR(sM) {Exception::ThrowException(Exception::ErrorCode::ERROR_EXCEPTION,sM);return false;}
/*���һ���쳣*/
#define OCC_PANIC(sM) {Exception::ThrowException(Exception::ErrorCode::PANIC_EXCEPTION,sM);ExitProcess(-65535);}
//���ú�
/*����ǲ��ǿ�ָ��*/
#define NULLPT(p) {if(!p){OCC_ERROR("null pointer.")}}
/*����ǲ����ڴ����ʧ��*/
#define ALLOC(p) {if(!p){OCC_PANIC("alloc error.")}}