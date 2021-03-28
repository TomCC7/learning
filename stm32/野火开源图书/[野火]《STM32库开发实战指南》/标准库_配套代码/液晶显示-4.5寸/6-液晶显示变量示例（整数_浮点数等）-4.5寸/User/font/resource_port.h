#ifndef __GUI_RESOURCE_PORT_H
#define	__GUI_RESOURCE_PORT_H

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif  

typedef int         BOOL;

/* ��Դ���ڵĻ���ַ */
#define GUI_RES_BASE             4096

/* �洢��FLASH�е���ԴĿ¼��С */
#define GUI_CATALOG_SIZE         (8*1024)
  
/* Ŀ¼��Ϣ���� */
typedef struct 
{
	char 	name[40];  /* ��Դ������ */
	u32  	size;      /* ��Դ�Ĵ�С */ 
	u32 	offset;    /* ��Դ����ڻ���ַ��ƫ�� */
}CatalogTypeDef;


/* ���ڱ���Ƿ�����Դ�ļ��޷��ҵ� */
extern BOOL res_not_found_flag;

BOOL RES_DevRead(u8 *buf,u32 addr,u32 size);
int RES_DevEraseSector(u32 addr);
void RES_DevTest(void);

s32 RES_GetOffset(const char *res_name);
s32 RES_GetInfo_AbsAddr(const char *res_name, CatalogTypeDef *dir);

#ifdef	__cplusplus
}
#endif
#endif /* __GUI_RESOURCE_PORT_H */
