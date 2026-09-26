
int wlc_phy_rssi_compute_nphy(long param_1,long param_2)

{
  short *psVar1;
  long lVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  short sVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  undefined4 local_1c;
  
  uVar5 = *(ushort *)(param_2 + 6);
  lVar2 = *(long *)(param_1 + 0x138);
  uVar4 = uVar5 >> 8;
  local_1c = CONCAT22(uVar5,uVar4) & 0xffffff;
  if (0x7f < (uVar5 & 0xff)) {
    local_1c = CONCAT22((uVar5 & 0xff) - 0x100,uVar4);
  }
  if (0x7f < uVar4) {
    local_1c = CONCAT22(local_1c._2_2_,uVar4 - 0x100);
  }
  uVar4 = *(ushort *)(param_2 + 8) & 0xff;
  uVar5 = *(ushort *)(param_2 + 8) & 0xff;
  if (0x7f < uVar4) {
    uVar5 = uVar4 - 0x100;
  }
  if ((local_1c._2_2_ == 0x20) || (local_1c._2_2_ == 0x10)) {
    local_1c = CONCAT22((short)local_1c,uVar5);
  }
  if (*(int *)(param_1 + 0x164) - 3U < 4) {
    local_1c = CONCAT22((local_1c._2_2_ - (short)*(char *)(param_1 + 0x212)) + -2,
                        ((short)local_1c + -2) - (short)*(char *)(param_1 + 0x213));
  }
  *(char *)(param_2 + 0x20) = (char)(local_1c >> 0x10);
  *(undefined1 *)(param_2 + 0x1f) = 0;
  *(char *)(param_2 + 0x21) = (char)local_1c;
  if ((0x13 < *(uint *)(param_1 + 0x164)) &&
     (1 < *(int *)(*(long *)(param_1 + 0x20) + 0x3c) - 0xa8eaU)) {
    sVar6 = wlc_phy_swrssi_compute_nphy(param_1,(long)&local_1c + 2,&local_1c);
    *(char *)(param_2 + 0x20) = (char)(local_1c >> 0x10);
    *(char *)(param_2 + 0x21) = (char)local_1c;
    goto LAB_00214034;
  }
  lVar9 = *(long *)(param_1 + 0x20);
  cVar3 = *(char *)(lVar9 + 0xa7);
  if (cVar3 == '\x01') {
    local_1c = (uint)local_1c._2_2_;
LAB_00213fd1:
    sVar6 = (short)local_1c;
    if (-0x15 < sVar6) goto LAB_00214034;
  }
  else {
    if (cVar3 == '\x02') goto LAB_00213fd1;
    if (cVar3 != *(char *)(lVar9 + 0xa5)) {
LAB_00214032:
      sVar6 = 0;
      goto LAB_00214034;
    }
    if (*(int *)(lVar9 + 0x3c) != 0xa8e7) {
      cVar3 = *(char *)(lVar9 + 0xa8);
      if (cVar3 == '\0') {
        if ((short)local_1c <= (short)local_1c._2_2_) {
          local_1c = (uint)local_1c._2_2_;
        }
      }
      else if (cVar3 == '\x01') {
        if ((short)local_1c._2_2_ <= (short)local_1c) {
          local_1c = (uint)local_1c._2_2_;
        }
      }
      else {
        if (cVar3 != '\x02') goto LAB_00214032;
        local_1c = (uint)((int)(short)local_1c + (int)(short)local_1c._2_2_) >> 1;
      }
      goto LAB_00213fd1;
    }
    cVar3 = phy_reg_read(param_1,0x83);
    if (cVar3 != '\0') {
      local_1c = local_1c >> 0x10;
    }
    if ((ushort)((short)local_1c + 0x5cU) < 0x53) goto LAB_00213fd1;
    sVar6 = -0x5c;
  }
  *(short *)(lVar2 + 0x26c + (long)*(short *)(lVar2 + 0x28c) * 2) = sVar6;
  uVar7 = *(int *)(lVar2 + 0x28c) + 1;
  iVar8 = 0;
  *(short *)(lVar2 + 0x28c) =
       (short)((int)((uint)(ushort)((short)uVar7 >> 0xf) << 0x10 | uVar7 & 0xffff) % 0x10);
  lVar9 = 0;
  do {
    psVar1 = (short *)(lVar2 + 0x26c + lVar9);
    lVar9 = lVar9 + 2;
    iVar8 = iVar8 + *psVar1;
  } while (lVar9 != 0x20);
  *(short *)(lVar2 + 0x28e) = (short)(iVar8 / 0x10);
LAB_00214034:
  return (int)sVar6;
}

