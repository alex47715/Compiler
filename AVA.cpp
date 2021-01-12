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
			*log.stream << "Â ËÅÊÑÈ×ÅÑÊÎÌ ÀÍÀËÈÇÅ ÎØÈÁÎÊ ÍÅ ÂÎÇÍÈÊËÎ\n";
		}
		else
		{
			*log.stream << "Â ËÅÊÑÈ×ÅÑÊÎÌ ÀÍÀËÈÇÅ ÂÎÇÍÈÊËÀ ÎØÈÁÊÀ\n";
		}
	
		MFST::Mfst mfst(lextable, GRB::getGreibach(),parm.out);
		LA::ShowIdTable(idtable, &mfst.outfile);
		LA::ShowLexTable(lextable, &mfst.outfile);

		MFST_TRACE_START(mfst.outfile);
		bool SytacsisAnalizer = mfst.start(*log.stream);
		mfst.outfile <<"\n\n"<< "\t\t\t\t\t\tÏÐÀÂÈËÀ ÊÎÒÎÐÛÅ ÈÑÏÎËÜÇÎÂÀËÈÑÜ\n\n";
		mfst.printrules();
		if (!SytacsisAnalizer)
		{
			*log.stream << "Â ÑÈÍÒÀÊÑÈ×ÅÑÊÎÌ ÀÍÀËÈÇÅ ÂÎÇÍÈÊËÀ ÎØÈÁÊÀ!!!\n";
			return 1;
		}
		mfst.outfile << "\nÑÈÍÒÀÊÑÈ×ÅÑÊÈÉ ÀÍÀËÈÇÀÒÎÐ ÇÀÊÎÍ×ÈË ÐÀÁÎÒÓ\n";
		SemErrors += SemAnaliz::IsReturnInMain(lextable,idtable, log);
		SemErrors += SemAnaliz::IsReturnInUserFunction(lextable, idtable, log);
		SemErrors += SemAnaliz::IsParamInFunction(lextable, idtable,log);
		SemErrors += SemAnaliz::IsParamInLibFunction(lextable, idtable,log);
		SemErrors += SemAnaliz::Types(lextable, idtable,log);

		if (SemErrors == 0)
		{
			*log.stream << "Â ÑÅÌÀÍÒÈ×ÅÑÊÎÌ ÀÍÀËÈÇÅ ÎØÈÁÎÊ ÍÅ ÂÎÇÍÈÊËÎ\n";
		}
		else
		{
			*log.stream << "Â ÑÅÌÀÍÒÈ×ÅÑÊÎÌ ÀÍÀËÈÇÅ ÂÎÇÍÈÊËÀ ÎØÈÁÊÀ!!!\n";
		}

		if ((LexerErrors + SemErrors) != 0)
		{
			*log.stream << "ÃÅÍÅÐÀÖÈß ÍÅÂÎÇÌÎÆÍÀ.ÎØÈÁÊÈ ÍÀ ÝÒÀÏÅ ÀÍÀËÈÇÀ!!!\n";
			return 1;
		}
		else {
			*log.stream << "ÃÅÍÅÐÀÖÈß ÂÛÏÎËÍÅÍÀ ÓÑÏÅØÍÎ\n";
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