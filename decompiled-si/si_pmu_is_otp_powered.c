
byte si_pmu_is_otp_powered(long param_1)

{
  byte extraout_AH;
  undefined4 uVar1;
  uint uVar2;
  long lVar3;
  byte bVar4;
  bool bVar5;
  
  uVar1 = si_coreidx();
  lVar3 = si_setcoreidx(param_1,0);
  uVar2 = *(uint *)(param_1 + 0x3c);
  if (uVar2 == 0x4350) {
LAB_001125f7:
    uVar2 = osl_readl(lVar3 + 0x60c);
    bVar4 = (byte)(uVar2 >> 0xb);
  }
  else if (uVar2 < 0x4351) {
    if (uVar2 == 0x4324) goto LAB_001125f7;
    if (uVar2 < 0x4325) {
      if (uVar2 != 0x4315) {
        if (uVar2 < 0x4316) {
          if (uVar2 != 0x10f6) {
            bVar5 = uVar2 == 0x4314;
            goto LAB_0011255c;
          }
          goto LAB_00112608;
        }
        if (uVar2 != 0x4319) {
          bVar5 = uVar2 == 0x4322;
          goto LAB_0011259d;
        }
      }
    }
    else {
      if (uVar2 == 0x4330) {
LAB_001125d5:
        uVar2 = osl_readl(lVar3 + 0x60c);
        bVar4 = (byte)(uVar2 >> 9);
        goto LAB_00112617;
      }
      if (uVar2 < 0x4331) {
        if (uVar2 == 0x4325) goto LAB_001125e6;
        bVar5 = uVar2 == 0x4329;
      }
      else {
        if (uVar2 == 0x4335) goto LAB_001125f7;
        if (uVar2 == 0x4336) goto LAB_001125d5;
        bVar5 = uVar2 == 0x4334;
      }
LAB_0011255c:
      if (!bVar5) goto LAB_001125d1;
    }
LAB_001125e6:
    uVar2 = osl_readl(lVar3 + 0x60c);
    bVar4 = (byte)(uVar2 >> 10);
  }
  else {
    if (uVar2 != 0xa8df) {
      if (uVar2 < 0xa8e0) {
        if (uVar2 == 0xa886) goto LAB_001125e6;
        if (uVar2 < 0xa887) {
          if (uVar2 == 0x4352) goto LAB_00112608;
          bVar5 = uVar2 == 0x4360;
        }
        else {
          if (uVar2 == 0xa887) goto LAB_001125d5;
          bVar5 = uVar2 == 0xa8d5;
        }
LAB_0011259d:
        if (bVar5) goto LAB_00112608;
      }
      else {
        if (uVar2 < 0xa8ec) {
          if (0xa8e9 < uVar2) goto LAB_001125f7;
          bVar5 = uVar2 == 0xa8e7;
        }
        else {
          if ((uVar2 == 0xa9c4) || (uVar2 == 0xaa06)) goto LAB_00112608;
          bVar5 = uVar2 == 0xa962;
        }
        if (bVar5) goto LAB_001125d5;
      }
LAB_001125d1:
      bVar4 = 1;
      goto LAB_0011261c;
    }
LAB_00112608:
    osl_readl(lVar3 + 0x60c);
    bVar4 = extraout_AH;
  }
LAB_00112617:
  bVar4 = bVar4 & 1;
LAB_0011261c:
  si_setcoreidx(param_1,uVar1);
  return bVar4;
}

