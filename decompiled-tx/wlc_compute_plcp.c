
void wlc_compute_plcp(undefined8 param_1,ulong param_2,uint param_3,uint param_4,byte *param_5)

{
  undefined2 uVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  
  uVar8 = (uint)param_2;
  if ((uVar8 & 0x3000000) == 0x2000000) {
    uVar6 = 0x800006;
    iVar2 = 0x3f;
    if ((param_4 & 0x300) == 0x100) {
      iVar2 = 0;
    }
    uVar4 = uVar8 & 0x70000;
    if ((uVar4 != 0x30000) && (uVar6 = 0x800007, uVar4 != 0x40000)) {
      uVar6 = (uVar4 == 0x20000) + 0x800004;
    }
    if ((param_2 & 0x100000) != 0) {
      uVar6 = uVar6 | 8;
    }
    uVar6 = uVar6 | iVar2 << 4;
    iVar2 = wlc_ratespec_nsts(param_2 & 0xffffffff);
    uVar4 = (iVar2 + -1) * 0x400 | uVar6;
    *param_5 = (byte)uVar6;
    param_5[2] = (byte)(uVar4 >> 0x10);
    param_5[1] = (byte)(uVar4 >> 8);
    uVar6 = (uint)((param_2 & 0xffffffff) >> 0x17) & 1;
    if ((param_2 & 0x400000) != 0) {
      uVar6 = uVar6 | 4;
    }
    uVar6 = uVar6 | (uVar8 & 0xf) << 4;
    uVar1 = (short)uVar6;
    if ((param_2 & 0x200000) != 0) {
      uVar1 = CONCAT11(1,(char)uVar6);
    }
    param_5[3] = (byte)uVar1;
    param_5[4] = (byte)((ushort)uVar1 >> 8) | 2;
    goto LAB_00129ea3;
  }
  bVar7 = (byte)param_2;
  if ((uVar8 & 0x3000000) == 0x1000000) {
    *param_5 = bVar7;
    if ((bVar7 == 0x20) || ((uVar8 & 0x70000) == 0x20000)) {
      *param_5 = bVar7 | 0x80;
    }
    param_5[1] = (byte)param_3;
    param_5[2] = (byte)(param_3 >> 8);
    bVar7 = (-((param_2 & 0x100000) == 0) & 0xf0U) + 0x17;
    if ((param_2 & 0x400000) != 0) {
      bVar7 = bVar7 | 0x40;
    }
    if ((param_2 & 0x800000) != 0) {
      bVar7 = bVar7 | 0x80;
    }
    param_5[3] = bVar7;
  }
  else {
    if (((param_2 & 0x3000000) == 0) && ((char)(&rate_info)[uVar8 & 0xff] < '\0')) {
      bVar7 = (&rate_info)[param_2 & 0xff];
      osl_memset(param_5,0,6);
      iVar2 = (param_3 & 0xfff) << 5;
      param_5[2] = param_5[2] | (byte)((uint)iVar2 >> 0x10);
      *param_5 = bVar7 & 0xf | *param_5 & 0xf0;
      *param_5 = *param_5 | (byte)iVar2;
      param_5[1] = param_5[1] | (byte)((uint)iVar2 >> 8);
      return;
    }
    uVar8 = uVar8 & 0xff;
    if (uVar8 == 4) {
      sVar5 = (short)(param_3 << 2);
LAB_00129e7d:
      bVar3 = 0;
    }
    else {
      if (4 < uVar8) {
        if (uVar8 == 0xb) {
          uVar8 = (param_3 * 0x10) / 0xb;
          sVar5 = (short)uVar8;
          if ((uVar8 & 0xffff) * -0xb + param_3 * 0x10 != 0) {
            sVar5 = sVar5 + 1;
          }
        }
        else {
          if (uVar8 != 0x16) goto LAB_00129e1d;
          uVar8 = (param_3 * 8) / 0xb;
          sVar5 = (short)uVar8;
          if ((uVar8 & 0xffff) * -0xb + param_3 * 8 != 0) {
            sVar5 = (short)(uVar8 + 1);
            bVar3 = 0x80;
            if (7 < (uVar8 + 1 & 0xffff) * 0xb + param_3 * -8) goto LAB_00129e7f;
          }
        }
        goto LAB_00129e7d;
      }
      if (uVar8 == 2) {
        sVar5 = (short)(param_3 << 3);
        goto LAB_00129e7d;
      }
LAB_00129e1d:
      bVar3 = 0;
      sVar5 = 0;
    }
LAB_00129e7f:
    param_5[2] = (byte)sVar5;
    param_5[1] = bVar3 | 4;
    param_5[3] = (byte)((ushort)sVar5 >> 8);
    *param_5 = bVar7 * '\x05';
  }
  param_5[4] = 0;
LAB_00129ea3:
  param_5[5] = 0;
  return;
}

