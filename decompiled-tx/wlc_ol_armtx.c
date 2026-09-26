
void wlc_ol_armtx(long *param_1,char param_2)

{
  byte bVar1;
  long *plVar2;
  long lVar3;
  char cVar4;
  ushort uVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  byte *pbVar9;
  long lVar10;
  long lVar11;
  undefined4 local_428;
  undefined4 local_424;
  undefined4 local_420;
  char local_41c;
  undefined4 local_41b;
  undefined1 local_417 [184];
  byte local_35f [736];
  byte local_7f;
  undefined1 local_7e;
  undefined2 local_7d;
  undefined2 local_7b;
  undefined1 local_79 [6];
  undefined1 local_73 [6];
  uint local_6d;
  undefined1 local_69 [16];
  undefined2 local_59;
  undefined2 local_57;
  undefined2 local_55;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  plVar2 = (long *)*param_1;
  if (plVar2 == (long *)0x0) {
    return;
  }
  if (*(char *)((long)param_1 + 0x8c) == '\0') {
    return;
  }
  lVar10 = plVar2[0x5f];
  cVar4 = wlc_bss_connected(lVar10);
  if (cVar4 == '\0') {
    return;
  }
  lVar6 = FUN_0018044b(plVar2);
  if (lVar6 == 0) {
    return;
  }
  osl_memset(&local_428,0,0x3e1);
  local_428 = 0x11;
  local_424 = 0;
  local_420 = 0x3d5;
  local_41c = param_2;
  if (param_2 == '\0') goto LAB_001808e8;
  lVar11 = 0;
  if ((((*(byte *)(lVar10 + 0x90) & 7) != 0) && (lVar11 = *(long *)(lVar6 + 0x10), lVar11 == 0)) &&
     (*(int *)(lVar10 + 0xa8) != -1)) {
    lVar11 = *(long *)(lVar10 + 0xb0 + (long)*(int *)(lVar10 + 0xa8) * 8);
  }
  lVar3 = *(long *)(lVar10 + 0x318);
  lVar7 = lVar3;
  do {
    if (*(uint *)(lVar3 + 0x38) <= (uint)((int)lVar7 - (int)lVar3)) {
      uVar8 = *(byte *)(lVar3 + 0x3c) & 0x7f;
      goto LAB_00180712;
    }
    pbVar9 = (byte *)(lVar7 + 0x3c);
    lVar7 = lVar7 + 1;
  } while ((*pbVar9 & 0x7f) != 0xc);
  uVar8 = 0xc;
LAB_00180712:
  local_7b = (undefined2)*(undefined4 *)(*param_1 + 0x518);
  uVar5 = *(ushort *)(*param_1 + 0x518) & 0x3800;
  if (((uVar5 == 0x1000) || (uVar8 == 4)) || ((uVar8 == 2 || ((uVar8 == 0xb || (uVar8 == 0x16))))))
  {
    uVar8 = uVar8 | 0x10000;
  }
  else if (uVar5 == 0x1800) {
    uVar8 = uVar8 | 0x20000;
  }
  else if (uVar5 == 0x2000) {
    uVar8 = uVar8 | 0x30000;
  }
  local_59 = wlc_acphy_txctl0_calc(plVar2,uVar8,4);
  local_57 = wlc_acphy_txctl1_calc(plVar2,uVar8,0);
  local_55 = wlc_acphy_txctl2_calc(plVar2,uVar8);
  local_7d = (undefined2)uVar8;
  local_6d = (uint)*(ushort *)(lVar10 + 0x112);
  local_41b = *(undefined4 *)(lVar10 + 0x90);
  local_7f = (byte)*(undefined4 *)(lVar6 + 8) & 0x40;
  osl_memcpy(local_69,lVar6 + 0xda,0x10);
  osl_memcpy(local_79,lVar10 + 0xf0,6);
  osl_memcpy(local_73,lVar10 + 0xf6,6);
  if ((lVar11 == 0) || ((*(uint *)(lVar10 + 0x90) & 7) == 0)) goto LAB_001808e8;
  lVar6 = *plVar2;
  if ((*(uint *)(lVar6 + 0x14) < 0xd) ||
     ((((-1 < (int)plVar2[0x46] || (*(char *)(lVar11 + 8) != '\x02')) ||
       ((char)plVar2[0x68] != '\0')) || ((*(uint *)(lVar10 + 0x90) & 8) != 0)))) {
LAB_0018089d:
    local_7e = false;
  }
  else {
    bVar1 = *(byte *)(lVar11 + 6);
    uVar8 = 5;
    if (*(char *)(lVar6 + 0x5d) == '\0') {
      uVar8 = *(uint *)(lVar6 + 0xd4);
    }
    if ((uVar8 <= bVar1) || (bVar1 < 4)) goto LAB_0018089d;
    local_7e = bVar1 < 0xc;
  }
  pbVar9 = local_35f;
  FUN_0017fa20(local_417,lVar11);
  do {
    if (*(long *)(lVar10 + 0xb0) != 0) {
      FUN_0017fa20(pbVar9);
    }
    pbVar9 = pbVar9 + 0xb8;
    lVar10 = lVar10 + 8;
  } while (pbVar9 != &local_7f);
LAB_001808e8:
  *(char *)((long)param_1 + 0x22c) = param_2;
  FUN_0017fcad(param_1,&local_428,0x3e1);
  return;
}

