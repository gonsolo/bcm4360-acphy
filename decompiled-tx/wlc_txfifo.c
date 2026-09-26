
void wlc_txfifo(long *param_1,uint param_2,undefined8 param_3,uint *param_4,char param_5,
               char param_6)

{
  short *psVar1;
  byte bVar2;
  long lVar3;
  long lVar4;
  char *pcVar5;
  ushort *puVar6;
  long *plVar7;
  undefined2 uVar8;
  uint uVar9;
  int iVar10;
  long lVar11;
  uint *puVar12;
  undefined1 local_88 [32];
  ushort *local_68;
  
  lVar11 = osl_pkttag(param_3);
  lVar11 = *(long *)(lVar11 + 0x10);
  lVar3 = *(long *)(lVar11 + 0x18);
  puVar12 = (uint *)osl_pkttag(param_3);
  if ((*(byte *)((long)puVar12 + 7) & 4) == 0) {
    lVar4 = *(long *)(lVar11 + 0x18);
    pcVar5 = *(char **)(lVar4 + 0x338);
    if ((pcVar5[8] != '\0') && (*(char *)(lVar4 + 0x22) != '\0')) {
      if ((*pcVar5 == '\x02') && (*(int *)(pcVar5 + 0x5c) == 0)) {
        if ((pcVar5[10] == '\0') || (pcVar5[0x58] != '\0')) {
          wlc_set_pmstate(lVar4,0);
          wlc_pm2_sleep_ret_timer_start(lVar4);
        }
        else {
          pcVar5[0x58] = '\x01';
        }
      }
      if ((((*(int *)(*param_1 + 0x54) != 0) && ((*(uint *)(lVar11 + 8) & 0x10040) != 0)) &&
          (pcVar5[8] != '\0')) && (pcVar5[10] == '\0')) {
        wlc_get_txh_info(param_1,param_3,local_88);
        if (((*local_68 & 0xfc) == 0x88 || (*local_68 & 0xfc) == 200) && (param_2 < 4)) {
          bVar2 = *(byte *)(lVar11 + 0xed);
          uVar9 = osl_pktprio(param_3);
          if ((bVar2 >> (*(byte *)((long)&wme_fifo2ac + (ulong)(byte)(&prio2fifo)[uVar9]) & 0x1f) &
              1) != 0) {
            if (pcVar5[0x28] == '\0') {
              wlc_set_apsd_stausp(lVar4,1);
            }
            *(uint *)(lVar11 + 8) = *(uint *)(lVar11 + 8) | 0x8000000;
          }
        }
      }
    }
  }
  if ((*puVar12 & 0x200) != 0) {
    *param_4 = puVar12[3];
    puVar6 = *(ushort **)(param_4 + 6);
    if (*(uint *)(*param_1 + 0x14) < 0x28) {
      *puVar6 = *puVar6 | 0x2000;
    }
    else {
      puVar6[1] = puVar6[1] | 0x1000;
    }
    if (*(uint *)(*param_1 + 0x14) < 0x28) {
      uVar8 = **(undefined2 **)(param_4 + 6);
    }
    else {
      uVar8 = (*(undefined2 **)(param_4 + 6))[1];
    }
    *(undefined2 *)((long)param_4 + 6) = uVar8;
  }
  uVar9 = 0xffffffff;
  lVar11 = osl_pkttag(param_3);
  *(undefined8 *)(lVar11 + 0x10) = 0;
  if (param_2 == 4) {
    uVar9 = param_4[1];
  }
  if ((*(int *)(*(long *)(*param_1 + 0x100) + 4) == 1) && ((char)param_1[0xc] != '\0')) {
    FUN_0013c509(param_1,1);
  }
  if (param_5 != '\0') {
    psVar1 = (short *)(param_1[7] + 0x38 + (ulong)param_2 * 2);
    *psVar1 = *psVar1 + (short)param_6;
  }
  if ((short)uVar9 != -1) {
    wlc_bmac_write_shm(param_1[4],0xa8,uVar9 & 0xffff);
  }
  if ((((*(int *)(*param_1 + 0x14) == 0x2c) || (*(int *)(*param_1 + 0x14) == 0x29)) &&
      (lVar11 = param_1[4], (*(byte *)(lVar11 + 0x16b) & 4) == 0)) &&
     ((*(byte *)(lVar11 + 0x170) & 0x20) == 0)) {
    wlc_ucode_wake_override_set(lVar11,0x20);
  }
  plVar7 = *(long **)(param_1[5] + (ulong)param_2 * 8);
  iVar10 = (**(code **)(*plVar7 + 0x40))(plVar7,param_3,param_5);
  if ((iVar10 < 0) && (param_5 != '\0')) {
    psVar1 = (short *)(param_1[7] + 0x38 + (ulong)param_2 * 2);
    *psVar1 = *psVar1 - (short)param_6;
  }
  iVar10 = *(int *)(*(long *)(*param_1 + 0x100) + 0x3c);
  if ((((iVar10 == 0x4352) || (iVar10 == 0x4331)) || (iVar10 == 0x4360)) &&
     (**(char **)(lVar3 + 0x338) != '\0')) {
    osl_readl(param_1[3] + 0x120);
  }
  return;
}

