
void wlc_phy_write_table_ext
               (long param_1,long *param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5,
               undefined2 param_6,undefined2 param_7)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  int iVar5;
  ushort uVar6;
  uint uVar7;
  int local_3c;
  
  uVar2 = *(uint *)(param_2 + 2);
  uVar3 = *(uint *)((long)param_2 + 0x14);
  lVar4 = *param_2;
  phy_reg_write(param_1,param_3,*(undefined2 *)((long)param_2 + 0xc));
  uVar7 = 0;
  phy_reg_write(param_1,param_4,uVar2 & 0xffff);
  do {
    if (*(uint *)(param_2 + 1) <= uVar7) {
      return;
    }
    if (uVar3 == 0x20) {
      puVar1 = (uint *)(lVar4 + (ulong)uVar7 * 4);
      phy_reg_write(param_1,param_6,*puVar1 >> 0x10);
      uVar6 = (ushort)*puVar1;
LAB_001b7849:
      phy_reg_write(param_1,param_7,uVar6);
    }
    else {
      if (uVar3 < 0x21) {
        if (uVar3 == 8) {
          uVar6 = (ushort)*(byte *)(lVar4 + (ulong)uVar7);
        }
        else {
          if (uVar3 != 0x10) goto LAB_001b7854;
          uVar6 = *(ushort *)(lVar4 + (ulong)uVar7 * 2);
        }
        goto LAB_001b7849;
      }
      if ((uVar3 == 0x3c) || (uVar3 == 0x40)) {
        local_3c = 0;
        do {
          uVar2 = *(uint *)(lVar4 + (ulong)(local_3c + uVar7 * 2) * 4);
          if (local_3c == 0) {
            phy_reg_write(param_1,param_5);
          }
          else {
            osl_writew(uVar2 & 0xffff,*(long *)(param_1 + 0x148) + 0x3fe);
          }
          osl_writew(uVar2 >> 0x10,*(long *)(param_1 + 0x148) + 0x3fe);
          local_3c = local_3c + 1;
        } while (local_3c != 2);
      }
      else if (uVar3 == 0x30) {
        iVar5 = 0;
        do {
          if (iVar5 == 0) {
            phy_reg_write(param_1,param_5,*(undefined2 *)(lVar4 + (ulong)(uVar7 * 3) * 2));
          }
          else {
            osl_writew(*(undefined2 *)(lVar4 + (ulong)(iVar5 + uVar7 * 3) * 2),
                       *(long *)(param_1 + 0x148) + 0x3fe);
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 != 3);
      }
    }
LAB_001b7854:
    uVar7 = uVar7 + 1;
  } while( true );
}

