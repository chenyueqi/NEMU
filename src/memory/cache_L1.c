#include "common.h"
#include "lib/misc.h"
#include "stdlib.h"
#include "time.h"

#define BLOCK_SIZE 64
#define Way_associate 8
#define set ((64*1024)/ BLOCK_SIZE / Way_associate)
typedef struct 
{
	uint8_t data[BLOCK_SIZE];	
	uint32_t tag;
	bool valid;
} LINE;

LINE cache_L1[set][Way_associate];

uint32_t cache_read_L1(hwaddr_t addr , size_t len);
void cache_write_L1(hwaddr_t addr, size_t len , uint32_t data);
static void cache_get_L1(hwaddr_t addr);
extern uint32_t dram_read(hwaddr_t addr,size_t len);
extern void dram_write(hwaddr_t addr,size_t len,uint32_t data);
extern uint32_t cache_read_L2(hwaddr_t addr, size_t len);
extern uint32_t cache_write_L2(hwaddr_t addr, size_t len , uint32_t data);

void init_cache_L1()
{
	int i,j;
	for(i = 0;i<set;i++)
	{
		for(j = 0;j<Way_associate;j++)
		{
			cache_L1[i][j].valid = false;
		}
	}
}

#define ADDR_offset 0x0000003f
#define ADDR_set 0x00001fc0 
#define ADDR_tag 0xffffe000
uint32_t cache_read_L1(hwaddr_t addr,size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	uint8_t offset;
	uint8_t set_num;
	uint32_t tag;
	int i;
	uint32_t data = 0;
	for(i = 0 ; i<len ;i++)
	{
		offset = (addr+i) & ADDR_offset;
		set_num = ((addr+i) & ADDR_set)>>6;
		tag = (addr+i) & ADDR_tag;

		int j;
		bool sign = 1;
		for(j = 0;j<Way_associate;j++)
		{
			if((cache_L1[set_num][j].tag == tag)&&(cache_L1[set_num][j].valid == true))
			{
				data += (((uint32_t)cache_L1[set_num][j].data[offset])<<(i*8));
				sign = 0;
			}
		}
		if(sign)
		{
			data += cache_read_L2(addr+i,1)<<(i*8);
			cache_get_L1(addr+i);
		}
	}
	return data ; 
}

void cache_write_L1(hwaddr_t addr, size_t len, uint32_t data)
{
	assert(len == 1 || len ==2 || len == 4 );
	uint8_t offset;
	uint8_t set_num;
	uint32_t tag;
	uint8_t temp;
	int i;
	for(i = 0;i<len;i++)
	{
		temp = data;
		data = data>>8;

		offset = (addr+i) & ADDR_offset;
		set_num = ((addr+i) & ADDR_set)>>6;
		tag = (addr+i) & ADDR_tag;
		int j;
		for(j = 0;j<Way_associate;j++)
		{
			if((cache_L1[set_num][j].tag == tag) && (cache_L1[set_num][j].valid == true))
			{
				cache_L1[set_num][j].data[offset] = temp;
			}
		}
		cache_write_L2(addr+i , 1 ,temp);
	}
}

static void cache_get_L1(hwaddr_t addr)
{
	uint8_t set_num = (addr & ADDR_set)>>6;
	uint32_t tag = addr & ADDR_tag;
	int i;
	uint8_t line;
	srand((unsigned)time(NULL));
	line = rand() % Way_associate;
	cache_L1[set_num][line].valid = true;
	cache_L1[set_num][line].tag = tag;
	for(i = 0 ; i < BLOCK_SIZE ; i++)//copy the block in the main memory
	{
		cache_L1[set_num][line].data[i] = cache_read_L2(tag+(addr&ADDR_set)+i,1);
	}
}
