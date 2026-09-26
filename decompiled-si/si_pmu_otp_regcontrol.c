
void si_pmu_otp_regcontrol(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  byte bVar6;
  undefined1 local_48 [24];
  
  if (*(int *)(param_1 + 0x20) < 5) {
    bVar6 = (byte)((*(uint *)(param_1 + 0x24) & 0x1e00000) >> 0x15);
  }
  else {
    bVar6 = (byte)((*(uint *)(param_1 + 0x24) & 0x7c00000) >> 0x16);
  }
  uVar1 = si_coreidx(param_1);
  lVar3 = si_setcoreidx(param_1,0);
  for (iVar5 = 0; (byte)iVar5 < bVar6; iVar5 = iVar5 + 1) {
    osl_snprintf(local_48,0x10,"reg%d",iVar5);
    lVar4 = getvar(0,local_48);
    if (lVar4 != 0) {
      uVar2 = bcm_strtoul(lVar4,0,0);
      osl_writel(iVar5,lVar3 + 0x658);
      osl_writel(uVar2,lVar3 + 0x65c);
    }
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

