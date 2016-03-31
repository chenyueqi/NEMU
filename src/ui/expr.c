#include "common.h"
#include<stdlib.h>
#include"nemu.h"
#include <elf.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
extern char *strtab;
extern Elf32_Sym *symtab;
extern int nr_symtab_entry;
enum {
	OR, AND,//priority 0,1
	BIT_OR,BIT_XOR,BIT_AND,BIT_NOT,//priority 2,3,4,5
	NE,EQ,LE,LS,GE,GT,//6,7,8,9,10,11
	RSHIFT,LSHIFT,//12,13
	ADD,SUB,//14,15
	MUL,DIV,MOD,//16,17,18
	NOT,POINTER,NEG,//19,20,21
	LP,RP,//22,23
	NUM,HEX,REG,TOK,//24,25,26,27
	NOTYPE//28


	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{"\\*",MUL},
	{" +",	NOTYPE},				// white space
	{"\\+", ADD},					// plus
	{"-",SUB},
	{"/",DIV},
	{"%",MOD},
	{"\\(",LP},
	{"\\)",RP},
	{"0x[0-9a-fA-F]+",HEX},
	{"[0-9]+",NUM},
	{"\\$(eax|ecx|edx|ebx|esp|ebp|esi|edi|eip|ax|cx|dx|bx|al|ah|cl|ch|dl|dh|nl|bh|eflags|es|cs|ss|ds|)",REG},
	{"[a-z0-9A-Z_]+", TOK},
	{">>",RSHIFT},
	{"<<",LSHIFT},
	{">=",GE},
	{"<=",LE},
	{">",GT},
	{"<",LS},
	{"!=",NE},
	{"&&",AND},
	{"\\|\\|",OR},
	{"!",NOT},
	{"~",BIT_NOT},
	{"&",BIT_AND},
	{"\\^",BIT_XOR},
	{"\\|",BIT_OR},
	{"==", EQ}						// equal
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];
/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') 
	{
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) 
		{
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) 
			{
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */
				switch(rules[i].token_type) 
				{
					case NOTYPE:break;//space will be ignored
						   
					default: 
						    if(substr_len<32)
							    strncpy(tokens[nr_token].str,substr_start,substr_len+1);
						    else 
						    {
							    Log("too long num");
							    return false;
						    }
						    tokens[nr_token++].type=rules[i].token_type;
						 break;
				}
				break;
			}
		}
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	return true; 
}
bool check_parentheses(int p,int q)
{
	if(tokens[p].type==LP&&tokens[q].type==RP)
	{
		int i=0;
		int po;
		for(po=p;po<=q;po++)
		{
			if(tokens[po].type==LP)
				i++;
			else if(tokens[po].type==RP)
				i--;
			if(i<0)
				return false;
		}
		if(i==0) 
		{
			return true;
		}
		else return false;
	}
	else return false;
}
int dominate_operate(int p,int q)
{
	int po;
	int do_po=p;
	for(po=p;po<=q;po++)
	{
		if(tokens[po].type<=tokens[do_po].type)
		{
			do_po=po;
		}
	}
	if(tokens[do_po].type==5||tokens[do_po].type==19||tokens[do_po].type==20||tokens[do_po].type==21)
	{
		for(po=p;po<q;po++)
		{
			if(tokens[po].type==tokens[do_po].type)
				do_po=po;
		}
	}
	return do_po;
}
int eval(int p,int q)
{
	int val=0;
	int j;
	if(p>q)
		assert(0);
	
	else if(p==q)
	{
		char *rec=NULL;
		char temp[5];
		switch(tokens[p].type)
		{
			case NUM:
				return atoi(tokens[p].str);break;
			case HEX:
				return strtoll(tokens[p].str,&rec,16);break;
			case REG:
			strcpy(temp,tokens[p].str);
			if(!strcmp(temp,"$eax"))return cpu.eax;
			else if(!strcmp(temp,"$ecx")) return cpu.ecx;
			else if(!strcmp(temp,"$edx")) return cpu.edx;
			else if(!strcmp(temp,"$ebx")) return cpu.ebx;
			else if(!strcmp(temp,"$esp")) return cpu.esp;
			else if(!strcmp(temp,"$eip")) return cpu.eip;
			else if(!strcmp(temp,"$edi")) return cpu.edi;
			else if(!strcmp(temp,"$esi")) return cpu.esi;
			else if(!strcmp(temp,"$ebp")) return cpu.ebp;

			else if(!strcmp(temp,"$al")) return reg_w(R_AX);
			else if(!strcmp(temp,"$ah")) return reg_w(R_AH);
			else if(!strcmp(temp,"$bl")) return reg_w(R_BL);
			else if(!strcmp(temp,"bh")) return reg_w(R_BH);
			else if(!strcmp(temp,"cl")) return reg_w(R_CL);
			else if(!strcmp(temp,"ch")) return reg_w(R_CH);
			else if(!strcmp(temp,"$dl")) return reg_w(R_DL);
			else if(!strcmp(temp,"$dh")) return reg_w(R_DH);
			else if(!strcmp(temp,"$eflags")) return cpu.EFLAGS;
			else if(!strcmp(temp,"$es")) return cpu.es;
			else if(!strcmp(temp,"$cs")) return cpu.cs;
			else if(!strcmp(temp,"$ss")) return cpu.ss;
			else if(!strcmp(temp,"$ds")) return cpu.ds;
			case TOK:
			for(j = 0;j < nr_symtab_entry ; j++)
			{
				//if(symtab[j].st_info == 0x11)
				//{
					if(!strcmp (&strtab[symtab[j].st_name] , tokens[p].str))
						return symtab[j].st_value;
				//}
				//else if(symtab[j].st_info == 0x12)
				//{
			//		if(!strcmp (&strtab[symtab[j].st_name] , tokens[p].str))
			//			return symtab[j].st_value;
			//	}
			}

		}
	}
	else if(check_parentheses(p,q)==true)
		return eval(p+1,q-1);
	else
	{
		int val1=0;
		int val2=0;
		int op=dominate_operate(p,q);
		if(tokens[op].type==NEG)
		{
			if(op!=0)
			{
				op--;
				val1=eval(p,op-1);
				val2=-eval(op+2,q);
			}
			else 
			{
				val=-eval(op+1,q);
			}
		}
		else if(tokens[op].type==POINTER)
		{
			if(op!=0)
			{
				op--;
				val1=eval(p,op-1);
				val2=swaddr_read(eval(op+2,q),4);
			}
			else
				val=swaddr_read(eval(op+1,q),4);
		}
		else if(tokens[op].type==NOT)
		{
			if(op!=0)
			{
				op--;
				val1=eval(p,op-1);
				val2=!eval(op+2,q);
			}
			else 
				val=!eval(op+1,q);
		}
		else if(tokens[op].type==BIT_NOT)
		{
			if(op!=0)
			{
				op--;
				val1=eval(p,op-1);
				val2=~eval(op+2,q);
			}
			else val=~eval(op+1,q);
		}
		else
		{
		val1=eval(p,op-1);
		val2=eval(op+1,q);
		switch(tokens[op].type)
		{
			case ADD: val= val1+val2; break;
			case SUB: val= val1-val2; break;
			case MUL: val= val1*val2; break;
			case DIV:
				  if(val2==0) 
					  assert(0);
				   else  
					val=   val1/val2;
					  break;
			case RSHIFT: val= val1>>val2; break;
			case LSHIFT: val= val1<<val2; break;
			case LS: val= val1<val2; break;
			case GT: val= val1>val2; break;	  
			case GE: val= val1>=val2; break;
			case LE: val= val1<=val2; break;
			case NE: val= val1!=val2; break;
			case EQ:  val= val1== val2; break;
			case BIT_AND: val= val1&val2; break;
			case BIT_XOR: val= val1^val2; break;
			case BIT_OR: val= val1|val2; break;
			case AND: val= val1&&val2; break;
			case OR: val= val1||val2; break;

		}
		}
	
	}
	return val;
}

uint32_t expr(char *e/*, bool *success*/) {
	if(!make_token(e)) {
		//*success = false;
		return 0;
	}
	int i;
	for(i=0;i<nr_token;i++)
	{
		if(tokens[i].type==MUL&&((i==0)||tokens[i-1].type<RP))
		{
			tokens[i].type=POINTER;
		}
		if(tokens[i].type==SUB&&((i==0)||tokens[i-1].type!=RP))
		{
			tokens[i].type=NEG;
		}
	}
	return eval(0,nr_token-1);
}

