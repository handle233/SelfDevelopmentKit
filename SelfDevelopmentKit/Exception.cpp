/**
* project : SelfDevelopmentKit
* file    : Exception.h
* Copyright 2021 handle All rights reserved.
**/
#pragma once
#include "Exception.h"

FILE* Exception::fLog = NULL;

char* Exception::MakeDateString() {
	time_t tTime = time(nullptr);
	tm tmTime;
	memcpy(&tmTime, localtime(&tTime), sizeof(tm));
	char* szBuffer = new char[MAX_PATH];
	strftime(szBuffer, MAX_PATH, "=%x %X\n", &tmTime);
	return szBuffer;
}
void Exception::InitLog(char* sfLog) {
	fLog = fopen(sfLog, "a+");
	assert(fLog != nullptr);
	char* pDate = MakeDateString();
	AddItem("======================");
	AddItem(pDate);
	AddItem("======================");
}
void Exception::AddItem(const char* MsgStr) {
	fprintf(fLog, MsgStr);
	fflush(fLog);
}
Exception::Exception(int Level, char* Description) {
	char LevelString[256] = "";
	switch (Level) {
	case INFO_EXCEPTION:
		strcpy(LevelString, "[INFO]");
		break;
	case WARNING_EXCEPTION:
		strcpy(LevelString, "[WARNING]");
		break;
	case ERROR_EXCEPTION:
		strcpy(LevelString, "[ERROR]");
		break;
	case PANIC_EXCEPTION:
		strcpy(LevelString, "[PANIC][FAILURE]");
		break;
	}
	char* sMsg = new char[strlen(LevelString) + strlen(Description)];
	sprintf(sMsg, "%s%s\n", LevelString, Description);
	AddItem(sMsg);

	//异常处理操作
	if (Level == PANIC_EXCEPTION) {
		throw;
	}
}