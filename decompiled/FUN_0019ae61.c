
void FUN_0019ae61(long param_1)

{
  long lVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  char cVar7;
  ushort uVar8;
  uint uVar9;
  char cVar10;
  byte bVar11;
  undefined1 uVar12;
  char cVar13;
  uint uVar14;
  uint uVar15;
  short sVar16;
  byte bVar17;
  
  lVar1 = *(long *)(param_1 + 0x138);
  bVar2 = 1;
  if ((*(byte *)(lVar1 + 0x910) & (*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) == 0) {
    bVar2 = (*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000 & *(byte *)(lVar1 + 0x911);
  }
  uVar8 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    *(undefined1 *)(lVar1 + 0x650) = 0x2b;
    *(undefined1 *)(lVar1 + 0x651) = 0x2b;
    *(undefined1 *)(lVar1 + 0x652) = 0x2b;
    *(undefined1 *)(lVar1 + 0x653) = 0x34;
    *(undefined1 *)(lVar1 + 0x655) = 100;
    *(undefined1 *)(lVar1 + 0x654) = 0x34;
    bVar3 = *(byte *)(lVar1 + 0x340);
  }
  else {
    *(undefined1 *)(lVar1 + 0x650) = 0x2f;
    *(undefined1 *)(lVar1 + 0x651) = 0x2f;
    *(undefined1 *)(lVar1 + 0x652) = 0x2f;
    *(undefined1 *)(lVar1 + 0x653) = 0x34;
    *(undefined1 *)(lVar1 + 0x655) = 100;
    *(undefined1 *)(lVar1 + 0x654) = 0x34;
    bVar3 = *(byte *)(lVar1 + 0x341);
  }
  bVar17 = *(byte *)(*(long *)(param_1 + 0x138) + 0x66e);
  *(byte *)(lVar1 + 0x65c) = bVar17;
  bVar11 = bVar3 & bVar17;
  bVar17 = (bVar17 | 1) & bVar3;
  if (bVar17 != 0) {
    bVar3 = 0xf;
    uVar12 = 0xf;
  }
  else {
    bVar3 = (-(bVar3 == 0) & 0xf1U) + 0x1e;
    uVar12 = (undefined1)(bVar3 + 0x23 >> 1);
  }
  uVar15 = 0;
  do {
    if (*(byte *)(param_1 + 0x168) <= (byte)uVar15) {
      phy_reg_mod(param_1,0x19e,2,uVar8 & 2);
      return;
    }
    uVar14 = uVar15 & 0xff;
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa7) >> (uVar15 & 0x1f) & 1) != 0) {
      sVar16 = (short)(uVar15 << 9) + 0x6dc;
      phy_reg_read(param_1,sVar16);
      FUN_0019ac69(param_1,0,0x45,bVar11,uVar14);
      cVar4 = FUN_0019ac69(param_1,1,0x30,bVar11,uVar14);
      cVar5 = FUN_0019ac69(param_1,2,0x23,bVar17,uVar14);
      FUN_0019ac69(param_1,4,uVar12,bVar17,uVar14);
      uVar6 = FUN_0019ac69(param_1,3,bVar3,1,uVar14);
      cVar7 = FUN_001911d3(param_1,cVar5,bVar17,uVar14);
      lVar1 = *(long *)(param_1 + 0x138);
      uVar9 = phy_reg_read(param_1,sVar16);
      if (bVar11 == 0) {
        cVar13 = -0x10;
      }
      else {
        cVar13 = *(char *)(lVar1 + 0x45f + (long)(int)uVar14 * 3) + -0x10;
      }
      cVar13 = cVar13 - *(char *)((ulong)(uVar9 & 1) + 0x46a + lVar1 + (long)(int)uVar14 * 0x78);
      cVar10 = '\x17' - cVar4;
      if (cVar13 <= (char)('\x17' - cVar4)) {
        cVar10 = cVar13;
      }
      cVar4 = FUN_001911d3(param_1,uVar6,1,uVar14);
      lVar1 = *(long *)(param_1 + 0x138);
      uVar9 = phy_reg_read(param_1,sVar16);
      if (bVar17 != 0) {
        cVar13 = *(char *)(lVar1 + 0x45f + (long)(int)uVar14 * 3) + -0x10;
      }
      else {
        cVar13 = -0x10;
      }
      cVar13 = cVar13 - *(char *)((ulong)(uVar9 & 1) + 0x46a + lVar1 + (long)(int)uVar14 * 0x78);
      if ((char)('\x17' - cVar5) < cVar13) {
        cVar13 = '\x17' - cVar5;
      }
      if ((*(ushort *)(param_1 + 0x17e) & 0x3800) == 0x1000) {
        cVar5 = (char)((uint)((int)cVar10 + (int)cVar7) >> 1);
        if (bVar2 != 0) goto LAB_0019b213;
        cVar4 = (char)((uint)((int)cVar13 + (int)cVar4) >> 1);
      }
      else {
        cVar5 = -(char)((uint)(cVar10 * -0x27 + cVar7 * -0x1a) >> 6);
LAB_0019b213:
        cVar4 = -(char)((uint)(cVar13 * -0x27 + cVar4 * -0x1a) >> 6);
      }
      FUN_0019249a(param_1,uVar14,(int)cVar5);
      FUN_001928ae(param_1,uVar14,(int)cVar4);
    }
    uVar15 = uVar15 + 1;
  } while( true );
}

