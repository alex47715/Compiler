#pragma once
#pragma once

#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "Parm.h"

#pragma region FST

#define FST_WHILE FST::FST(6, \
	FST::NODE(1, FST::RELATION('w', 1)), \
	FST::NODE(1, FST::RELATION('h', 2)), \
	FST::NODE(1, FST::RELATION('i', 3)), \
	FST::NODE(1, FST::RELATION('l', 4)), \
	FST::NODE(1, FST::RELATION('e', 5)), \
	FST::NODE())



#pragma region INT
#define FST_INT FST::FST(8,\
FST::NODE(1, FST::RELATION('i', 1)),\
FST::NODE(1, FST::RELATION('n', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE(1, FST::RELATION('e', 4)),\
FST::NODE(1, FST::RELATION('g', 5)),\
FST::NODE(1, FST::RELATION('e', 6)),\
FST::NODE(1, FST::RELATION('r', 7)),\
FST::NODE())
#pragma endregion

#pragma region STRING
#define FST_STRING FST::FST(7,\
FST::NODE(1, FST::RELATION('s', 1)),\
FST::NODE(1, FST::RELATION('t', 2)),\
FST::NODE(1, FST::RELATION('r', 3)),\
FST::NODE(1, FST::RELATION('i', 4)),\
FST::NODE(1, FST::RELATION('n', 5)),\
FST::NODE(1, FST::RELATION('g', 6)),\
FST::NODE())
#pragma endregion


#pragma region FUNCTION
#define FST_FUNCTION FST::FST(9,\
FST::NODE(1, FST::RELATION('f', 1)),\
FST::NODE(1, FST::RELATION('u', 2)),\
FST::NODE(1, FST::RELATION('n', 3)),\
FST::NODE(1, FST::RELATION('c', 4)),\
FST::NODE(1, FST::RELATION('t', 5)),\
FST::NODE(1, FST::RELATION('i', 6)),\
FST::NODE(1, FST::RELATION('o', 7)),\
FST::NODE(1, FST::RELATION('n', 8)),\
FST::NODE())
#pragma endregion


#pragma region DECLARE
#define FST_DECLARE FST::FST(8,\
FST::NODE(1, FST::RELATION('d', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('c', 3)),\
FST::NODE(1, FST::RELATION('l', 4)),\
FST::NODE(1, FST::RELATION('a', 5)),\
FST::NODE(1, FST::RELATION('r', 6)),\
FST::NODE(1, FST::RELATION('e', 7)),\
FST::NODE())
#pragma endregion


#pragma region RETURN
#define FST_RETURN FST::FST(7,\
FST::NODE(1, FST::RELATION('r', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE(1, FST::RELATION('u', 4)),\
FST::NODE(1, FST::RELATION('r', 5)),\
FST::NODE(1, FST::RELATION('n', 6)),\
FST::NODE())
#pragma endregion


#pragma region OUT
#define FST_PRINT FST::FST(4,\
FST::NODE(1, FST::RELATION('o', 1)),\
FST::NODE(1, FST::RELATION('u', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE())
#pragma endregion


#pragma region MAIN
#define FST_MAIN FST::FST(5,\
FST::NODE(1, FST::RELATION('m', 1)),\
FST::NODE(1, FST::RELATION('a', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('n', 4)),\
FST::NODE())
#pragma endregion


#pragma region LEFTHESIS
#define FST_LEFTHESIS FST::FST(2,\
FST::NODE(1, FST::RELATION('(', 1)),\
FST::NODE())
#pragma endregion


#pragma region RIGHTHESIS
#define FST_RIGHTHESIS FST::FST(2,\
FST::NODE(1, FST::RELATION(')', 1)),\
FST::NODE())
#pragma endregion


#pragma region SEMICOLON
#define FST_SEMICOLON FST::FST(2,\
FST::NODE(1, FST::RELATION(';', 1)),\
FST::NODE())
#pragma endregion


#pragma region COMMA
#define FST_COMMA FST::FST(2,\
FST::NODE(1, FST::RELATION(',', 1)),\
FST::NODE())
#pragma endregion


#pragma region LEFTBRACE
#define FST_LEFTBRACE FST::FST(2,\
FST::NODE(1, FST::RELATION('{', 1)),\
FST::NODE())
#pragma endregion


