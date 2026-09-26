
void si_pmu_otp_chipcontrol(long param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_48 [24];
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  if (*(int *)(param_1 + 0x20) < 5) {
    uVar6 = (*(uint *)(param_1 + 0x24) & 0x1e000000) >> 0x19;
  }
  else {
    uVar6 = *(uint *)(param_1 + 0x24) >> 0x1b;
  }
  for (uVar5 = 0; uVar5 < uVar6; uVar5 = uVar5 + 1) {
    osl_snprintf(local_48,0x10,"chipc%d",uVar5);
    lVar4 = getvar(0,local_48);
    if (lVar4 != 0) {
      uVar2 = bcm_strtoul(lVar4,0,0);
      osl_writel(uVar5,lVar3 + 0x650);
      osl_writel(uVar2,lVar3 + 0x654);
    }
  }
  si_setcoreidx(param_1,uVar1);
  return;
}

