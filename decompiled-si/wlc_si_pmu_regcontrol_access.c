
void wlc_si_pmu_regcontrol_access(long param_1,byte param_2,uint *param_3,char param_4)

{
  undefined8 uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  undefined4 local_30;
  undefined4 local_2c;
  
  uVar2 = (uint)param_2;
  uVar1 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18);
  lVar3 = si_switch_core(uVar1,0x800,&local_2c,&local_30);
  lVar4 = lVar3 + 0x658;
  if (param_4 != '\0') {
    osl_writel(uVar2,lVar4);
    uVar2 = *param_3;
    lVar4 = lVar3 + 0x65c;
  }
  osl_writel(uVar2,lVar4);
  uVar2 = osl_readl(lVar3 + 0x65c);
  *param_3 = uVar2;
  si_restore_core(uVar1,local_2c,local_30);
  return;
}

