
uint wlc_lcn40phy_iqest_rssi_tempcorr(long param_1,undefined1 param_2,short param_3)

{
  byte bVar1;
  long lVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  
  lVar2 = *(long *)(param_1 + 0x138);
  bVar1 = *(byte *)(param_1 + 0x17e);
  sVar3 = wlc_lcn40phy_tempsense(param_1,param_2);
  iVar4 = wlc_phy_chanspec_bandrange_get(param_1,*(undefined2 *)(param_1 + 0x17e));
  if (iVar4 == 1) {
    if (param_3 == 0) {
      sVar6 = *(short *)(lVar2 + 0x8d2);
      goto LAB_001fa00b;
    }
  }
  else {
    if (iVar4 < 2) {
      if (iVar4 == 0) {
        sVar6 = 0;
        if (param_3 != 0) {
          sVar6 = *(short *)(lVar2 + 0x8c2);
        }
        if (bVar1 < 5) {
          sVar6 = sVar6 + (short)*(undefined4 *)(lVar2 + 0x8bc) + *(short *)(lVar2 + 0x8b6);
          if (param_3 == 0) {
            sVar6 = sVar6 + *(short *)(lVar2 + 0x8c6);
          }
        }
        else if (bVar1 < 10) {
          sVar6 = sVar6 + *(short *)(lVar2 + 0x8be) + (short)*(undefined4 *)(lVar2 + 0x8b8);
          if (param_3 == 0) {
            sVar6 = sVar6 + (short)*(undefined4 *)(lVar2 + 0x8c8);
          }
        }
        else {
          sVar6 = sVar6 + (short)*(undefined4 *)(lVar2 + 0x8c0) + *(short *)(lVar2 + 0x8ba);
          if (param_3 == 0) {
            sVar6 = sVar6 + *(short *)(lVar2 + 0x8ca);
          }
        }
        goto LAB_001fa00b;
      }
LAB_001f9f2b:
      sVar6 = 0;
      goto LAB_001fa00b;
    }
    if (iVar4 == 2) {
      if (param_3 == 0) {
        if (bVar1 < 0x78) {
          sVar6 = (short)*(undefined4 *)(lVar2 + 0x8d0);
        }
        else {
          sVar6 = *(short *)(lVar2 + 0x8ce);
        }
        goto LAB_001fa00b;
      }
    }
    else {
      if (iVar4 != 3) goto LAB_001f9f2b;
      if (param_3 == 0) {
        sVar6 = (short)*(undefined4 *)(lVar2 + 0x8cc);
        goto LAB_001fa00b;
      }
    }
  }
  sVar6 = (short)*(undefined4 *)(lVar2 + 0x8c4);
LAB_001fa00b:
  sVar6 = (sVar3 - *(char *)(lVar2 + 0x8b4)) * sVar6;
  uVar5 = (int)sVar6 >> 0x1f;
  uVar5 = ((int)sVar6 ^ uVar5) - uVar5 >> 8;
  if (sVar6 < 0) {
    uVar5 = -uVar5;
  }
  return uVar5;
}

