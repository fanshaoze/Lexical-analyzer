#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;


#define AND         1
#define ARRAY       2
#define BEGIN		3
#define CASE		4
#define CONST		5
#define DIV			6
#define DO			7
#define DOWNTO		8
#define ELSE		9
#define END			10
#define _FILE		11
#define FOR			12
#define FUNC		13
#define GOTO		14
#define IF			15
#define IN			16
#define LABEL		17
#define MOD			18
#define NIL			19
#define NOT			20
#define OF			21
#define OR			22
#define PACKED		23
#define PROC		24
#define PROG		25
#define RECORD		26
#define REPEAT		27
#define SET			28
#define THEN		29
#define TO			30
#define TYPE		31
#define UNTIL		32
#define VAR			33
#define WHILE		34
#define WITH		35
#define INTEGER		36
#define _REAL		37
#define _STRING		38
#define ID			39
#define INT			40
#define REAL		41
#define STRING		42
#define PLUS		43
#define MINUS		44
#define MULTI		45
#define RDIV		46
#define EQ			47
#define LT			48
#define GT			49
#define LE			50
#define GE			51
#define NE			52
#define LR_BRAC		53
#define RR_BRAC		54
#define COMMA		55
#define P_MARK		56
#define F_STOP		57
#define RANGE		58
#define COLON		59
#define ASSIGN		60
#define SEMIC		61
#define CAP			62
#define EXP			63
#define LS_BRAC		64
#define RS_BRAC		65

const char outresult[66][10] = { "",
                                "AND", "ARRAY", "BEGIN", "CASE",
                                "CONST", "DIV", "DO", "DOWNTO",
                                "ELSE", "END", "FILE", "FOR",
                                "FUNCTION", "GOTO", "IF", "IN",
                                "LABEL", "MOD", "NIL", "NOT",
                                "OF", "OR", "PACKED", "PROCEDURE",
                                "PROGRAM", "RECORD", "REPEAT", "SET",
                                "THEN", "TO", "TYPE", "UNTIL",
                                "VAR", "WHILE", "WITH","INTEGER", 
								"_REAL", "_STRING","ID","INTEGER", "_REAL",
								"_STRING","PLUS",
                                "MINUS", "MULTI", "RDIV", "EQ",
                                "LT", "GT", "LE", "GE",
                                "NE", "LR_BRAC", "RR_BRAC", "COMMA",
                                "P_MARK", "F_STOP", "RANGE", "COLON",
                                "ASSIGN", "SEMIC", "CAP", "EXP",
                                "LS_BRAC", "RS_BRAC"};

