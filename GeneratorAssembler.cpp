#include "pch.h"



bool Generator::CodeGeneration(LT::LexTable& lextable, IT::IdTable& idtable)
{
	std::ofstream Assembler(ASSEMBLER_PATH);
	if (!Assembler.is_open())
		throw ERROR_THROW(101);
	
	Assembler << BEGIN;
	Assembler << ".const\n";
	Assembler << "OVERFLOWMESSAGE " << " BYTE " << "\'Îøèáêà:ÏÅÐÅÏÎËÍÅÍÈÅ!!!\'," << 0 << std::endl;
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idtype == IT::L)
		{
			Assembler << "\t" << idtable.table[i].scope<<idtable.table[i].id;
			if (idtable.table[i].iddatatype ==IT::INT)
			{
				Assembler << " SDWORD " << idtable.table[i].value.vint << std::endl;
			}
			if (idtable.table[i].iddatatype == IT::STR)
			{
				Assembler << " BYTE " <<'\''<< idtable.table[i].value.vstr.str<<'\'' << ", 0\n";
			}

		}
	}

	Assembler << ".data\n";
	
	for (int i = 0; i < idtable.size; i++)
	{
		if (idtable.table[i].idtype == IT::IDTYPE::V)
		{
			Assembler << "\t" << idtable.table[i].scope<< idtable.table[i].id<<IT::V;
			if (idtable.table[i].iddatatype == IT::STR)
				Assembler << " DWORD ?\n";
			if (idtable.table[i].iddatatype ==IT::INT)
				Assembler << " DWORD ?\n";
		}
	}
	Assembler << "\n.code\n";
	bool IsMain = false;
	bool IsFunction = false;
	int IsFunctionIndex;
	int WhileLine = 0;
	bool WhileExist = false;
	char LogicOperator;
	for (int i = 0; i < lextable.size; i++)
	{
		switch (lextable.table[i].lexeme)
		{
		   case LEX_MAIN:
		    {
			        Assembler << "main PROC\n";
			        IsMain = true;
			        break;
		    }

			case LEX_FUNCTION:
			{
					IsFunction = true;
					i++;
					IsFunctionIndex = i;
					Assembler << (idtable.table[lextable.table[i].idxTI]).id << " PROC ";
					i += 2;
					while (lextable.table[i].lexeme != LEX_RIGHTHESIS)
					{
						if (lextable.table[i].lexeme == LEX_ID)
						{
							
							Assembler << idtable.table[lextable.table[i].idxTI].scope << idtable.table[lextable.table[i].idxTI].id<<IT::V << " : ";
							if (idtable.table[lextable.table[i].idxTI].iddatatype ==IT::INT || idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
							{
								Assembler << " DWORD ";
							}
						}
						if(lextable.table[i+1].lexeme!=LEX_RIGHTHESIS&& lextable.table[i].lexeme == LEX_ID)
						Assembler << ", ";
						i++;
					}
					Assembler << std::endl;
				break;
			}
		
			case LEX_BRACELET:
			{

				if (IsFunction)
				{
					Assembler << "OVERFLOW:\npush OFFSET OVERFLOWMESSAGE\ncall outstrline\npush -1\n\tcall\t\tExitProcess\n" << idtable.table[lextable.table[IsFunctionIndex].idxTI].id << " ENDP\n\n";
					IsFunction = false;
				}
				else
				{
					Assembler << "call\tsystem_pause\n \tcall\t\tExitProcess\nZEROERROR:\n" <<
						"OVERFLOW:\npush OFFSET OVERFLOWMESSAGE\ncall outstrline\npush -1\n\tcall\t\tExitProcess\n" <<" main ENDP\nEND main";
				}
				IsFunctionIndex = 0;
				break;
			}
			case LEX_RETURN:
			{
				i = Generator::GenerateExpression(Assembler, lextable, idtable, ++i);
				if (!IsMain)
					Assembler << " \nret\n";
				else
					Assembler << "push eax\n";
				break;
			}
			case LEX_OUT:
			{
				IT::IDDATATYPE type = Generator::GetType(lextable, idtable, i + 1);
				i = Generator::GenerateExpression(Assembler, lextable, idtable, ++i);
				if (type ==IT::INT)
					Assembler << "push eax\ncall outnumline\n";
				
				else if(type == IT::STR)
				{
					Assembler << "push eax\ncall outstrline\n";
				}
				break;
			}
			case LEX_EQUALS:
			{
				int idx = lextable.table[i - 1].idxTI;
				i = Generator::GenerateExpression(Assembler, lextable, idtable, ++i);
				Assembler << "push eax\npop " << idtable.table[idx].scope << idtable.table[idx].id;
				if (idtable.table[idx].idtype == IT::V)
					Assembler << IT::V;
				Assembler << std::endl;
				break;
			}
			
			case LEX_WHILE:
			{
				WhileExist = true;
				WhileLine = lextable.table[i].sn;
				Assembler << "TOWHILE" << WhileLine << ":\n";
				Assembler <<
					"push " << idtable.table[lextable.table[i + 2].idxTI].scope << idtable.table[lextable.table[i + 2].idxTI].id;
				if (idtable.table[lextable.table[i + 2].idxTI].idtype == IT::V)
					Assembler << IT::V;
				Assembler << std::endl;

				Assembler << "push " << idtable.table[lextable.table[i + 4].idxTI].scope << idtable.table[lextable.table[i + 4].idxTI].id;
				if (idtable.table[lextable.table[i + 4].idxTI].idtype == IT::V)
					Assembler << IT::V;
				Assembler << std::endl << "pop ebx\npop eax\ncmp eax, ebx\n";
				LogicOperator = lextable.table[i + 3].lexeme;
				Generator::Operations(Assembler, lextable.table[i + 3].lexeme, WhileLine);


				break;
			}
			case LEX_RIGHT_SQUARE_BRACE:
			{
				if (WhileExist)
				{
					Assembler << "jmp TOWHILE" << WhileLine << "\n";
					Assembler << "SKIP" << WhileLine << ":\n";
				}
				break;
			}
		default:
			break;
		}
	}
	
	std::stack<std::string> MyStack;
	Assembler.close();
	return true;

}



