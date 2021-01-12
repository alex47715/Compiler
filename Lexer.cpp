#include "pch.h"
#include "Lexer.h"
#include "FST.h"


char LA::SerchTokens(const char* string) {
	FST::FST MACHINES[] = {FST_WHILE,FST_LEFT_SQUARE_BRACE,FST_RIGHT_SQUARE_BRACE,
	 FST_STRING, FST_FUNCTION, FST_DECLARE,
	 FST_RETURN, FST_PRINT, FST_MAIN,
	 FST_LEFTHESIS, FST_RIGHTHESIS, FST_SEMICOLON, FST_COMMA,
	 FST_LEFTBRACE, FST_BRACELET,
	 FST_PLUS, FST_MINUS, FST_STAR, FST_EQUALS,
	 FST_STRING_LITERAL, FST_INTEGER_LITERAL, FST_INT,
	 GRAPH_POW,GRAPH_RANDOM, FST_BIGGEROREQUAL,FST_SMALLEROREQUAL,FST_NOTEQUAL,FST_SMALLERTHAN,
	 FST_BIGGERTHAN,FST_EQUALS_TWO,FST_ID
	};	
	const int size = sizeof(MACHINES) / sizeof(MACHINES[0]);
	const char TOKENS[] = {LEX_WHILE,LEX_LEFT_SQUARE_BRACE,LEX_RIGHT_SQUARE_BRACE,
	 LEX_STRING, LEX_FUNCTION, LEX_DECLARE,
	 LEX_RETURN, LEX_OUT, LEX_MAIN,
	 LEX_LEFTHESIS, LEX_RIGHTHESIS, LEX_SEMICOLON, LEX_COMMA,
	 LEX_LEFTBRACE, LEX_BRACELET,
	 LEX_PLUS, LEX_MINUS, LEX_STAR, LEX_EQUALS,
	 LEX_STRING_LITERAL, LEX_INTEGER_LITERAL,
	 LEX_INT,LEX_POW,LEX_RAND,LEX_BIGGEROREQUAL,LEX_SMALLEROREQUAL,
	 LEX_NOTEQUAL,LEX_SMALLERTHEN,LEX_BIGGERTHEN,LEX_EQUAL_ID,LEX_ID
		
	};
	
	for (int i = 0; i < size; ++i) {
		if (execute(string, MACHINES[i])) {
			return TOKENS[i];
		}
	}

	return EOF;
}

