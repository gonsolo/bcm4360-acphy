
undefined8 wlc_bmac_btc_mode_set(long param_1,int param_2)

{
  ushort *puVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  long lVar5;
  bool bVar6;
  ushort local_38;
  ushort local_36;
  ushort local_34;
  
  if (8 < param_2) {
    return 0xfffffffe;
  }
  if (param_2 == 8) {
    if ((((((0xe < *(uint *)(param_1 + 0x84)) &&
           ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x20) != 0)) &&
          ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1c) & 1) == 0)) ||
         ((((*(byte *)(param_1 + 0x8c) & 1) != 0 && (-1 < *(char *)(param_1 + 0x90))) &&
          ((uVar2 = *(uint *)(*(long *)(param_1 + 0xb8) + 0x1c), (uVar2 & 1) != 0 ||
           ((uVar2 & 4) != 0)))))) && ((*(byte *)(param_1 + 0xa7) & 0x20) != 0)) ||
       (param_2 = 0, *(char *)(param_1 + 0x90) < '\0')) {
      if (*(byte *)(*(long *)(param_1 + 0xb0) + 0x18) < 3) {
LAB_00164b5f:
        param_2 = 1;
      }
      else {
        iVar3 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c);
        if (iVar3 == 0xa886) {
          bVar6 = *(int *)(*(long *)(param_1 + 0xb8) + 0x28) != 0xe078;
          param_2 = bVar6 + 1 + (uint)bVar6;
        }
        else {
          param_2 = 5;
          if (iVar3 == 0xa8dc) goto LAB_00164b5f;
        }
      }
LAB_00164924:
      if (((2 < *(int *)(*(long *)(param_1 + 0xb0) + 4)) && (0xc < *(uint *)(param_1 + 0x84))) &&
         ((*(byte *)(param_1 + 0xab) & 0x20) == 0)) {
        return 0xfffffffd;
      }
    }
  }
  else if (param_2 != 0) goto LAB_00164924;
  bVar4 = 0;
  osl_memset(&local_38,0,10);
  *(undefined2 *)(*(long *)(param_1 + 0xb0) + 8) = 0;
  if (*(char *)(param_1 + 0x10c) != '\0') {
    bVar4 = osl_readl(*(long *)(param_1 + 0xd0) + 0x120);
    bVar4 = bVar4 & 1;
  }
  if (param_2 == 0) {
    local_38 = local_38 & 0xffef;
    goto LAB_00164ac3;
  }
  lVar5 = *(long *)(param_1 + 0xb0);
  local_38 = local_38 | 0x10;
  if (*(int *)(lVar5 + 4) == 2) {
    if ((*(byte *)(param_1 + 0x8d) & 0x40) == 0) {
      local_36 = local_36 & 0xfeff;
      goto LAB_00164ac3;
    }
    local_36 = local_36 | 0x100;
    *(undefined4 *)(lVar5 + 0xc) = 0x30;
  }
  else {
    if (0xc < *(uint *)(param_1 + 0x84)) {
      if (param_2 == 5) {
LAB_00164a0e:
        *(ushort *)(lVar5 + 8) = *(ushort *)(lVar5 + 8) | 8;
      }
      else {
        if (param_2 == 3) {
          if ((*(int *)(*(long *)(param_1 + 0xb8) + 0x3c) == 0x4331) &&
             ((*(byte *)(param_1 + 0x8e) & 0x40) != 0)) goto LAB_00164a1b;
          *(ushort *)(lVar5 + 8) = *(ushort *)(lVar5 + 8) | 0x80;
LAB_00164a07:
          lVar5 = *(long *)(param_1 + 0xb0);
          goto LAB_00164a0e;
        }
        if (param_2 == 4) {
LAB_00164a1b:
          *(ushort *)(lVar5 + 8) = *(ushort *)(lVar5 + 8) | 0x100;
          goto LAB_00164a07;
        }
        *(ushort *)(lVar5 + 8) = *(ushort *)(lVar5 + 8) | 0x14;
      }
      if (((((*(uint *)(param_1 + 0x84) < 0xf) ||
            ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1b) & 0x20) == 0)) ||
           ((*(byte *)(*(long *)(param_1 + 0xb8) + 0x1c) & 1) != 0)) &&
          ((((*(byte *)(param_1 + 0x8c) & 1) == 0 || (*(char *)(param_1 + 0x90) < '\0')) ||
           ((uVar2 = *(uint *)(*(long *)(param_1 + 0xb8) + 0x1c), (uVar2 & 1) == 0 &&
            ((uVar2 & 4) == 0)))))) || ((*(byte *)(param_1 + 0xa7) & 0x20) == 0)) {
        if (*(int *)(*(long *)(param_1 + 0xb0) + 4) == 4) {
          local_34 = local_34 | 0x2000;
        }
        else {
          puVar1 = (ushort *)(*(long *)(param_1 + 0xb0) + 8);
          *puVar1 = *puVar1 | 1;
        }
      }
      else {
        puVar1 = (ushort *)(*(long *)(param_1 + 0xb0) + 8);
        *puVar1 = *puVar1 | 0x40;
      }
      goto LAB_00164ac3;
    }
    *(ushort *)(lVar5 + 8) = *(ushort *)(lVar5 + 8) | 0xc;
    *(undefined4 *)(*(long *)(param_1 + 0xb0) + 0xc) = 0x870;
  }
  *(undefined4 *)(*(long *)(param_1 + 0xb0) + 0x10) = 0x20;
LAB_00164ac3:
  **(int **)(param_1 + 0xb0) = param_2;
  if ((bVar4 != 0) && (*(char *)(param_1 + 0x10c) != '\0')) {
    wlc_bmac_suspend_mac_and_wait(param_1);
  }
  wlc_bmac_mhf(param_1,0,0x10,local_38,2);
  wlc_bmac_mhf(param_1,1,0x100,local_36,2);
  wlc_bmac_mhf(param_1,2,0x2000,local_34,2);
  FUN_001638b9(param_1);
  if ((bVar4 != 0) && (*(char *)(param_1 + 0x10c) != '\0')) {
    wlc_bmac_enable_mac(param_1);
  }
  return 0;
}

