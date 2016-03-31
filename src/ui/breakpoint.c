#include "ui/breakpoint.h"
#include"ui/expr.h"

#include "nemu.h"

#define NR_BP 32

uint8_t num_bw = 0 ;

static BP bp_pool[NR_BP];
static BP *head, *free_;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].type='b';
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
		bp_pool[i].address=0xffffffff;
		bp_pool[i].content=0xff;
		bp_pool[i].val=0;
	}
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
}
BP* new_bp(int num,uint32_t baddress,char c,char *s)
{
	if(free_->next==NULL)
	{
		assert(0);
	}
	else if(head==NULL)
	{
		assert(head==NULL);
		head=&bp_pool[0];
		free_=head->next;
		head->next=NULL;
		head->NO=num;
		head->type=c;
		if(head->type=='b')
		{
			head->address=baddress;
			if(swaddr_read(baddress,1) != 0)
			{
				head->content=swaddr_read(baddress,1);
				swaddr_write(baddress,1,0xcc);
			}
		}
		else if(head->type=='w')
		{
			strcpy(head->s,s);
			head->val=expr(head->s);
		}
		return head;
	}
	else
	{
		BP* p=head;
		BP* p1=head;
		while(p!=NULL)
		{
			if(p->address==baddress&&p->type==c&&c=='b')
				assert(0);
			if(p->NO==num)
			{
				p->type=c;
				if(p->type=='b')
				{
					p->address=baddress;
					if(swaddr_read(baddress,1) != 0)
					{
						p->content=swaddr_read(baddress,1);
						swaddr_write(baddress,1,0xcc);
					}
				}
				else if(p->type=='w')
				{
					strcpy(p->s,s);
					p->val=expr(p->s);
				}
				return p;
			}
			p1=p;
			p=p->next;
		}
		p1->next=free_;
		p1=free_;
		free_=free_->next;
		p1->next=NULL;
		p1->NO=num;
		p1->type=c;
		if(p1->type=='b')
		{
			p1->address=baddress;
			if(swaddr_read(baddress,1) != 0)
			{
				p1->content=swaddr_read(baddress,1);
				swaddr_write(baddress,1,0xcc);
			}
		}
		else if(p1->type=='w')
		{
			strcpy(p1->s,s);
			p1->val=expr(p1->s);
		}
		return p1;
	}
}

void free_bp(int num)
{
	if(head==NULL)
	{
		assert(0);
	}
	BP* p=head;
	if(p->next==NULL)
	{
		swaddr_write(p->address,1,p->content);
		init_bp_pool();
	}
        else	
	{
		while(p->next!=NULL)//maybe some bug here
	{
		if(p->next->NO==num)
		{
			BP* bp;
			bp=p->next;
			swaddr_write(bp->address,1,bp->content);
			p->next=bp->next;
			bp->next=free_;
			free_=bp;
			break;
		}
		p=p->next;
	}
	}
}
BP*  bfind(swaddr_t e,char c)
{
	BP* p=head;
	while(p!=NULL)
	{
		if(p->address==e&&p->type==c)
		break;
		p=p->next;
	}

		return p;
}
void infoutb()
{
	BP* p=head;
	while(p!=NULL)
	{
		if(p->type=='b')
		{
			printf("  breakpoint  %d  0X%X   0x%x\n",p->NO,p->address,p->content);
		}
		p=p->next;
	}
}

void reset_b()
{
	BP *p=head;
	while(p!=NULL)
	{
		if(p->type == 'b')
		{
			if(swaddr_read(p->address,1) != 0)
				if(swaddr_read(p->address,1) !=0xcc)
				{
					p->content = swaddr_read(p->address,1);
					swaddr_write(p->address,1,0xcc);
				}
		}
		p = p->next;
	}

}

void infoutw()
{
	BP* p=head;
	while(p!=NULL)
	{
		if(p->type=='w')
		{
			printf("  watchpoint   %d    %s\n",p->NO,p->s);
		}
		p=p->next;
	}
}

bool checkw()
{
	BP* p=head;
	while(p!=NULL)
	{
		if(p->type=='w')
		{
			if(expr(p->s)!=p->val)			
			{
				printf("the watchpoint report: NO.%d change from 0x%X to 0x%X expr:%s\n",p->NO,p->val,expr(p->s),p->s);
				p->val=expr(p->s);
				return true;
			}	
		}
		p=p->next;
	}
	return false;
}
/* TODO: Implement the function of breakpoint */
