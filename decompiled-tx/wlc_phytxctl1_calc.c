
uint wlc_phytxctl1_calc(long param_1,ulong param_2,ushort param_3)

{
  long lVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  lVar1 = *(long *)(param_1 + 0x58 + (-(ulong)((param_3 & 0xc000) == 0) & 0xfffffffffffffff8));
  uVar6 = (uint)param_2;
  sVar3 = (short)*(undefined4 *)(lVar1 + 8);
  if ((sVar3 != 8) && (sVar3 != 5)) {
    if ((uVar6 & 0x70000) != 0x10000) {
      if ((uVar6 & 0x70000) != 0x20000) {
        osl_printf("rspec 0x%08x\n");
      }
      if (((int)(param_2 & 0xff) == 0x20) ||
         (((param_2 & 0x3000000) == 0 && ((char)(&rate_info)[param_2 & 0xff] < '\0')))) {
        uVar9 = 5;
      }
      else {
        uVar9 = 4;
      }
      goto LAB_00131f7c;
    }
    if (((param_3 & 0x3800) == 0x1800) &&
       (uVar5 = wlc_phy_chanspec_get(*(undefined8 *)(*(long *)(param_1 + 0x40) + 0x10)),
       (uVar5 & 0x700) == 0x100)) {
      uVar9 = 3;
      uVar5 = wlc_phy_chanspec_get(*(undefined8 *)(*(long *)(param_1 + 0x40) + 0x10));
      if ((uVar5 & 0x3800) == 0x1800) goto LAB_00131f7c;
    }
  }
  uVar9 = 2;
LAB_00131f7c:
  sVar3 = (short)*(undefined4 *)(lVar1 + 8);
  if (sVar3 == 7) {
    uVar4 = wlc_stf_spatial_expansion_get(param_1,param_2 & 0xffffffff);
    bVar2 = wlc_stf_get_pwrperrate(param_1,param_2 & 0xffffffff,uVar4);
    uVar6 = (uint)bVar2 << 3 | (uint)uVar4 << 10;
  }
  else if ((uVar6 & 0x3000000) == 0x1000000) {
    uVar6 = 3;
    if ((7 < (int)(param_2 & 0xff) - 8U) && (uVar6 = 1, (param_2 & 0x300) == 0)) {
      uVar6 = ~-(uint)((param_2 & 0x100000) == 0) & 2;
    }
    uVar6 = uVar6 << 3;
    uVar9 = uVar9 | (uint)(byte)(&DAT_00593ac0)[(param_2 & 0xff) * 0x14] << 8;
  }
  else {
    if ((((param_2 & 0x3000000) == 0) &&
        ((((uVar6 = uVar6 & 0x7f, uVar6 == 4 || (uVar6 == 2)) || (uVar6 == 0xb)) || (uVar6 == 0x16))
        )) && (((sVar3 != 5 && (sVar3 != 6)) && (sVar3 != 8)))) {
      return uVar9;
    }
    iVar7 = wlc_rate_legacy_phyctl(param_2 & 0xff);
    iVar8 = 0;
    if ((short)iVar7 != -1) {
      iVar8 = iVar7;
    }
    uVar6 = iVar8 << 8;
    uVar9 = uVar9 | (uint)((param_2 & 0x300) != 0) << 3;
  }
  return uVar6 | uVar9;
}

