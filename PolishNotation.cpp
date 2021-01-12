
#include "pch.h"

namespace PN
{
	
	
	int GetExpression(LT::LexTable lexTable, int i)
	{
		for (; lexTable.table[i].lexeme != LEX_SEMICOLON; i++);
		return i;
	}

	int Priorities(char operation)
	{
		if (operation == LEX_LEFTHESIS || operation == LEX_RIGHTHESIS)
			return 1;
		if (operation == LEX_MINUS || operation == LEX_PLUS)
			return 2;
		if (operation == LEX_DIRSLASH || operation == LEX_STAR)
			return 3;
	}

	int AnalizExpression(LT::Entry* expr, LT::LexTable lexTable, IT::IdTable idtable, int pos, std::ofstream* outfile)
	{
		for (int i = pos, j = GetExpression(lexTable, pos); i < j; i++)
		{
			*outfile << lexTable.table[i].lexeme;
		}
		*outfile << " >>> ";
		std::stack<LT::Entry> Stack;
		int SizeExpression = 0;
		short LeftBracket = 0;

		for (int j = GetExpression(lexTable, pos); pos < j; pos++)
		{
			if ((lexTable.table[pos].lexeme == LEX_ID || lexTable.table[pos].lexeme == LEX_LITERAL) && !CHECKFUNCTIONS(pos))
				expr[SizeExpression++] = lexTable.table[pos];
			
			else if (lexTable.table[pos].idxTI!=LT_TI_NULLIDX && CHECKFUNCTIONS(pos))
			{
				LT::Entry Copy = lexTable.table[pos];
				Copy.lexeme = POLISH_FUNC;
				pos++;
				for (int ParmIndex = 0; ParmIndex < idtable.table[Copy.idxTI].value.params.amount; pos++)
				{
					if (lexTable.table[pos].lexeme == LEX_ID || lexTable.table[pos].lexeme == LEX_LITERAL)
					{
						expr[SizeExpression++] = lexTable.table[pos];
						ParmIndex++;
					}
				}
				expr[SizeExpression++] = Copy;
			}
			else if (lexTable.table[pos].lexeme == LEX_RIGHTHESIS)
			{
				
				while (Stack.size())
				{
					if (Stack.top().lexeme == LEX_LEFTHESIS)	break;
					expr[SizeExpression++] = Stack.top();
					Stack.pop();
				}
				Stack.pop();	LeftBracket--;
			}
			else if (lexTable.table[pos].lexeme == LEX_LEFTHESIS)
			{
				LeftBracket++;
				Stack.push(lexTable.table[pos]);
			}
			else if (Stack.size() == 0 || Stack.top().lexeme == LEX_LEFTHESIS)
			{
				
				Stack.push(lexTable.table[pos]);
			}
			else
			{
				
				while (Stack.size())
				{
					if (Priorities(lexTable.table[pos].lexeme) > Priorities(Stack.top().lexeme)) break;
					expr[SizeExpression++] = Stack.top();
					Stack.pop();
				}
				Stack.push(lexTable.table[pos]);
			}
		}
		
		while (Stack.size() != 0)
		{
			expr[SizeExpression++] = Stack.top();
			Stack.pop();
		}
	
		for (int i = 0; i < SizeExpression; i++)
		{
			*outfile << expr[i].lexeme;
		}
		*outfile << std::endl;
		return SizeExpression;
	}

	void GetNewExpression(LT::LexTable& lexTable, IT::IdTable& idTable, LT::Entry* expr, int numConver, int sizeExpr)
	{
		for (int j = numConver, g = 0; g < sizeExpr; j++, g++)
		{
			lexTable.table[j] = expr[g];
			if (ELEMIT)		
				idTable.table[lexTable.table[j].idxTI].idxfirstLE = j;
		}
	}

	void DellNullEntryLt(LT::LexTable& lexTable, IT::IdTable& idTable, int numConver,int sizeExpr, int endExpr)
	{
		for (int r = endExpr - (numConver + sizeExpr), g = 0; g < r; g++)
		{
			for (int j = numConver + sizeExpr; j < lexTable.size; j++)
			{
				lexTable.table[j] = lexTable.table[j + 1];
				if (ELEMIT)		
					idTable.table[lexTable.table[j].idxTI].idxfirstLE = j;
			}
			lexTable.size--;
		}
	}

	void PolishNotation(LT::LexTable& lexTable, IT::IdTable& idTable, std::ofstream* outfile)
	{
		*outfile << "\n\t\tPolish Notation:\n";
		Check check;
		LT::Entry Expressions[200];
		int StartOfExpression = 0;
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].lexeme == LEX_EQUALS || lexTable.table[i].lexeme == LEX_RETURN || lexTable.table[i].lexeme == LEX_OUT)
			{
		
				StartOfExpression = i + 1;
				int EndExpression = GetExpression(lexTable, StartOfExpression);
				int SizeExpression = AnalizExpression(Expressions, lexTable, idTable, StartOfExpression, outfile);
				GetNewExpression(lexTable, idTable, Expressions, StartOfExpression,SizeExpression);
				DellNullEntryLt(lexTable, idTable, StartOfExpression,SizeExpression,EndExpression);
			}
		}
	}
}

