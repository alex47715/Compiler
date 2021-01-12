#pragma once
#include <tchar.h>
#include <iostream>
#define PARM_IN L"-in:"
#define PARM_OUT L"-out:"
#define PARM_LOG L"-log:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".out"
#define PARM_LOG_DEFAULT_EXT L".log"
#define ASSEMBLER_PATH "C:\\Labs\\LABSYP\\wpf\\WPF\\KP\\AVA\\AsmExecute\\ASM.asm"
namespace Parm {
	struct PARM {
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}