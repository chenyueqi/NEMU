#include "common.h"
#include "lib/misc.h"
#include "stdlib.h"
#include "time.h"

#define BLOCK_SIZE 64
#define Way_associate 16
#define set ((4*1024*1024)/ BLOCK_SIZE / Way_associate)
typedef struct 
{
	uint8_t data[BLOCK_SIZE];	
	uint32_t tag;
	bool valid;
	bool dirty;
} LINE;

LINE cache_L2[set][Way_associate];

uint32_t cache_read_L2(hwaddr_t addr , size_t len);
void cache_write_L2(hwaddr_t addr, size_t len , uint32_t data);
static void cache_get_L2(hwaddr_t addr);
static void cache_back_L2(uint16_t set_num , uint8_t line);
extern uint32_t dram_read(hwaddr_t addr,size_t len);
extern void dram_write(hwaddr_t addr,size_t len,uint32_t data);

void init_cache_L2()
{
	int i,j;
	for(i = 0;i<set;i++)
	{
		for(j = 0;j<Way_associate;j++)
		{
			cache_L2[i][j].valid = false;
			cache_L2[i][j].dirty = false;
		}
	}
}

#define ADDR_offset 0x0000003f
#define ADDR_set 0x0002ffc0 
#define ADDR_tag 0xfffd0000
uint32_t cache_read_L2(hwaddr_t addr,size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	uint8_t offset;
	uint16_t set_num;
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
			if((cache_L2[set_num][j].tag == tag)&&(cache_L2[set_num][j].valid == true))
			{
				data += (((uint32_t)cache_L2[set_num][j].data[offset])<<(i*8));
				sign = 0;
			}
		}
		if(sign)
		{

			data += dram_read(addr+i,1)<<(i*8);
			cache_get_L2(addr+i);
		}
	}
	return data ; 
}

void cache_write_L2(hwaddr_t addr, size_t len, uint32_t data)
{
	assert(len == 1 || len ==2 || len == 4 );
	uint8_t offset;
	uint16_t set_num;
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
		int sign = 1;
		for(j = 0;j<Way_associate;j++)
		{
			if((cache_L2[set_num][j].tag == tag) && (cache_L2[set_num][j].valid == true))
			{
				cache_L2[set_num][j].dirty = true;
				cache_L2[set_num][j].data[offset] = temp;
				sign = 0;
			}
		}
		if(sign)
		{
			dram_write(addr+i,1,temp);
			cache_get_L2(addr + i);
		}

	}
}

static void cache_get_L2(hwaddr_t addr)
{
	uint16_t set_num = (addr & ADDR_set)>>6;
	uint32_t tag = addr & ADDR_tag;
	int i;
	uint8_t line;
	srand((unsigned)time(NULL));
	line = rand() % Way_associate;
	if(cache_L2[set_num][line].valid == true)
	{
			cache_back_L2(set_num , line);
	}
	cache_L2[set_num][line].valid = true;
	cache_L2[set_num][line].dirty = false;
	cache_L2[set_num][line].tag = tag;
	for(i = 0 ; i < BLOCK_SIZE ; i++)//copy the block in the main memory
	{
		cache_L2[set_num][line].data[i] = dram_read(tag+(addr & ADDR_set)+i,1);
	}
}

static void cache_back_L2(uint16_t set_num , uint8_t line)
{
	if(cache_L2[set_num][line].dirty == true)
	{
		int i;
		for(i = 0;i < BLOCK_SIZE ; i++)
		{
			dram_write(cache_L2[set_num][line].tag+((uint32_t)set_num<<6)+i,1,cache_L2[set_num][line].data[i]);
		}
	}
}
