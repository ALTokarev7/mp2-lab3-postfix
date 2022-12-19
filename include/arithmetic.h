// ���������� ������� � ������� ��� ���������� �������������� ���������
#define _USE_MATH_DEFINES
#include"stack.h"
#include<string>
#include<vector>
#include<map>
#include<functional>
#include<cmath>
#include<utility>


enum PRIORITY { SKOB = 0, ADD_SUB, MUL_DIV, UNMIN, POW, FUNC };

class Lexem
{
protected:
	string repr;
	pair<int, int> pos;
public:
	Lexem(string repr, pair<int, int> pos)
	{
		this->repr = repr;
		this->pos = pos;
	}

	const pair<int, int>& getPos() { return pos; }

	~Lexem() = default;

	virtual const string& show() = 0;

	virtual const bool isOperand() = 0;
};

class Operation : public Lexem
{
private:
	int prt;
public:
	Operation(string repr, int prt, pair<int, int> pos) : Lexem(repr, pos) { this->prt = prt; }

	~Operation() = default;

	const int priority() { return prt; }

	virtual const string& show() { return this->repr; }

	virtual const bool isOperand() { return false; }
};

class Operand : public Lexem
{
protected:
	const double value;
public:
	Operand(string repr, double val, pair<int, int> pos) : Lexem(repr, pos), value(val) {}

	~Operand() = default;

	virtual const string& show() { return this->repr; }

	virtual const bool isOperand() { return true; }

	virtual const double getValue() = 0;
};

class Const : public Operand
{
public:
	Const(string repr, double value, pair<int, int> pos) : Operand(repr, value, pos) {}

	~Const() = default;

	virtual const string& show() { return this->repr; }

	virtual const bool isOperand() { return true; }

	virtual const double getValue() { return this->value; }
};

class Var : public Operand
{
private:
	map<char, double>& values;
public:
	Var(string repr, map<char, double>& vals, pair<int, int> pos) : Operand(repr, 0.0, pos), values(vals) {}

	~Var() = default;

	virtual const string& show() { return this->repr; }

	virtual const bool isOperand() { return true; }

	virtual const double getValue() { return values[this->repr[0]]; }
};

class TPostfix
{
private:
	//�������� ���������
	string inputStr;
	vector<Lexem*> lexemVec;

	//��������������� ��������� ��� ��������: ������ ���������� � �� ��������, �������
	string vars;
	map<char, double> varsValues;
	map<string, function<double(double)>> funcs;

	//��������������� �������
	double stringToDouble(string numStr);

	Operand* applyOperation(Lexem* op, Operand* first, Operand* second);

	Operand* applyPrefFun(Lexem* fun, Operand* operand);

	void fillFuncsMap();

	// �������� ������������ ��������� (������� ���������� ������)
	void inputCheck();

	//�������� ������
	void inputToLexem();

	void lexemToPostfix();

	double calculatePostfix();

public:
	TPostfix(string expr);

	~TPostfix() = default;

	string getInputStr() { return inputStr; }

	string getPostfixStr();

	double calculate();
};