#pragma region BRACELET
#define FST_BRACELET FST::FST(2,\
FST::NODE(1, FST::RELATION('}', 1)),\
FST::NODE())
#pragma endregion


#pragma region PLUS
#define FST_PLUS FST::FST(2,\
FST::NODE(1, FST::RELATION('+', 1)),\
FST::NODE())
#pragma endregion


#pragma region MINUS
#define FST_MINUS FST::FST(2,\
FST::NODE(1, FST::RELATION('-', 1)),\
FST::NODE())
#pragma endregion


#pragma region STAR
#define FST_STAR FST::FST(2,\
FST::NODE(1, FST::RELATION('*', 1)),\
FST::NODE())
#pragma endregion

#pragma region EQUALS
#define FST_EQUALS FST::FST(2,\
FST::NODE(1, FST::RELATION('=', 1)),\
FST::NODE())
#pragma endregion

#pragma region EQUALS_ID
#define FST_EQUALS_TWO FST::FST(2,\
FST::NODE(1, FST::RELATION('~', 1)),\
FST::NODE())
#pragma endregion

#pragma region BIGGERTHAN
#define FST_BIGGERTHAN FST::FST(2,\
FST::NODE(1, FST::RELATION('>', 1)),\
FST::NODE())
#pragma endregion


#pragma region SMALLERTHEN
#define FST_SMALLERTHAN FST::FST(2,\
FST::NODE(1, FST::RELATION('<', 1)),\
FST::NODE())
#pragma endregion


#pragma region NOTEQUAL
#define FST_NOTEQUAL FST::FST(2,\
FST::NODE(1, FST::RELATION('!', 1)),\
FST::NODE())
#pragma endregion


#pragma region SMALLEROREQUAL
#define FST_SMALLEROREQUAL FST::FST(2,\
FST::NODE(1, FST::RELATION('#', 1)),\
FST::NODE())
#pragma endregion

#pragma region SQUARE_BRACE

#define FST_LEFT_SQUARE_BRACE FST::FST(2,\
FST::NODE(1, FST::RELATION('[', 1)),\
FST::NODE())

#define FST_RIGHT_SQUARE_BRACE FST::FST(2,\
FST::NODE(1, FST::RELATION(']', 1)),\
FST::NODE())

#pragma endregion

#pragma region BIGGEROREQUAL
#define FST_BIGGEROREQUAL FST::FST(2,\
FST::NODE(1, FST::RELATION('�', 1)),\
FST::NODE())
#pragma endregion



#pragma region IDEN
#define FST_ID FST::FST(2, \
FST::NODE(116,\
FST::RELATION('a', 0), FST::RELATION('a', 1),\
FST::RELATION('b', 0), FST::RELATION('b', 1),\
FST::RELATION('c', 0), FST::RELATION('c', 1),\
FST::RELATION('d', 0), FST::RELATION('d', 1),\
FST::RELATION('e', 0), FST::RELATION('e', 1),\
FST::RELATION('f', 0), FST::RELATION('f', 1),\
FST::RELATION('g', 0), FST::RELATION('g', 1),\
FST::RELATION('h', 0), FST::RELATION('h', 1),\
FST::RELATION('i', 0), FST::RELATION('i', 1),\
FST::RELATION('j', 0), FST::RELATION('j', 1),\
FST::RELATION('k', 0), FST::RELATION('k', 1),\
FST::RELATION('l', 0), FST::RELATION('l', 1),\
FST::RELATION('m', 0), FST::RELATION('m', 1),\
FST::RELATION('n', 0), FST::RELATION('n', 1),\
FST::RELATION('o', 0), FST::RELATION('o', 1),\
FST::RELATION('p', 0), FST::RELATION('p', 1),\
FST::RELATION('q', 0), FST::RELATION('q', 1),\
FST::RELATION('r', 0), FST::RELATION('r', 1),\
FST::RELATION('s', 0), FST::RELATION('s', 1),\
FST::RELATION('t', 0), FST::RELATION('t', 1),\
FST::RELATION('u', 0), FST::RELATION('u', 1),\
FST::RELATION('v', 0), FST::RELATION('v', 1),\
FST::RELATION('w', 0), FST::RELATION('w', 1),\
FST::RELATION('x', 0), FST::RELATION('x', 1),\
FST::RELATION('y', 0), FST::RELATION('y', 1),\
FST::RELATION('z', 0), FST::RELATION('z', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1),\
FST::RELATION('�', 0), FST::RELATION('�', 1)\
),\
FST::NODE())
#pragma endregion


