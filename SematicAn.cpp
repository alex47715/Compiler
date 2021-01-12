#include "pch.h"
//
namespace SemAnaliz
{
	 Error::ERROR Buffer;
	short SemAnaliz::IsReturnInMain(LT::LexTable& lextable, IT::IdTable& idtable,Log::LOG logfile)
	{
		short Errors = 0;
		short IsReturn = 0;
		short ReturnId = 0;//1 - не весь код возвращает значение
		for (int lexema_I = 0; lexema_I < lextable.size; lexema_I++)
		{
			if (lextable.table[lexema_I].lexeme == LEX_MAIN)
			{
				for (int lexIndexInMain = lexema_I; lexIndexInMain < lextable.size; lexIndexInMain++)
				{
					if (lextable.table[lexIndexInMain].lexeme == LEX_LEFT_SQUARE_BRACE)
					{
						IsReturn++;
					}
					if (lextable.table[lexIndexInMain].lexeme == LEX_RIGHT_SQUARE_BRACE)
					{
						IsReturn--;
					}
					if (lextable.table[lexIndexInMain].lexeme == LEX_FUNCTION)
					{
						Errors++;
						 Buffer = Error::geterrorin(702, lextable.table[lexema_I].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					if (lextable.table[lexIndexInMain].lexeme == LEX_RETURN)
					{
						
						for ( ; lexIndexInMain <lextable.size&&lextable.table[lexIndexInMain].lexeme!=LEX_SEMICOLON; lexIndexInMain++)
						{
							if (lextable.table[lexIndexInMain].idxTI != LT_TI_NULLIDX && idtable.table[lextable.table[lexIndexInMain].idxTI].iddatatype !=IT::INT)
							{
								Errors++;
								 Buffer = Error::geterrorin(703, lextable.table[lexema_I].sn, -1);
								*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
							}//мейн должен возвращать int
						}	

						if (IsReturn == 0)
						{
							ReturnId = -1;
						}
						else
							ReturnId = 1;
					}
					
				}
				if (ReturnId == 1)
				{
					Errors++;
					 Buffer = Error::geterrorin(701, lextable.table[lexema_I].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
				}//warming - не весь код возвращает return
				if (ReturnId == 0)
				{
					Errors++;
					 Buffer = Error::geterrorin(700, lextable.table[lexema_I].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
				}//warming - нет return

				break;
			}
			
		}
		return Errors;
	}

	short SemAnaliz::IsReturnInUserFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile)
	{
		short Errors = 0;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexeme == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F 
				&& lextable.table[i-1].lexeme == LEX_FUNCTION)
			{
				
				IT::IDDATATYPE CurrentTypeOfFunction = idtable.table[lextable.table[i].idxTI].iddatatype;
				
				
				while (lextable.table[i].lexeme != LEX_LEFTBRACE && i < lextable.size)//пропускаем парамметры функции
				{
					i++;
				}
				short IsReturn = 0;
				short ReturnId = 0;
				
				for (; i < lextable.size && lextable.table[i].lexeme!=LEX_BRACELET; i++)
				{
					
					if (lextable.table[i].lexeme == LEX_LEFT_SQUARE_BRACE)//вложенность
					{
						IsReturn++;
					}
					if (lextable.table[i].lexeme == LEX_RIGHT_SQUARE_BRACE)
					{
						IsReturn--;
					}
					if (lextable.table[i].lexeme == LEX_RETURN)
					{
						
						for (; i < lextable.size && lextable.table[i].lexeme != LEX_SEMICOLON; i++)
						{
							if (lextable.table[i].idxTI != LT_TI_NULLIDX && idtable.table[lextable.table[i].idxTI].iddatatype != CurrentTypeOfFunction)
							{
								Errors++;
								 Buffer = Error::geterrorin(704, lextable.table[i].sn, -1);
								*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
							}
						}
						if (IsReturn != 0)
							ReturnId = 1;
						if (IsReturn == 0)
							ReturnId = -1;
					}
				}
				switch (ReturnId)
				{
				case -1:
					break;
				case 0:
					Errors++;
					 Buffer = Error::geterrorin(700, lextable.table[i].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//ВЫШЕ ОПИСАНО
					break;
				case 1:
					Errors++;
					 Buffer = Error::geterrorin(701, lextable.table[i].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//ВЫШЕ ОПИСАНО
					break;
				default:
					break;
				}
			}
		}
		return Errors;
	}

	short SemAnaliz::IsParamInFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile)
	{
		short Errors = 0;
		for (int i = 0; i < lextable.size; i++)
		{
			//ищем функцию
			if (lextable.table[i].lexeme == LEX_ID && lextable.table[i - 1].lexeme != LEX_FUNCTION &&
				idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
			{
				int FunctionPosition = i;
				int NumberOfArgument = 0;//номер аргумента
				i++;
				while (lextable.table[i].lexeme!=LEX_RIGHTHESIS && i < lextable.size)
				{
					
					if (lextable.table[i].lexeme == LEX_ID || (lextable.table[i].idxTI!=TI_NULLIDX&&
						idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L))
					{
					
						
						if (idtable.table[lextable.table[FunctionPosition].idxTI].value.params.amount <= NumberOfArgument)
						{// аргументов больше чем параметров в функции
							Errors++;
							 Buffer = Error::geterrorin(705, lextable.table[i].sn, -1);
							*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
						}
							//соответствие типов параметров и аргументоав
							if (idtable.table[lextable.table[FunctionPosition].idxTI].value.params.types[NumberOfArgument] !=
								idtable.table[lextable.table[i].idxTI].iddatatype
								)
							{
								Errors++;
								 Buffer = Error::geterrorin(706, lextable.table[i].sn, -1);
								*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//тип аргумента не соответствует типу параметра
							}
							NumberOfArgument++;
						
					}
					i++;
				}
				if (idtable.table[lextable.table[FunctionPosition].idxTI].value.params.amount > NumberOfArgument)
				{//мало агрументов передано
					Errors++;
					 Buffer = Error::geterrorin(707, lextable.table[i].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
				}
			}
		}
		return Errors;
	}
	
	short SemAnaliz::IsParamInLibFunction(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile)
	{
		short Errors = 0;
		for (int i = 0; i < lextable.size; i++)
		{
			if (SemAnaliz::IsLibFunction(lextable.table[i].lexeme) && lextable.table[i - 1].lexeme == LEX_FUNCTION)
			{//нельзя переопределять функцию
				Errors++;
				 Buffer = Error::geterrorin(708, lextable.table[i].sn, -1);
				*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
			}

			if (SemAnaliz::IsLibFunction(lextable.table[i].lexeme))
			{
			
				short CountOfParams = 0;

				switch (lextable.table[i].lexeme)
				{
				
				case LEX_RAND:
					i++;
					while (lextable.table[i].lexeme != LEX_RIGHTHESIS && i < lextable.size)
					{
						if (lextable.table[i].lexeme == LEX_ID)
							if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
							{
								Errors++;
								 Buffer = Error::geterrorin(706, lextable.table[i].sn, -1);
								*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
							}//тип арнгумента не соответсвует типу параметра
							else
							{
								CountOfParams++;
							}
						if (lextable.table[i].idxTI != LT_TI_NULLIDX)
							if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L)
								if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
								{
									Errors++;
									 Buffer = Error::geterrorin(706, lextable.table[i].sn, -1);
									*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//тип литерала не соответствует типу параметра
								}
								else {
									CountOfParams++;
								}
						i++;
					}
					if (CountOfParams < 1)
					{
						Errors++;
						 Buffer = Error::geterrorin(707, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					else if (CountOfParams > 1)
					{
						Errors++;
						 Buffer = Error::geterrorin(705, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//СЛИШКОМ МНОГО
					}

					break;
				case LEX_POW:
					i++;
					while (lextable.table[i].lexeme != LEX_RIGHTHESIS && i < lextable.size)
					{
						if (lextable.table[i].lexeme == LEX_ID)
							if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
							{
								Errors++;
								 Buffer = Error::geterrorin(706, lextable.table[i].sn, -1);
								*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
							}//неправильный передаваемый тип
							else
							{
								CountOfParams++;
							}
						if (lextable.table[i].idxTI != LT_TI_NULLIDX)
							if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L)
								if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
								{
									Errors++;
									 Buffer = Error::geterrorin(706, lextable.table[i].sn, -1);
									*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//тип литерала не соответствует типу параметра
								}
								else {
									CountOfParams++;
								}
						i++;
					}
					if (CountOfParams < 2)
					{
						Errors++;
						 Buffer = Error::geterrorin(707, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					else if (CountOfParams > 2)
					{
						Errors++;
						 Buffer = Error::geterrorin(705, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//СЛИШКОМ МНОГО
					}

					break;
				case LEX_OUT:
				{
					i += 2;
					while (lextable.table[i].lexeme != LEX_RIGHTHESIS && i < lextable.size)
					{
						CountOfParams++;
						i++;
					}
					if (CountOfParams < 1)
					{
						Errors++;
						 Buffer = Error::geterrorin(707, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					else if (CountOfParams > 1)
					{
						Errors++;
						 Buffer = Error::geterrorin(705, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//СЛИШКОМ МНОГО
					}
					break;
				}
				default:
					Errors++;
					 Buffer = Error::geterrorin(709, lextable.table[i].sn, -1);
					*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//неопознаная библиотечная функция
					break;
				}
			}
		}
		return Errors;
	}
	bool SemAnaliz::IsLibFunction(unsigned char lex)
	{
		switch (lex)
		{
		case LEX_RAND:
			return true;
		case LEX_POW:
			return true;
		case LEX_OUT:
			return true;
		default:
			return false;
			break;
		}
	}

	short SemAnaliz::Types(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG logfile)
	{
		short Errors = 0;
		IT::IDDATATYPE currentType;
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexeme == LEX_EQUALS )
			{
				currentType = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
				while (lextable.table[i].lexeme!=LEX_SEMICOLON && i<lextable.size)
				{
					i++;
					if ((lextable.table[i].lexeme == LEX_ID || lextable.table[i].lexeme == LEX_LITERAL)
						&& idtable.table[lextable.table[i].idxTI].iddatatype != currentType)
					{
						if (idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F ||
							idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::S)
						{
							Errors++;
							 Buffer = Error::geterrorin(710, lextable.table[i].sn, -1);
							*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
						}//не тот тип
						else if(idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::V ||
							idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::L)
						{
							Errors++;
							 Buffer = Error::geterrorin(710, lextable.table[i].sn, -1);
							*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
						}//не тот тип данных
					}
					else if (lextable.table[i].lexeme == LEX_ID
						&& (idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::F&&
							idtable.table[lextable.table[i].idxTI].idtype != IT::IDTYPE::S)
						&& lextable.table[i + 1].lexeme == LEX_LEFTHESIS)
					{
						Errors++;
						 Buffer = Error::geterrorin(711, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;//не верный вызов функции
					}
					else if (lextable.table[i].lexeme == LEX_RAND && currentType != IT::IDDATATYPE::INT)
					{
						Errors++;
						 Buffer = Error::geterrorin(710, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					else if (lextable.table[i].lexeme == LEX_POW && currentType != IT::IDDATATYPE::INT)
					{
						Errors++;
						 Buffer = Error::geterrorin(710, lextable.table[i].sn, -1);
						*logfile.stream << '(' << Buffer.id << ')' << Buffer.message << " в строке " << Buffer.inext.line << std::endl;
					}
					if (SemAnaliz::IsLibFunction(lextable.table[i].lexeme) ||
						lextable.table[i].lexeme == LEX_FUNCTION)
					{
						while (lextable.table[i].lexeme != LEX_RIGHTHESIS && i < lextable.size)
							i++;
					}
				}
			}
		}
		return Errors;
	}
	
}

