
void FUN_001b0ce9(long param_1)

{
  int iVar1;
  long lVar2;
  undefined2 uVar3;
  undefined8 uVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  undefined8 local_48 [3];
  
  lVar2 = *(long *)(param_1 + 0x138);
  local_48[0] = 0;
  if ((*(uint *)(param_1 + 0x19c) & 0x21e) == 0) {
    wlc_phy_stay_in_carriersearch_acphy(param_1,1);
    FUN_001906f4(param_1,0);
    FUN_00194e38(param_1,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa5),0);
    uVar3 = phy_reg_read(param_1,0x401);
    phy_reg_mod(param_1,0x401,7,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa5));
    phy_reg_mod(param_1,0x401,0x7000,
                ((ulong)*(byte *)(*(long *)(param_1 + 0x20) + 0xa5) & 0xf) << 0xc);
    for (uVar6 = 0; bVar5 = (byte)uVar6, bVar5 < *(byte *)(param_1 + 0x168); uVar6 = uVar6 + 1) {
      uVar7 = uVar6 & 0xff;
      if ((*(byte *)(*(long *)(param_1 + 0x20) + 0xa5) >> (uVar6 & 0x1f) & 1) != 0) {
        FUN_001b0534(param_1,local_48,1,0,0,1,uVar7);
        *(undefined2 *)(lVar2 + 0x44e + (long)(int)uVar7 * 2) =
             *(undefined2 *)((long)local_48 + (long)(int)uVar7 * 2);
        if (bVar5 == 1) {
          uVar4 = 0x845;
LAB_001b0e30:
          phy_reg_mod(param_1,uVar4,0x3ff);
        }
        else {
          if (bVar5 == 0) {
            uVar4 = 0x645;
            goto LAB_001b0e30;
          }
          if (bVar5 == 2) {
            uVar4 = 0xa45;
            goto LAB_001b0e30;
          }
        }
        iVar1 = *(int *)(param_1 + 0x164);
        if (((((iVar1 == 5) || (iVar1 == 2)) || (iVar1 == 6)) || (iVar1 == 3)) &&
           (*(char *)(*(long *)(param_1 + 0x138) + 0x348) != '\0')) {
          if (bVar5 == 0) {
            uVar4 = 0x64c;
          }
          else {
            if (bVar5 != 1) goto LAB_001b0e95;
            uVar4 = 0x84c;
          }
          phy_reg_mod(param_1,uVar4,0x3ff);
        }
      }
LAB_001b0e95:
    }
    phy_reg_write(param_1,0x401,uVar3);
    wlc_phy_stay_in_carriersearch_acphy(param_1,0);
  }
  return;
}