const char Kwords[39][10] = {
"", "and", "array", "begin", "case",
"const", "div", "do", "downto",
"else", "end", "file", "for",
"function", "goto", "if", "in",
"label", "mod", "nil", "not",
"of", "or", "packed", "procedure",
"program", "record", "repeat", "set",
"then", "to", "type", "until",
"var", "while", "with","integer", "real", "string"};
typedef union {
int    idata;
float  fdata;
char* cdata;
}identifier;
typedef struct
{
    int Typecode;
    identifier data;
}Token;
Token tokens[10000];
void retract(FILE* fp,int index){
    fseek(fp , -1L*index, 1);
}
void tract(FILE* fp,int index){
    fseek(fp , 1L*index , 1);
}
Token gettoken(char* token){
    int flag = 0;
    int i  = 0;
	Token tokendata0;
	tokendata0.data.cdata = new char[20];
    for (i = 1;i<=38;i++){
		//cout<<token<<","<<Kwords[i]<<endl;
        if(strcmp(token,Kwords[i]) == 0){
			
            flag = 1;
			tokendata0.Typecode = i;
			tokendata0.data.cdata = "&";
			break;
        }
    }
    if (flag == 0){
        tokendata0.Typecode = ID;
		//cout<<token<<endl;
		strcpy(tokendata0.data.cdata,token);
		//cout<<tokendata0.data.cdata<<endl;
    }
	//cout<<tokendata0.Typecode<<","<<tokendata0.data.cdata<<endl;
    return tokendata0;
}
int install_num(char* token){
    return  atoi(token);
}
float install_float(char* token){
    return atof(token);
}
void outputword(int index,Token tokens[10000]){
	int typecode0;
	int i = 0;
	for (i = 0;i<index;i++){
		typecode0 = tokens[i].Typecode;
		cout<<"token"<<i<<":"<<outresult[typecode0]<<":"<<tokens[i].Typecode<<",";
		switch(tokens[i].Typecode) {
			case INT:
                cout<<tokens[i].data.idata<<endl;
                break;
            case REAL:
                cout<<tokens[i].data.fdata<<endl;
                break;
            default:
                cout<<tokens[i].data.cdata<<endl;
                break;
		}
	}
}
int main() {
	char* tokenstr;
	int count;
	int lengths;
	int m_typecode;
    Token tokens[10000];
    FILE *fp;
    char* filename;
    int index = 0;
    int i = 0;
	cout<<"please input the file's name:"<<endl;
    filename = "test0.c";
    if ((fp = fopen(filename,"r"))==NULL)
        cout<<"error of file"<<endl;
	char ch = fgetc(fp);
	for (i = 0;i<10000;i++){
		tokens[i].Typecode = 1;
		tokens[i].data.idata = 1;
	}
    while (ch != EOF){
		int length;
		char token[20];
		if (ch == 32 || ch == 9|| ch == 10||ch == 123){
			cout<<ch;
			//tract(fp,1);
			if (ch == 123){
				while(ch != 125){
					ch = fgetc(fp);
				}
				ch = fgetc(fp);
				continue;
			}
			else {
				ch = fgetc(fp);
				continue;
			}
		}
		if (isalpha(ch)){
			length = 0;
			token[length] = ch;
			length += 1;
			token[length] = '\0';
			ch = fgetc(fp);
			while (isalnum(ch)){
				token[length] = ch;
				ch = fgetc(fp);
				length++;
				token[length] = '\0';
			}
			Token tokendata;
			retract(fp,1);
			tokendata = gettoken(token);
			tokens[index].Typecode = tokendata.Typecode;
			tokens[index].data.cdata = new char[20];	
			strcpy(tokens[index].data.cdata,tokendata.data.cdata);
		}
		else {
			int flag;
			if (isdigit(ch)){
				length = 0;
				token[length] = ch;
				length ++;
				token[length] = '\0';
				ch = fgetc(fp);
				flag = 0;
				while (isdigit(ch)||(ch == '.' && flag == 0)){
					if (ch == '.'){
						flag += 1;
					}
					token[length] = ch;
					length ++;
					ch = fgetc(fp);
					token[length] = '\0';
				}
				retract(fp,1);
				if  (flag == 0){
					tokens[index].Typecode = INT;
					tokens[index].data.idata = install_num(token);
				}
				else {
					retract(fp,1);
					tokens[index].Typecode = REAL;
					tokens[index].data.fdata = install_float(token);
				}
			}
			else {
				switch (ch)
				{
					case '+':
							tokens[index].Typecode = PLUS;
							tokens[index].data.cdata = "&";
							break;

					case '-':
							tokens[index].Typecode = MINUS;
							tokens[index].data.cdata = "&";
							break;
					case '*':
						ch = fgetc(fp);
						if (ch == '*') {
							tokens[index].Typecode = EXP;
							tokens[index].data.cdata = "&";
							break;
						}
						else {
							retract(fp,1);
							tokens[index].Typecode = MULTI;
							tokens[index].data.cdata = "&";
							break;
						}
					case '/':
							tokens[index].Typecode = RDIV;
							tokens[index].data.cdata = "&";
							break;
					case '=':
							tokens[index].Typecode = EQ;
							tokens[index].data.cdata = "&";
							break;
					case '<':
						ch = fgetc(fp);
						if (ch == '=') {
							tokens[index].Typecode = LE;
							tokens[index].data.cdata = "&";
							break;
						}
						else if (ch == '>') {
							tokens[index].Typecode = NE;
							tokens[index].data.cdata = "&";
							break;
						}
						else {
							retract(fp,1);
							tokens[index].Typecode = LT;
							tokens[index].data.cdata = "&";
							break;
						}
					case '>':
						ch = fgetc(fp);
						if (ch == '='){
							tokens[index].Typecode = GE;
							tokens[index].data.cdata = "&";
							break;
						}
						else {
							retract(fp,1);
							tokens[index].Typecode = GT;
							tokens[index].data.cdata = "&";
							break;
						}
					case '(':
							tokens[index].Typecode = LR_BRAC;
							tokens[index].data.cdata = "&";
							break;
					case ')':
						tokens[index].Typecode = RR_BRAC;
						tokens[index].data.cdata = "&";
						break;
					case ',':
						tokens[index].Typecode = COMMA;
						tokens[index].data.cdata = "&";
						break;
					case '`':
						tokens[index].Typecode = P_MARK;
						tokens[index].data.cdata = "&";
						break;
					case '.':
						ch = fgetc(fp);
						if (ch == '.') {
							tokens[index].Typecode = RANGE;
							tokens[index].data.cdata = "&";
							break;
						}
						else {
							retract(fp,1);
							tokens[index].Typecode = F_STOP;
							tokens[index].data.cdata = "&";
							break;
						}
					case ':':
						ch = fgetc(fp);
						if (ch == '='){
							tokens[index].Typecode = ASSIGN;
							tokens[index].data.cdata = "&";
							break;
						}
						else {
							retract(fp,1);
							tokens[index].Typecode = COLON;
							tokens[index].data.cdata = "&";
							break;
						}
					case ';':
						tokens[index].Typecode = SEMIC;
						tokens[index].data.cdata = "&";
						break;
		
					case '^':
						tokens[index].Typecode = CAP;
						tokens[index].data.cdata = "&";
						break;
				
					case '[':
						tokens[index].Typecode = LS_BRAC;
						tokens[index].data.cdata = "&";
						break;
					case ']':
						tokens[index].Typecode = RS_BRAC;
						tokens[index].data.cdata = "&";
						break;
					case '\'':
						count = 1;
						lengths = 0;
						ch = fgetc(fp);
						while (ch != '\''){
							count+=1;
							ch = fgetc(fp);
							cout<<ch;
						}
						count+=1;
						retract(fp,count);
						tokenstr = new char[count];
						tokens[index].data.cdata = new char[count];
						for (lengths = 0;lengths < count;lengths++){
							ch = fgetc(fp);
							cout<<ch;
							tokenstr[lengths] = ch;
						}
						tokens[index].Typecode = STRING;
						strcpy(tokens[index].data.cdata,tokenstr);
						cout<<tokens[index].data.cdata<<"string"<<endl;
						break;
					default:
						break;
				}
			}
		}
		
		m_typecode = tokens[index].Typecode;
		cout<<"token"<<index<<":"<<outresult[m_typecode]<<":"<<tokens[index].Typecode<<",";
		switch(tokens[index].Typecode) {
			case INT:
                cout<<tokens[index].data.idata<<endl;
                break;
            case REAL:
                cout<<tokens[index].data.fdata<<endl;
                break;
            default:
                cout<<tokens[index].data.cdata<<endl;
                break;
		}
		index += 1;
		if (ch == EOF){
			break;
		}
		else  ch = fgetc(fp);
	}
	outputword(index,tokens);
	return 0;
}




