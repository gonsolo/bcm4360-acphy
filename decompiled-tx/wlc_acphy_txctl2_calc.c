
uint wlc_acphy_txctl2_calc(undefined8 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  byte bVar4;
  uint *puVar5;
  
  iVar1 = wlc_ratespec_nss(param_2);
  if ((param_2 & 0x3000000) == 0x1000000) {
    uVar2 = param_2 & 0xff;
    goto LAB_00129f3d;
  }
  if ((param_2 & 0x3000000) == 0x2000000) {
    uVar2 = (iVar1 + -1) * 0x10 | param_2 & 0xf;
    goto LAB_00129f3d;
  }
  if ((param_2 & 0x3000000) == 0) {
    bVar4 = (byte)param_2;
    puVar5 = &ofdm_rates;
    uVar2 = param_2;
    if (-1 < (char)(&rate_info)[param_2 & 0xff]) goto LAB_00129f15;
  }
  else {
    uVar2 = wlc_rate_rspec2rate(param_2);
LAB_00129f15:
    bVar4 = (byte)uVar2;
    puVar5 = &cck_rates;
  }
  uVar3 = 0;
  while ((uVar2 = (uint)uVar3, (uVar2 & 0xffff) < *puVar5 &&
         ((*(byte *)((long)puVar5 + (uVar3 & 0xffff) + 4) & 0x7f) != bVar4))) {
    uVar3 = (ulong)(uVar2 + 1);
  }
LAB_00129f3d:
  if ((param_2 & 0x100000) != 0) {
    uVar2 = uVar2 | 0x40;
  }
  return uVar2;
}

