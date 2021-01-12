#pragma once
#include "IT.h"
#include "LT.h"
#include <stack>
#include <iostream>
#include "Error.h"

#define POLISH_FUNC '@'

#define ELEMIT			lexTable.table[j].lexeme == LEX_ID ||\
	lexTable.table[j].lexeme == LEX_LITERAL

#define CHECKOPERAND(i)	((lexTable.table[i - 1].lexeme == LEX_ID ||\
	lexTable.table[i - 1].lexeme == LEX_RIGHTHESIS ||\
	lexTable.table[i - 1].lexeme == LEX_LITERAL) &&\
	(lexTable.table[i + 1].lexeme == LEX_ID ||\
	lexTable.table[i + 1].lexeme == LEX_LITERAL ||\
	lexTable.table[i + 1].lexeme == LEX_LEFTHESIS) ||\
	(lexTable.table[i - 1].lexeme == LEX_EQUALS &&\
	(lexTable.table[i].lexeme == LEX_PLUS || lexTable.table[i].lexeme == LEX_MINUS)))


#define CHECKFUNCTIONS(i) (idtable.table[lexTable.table[i].idxTI].idtype == IT::F ||\
idtable.table[lexTable.table[i].idxTI].idtype == IT::S)
namespace PN
{
	struct Check
	{
		short operand = 0;
		short operation = 0;

	};

	int GetExpression(LT::LexTable lexTable, int i);
	void PolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable, std::ofstream* outfile);
	int Priorities(char operation);
	int AnalizExpression(LT::Entry* expr, LT::LexTable lexTable, IT::IdTable idtable, int pos, std::ofstream* outfile);
	void GetNewExpression(LT::LexTable& lexTable, IT::IdTable& idTable, LT::Entry* expr, int numConver, int sizeExpr);
	void DellNullEntryLt(LT::LexTable& lexTable, IT::IdTable& idTable, int numConver, int sizeExpr, int endExpr);
}