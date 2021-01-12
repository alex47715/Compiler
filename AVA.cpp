#include "pch.h"
#include "Error.h"
#include "FST.h"
#include "GreibachSyntax.h"
#include "In.h"
#include "IT.h"
#include "Lexer.h"
#include "Log.h"
#include "LT.h"
#include "MFST.h"
#include "Parm.h"
#include "PolishNotation.h"



int _tmain(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "rus");
	
	Log::LOG log = Log::INITLOG;

	try {

		short LexerErrors = 0;
		short SemErrors = 0;

		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);

		LexerErrors = LA::LexAnalizer(lextable, idtable, in, parm, log);

		if (LexerErrors == 0)
		{
			*log.stream << "� ����������� ������� ������ �� ��������\n";
		}
		else
		{
			*log.stream << "� ����������� ������� �������� ������\n";
		}
	
		MFST::Mfst mfst(lextable, GRB::getGreibach(),parm.out);
		LA::ShowIdTable(idtable, &mfst.outfile);
		LA::ShowLexTable(lextable, &mfst.outfile);

		MFST_TRACE_START(mfst.outfile);
		bool SytacsisAnalizer = mfst.start(*log.stream);
		mfst.outfile <<"\n\n"<< "\t\t\t\t\t\t������� ������� ��������������\n\n";
		mfst.printrules();
		if (!SytacsisAnalizer)
		{
			*log.stream << "� �������������� ������� �������� ������!!!\n";
			return 1;
		}
		mfst.outfile << "\n�������������� ���������� �������� ������\n";
		SemErrors += SemAnaliz::IsReturnInMain(lextable,idtable, log);
		SemErrors += SemAnaliz::IsReturnInUserFunction(lextable, idtable, log);
		SemErrors += SemAnaliz::IsParamInFunction(lextable, idtable,log);
		SemErrors += SemAnaliz::IsParamInLibFunction(lextable, idtable,log);
		SemErrors += SemAnaliz::Types(lextable, idtable,log);

		if (SemErrors == 0)
		{
			*log.stream << "� ������������� ������� ������ �� ��������\n";
		}
		else
		{
			*log.stream << "� ������������� ������� �������� ������!!!\n";
		}

		if ((LexerErrors + SemErrors) != 0)
		{
			*log.stream << "��������� ����������.������ �� ����� �������!!!\n";
			return 1;
		}
		else {
			*log.stream << "��������� ��������� �������\n";
		}
		PN::PolishNotation(lextable, idtable, &mfst.outfile);
		Generator::CodeGeneration(lextable, idtable);
		mfst.outfile.close();
		LT::Delete(lextable);
		IT::Delete(idtable);
		Log::Close(log);
	}
	catch (Error::ERROR e) {

		Log::WriteError(log, e);
	}
	return 0;
}