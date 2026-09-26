
void wlc_bmac_copyto_objmem(undefined8 *param_1,int param_2,long param_3,uint param_4,uint param_5)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  long lVar5;
  long lVar6;
  int iVar7;
  
  if (0 < (int)param_4) {
    iVar7 = 0;
    if ((param_5 & 0x40000) == 0) {
      do {
        FUN_00162c15(param_1,iVar7 + param_2,
                     CONCAT11(*(undefined1 *)(param_3 + 1 + (long)iVar7),
                              *(undefined1 *)(param_3 + iVar7)),param_5);
        iVar7 = iVar7 + 2;
      } while (iVar7 < (int)param_4);
    }
    else {
      for (iVar7 = 0; iVar7 < (int)(param_4 & 0xfffffffc); iVar7 = iVar7 + 4) {
        lVar5 = (long)iVar7;
        bVar1 = *(byte *)(param_3 + 1 + lVar5);
        bVar2 = *(byte *)(param_3 + 2 + lVar5);
        bVar3 = *(byte *)(param_3 + lVar5);
        bVar4 = *(byte *)(param_3 + 3 + lVar5);
        lVar5 = param_1[0x1a];
        tcm_sem_enter(*param_1);
        lVar6 = lVar5 + 0x160;
        osl_writel((uint)(iVar7 + param_2) >> 2 | param_5,lVar6);
        osl_readl(lVar6);
        osl_writel((uint)bVar1 << 8 | (uint)bVar2 << 0x10 | (uint)bVar3 | (uint)bVar4 << 0x18,
                   lVar5 + 0x164);
        tcm_sem_exit(*param_1);
      }
      if ((param_4 & 3) != 0) {
        FUN_00162c15(param_1,iVar7 + param_2,
                     CONCAT11(*(undefined1 *)(param_3 + 1 + (long)iVar7),
                              *(undefined1 *)(param_3 + iVar7)),param_5);
      }
    }
  }
  return;
}

