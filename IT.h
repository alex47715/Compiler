#pragma once

#define ID_MAXSIZE		32
#define SCOPE_MAXSIZE	10
#define TI_MAXSIZE		4096
#define TI_INT_DEFAULT	0x00000000
#define TI_STR_DEFAULT	0x00
#define TI_NULLIDX		((int)0xffffffff)
#define TI_STR_MAXSIZE	255
#define RANDOM_TYPE IT::IDDATATYPE::INT
#define POW_TYPE IT::IDDATATYPE::INT
#define MAX_PARAMS_COUNT 5			   	 //������������ ���������� ���������� � �������
#define POW_PARAMS_COUNT 2				 //���-�� ���������� � ������� pow
#define RANDOM_PARAMS_COUNT 1				 //���-�� ���������� � ������� rand
#define POW_PARAMS_CNT 2				 //���-�� ���������� � ������� pow
#define RANDOM_PARAMS_CNT 1				 //���-�� ���������� � ������� rand
#define SIN_PARAM_CNT 1
#define TI_INT_MAXSIZE   INT32_MAX		 
#define TI_INT_MINSIZE   INT32_MIN

namespace IT {
	enum IDDATATYPE { INT = 1,STR = 2};//���� ������ ���������������: ��������, ���������,���������� ��������������
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5, Z = 6 };//���� ���������������: V = ����������, F = �������, P =��������, L =�������, S = ����������� ������� Z - ����

	static IDDATATYPE LENGHT_PARAMS[] = { IT::STR };
	static IDDATATYPE LENGHT_POW[] = {IT::INT,IT::INT };
	static IDDATATYPE LENGHT_RAND[] = {IT::INT };
	static IDDATATYPE LENGHT_SIN[] = { IT::INT };
	struct Entry {
		int idxfirstLE;
		char scope[SCOPE_MAXSIZE];
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		struct parm
		{
			IDDATATYPE* types;
			short amount;
			parm(int amount, IDDATATYPE* types)
			{
				this->amount = amount;
				this->types = types;
			}
		};
		union {
			int vint;
			struct {
				char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr;
			struct
			{
				IDDATATYPE* types;
				
				short amount;
			} params;
		} value;
		Entry() = default;
		Entry(int idxfirstLE, const char* scope, const char* id, IDTYPE idtype, int value);
		Entry(int idxfirstLE, const char* scope, const char* id, IDTYPE idtype, double value);
		Entry(int idxfirstLE, const char* scope, const char* id, IDTYPE idtype, const char* value);
		Entry(int idxfirstLE, const char* scope, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
		Entry(int idxfirstLE, const char* scope, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, Entry::parm value);
	};

	struct IdTable {
		int maxsize;
		int size;
		Entry* table;
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, const Entry& entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, const char scope[SCOPE_MAXSIZE], const char id[ID_MAXSIZE]);
	int IsId(IdTable& idtable, const char scope[SCOPE_MAXSIZE], const char id[ID_MAXSIZE], bool lexFlag);
	int IsLiteral(IdTable& idtable, const char literal[TI_STR_MAXSIZE]);
	int IsLiteral(IdTable& idtable, int literal);
	void Delete(IdTable& idtable);
}