#include "sys.h"
#include "usart.h"
#define STARTADDR 0x0800F000
volatile FLASH_Status FLASHStatus = FLASH_BUSY;
void WriteFlashOneWord(uint32_t WriteAddress, uint32_t WriteData)
{ 
	FLASH_UnlockBank1(); 
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	FLASHStatus = 1; //���״ָ̬ʾ��־λ 
	FLASHStatus = FLASH_ErasePage(STARTADDR); 
	if(FLASHStatus == FLASH_COMPLETE) 
	{ 
		FLASHStatus = 1; //���״ָ̬ʾ��־λ 
		FLASHStatus = FLASH_ProgramWord(STARTADDR+WriteAddress, WriteData); //flash.c ��API���� 
	} 
	FLASHStatus = 1; //���״ָ̬ʾ��־λ 
	FLASH_LockBank1(); 
} 
	

void WriteFlashData(uint32_t WriteAddress, uint8_t data[], uint32_t num)
{ 
	uint32_t i = 0; 
	uint16_t temp = 0; 
	FLASH_UnlockBank1(); //����flash 
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	FLASHStatus = 1; //���״ָ̬ʾ��־λ 
	FLASHStatus = FLASH_ErasePage(STARTADDR);//������ҳ 
	if(FLASHStatus == FLASH_COMPLETE)//flash������� 
	{ 
		FLASHStatus = 1; //���״ָ̬ʾ��־λ 
		for(i=0; i<num; i++) { 
				temp = (uint16_t)data[i]; 
				FLASHStatus = FLASH_ProgramHalfWord(STARTADDR+WriteAddress+i*2, temp);//д������ 
		} 
	} 
	FLASHStatus = 1; //���״ָ̬ʾ��־λ 
	FLASH_LockBank1(); //����flash 
} 



int ReadFlashNBtye(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum) {
	int DataNum = 0; 
	ReadAddress = (uint32_t)STARTADDR + ReadAddress; 
	while(DataNum < ReadNum) { 
		*(ReadBuf + DataNum) = *(__IO uint8_t*) 
		ReadAddress++; 
		DataNum++; 
	} 
	return DataNum; 
}

void ReadFlashData(uint32_t ReadAddress, uint8_t *dest_Data, uint32_t num) { 
	int i = 0; 
	ReadAddress = (uint32_t)STARTADDR + ReadAddress; 
	while(i < num) { 
		*(dest_Data+i) = *(__IO uint16_t*) 
		ReadAddress;
		ReadAddress += 2; 
		i++; 
	} 
}


