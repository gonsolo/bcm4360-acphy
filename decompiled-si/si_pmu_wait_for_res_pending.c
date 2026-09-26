
undefined8
si_pmu_wait_for_res_pending(undefined8 param_1,long param_2,uint param_3,char param_4,int *param_5)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  undefined4 local_3c [3];
  
  iVar3 = 0;
  local_3c[0] = 0;
  local_3c[0] = si_pmu_get_pmutimer();
  do {
    iVar1 = osl_readl(param_2 + 0x610);
    if (param_4 == '\x01') {
      if (iVar1 == 0) {
LAB_00112e88:
        uVar2 = 0;
        goto LAB_00112e8a;
      }
    }
    else if (iVar1 != 0) goto LAB_00112e88;
    if (param_3 <= (uint)(iVar3 << 5)) {
      uVar2 = CONCAT71((uint7)(uint3)((uint)(iVar3 << 5) >> 8),1);
LAB_00112e8a:
      *param_5 = iVar3 << 5;
      return uVar2;
    }
    iVar1 = si_pmu_get_pmutime_diff(param_1,param_2,local_3c);
    iVar3 = iVar3 + iVar1;
  } while( true );
}

