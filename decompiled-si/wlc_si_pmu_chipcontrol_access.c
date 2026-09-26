
void wlc_si_pmu_chipcontrol_access(long param_1,undefined1 param_2,undefined4 *param_3,char param_4)

{
  undefined8 uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  undefined4 local_40;
  undefined4 local_3c [3];
  
  uVar1 = *(undefined8 *)(*(long *)(param_1 + 0x20) + 0x18);
  lVar3 = si_switch_core(uVar1,0x800,local_3c,&local_40);
  lVar4 = lVar3 + 0x654;
  if (param_4 == '\0') {
    osl_writel(param_2,lVar3 + 0x650);
  }
  else {
    osl_writel(param_2,lVar3 + 0x650);
    osl_writel(*param_3,lVar4);
    lVar4 = lVar3 + 0x65c;
  }
  uVar2 = osl_readl(lVar4);
  *param_3 = uVar2;
  si_restore_core(uVar1,local_3c[0],local_40);
  return;
}

