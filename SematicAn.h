#pragma once
#include "pch.h"
#include "IT.h"

namespace SemAnaliz
{
	
	

	short IsReturnInMain(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile);
	short IsParamInFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile);
	short IsParamInLibFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile);
	
	short Types(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile);
	short IsReturnInUserFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile);
	
	bool IsLibFunction(unsigned char lex);
}