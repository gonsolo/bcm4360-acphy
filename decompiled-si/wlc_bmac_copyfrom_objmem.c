
void wlc_bmac_copyfrom_objmem
               (undefined8 *param_1,int param_2,long param_3,uint param_4,uint param_5)

{
  undefined2 uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  if (0 < (int)param_4) {
    iVar5 = 0;
    if ((param_5 & 0x40000) == 0) {
      do {
        uVar1 = FUN_001625ca(param_1,iVar5 + param_2,param_5);
        lVar4 = (long)iVar5;
        iVar5 = iVar5 + 2;
        *(char *)(param_3 + lVar4) = (char)uVar1;
        *(char *)(param_3 + 1 + lVar4) = (char)((ushort)uVar1 >> 8);
      } while (iVar5 < (int)param_4);
    }
    else {
      for (; iVar5 < (int)(param_4 & 0xfffffffc); iVar5 = iVar5 + 4) {
        lVar4 = param_1[0x1a];
        tcm_sem_enter(*param_1);
        lVar3 = lVar4 + 0x160;
        osl_writel((uint)(iVar5 + param_2) >> 2 | param_5,lVar3);
        osl_readl(lVar3);
        uVar2 = osl_readl(lVar4 + 0x164);
        tcm_sem_exit(*param_1);
        lVar4 = (long)iVar5;
        *(char *)(param_3 + lVar4) = (char)uVar2;
        *(char *)(param_3 + 1 + lVar4) = (char)((uint)uVar2 >> 8);
        *(char *)(param_3 + 3 + lVar4) = (char)((uint)uVar2 >> 0x18);
        *(char *)(param_3 + 2 + lVar4) = (char)((uint)uVar2 >> 0x10);
      }
      if ((param_4 & 3) != 0) {
        uVar1 = FUN_001625ca(param_1,iVar5 + param_2,param_5);
        *(char *)(param_3 + iVar5) = (char)uVar1;
        *(char *)(param_3 + 1 + (long)iVar5) = (char)((ushort)uVar1 >> 8);
      }
    }
  }
  return;
}