short LA::LexAnalizer(LT::LexTable& lextable, IT::IdTable& idtable, In::IN& in, Parm::PARM& parm, Log::LOG& log) {
	short LexerErrors = 0;
	std::ofstream outfile(parm.out);
	outfile << "01 ";
	bool MinusId = false;
	std::string Word = "";
	std::string NowRegion = "";
	std::string PastRegion = "";
	std::string NowFunction = "";
	std::string PastId = "";
	bool IsFunctionDeclare = false;

	for (int i = 0, line = 1; in.text[i]; ++i) {
		IT::IDDATATYPE iddatatype;
		auto fillTables = [&] {
			char Token = SerchTokens(Word.c_str());
			if (Token == EOF) {
				LexerErrors++;
				Log::Write(log, Word.c_str(), " - ", "");
				Error::ERROR Buffer = Error::geterrorin(129, line, -1);
				*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line<< std::endl;
			}

			int Ti_Idx = TI_NULLIDX;
			
			iddatatype = (Token == LEX_INT || Token == LEX_INTEGER_LITERAL) ?(IT::IDDATATYPE::INT) :(Token == LEX_STRING || Token == LEX_STRING_LITERAL) ? IT::IDDATATYPE::STR : iddatatype;

			if (Token == LEX_LEFTHESIS) {
				IsFunctionDeclare = lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_FUNCTION;

				if (IsFunctionDeclare) {
					PastRegion = NowRegion;
					NowRegion += NowFunction;
				}
			}
			else if (Token == LEX_RIGHTHESIS && IsFunctionDeclare) {
				NowRegion = PastRegion;
				IsFunctionDeclare = false;
			}
			else if (Token == LEX_LEFTBRACE) {
				PastRegion = NowRegion;
				NowRegion += NowFunction;
			}
			else if (Token == LEX_BRACELET) {
				NowRegion.clear();
				NowFunction.clear();
			}
			else if (Token == LEX_INTEGER_LITERAL ) {
				
				Ti_Idx = IT::IsId(idtable, NowRegion.c_str(), Word.c_str(), true);
				
					if (lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '=' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == ',' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '(' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '>' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '<' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '`' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '$' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '~')
					{
						int Find = IT::IsId(idtable, NowRegion.c_str(), ("_"+Word).c_str(), true);
						if (Find != LT_TI_NULLIDX)
						{
							Ti_Idx = Find;
							MinusId = true;
						}

					}
				
				if (Ti_Idx== LT_TI_NULLIDX) {
					IT::Add(idtable, { lextable.size,  NowRegion.c_str(), Word.c_str(), IT::IDDATATYPE::INT, IT::IDTYPE::L });
					if (atoll(Word.c_str()) >_I32_MAX || atoll(Word.c_str()) <_I32_MIN)
					{
						LexerErrors++;
						Error::ERROR Buffer = Error::geterrorin(132, line, -1);
						*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line<< std::endl;
						
					}
					idtable.table[idtable.size - 1].value.vint = atoi(Word.c_str());
					if (lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '=' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == ',' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '(' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '>' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '<' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '`' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '$' ||
						lextable.table[lextable.size - 1].lexeme == '-' && lextable.table[lextable.size - 2].lexeme == '~')
					{
						idtable.table[idtable.size - 1].value.vint *= (-1);
						strcpy_s(idtable.table[idtable.size - 1].id , ("_" + Word).c_str());
						MinusId = true;
					}
				}
			
				Token = LEX_LITERAL;
			}
			
			else if (Token == LEX_RAND)
			{
			
				IT::Add(idtable, { lextable.size,  NowRegion.c_str(), "random", iddatatype, IT::IDTYPE::S, {1, IT::LENGHT_RAND} });
			}
			else if (Token == LEX_POW)
			{

				IT::Add(idtable, { lextable.size,  NowRegion.c_str(), "inpow", iddatatype, IT::IDTYPE::S , {2, IT::LENGHT_POW} });
			}
			else if (Token == LEX_OUT)
			{
				IT::Add(idtable, { lextable.size,  NowRegion.c_str(), "out", iddatatype, IT::IDTYPE::S });
				idtable.table[idtable.size - 1].value.params.amount = 1;
			}
			else if (Token == LEX_STRING_LITERAL) {
				std::string NewId = Word.substr(1, Word.size() - 2);
				for (int CounterStr = 0; CounterStr < NewId.length(); CounterStr++)
				{
					if (NewId[CounterStr] == ' ')
						NewId[CounterStr] = '_';
				}
				std::string Literal = Word.substr(1, Word.size() - 2);
				Ti_Idx = IT::IsId(idtable, NowRegion.c_str(), Literal.c_str(), true);
				if (Ti_Idx == LT_TI_NULLIDX) {
					IT::Add(idtable, { lextable.size,  NowRegion.c_str(), NewId.c_str(), IT::IDDATATYPE::STR, IT::IDTYPE::L });
					strcpy_s(idtable.table[idtable.size - 1].value.vstr.str, Literal.c_str());
					idtable.table[idtable.size - 1].value.vstr.len = Literal.length();
					strcpy_s(idtable.table[idtable.size - 1].id, NewId.c_str());
				}
				Token = LEX_LITERAL;
				
			}
			else if (Token == LEX_ID || Token == LEX_POW || Token == LEX_RAND ||Token ==LEX_OUT) {
				std::string id = Word.substr(0, ID_MAXSIZE);
				Ti_Idx = IT::IsId(idtable, NowRegion.c_str(), id.c_str());
				
				if (Ti_Idx == TI_NULLIDX) {
					if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_DECLARE
						&& lextable.table[lextable.size - 1].lexeme == LEX_DATATYPE) {
						IT::Add(idtable, { lextable.size,  NowRegion.c_str(), id.c_str(), iddatatype, IT::IDTYPE::V });
					}
					else if (lextable.size >= 1 && (lextable.table[lextable.size - 1].lexeme == LEX_POW) ||
						(lextable.table[lextable.size - 1].lexeme == LEX_RAND ) || lextable.size >= 1 && (lextable.table[lextable.size - 1].lexeme == LEX_OUT)) {
						IT::Add(idtable, { lextable.size,  NowRegion.c_str(), id.c_str(), iddatatype, IT::IDTYPE::V });
					}
					else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexeme == LEX_FUNCTION) {
						NowFunction = id;
						IT::Add(idtable, { lextable.size,  NowRegion.c_str(), id.c_str(), iddatatype, IT::IDTYPE::F });
					}
					else if (lextable.size >= 1 && lextable.table[lextable.size - 1].lexeme == LEX_DATATYPE
						&& IsFunctionDeclare) {
						IT::Add(idtable, { lextable.size,  NowRegion.c_str(), id.c_str(), iddatatype, IT::IDTYPE::P });
					}
					else {
						LexerErrors++;
						Log::Write(log, Word.c_str(), " - ", "");
						Error::ERROR Buffer = Error::geterrorin(124, line, -1);
						*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
						
					}
				}
				else if (lextable.size >= 2 && lextable.table[lextable.size - 2].lexeme == LEX_DECLARE
					|| lextable.size >= 1 && lextable.table[lextable.size - 1].lexeme == LEX_FUNCTION) {
					LexerErrors++;
					Log::Write(log, Word.c_str(), " - ", "");
					Error::ERROR Buffer = Error::geterrorin(123, line, -1);
					*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					
				}

			}
			else if (Token == LEX_MAIN && NowRegion.empty()) {
				Ti_Idx = IT::IsId(idtable, "", Word.c_str());

				if (Ti_Idx != TI_NULLIDX) {
					LexerErrors++;
					Log::Write(log, Word.c_str(), " - ", "");
					Error::ERROR Buffer = Error::geterrorin(131, line, -1);
					*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					
				}
				NowRegion.clear();
				NowFunction = Word;

				IT::Add(idtable, { lextable.size, "", Word.c_str(), IT::IDTYPE::F, 0 });
			}
			
			Token = (Token == LEX_INT || Token == LEX_STRING) ? LEX_DATATYPE : Token;

			
		
			if (Token == LEX_ID  || Token == LEX_MAIN) {
				if (Ti_Idx == TI_NULLIDX)
					LT::Add(lextable, { Token, line, idtable.size - 1 });
				else 
					LT::Add(lextable, { Token, line, Ti_Idx });
			}
			else if (Token == LEX_LITERAL)
			{
				if (Ti_Idx == LT_TI_NULLIDX && !MinusId) 
					LT::Add(lextable, { Token, line, idtable.size - 1 });
				
				else if(Ti_Idx == LT_TI_NULLIDX && MinusId)
				{
				
					lextable.table[lextable.size - 1].idxTI = idtable.size - 1;
					lextable.table[lextable.size - 1].lexeme = LEX_LITERAL;
					lextable.table[lextable.size - 1].sn = line;
					MinusId = false;
				}
				else if (MinusId)
				{
					lextable.table[lextable.size - 1].idxTI = Ti_Idx;
					lextable.table[lextable.size - 1].lexeme = LEX_LITERAL;
					lextable.table[lextable.size - 1].sn = line;
					MinusId = false;
				}
				else
					LT::Add(lextable, { Token, line, Ti_Idx});
			}
			else if (SemAnaliz::IsLibFunction(Token))
			{
				LT::Add(lextable, { Token, line, idtable.size - 1 });
			}
			else 
				LT::Add(lextable, { Token, line, LT_TI_NULLIDX });
			

			outfile << Token;
			Word.clear();
		};

		unsigned char& ch = in.text[i];
		if (in.code[ch] == In::IN::T)
			Word += ch;
		else if (in.code[ch] == In::IN::Q) {
			do {
				Word += ch;
				i++;
				ch = in.text[i];
			} while (in.code[ch] != In::IN::Q);
			Word += ch;
			fillTables();
		}
		else if (in.code[ch] == In::IN::S || in.code[ch] == In::IN::O || ch == IN_CODE_DELIM) {
			if (!Word.empty()) {
				if (ch == '=')
					PastId = Word;
				fillTables();
			}
			if (in.code[ch] == In::IN::O) {

				Word = ch;
				fillTables();
			}
		}

		if (ch == IN_CODE_DELIM) {
			line++;
			if (in.text[i + 1]) {
				outfile << "\n" << std::setw(2) << std::setfill('0') << line << " ";
				i++;
			}
		}
	}

	if (IT::IsId(idtable, "", "main") == TI_NULLIDX) {
		LexerErrors++;
		Error::ERROR Buffer = Error::geterror(130);
		*log.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке "<< std::endl;
	}
	LA::WriteInfoAboutFunctions(lextable, idtable);
	outfile.close();
	return LexerErrors;
}

