
uint wlc_acphy_txctl0_calc(long *param_1,uint param_2,char param_3)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2 & 0x3000000;
  uVar3 = 3;
  if (((uVar2 != 0x2000000) && (uVar3 = 2, uVar2 != 0x1000000)) && (uVar3 = 1, uVar2 == 0)) {
    uVar2 = param_2 & 0x7f;
    if (((uVar2 == 4) || (uVar2 == 2)) || (uVar2 == 0xb)) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)(uVar2 != 0x16);
    }
  }
  if ((byte)(param_3 - 1U) < 2) {
    uVar3 = uVar3 | 0x10;
    piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x18);
    *piVar1 = *piVar1 + 1;
  }
  if ((param_2 & 0x200000) == 0) {
    uVar2 = wlc_stf_d11hdrs_phyctl_txant(param_1,param_2);
    uVar2 = uVar2 | uVar3;
  }
  else {
    uVar2 = (uint)*(byte *)(param_1[0xaa] + 1) << 6 | uVar3 | 8;
  }
  param_2 = param_2 & 0x70000;
  uVar3 = 0xffff8000;
  if ((param_2 != 0x30000) && (uVar3 = 0xffffc000, param_2 != 0x40000)) {
    uVar3 = 0;
    if (param_2 == 0x20000) {
      uVar3 = 0x4000;
    }
  }
  return uVar2 | 4 | uVar3;
}

