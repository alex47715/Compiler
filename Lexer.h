#pragma once
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "Log.h"

namespace LA {
	char SerchTokens(const char* string);
	short LexAnalizer(LT::LexTable& lextable, IT::IdTable& idtable, In::IN& in, Parm::PARM& parm, Log::LOG& log);
	void WriteInfoAboutFunctions(LT::LexTable& lextable, IT::IdTable& idtable);
	void ShowIdTable(IT::IdTable& idtable, std::ofstream* outfile);
	void ShowLexTable(LT::LexTable& lextable, std::ofstream* outfile);
	
}