IT::IDDATATYPE Generator::GetType(LT::LexTable lextable, IT::IdTable idtable, int i)
{
	for (;lextable.table[i].lexeme!=LEX_SEMICOLON ; i++)
	{
		if (lextable.table[i].idxTI != LT_TI_NULLIDX)
		{
			return idtable.table[lextable.table[i].idxTI].iddatatype;
		}
	}
}

int Generator::GenerateExpression(std::ofstream& AsmFile, LT::LexTable& LEXTABLE, IT::IdTable& idtable, int i) {
	for (; LEXTABLE.table[i].lexeme != LEX_SEMICOLON; i++)
	{
		switch (LEXTABLE.table[i].lexeme)
		{
		case LEX_PLUS:
		{
			AsmFile << "pop eax" << std::endl <<
				"pop ebx" << std::endl << "add eax,ebx" << std::endl << "push eax\n" <<
				"jo OVERFLOW\n";
			break;
		}
		case LEX_MINUS:
		{
			AsmFile << "pop ebx" << std::endl <<
				"pop eax" << std::endl << "sub eax,ebx" << std::endl << "push eax" << std::endl <<
				"jo OVERFLOW\n";
			break;
		}
		case LEX_STAR:
		{
			AsmFile << "pop ebx" << std::endl <<
				"pop eax" << std::endl << "mul ebx" << std::endl << "push eax" << std::endl <<
				"jo OVERFLOW\n";
			break;
		}
		case LEX_LITERAL:
		case LEX_ID:
		{
			if (idtable.table[LEXTABLE.table[i].idxTI].iddatatype == IT::INT)
			{
				AsmFile << "push " << idtable.table[LEXTABLE.table[i].idxTI].scope << idtable.table[LEXTABLE.table[i].idxTI].id;
				if (idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::V || idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::P)
					AsmFile << IT::V;
				AsmFile << std::endl;
			}

			else if ((idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::L) && idtable.table[LEXTABLE.table[i].idxTI].iddatatype == IT::STR)
			{
				AsmFile << "push OFFSET " <<
					idtable.table[LEXTABLE.table[i].idxTI].scope <<
					idtable.table[LEXTABLE.table[i].idxTI].id << std::endl;
			}
			else
			{
				AsmFile << "push  " << idtable.table[LEXTABLE.table[i].idxTI].scope << idtable.table[LEXTABLE.table[i].idxTI].id;
				if (idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::V || idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::P)
					AsmFile << IT::V;
				AsmFile << std::endl;
			}
			break;
		}
		case POLISH_FUNC:
		{
			AsmFile << "call " << idtable.table[LEXTABLE.table[i].idxTI].id << std::endl;
			if (idtable.table[LEXTABLE.table[i].idxTI].idtype == IT::S)
				AsmFile << " pop ecx\n";
			AsmFile << " push eax\n";
			break;
		}
		default:
			break;
		}
	}
	AsmFile << "pop eax\n";
	return i;
}

void Generator::Operations(std::ofstream& AsmFile, char lex, int sn)
{
	switch (lex)
	{
	case LEX_SMALLEROREQUAL:
	{
		AsmFile << "ja SKIP" << sn << "\n";

		break;
	}
	case LEX_BIGGERTHEN:
	{
		AsmFile << "jbe SKIP" << sn << "\n";
		break;
	}
	case LEX_SMALLERTHEN:
	{
		AsmFile << "jae SKIP" << sn << "\n";

		break;
	}
	case LEX_BIGGEROREQUAL:
	{
		AsmFile << "jb SKIP" << sn << "\n";

		break;
	}
	case LEX_NOTEQUAL:
	{
		AsmFile << "je SKIP" << sn << "\n";

		break;
	}
	case LEX_EQUAL_ID:
	{
		AsmFile << "jne SKIP" << sn << "\n";

		break;
	}
	default:
		break;
	}
}

void Generator::WhileOperations(std::ofstream& AsmFile, char lex, int sn)
{
	switch (lex)
	{
	
	case LEX_SMALLERTHEN:
	{
		AsmFile << "jb TOWHILE" << sn << "\n";

		break;
	}
	case LEX_SMALLEROREQUAL:
	{
		AsmFile << "jbe TOWHILE" << sn << "\n";

		break;
	}
	case LEX_NOTEQUAL:
	{
		AsmFile << "jne TOWHILE" << sn << "\n";

		break;
	}
	case LEX_BIGGERTHEN:
	{
		AsmFile << "jae TOWHILE" << sn << "\n";
		break;
	}
	case LEX_BIGGEROREQUAL:
	{
		AsmFile << "jae TOWHILE" << sn << "\n";

		break;
	}
	case LEX_EQUAL_ID:
	{
		AsmFile << "je TOWHILE" << sn << "\n";

		break;
	}
	default:
		break;
	}
}