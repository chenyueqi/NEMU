#include "ui/ui.h"
#include "nemu.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"common.h"
#include"ui/breakpoint.h"
#include"ui/expr.h"
#include <elf.h>

extern char *strtab;
extern Elf32_Sym *symtab;
extern char nr_symtab_entry;
extern uint8_t num_bw;
int nemu_state = END;

void cpu_exec(uint32_t);
void restart();

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}
	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
	
			fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}

void find_fun_and_print_stack(swaddr_t addr)
{

	int j = 0;
	for(;j<nr_symtab_entry ; j++)
	{
		if(symtab[j].st_info == 0x12)
		{
			if(addr>= symtab[j].st_value && addr <= (symtab[j].st_value + symtab[j].st_size))
			{
				printf("%s\t0x%x\n" , &strtab[symtab[j].st_name],addr);
			}
		}
	}
}

void main_loop() {
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r();}
		else if(strcmp(p, "q") == 0) { return; }
		else if(strcmp(p, "si") ==0)
		{
			if (nemu_state == END)
			restart();
			nemu_state = RUNNING;
			p=strtok(NULL,"");
		  	if(NULL==p)
			{
				cpu_exec(1);
			}
			else
			{
				int n=expr(p);
				int i=0;
				for(;i<n;i++)
					cpu_exec(1);
			}	
			if (nemu_state != END)
					nemu_state = STOP;
		}
		/* TODO: Add more commands */
		else if(strcmp(p, "info")==0)
		{
			p=strtok(NULL," ");
			if('r'==*p)
			{
				printf("eax        0x%X\n",cpu.eax);
				printf("ecx        0x%X\n",cpu.ecx);
				printf("edx        0x%X\n",cpu.edx);
				printf("ebx        0x%X\n",cpu.ebx);
				printf("esp        0x%X\n",cpu.esp);
				printf("ebp        0x%X\n",cpu.ebp);
				printf("esi        0x%X\n",cpu.esi);
				printf("edi        0x%X\n",cpu.edi);

			}
			else if(*p=='b')
			{
				infoutb();
			}
			else if(*p=='w')
			{
				infoutw();
			}
		}
		else if(strcmp(p,"x")==0)
		{
			p=strtok(NULL," ");
			int n=atoi(p);
			p=strtok(NULL,"");
			uint32_t x=0;
			x=expr(p);
			int i=0;
			for(i=0;i<n;i++)
			{
				uint32_t  num;
				num=swaddr_read(x,4);
				printf("0x%X	0x%x\n",x,num);
				x+=4;
			}

		}
		else if(strcmp(p,"b")==0)
		{
		//	p=strtok(NULL," ");
		//	int n=atoi(p);
			p=strtok(NULL,"");
			num_bw++;
			BP* q=new_bp(num_bw,expr(p),'b','\0');
			printf("  breakpoint:	%d    0x%X\n",q->NO,q->address);
		}
		else if(strcmp(p,"bt") == 0)
		{
			swaddr_t addr = cpu.eip;
			uint32_t ebp = cpu.ebp;
			while(ebp != 0)
			{
				find_fun_and_print_stack(addr);
				if(ebp + 4 < 0x8000000)
				{
					addr = swaddr_read(ebp + 4 , 4 );
					ebp = swaddr_read(ebp , 4);
				}
				else
				break;
			}
		}
		else if(strcmp(p,"d")==0)
		{
			p=strtok(NULL," ");
			int n=atoi(p);
			free_bp(n);
		}
		else if(strcmp(p,"w")==0)
		{
//			p=strtok(NULL," ");
//			int n=atoi(p);
			num_bw++;
			p=strtok(NULL,"");
			BP* q=new_bp(num_bw,expr(p),'w',p);
			printf("  watchpoint:	%d    %s\n",q->NO,q->s);
		}
		else if(strcmp(p,"p")==0)
		{
			p=strtok(NULL,"");
			printf("expr= 0x%x\n",expr(p));
		}

		else { printf("Unknown command '%s'\n", p); }
	}
}
