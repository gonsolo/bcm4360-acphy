
void wlc_phy_desense_aci_engine_acphy(long param_1)

{
  ushort uVar1;
  ushort uVar2;
  long lVar3;
  long lVar4;
  char cVar5;
  int iVar6;
  undefined8 uVar7;
  byte bVar8;
  uint uVar9;
  byte bVar10;
  byte bVar11;
  long lVar12;
  byte bVar13;
  uint uVar14;
  uint uVar15;
  byte bVar16;
  uint uVar17;
  bool bVar18;
  bool bVar19;
  uint auStack_38 [4];
  
  lVar3 = *(long *)(param_1 + 0x138);
  if (*(long *)(lVar3 + 0x8a8) == 0) {
    uVar7 = func_0x00193c3b(param_1,*(undefined2 *)(param_1 + 0x17e),1);
    *(undefined8 *)(lVar3 + 0x8a8) = uVar7;
  }
  lVar4 = *(long *)(lVar3 + 0x8a8);
  if (*(char *)(lVar4 + 0x45) != '\0') {
    *(char *)(lVar4 + 0x45) = *(char *)(lVar4 + 0x45) + -1;
    return;
  }
  bVar10 = 1;
  if (*(int *)(param_1 + 0x404) != 0) {
    bVar10 = (char)*(int *)(param_1 + 0x404) - 1;
  }
  uVar1 = *(ushort *)(param_1 + 0x3fa + (ulong)bVar10 * 2);
  bVar10 = 1;
  if (*(int *)(param_1 + 0x420) != 0) {
    bVar10 = (char)*(int *)(param_1 + 0x420) - 1;
  }
  uVar2 = *(ushort *)(param_1 + 0x41c + (ulong)bVar10 * 2);
  bVar10 = 1;
  if (*(int *)(param_1 + 0x400) != 0) {
    bVar10 = (char)*(int *)(param_1 + 0x400) - 1;
  }
  bVar16 = *(byte *)(lVar4 + 0x44);
  bVar8 = 1;
  if (*(int *)(param_1 + 0x418) != 0) {
    bVar8 = (char)*(int *)(param_1 + 0x418) - 1;
  }
  lVar12 = (long)(int)(uint)bVar16;
  *(uint *)(lVar4 + 0x30 + lVar12 * 4) =
       (uint)*(ushort *)(param_1 + 0x3f6 + (ulong)bVar10 * 2) +
       (uint)*(ushort *)(param_1 + 0x414 + (ulong)bVar8 * 2) * 2;
  *(uint *)(lVar4 + 0x1c + lVar12 * 4) = (uint)uVar1 + (uint)uVar2 * 2;
  auStack_38[0] = *(uint *)(lVar4 + 0x1c);
  *(byte *)(lVar4 + 0x44) = bVar16 + 1 & 3;
  auStack_38[1] = *(uint *)(lVar4 + 0x20);
  auStack_38[2] = *(uint *)(lVar4 + 0x24);
  auStack_38[3] = *(uint *)(lVar4 + 0x28);
  bVar10 = auStack_38[0] < auStack_38[1];
  uVar15 = auStack_38[1];
  if (!(bool)bVar10) {
    uVar15 = auStack_38[0];
  }
  if (uVar15 < auStack_38[2]) {
    bVar10 = 2;
    uVar15 = auStack_38[2];
  }
  if (uVar15 < auStack_38[3]) {
    bVar10 = 3;
    uVar15 = auStack_38[3];
  }
  auStack_38[bVar10] = 0;
  uVar14 = *(uint *)(lVar4 + 0x30);
  uVar9 = *(uint *)(lVar4 + 0x34);
  if (auStack_38[1] < auStack_38[0]) {
    auStack_38[1] = auStack_38[0];
  }
  if (auStack_38[1] <= auStack_38[2]) {
    auStack_38[1] = auStack_38[2];
  }
  if (auStack_38[1] <= auStack_38[3]) {
    auStack_38[1] = auStack_38[3];
  }
  auStack_38[2] = *(uint *)(lVar4 + 0x38);
  uVar17 = auStack_38[1] + uVar15 >> 1;
  auStack_38[3] = *(uint *)(lVar4 + 0x3c);
  bVar10 = uVar14 < uVar9;
  uVar15 = uVar9;
  if (!(bool)bVar10) {
    uVar15 = uVar14;
  }
  if (uVar15 < auStack_38[2]) {
    bVar10 = 2;
    uVar15 = auStack_38[2];
  }
  if (uVar15 < auStack_38[3]) {
    bVar10 = 3;
    uVar15 = auStack_38[3];
  }
  auStack_38[0] = uVar14;
  auStack_38[1] = uVar9;
  auStack_38[bVar10] = 0;
  uVar14 = auStack_38[1];
  if (auStack_38[1] < auStack_38[0]) {
    uVar14 = auStack_38[0];
  }
  if (uVar14 <= auStack_38[2]) {
    uVar14 = auStack_38[2];
  }
  if (uVar14 <= auStack_38[3]) {
    uVar14 = auStack_38[3];
  }
  uVar15 = uVar14 + uVar15 >> 1;
  if (((uVar17 < 0x12d) && (*(char *)(lVar4 + 0x18) == '\0')) && (uVar15 < 0x259)) {
    return;
  }
  bVar10 = *(byte *)(lVar4 + 0x11);
  bVar16 = *(byte *)(lVar4 + 0x2c);
  bVar8 = *(byte *)(lVar4 + 0x2d);
  bVar11 = *(byte *)(lVar4 + 0x2e);
  if (uVar17 < 0x12d) {
    uVar14 = (uint)bVar10;
    bVar13 = 0xc;
    if (uVar14 - bVar16 != 1) {
      bVar13 = (-(uVar17 < 100) & 0xfcU) + 8;
    }
    if (bVar13 < bVar11) {
      if (bVar16 < bVar10) {
        iVar6 = (int)(bVar16 + uVar14) >> 1;
        if ((int)(uVar14 - 1) < iVar6) {
          iVar6 = uVar14 - 1;
        }
        bVar8 = (byte)iVar6;
        if (iVar6 < 0) {
          bVar8 = 0;
        }
      }
      else {
        iVar6 = uVar14 - 4;
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        bVar8 = (byte)iVar6;
      }
      uVar14 = (uint)bVar8;
      bVar8 = bVar10;
      goto code_r0x0019b83e;
    }
    uVar14 = (uint)bVar10;
  }
  else {
    uVar14 = bVar10 + 4;
    bVar16 = bVar10;
    if (bVar10 < bVar8) {
      uVar9 = bVar10 + 1;
      uVar14 = (int)((uint)bVar8 + (uint)bVar10) >> 1;
      if (uVar14 < uVar9) {
        uVar14 = uVar9;
      }
    }
code_r0x0019b83e:
    bVar11 = 0;
  }
  *(byte *)(lVar4 + 0x2c) = bVar16;
  *(byte *)(lVar4 + 0x2d) = bVar8;
  bVar10 = *(byte *)(lVar4 + 0x40);
  bVar16 = *(byte *)(lVar4 + 0x41);
  uVar9 = bVar11 + 1;
  if (0xff < bVar11 + 1) {
    uVar9 = 0xff;
  }
  bVar8 = *(byte *)(lVar4 + 0x10);
  uVar17 = (uint)bVar8;
  *(char *)(lVar4 + 0x2e) = (char)uVar9;
  bVar11 = *(byte *)(lVar4 + 0x42);
  if (uVar15 < 0x259) {
    uVar9 = (uint)bVar8;
    bVar13 = 0xc;
    if (uVar9 - bVar10 != 1) {
      bVar13 = (-(uVar15 < 300) & 0xfcU) + 8;
    }
    if (bVar11 <= bVar13) goto code_r0x0019b8ec;
    if (bVar10 < bVar8) {
      uVar17 = (int)(bVar10 + uVar9) >> 1;
      if ((int)(uVar9 - 1) < (int)uVar17) {
        uVar17 = uVar9 - 1;
      }
    }
    else {
      uVar17 = uVar9 - 4;
    }
    bVar16 = bVar8;
    if ((int)uVar17 < 0) {
      uVar17 = 0;
    }
  }
  else {
    bVar10 = bVar8;
    uVar17 = bVar8 + 4;
    if (bVar8 < bVar16) {
      uVar15 = bVar8 + 1;
      uVar17 = (int)((uint)bVar16 + (uint)bVar8) >> 1;
      if (uVar17 < uVar15) {
        uVar17 = uVar15;
      }
    }
  }
  bVar11 = 0;
code_r0x0019b8ec:
  *(byte *)(lVar4 + 0x40) = bVar10;
  *(byte *)(lVar4 + 0x41) = bVar16;
  uVar15 = bVar11 + 1;
  if (0xff < bVar11 + 1) {
    uVar15 = 0xff;
  }
  *(char *)(lVar4 + 0x42) = (char)uVar15;
  uVar15 = 0x18;
  if ((byte)uVar14 < 0x19) {
    uVar15 = uVar14;
  }
  cVar5 = (char)uVar15;
  uVar14 = 0x30;
  if ((byte)uVar17 < 0x31) {
    uVar14 = uVar17;
  }
  uVar9 = uVar14;
  if (*(char *)(lVar3 + 0x671) != '\0') {
    uVar9 = (int)*(char *)(lVar4 + 0x19) + 0x5a;
    if ((int)uVar9 < 0) {
      uVar9 = 0;
    }
    uVar17 = uVar15 & 0xff;
    if ((int)uVar9 < (int)(uVar15 & 0xff)) {
      uVar17 = uVar9;
    }
    cVar5 = (char)uVar17;
    uVar15 = (int)*(char *)(lVar4 + 0x19) + 0x55;
    if ((int)uVar15 < 0) {
      uVar15 = 0;
    }
    uVar9 = uVar14 & 0xff;
    if ((int)uVar15 < (int)(uVar14 & 0xff)) {
      uVar9 = uVar15;
    }
  }
  bVar18 = cVar5 != *(char *)(lVar4 + 0x11);
  if (bVar18) {
    *(char *)(lVar4 + 0x11) = cVar5;
    *(undefined4 *)(lVar4 + 0x1c) = 100;
    *(undefined4 *)(lVar4 + 0x20) = 100;
    *(undefined4 *)(lVar4 + 0x24) = 100;
    *(undefined4 *)(lVar4 + 0x28) = 100;
  }
  cVar5 = (char)uVar9;
  bVar19 = cVar5 != *(char *)(lVar4 + 0x10);
  if (bVar19) {
    *(char *)(lVar4 + 0x10) = cVar5;
    *(undefined4 *)(lVar4 + 0x30) = 300;
    *(undefined4 *)(lVar4 + 0x34) = 300;
    *(undefined4 *)(lVar4 + 0x38) = 300;
    *(undefined4 *)(lVar4 + 0x3c) = 300;
  }
  *(undefined1 *)(lVar4 + 0x18) = 0;
  iVar6 = osl_memcmp(lVar3 + 0x65f,lVar4 + 0x10,9);
  *(bool *)(lVar4 + 0x18) = iVar6 != 0;
  if (bVar19 || bVar18) {
    func_0x0019b279(param_1,1);
    *(undefined1 *)(lVar4 + 0x45) = 1;
  }
  return;
}