#pragma region STRING_LITERAL
#define FST_STRING_LITERAL FST::FST(3,\
FST::NODE(1, FST::RELATION('\'', 1)),\
FST::NODE(70,\
FST::RELATION('a', 1),\
FST::RELATION('b', 1),\
FST::RELATION('c', 1),\
FST::RELATION('d', 1),\
FST::RELATION('e', 1),\
FST::RELATION('f', 1),\
FST::RELATION('g', 1),\
FST::RELATION('h', 1),\
FST::RELATION('i', 1),\
FST::RELATION('j', 1),\
FST::RELATION('k', 1),\
FST::RELATION('l', 1),\
FST::RELATION('m', 1),\
FST::RELATION('n', 1),\
FST::RELATION('o', 1),\
FST::RELATION('p', 1),\
FST::RELATION('q', 1),\
FST::RELATION('r', 1),\
FST::RELATION('s', 1),\
FST::RELATION('t', 1),\
FST::RELATION('u', 1),\
FST::RELATION('v', 1),\
FST::RELATION('w', 1),\
FST::RELATION('x', 1),\
FST::RELATION('y', 1),\
FST::RELATION('z', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('�', 1),\
FST::RELATION('0', 1),\
FST::RELATION('1', 1),\
FST::RELATION('2', 1),\
FST::RELATION('3', 1),\
FST::RELATION('4', 1),\
FST::RELATION('5', 1),\
FST::RELATION('6', 1),\
FST::RELATION('7', 1),\
FST::RELATION('8', 1),\
FST::RELATION('9', 1),\
FST::RELATION(' ', 1),\
FST::RELATION('\'', 2)\
),\
FST::NODE())
#pragma endregion


#pragma region INTEGER_LITERAL
#define FST_INTEGER_LITERAL FST::FST(2,\
FST::NODE(20,\
FST::RELATION('-', 0), FST::RELATION('0', 1),\
FST::RELATION('1', 0), FST::RELATION('1', 1),\
FST::RELATION('2', 0), FST::RELATION('2', 1),\
FST::RELATION('3', 0), FST::RELATION('3', 1),\
FST::RELATION('4', 0), FST::RELATION('4', 1),\
FST::RELATION('5', 0), FST::RELATION('5', 1),\
FST::RELATION('6', 0), FST::RELATION('6', 1),\
FST::RELATION('7', 0), FST::RELATION('7', 1),\
FST::RELATION('8', 0), FST::RELATION('8', 1),\
FST::RELATION('9', 0), FST::RELATION('9', 1)\
),\
FST::NODE())
#pragma endregion 


#pragma region POW
#define GRAPH_POW FST::FST( 6,\
    FST::NODE(1,FST::RELATION('i',1)),\
	FST::NODE(1,FST::RELATION('n',2)),\
	FST::NODE(1,FST::RELATION('p',3)),\
	FST::NODE(1,FST::RELATION('o',4)),\
	FST::NODE(1,FST::RELATION('w',5)),\
	FST::NODE())
#pragma endregion 


#pragma region RANDOM
#define GRAPH_RANDOM FST::FST(7,\
	FST::NODE(1,FST::RELATION('r',1)),\
	FST::NODE(1,FST::RELATION('a',2)),\
	FST::NODE(1,FST::RELATION('n',3)),\
	FST::NODE(1,FST::RELATION('d',4)),\
	FST::NODE(1,FST::RELATION('o',5)),\
	FST::NODE(1,FST::RELATION('m',6)),\
	FST::NODE())
#pragma endregion



namespace FST {
	struct RELATION {			// �����:������ -> ������� ����� ��������� ��
		char symbol;			// ������ ��������
		short nnode;			// ����� ������� �������

		RELATION(char c = 0x00, short ns = NULL);
	};

	struct NODE {				// ������� ����� ���������
		short n_relation;		// ���������� ����������� �����
		RELATION* relations;	// ����������� �����

		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST {				// ������������������� �������� �������
		short position;			// ������� ������� � �������
		short nstates;			// ���������� ��������� ��������
		NODE* nodes;			// ���� ���������: [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;			// ��������� ��������� �������� �� ������ �������

		FST(short ns, NODE n, ...);
		~FST();
	};

	// ��������� ������������� �������
	bool execute(const char* string, FST& fst);
};