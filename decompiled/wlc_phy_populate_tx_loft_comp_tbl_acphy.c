
void wlc_phy_populate_tx_loft_comp_tbl_acphy(long param_1,short *param_2)

{
  long lVar1;
  ushort uVar2;
  byte *pbVar3;
  ulong uVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined8 uVar7;
  byte bVar8;
  byte bVar9;
  char local_88 [16];
  char local_78 [16];
  byte local_68 [16];
  byte local_58 [16];
  byte local_48 [14];
  short local_3a [5];
  
  local_68[0] = 0x80;
  local_68[1] = 0x80;
  local_68[2] = 0x20;
  local_68[3] = 0x80;
  local_68[4] = 0x1a;
  local_68[5] = 0x1c;
  local_78[0] = '\0';
  local_78[1] = 0;
  local_78[2] = 0;
  local_78[3] = 0;
  local_78[4] = 0;
  local_78[5] = 0;
  local_78[6] = 0xec;
  local_78[7] = 0xf6;
  local_78[8] = 0xf6;
  local_78[9] = 0xf8;
  local_78[10] = 0xf6;
  local_78[0xb] = 0xfa;
  local_88[0] = '\0';
  local_88[1] = 0;
  local_88[2] = 0;
  local_88[3] = 0;
  local_88[4] = 0;
  local_88[5] = 0;
  local_88[6] = 0;
  local_88[7] = 0xfb;
  local_88[8] = 0xf2;
  local_88[9] = 0xfc;
  local_88[10] = 0xf6;
  local_88[0xb] = 0xfb;
  local_58[0] = 200;
  local_58[1] = 0x95;
  local_58[2] = 100;
  if (*(short *)(param_1 + 0x16a) != 0x30b) {
    local_48[0] = 0;
    local_48[1] = 0;
    local_48[2] = 0;
    uVar2 = phy_reg_read(param_1,0x19e);
    phy_reg_mod(param_1,0x19e,2,2);
    pbVar3 = local_58;
    pbVar6 = local_48;
    pbVar5 = pbVar3 + *(byte *)(param_1 + 0x168);
    for (; pbVar3 != pbVar5; pbVar3 = pbVar3 + 1) {
      *pbVar6 = *pbVar3 <= (byte)*(undefined2 *)(param_1 + 0x17e);
      pbVar6 = pbVar6 + 1;
    }
    bVar9 = 0;
    do {
      for (bVar8 = 0; bVar8 < *(byte *)(param_1 + 0x168); bVar8 = bVar8 + 1) {
        if (bVar8 == 0) {
          local_3a[0] = *param_2;
          uVar7 = 0x42;
LAB_0019d993:
          wlc_phy_table_write_acphy(param_1,uVar7,1,bVar9,0x10,local_3a);
        }
        else if (bVar8 < 3) {
          if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
            local_3a[0] = param_2[bVar8];
          }
          else {
            uVar4 = (ulong)bVar8;
            lVar1 = (ulong)(bVar9 <= local_68[uVar4 + (ulong)local_48[uVar4] * 3]) +
                    ((ulong)local_48[uVar4] + uVar4 * 2) * 2 + -0x38;
            local_3a[0] = (ushort)(byte)((char)((ushort)param_2[bVar8] >> 8) +
                                        local_78[lVar1 + 0x38]) * 0x100 +
                          (ushort)(byte)((char)param_2[bVar8] + local_88[lVar1 + 0x38]);
          }
          if (bVar8 == 1) {
            uVar7 = 0x62;
          }
          else {
            uVar7 = 0x82;
          }
          goto LAB_0019d993;
        }
      }
      bVar9 = bVar9 + 1;
    } while (bVar9 != 0x80);
    phy_reg_mod(param_1,0x19e,2,uVar2 & 2);
  }
  return;
}

