
undefined1 FUN_0010fe8d(long param_1)

{
  uint *puVar1;
  ushort uVar2;
  ushort uVar3;
  undefined2 uVar4;
  long lVar5;
  char cVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  long lVar13;
  int iVar14;
  uint uVar15;
  undefined1 uVar16;
  uint uVar17;
  uint uVar18;
  int local_4c;
  uint local_3c [3];
  
  local_3c[0] = 0;
  uVar15 = *(uint *)(param_1 + 0xa8);
  uVar2 = *(ushort *)(param_1 + 0xa6);
  uVar3 = *(ushort *)(param_1 + 0xa4);
  uVar10 = uVar15 & 0xffff;
  uVar17 = -(uint)((*(uint *)(param_1 + 0xc) & 0x10) == 0) & 0xfffffff1;
  iVar14 = *(int *)(param_1 + 0xec);
  local_4c = 0;
  if (0xcc < *(ushort *)(param_1 + 0xe4)) {
    local_4c = *(int *)(param_1 + 0xe8);
  }
  uVar18 = 0;
  do {
    if (iVar14 - (uVar3 - 1 & uVar10 - uVar2) <= uVar18) {
      uVar16 = 0;
LAB_001100df:
      *(short *)(param_1 + 0xa8) = (short)uVar15;
      if (*(char *)(param_1 + 0x40) == '\0') {
        iVar14 = (uVar15 & 0xffff) << 3;
        lVar13 = *(long *)(param_1 + 0x50) + 8;
      }
      else {
        iVar14 = (uVar15 & 0xffff) * 0x10 + *(int *)(param_1 + 0xe0);
        lVar13 = *(long *)(param_1 + 0x50) + 4;
      }
      osl_writel(iVar14,lVar13);
      return uVar16;
    }
    lVar13 = osl_pktget(*(undefined8 *)(param_1 + 0x30),
                        uVar17 + 0xf + (uint)*(ushort *)(param_1 + 0xe4) + local_4c);
    if (lVar13 == 0) {
      if (uVar18 == 0) {
        if (*(char *)(param_1 + 0x40) == '\0') {
          cVar6 = FUN_0010edfe(param_1);
        }
        else {
          cVar6 = FUN_0010ee80(param_1);
        }
        uVar16 = 1;
        if (cVar6 == '\0') goto LAB_0010ff54;
      }
      else {
LAB_0010ff54:
        uVar16 = 0;
      }
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
      goto LAB_001100df;
    }
    uVar11 = 0;
    if ((*(byte *)(param_1 + 0xc) & 0x10) != 0) {
      iVar7 = osl_pktdata(*(undefined8 *)(param_1 + 0x30),lVar13);
      uVar11 = (uVar17 + 0x10) - iVar7 & uVar17 + 0xf;
    }
    if (uVar11 + local_4c != 0) {
      osl_pktpull(*(undefined8 *)(param_1 + 0x30),lVar13);
    }
    puVar8 = (undefined4 *)osl_pktdata(*(undefined8 *)(param_1 + 0x30),lVar13);
    *puVar8 = 0;
    uVar4 = *(undefined2 *)(param_1 + 0xe4);
    lVar5 = *(long *)(param_1 + 0xc0);
    uVar9 = osl_pktdata(*(undefined8 *)(param_1 + 0x30),lVar13);
    uVar11 = osl_dma_map(*(undefined8 *)(param_1 + 0x30),uVar9,uVar4,2,lVar13,
                         (ulong)(uVar15 & 0xffff) * 0x90 + lVar5);
    uVar12 = uVar15 & 0xffff;
    *(long *)(*(long *)(param_1 + 0xb0) + (ulong)(uVar15 & 0xffff) * 8) = lVar13;
    local_3c[0] = 0;
    if (*(char *)(param_1 + 0x40) == '\0') {
      local_3c[0] = 0x10000000;
      if (uVar12 != *(ushort *)(param_1 + 0xa4) - 1) {
        local_3c[0] = 0;
      }
      local_3c[0] = *(ushort *)(param_1 + 0xe4) & 0x1fff | local_3c[0];
      if ((*(int *)(param_1 + 0xfc) == 0) || ((uVar11 & 0xc0000000) == 0)) {
        puVar1 = (uint *)(*(long *)(param_1 + 0x60) + (ulong)uVar12 * 8);
        puVar1[1] = uVar11 + *(int *)(param_1 + 0xfc);
        *puVar1 = local_3c[0];
      }
      else {
        puVar1 = (uint *)(*(long *)(param_1 + 0x60) + (ulong)uVar12 * 8);
        local_3c[0] = (uVar11 >> 0x1e) << 0x10 | local_3c[0];
        puVar1[1] = (uVar11 & 0x3fffffff) + *(int *)(param_1 + 0xfc);
        *puVar1 = local_3c[0];
      }
    }
    else {
      if (uVar12 == *(ushort *)(param_1 + 0xa4) - 1) {
        local_3c[0] = 0x10000000;
      }
      FUN_0010ea38(param_1,*(undefined8 *)(param_1 + 0x60),uVar11,uVar15 & 0xffff,local_3c,
                   *(undefined2 *)(param_1 + 0xe4));
    }
    uVar18 = uVar18 + 1;
    uVar15 = uVar15 + 1 & *(int *)(param_1 + 0xa4) - 1U;
  } while( true );
}