void LA::ShowIdTable(IT::IdTable& idtable, std::ofstream* outfile)
{
	*outfile << "\n----------------------------------------------------ID TABLE--------------------------------------------" << std::endl;
	*outfile << "\t|ID|\t\t\t|SCOPE|\t\t\t|TYPE|\t\t\t|IDTYPE|\t\t\t|value|\t\t\t|LEidX|" << std::endl;
	for (int i = 0; i < idtable.size; i++)
	{
		*outfile <<'|'<< i<<"| "<<idtable.table[i].id << "\t\t\t\t" << idtable.table[i].scope << "\t\t\t\t";
		switch (idtable.table[i].iddatatype)
		{
		case IT::INT:
			*outfile << "INT\t\t\t\t";
			break;
		case IT::STR:
			*outfile << "STR\t\t\t\t";
			break;
		default:
			break;
		}

		switch (idtable.table[i].idtype)
		{
		case IT::IDTYPE::V:
			*outfile << "var\t\t\t\t";
			break;
		case IT::IDTYPE::F:
			*outfile << "func\t\t\t\t";
			break;
		case IT::IDTYPE::S:
			*outfile << "std func\t\t\t\t";
			break;
		case IT::IDTYPE::L:
			*outfile << "literal\t\t\t\t";
			break;
		case IT::IDTYPE::P:
			*outfile << "params\t\t\t";
			break;
		default:
			break;
		}
		if (idtable.table[i].idtype == IT::IDTYPE::L)
		{
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
			{
				*outfile << idtable.table[i].value.vint;
			}
			
			if (idtable.table[i].iddatatype == IT::IDDATATYPE::STR)
			{
				*outfile << idtable.table[i].value.vstr.str;
			}
		}
		else {
			*outfile << "NULL";
		}
		*outfile << '\t' << idtable.table[i].idxfirstLE << std::endl;
	}
	*outfile << "------------------------------------------------------------------------------------------------------------\n\n" << std::endl;
}
void LA::WriteInfoAboutFunctions(LT::LexTable& lextable, IT::IdTable& idtable)
{
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F &&
			lextable.table[i - 1].lexeme == LEX_FUNCTION) {
			int NowFunctionPosition = i;
			short ParamsSize = 0;
			idtable.table[lextable.table[i].idxTI].value.params.amount = 0;
			idtable.table[lextable.table[i].idxTI].value.params.types = new IT::IDDATATYPE;
			i += 2;
			while (lextable.table[i].lexeme != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].lexeme == LEX_ID)
				{
					idtable.table[lextable.table[NowFunctionPosition].idxTI].value.params.amount++;
					int j = 0;
					IT::IDDATATYPE* buffer = new IT::IDDATATYPE[idtable.table[lextable.table[NowFunctionPosition].idxTI].value.params.amount];
					for (; j < idtable.table[lextable.table[NowFunctionPosition].idxTI].value.params.amount - 1; j++)
					{
						buffer[j] = idtable.table[lextable.table[NowFunctionPosition].idxTI].value.params.types[j];
					}
					idtable.table[lextable.table[NowFunctionPosition].idxTI].value.params.types[j] = idtable.table[lextable.table[i].idxTI].iddatatype;
				}
				i++;
			}

		}
	}
}
void LA::ShowLexTable(LT::LexTable& lextable, std::ofstream* outfile)
{
	*outfile << "-------------------------------[LEXTABLE]---------------------------------" << std::endl;
	*outfile << "\t\t\t|LEXEME|\t\t\t|Строка|\t\t\t|idx|" << std::endl;
	for (int i = 0; i < lextable.size; i++)
	{
		*outfile <<'|'<< i<<"| \t\t\t" << lextable.table[i].lexeme << "\t\t\t\t\t" << lextable.table[i].sn<<"\t\t\t\t";
		if (lextable.table[i].idxTI != TI_NULLIDX)
			*outfile << lextable.table[i].idxTI;
		else
			*outfile << "NULL";
		*outfile << std::endl;
	}
	*outfile << "-----------------------------------------------------------------------------------------------------------\n" << std::endl;
}