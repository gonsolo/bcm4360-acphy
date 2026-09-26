
undefined8 FUN_00168c3d(long param_1)

{
  uint uVar1;
  long lVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  uint uVar9;
  undefined8 extraout_RDX;
  int iVar10;
  uint *puVar11;
  uint *puVar12;
  long lVar13;
  int iVar14;
  uint uVar15;
  uint local_58 [7];
  uint local_3c [3];
  
  puVar11 = &DAT_00510c40;
  puVar12 = local_58;
  for (uVar8 = 7; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  lVar2 = *(long *)(param_1 + 0xd0);
  iVar10 = *(int *)(param_1 + 0x84);
  uVar4 = osl_readl(lVar2 + 0x15c);
  DAT_006f0fb8 = (ushort)(uVar4 >> 1) & 0xffc;
  if ((*(uint *)(param_1 + 0x84) == 0x2c) || (*(uint *)(param_1 + 0x84) < 0x2b)) {
    uVar4 = 0x2a;
  }
  else {
    osl_writew(0x1500,lVar2 + 0x42c);
    osl_writew(0x28ff,lVar2 + 0x42e);
    osl_writew(0x2900,lVar2 + 0x43a);
    osl_writew(0x3cff,lVar2 + 0x43c);
    osl_writew(0x101,lVar2 + 0x406);
    uVar4 = 0x7a;
    osl_writew(1,lVar2 + 0x406);
  }
  DAT_0059c7d0 = DAT_006f0fb8;
  osl_writew(DAT_006f0fb8,lVar2 + 0x542);
  osl_writew(5,lVar2 + 0x540);
  for (iVar14 = 0xd1; (uVar6 = osl_readw(lVar2 + 0x540), (uVar6 & 1) != 0 && (iVar14 != 9));
      iVar14 = iVar14 + -10) {
    osl_delay(10);
  }
  puVar11 = local_58;
  osl_readw(lVar2 + 0x540);
  do {
    uVar1 = *puVar11;
    sVar3 = (short)uVar4;
    uVar9 = uVar4;
    uVar7 = uVar4;
    uVar15 = uVar4;
    if (uVar1 != 7) {
      iVar14 = *(int *)(param_1 + 0x84);
      if ((((iVar14 == 0x2c) || (iVar14 == 0x29)) || (iVar14 == 0x2d)) ||
         ((iVar14 == 0x2e || (uVar15 = 0xb, iVar14 == 0x2f)))) {
        uVar15 = 6;
      }
      sVar3 = DAT_0059c7d0 - sVar3;
      uVar9 = uVar15 * 2;
      uVar7 = (uint)CONCAT62((int6)(uVar8 >> 0x10),
                             *(undefined2 *)
                              (&DAT_00510be0 + ((long)(int)uVar1 + (long)(iVar10 + -0x28) * 6) * 2))
      ;
    }
    puVar11 = puVar11 + 1;
    osl_writew(sVar3,lVar2 + 0x54a);
    uVar8 = (ulong)uVar7;
    osl_writew((short)uVar7,lVar2 + 0x54c,extraout_RDX,uVar8);
    osl_writew(uVar15,lVar2 + 0x520);
    osl_writew((uVar9 - 4) * 0x100 & 0xffff | uVar9,lVar2 + 0x54e);
    osl_writew(0x740c,lVar2 + 0x550);
    osl_writew(uVar1 & 0xffff | 0x10,lVar2 + 0x548);
  } while (puVar11 != local_3c);
  iVar14 = 1;
  iVar10 = 0;
  lVar13 = lVar2 + 0x530;
  do {
    iVar5 = iVar10 + 2;
    osl_writew(iVar10,lVar2 + 0x534);
    if (0x29 < iVar5) {
      iVar5 = 0x29;
    }
    osl_writew((short)iVar5,lVar2 + 0x536);
    osl_writew(iVar5 + iVar14 & 0xffff,lVar2 + 0x532);
    osl_writew((ushort)(iVar10 << 4) | 0x8007,lVar13);
    for (iVar5 = 0xd1; (sVar3 = osl_readw(lVar13), sVar3 != 0 && (iVar5 != 9)); iVar5 = iVar5 + -10)
    {
      osl_delay(10);
    }
    iVar10 = iVar10 + 1;
    iVar14 = iVar14 + -1;
    osl_readw(lVar13);
  } while (iVar10 != 0x2a);
  return 0;
}

