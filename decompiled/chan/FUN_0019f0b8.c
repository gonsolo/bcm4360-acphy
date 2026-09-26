
void FUN_0019f0b8(long param_1)

{
  char cVar1;
  long lVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined6 *puVar6;
  undefined8 uVar7;
  ushort uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined1 *puVar14;
  uint uVar15;
  bool bVar16;
  undefined1 local_68 [62];
  undefined2 local_2a;
  
  local_2a = 0x49;
  uVar4 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  uVar8 = *(ushort *)(param_1 + 0x17e);
  if ((uVar8 & 0xc000) == 0) {
    iVar13 = *(int *)(*(long *)(param_1 + 0x20) + 0xb0);
LAB_0019f124:
    bVar16 = iVar13 == 2;
  }
  else {
    bVar16 = false;
    if ((uVar8 & 0xc000) == 0xc000) {
      iVar13 = *(int *)(*(long *)(param_1 + 0x20) + 0xac);
      goto LAB_0019f124;
    }
  }
  if (*(short *)(param_1 + 0x16a) == 0x2069) {
    if ((uVar8 & 0xc000) == 0) {
      phy_reg_write(param_1,0x1ec,2);
      phy_reg_mod(param_1,0x2e4,0x3f00,0xf00);
      if (bVar16) {
        bVar3 = *(char *)(param_1 + 0x16c) - 0x10;
        puVar14 = acphy_txgain_ipa_2g_2069rev0;
        if (bVar3 < 0x17) {
          puVar14 = (&PTR_acphy_txgain_ipa_2g_2069rev16_00559e30)[bVar3];
        }
      }
      else {
        switch(*(char *)(param_1 + 0x16c)) {
        case '\x04':
        case '\b':
          puVar14 = acphy_txgain_epa_2g_2069rev4;
          bVar3 = *(byte *)(*(long *)(param_1 + 0x138) + 0x349);
          if (bVar3 < 2) {
            puVar14 = (&PTR_acphy_txgain_epa_2g_2069rev4_00559ef0)[bVar3];
          }
          break;
        default:
          puVar14 = acphy_txgain_epa_2g_2069rev0;
          break;
        case '\x10':
          puVar14 = acphy_txgain_epa_2g_2069rev16;
          break;
        case '\x11':
        case '\x17':
        case '\x19':
          puVar14 = (undefined1 *)&acphy_txgain_epa_2g_2069rev17;
          if (*(char *)(*(long *)(param_1 + 0x138) + 0x354) != '\0') {
            bVar3 = *(byte *)(*(long *)(param_1 + 0x20) + 0xd6);
            iVar9 = (uint)bVar3 + (uint)bVar3 * 2;
            for (iVar13 = 0; iVar13 != iVar9; iVar13 = iVar13 + 3) {
              iVar5 = 0;
              do {
                iVar11 = iVar5 + iVar9;
                iVar10 = iVar5 + iVar13;
                iVar5 = iVar5 + 1;
                (&acphy_txgain_epa_2g_2069rev17)[iVar10] = (&acphy_txgain_epa_2g_2069rev17)[iVar11];
              } while (iVar5 != 3);
            }
            puVar14 = (undefined1 *)&acphy_txgain_epa_2g_2069rev17;
          }
          break;
        case '\x12':
        case '\x18':
        case '\x1a':
          puVar14 = acphy_txgain_epa_2g_2069rev18;
          break;
        case ' ':
        case '!':
        case '\"':
        case '#':
        case '%':
        case '&':
          puVar14 = acphy_txgain_epa_2g_2069rev33_37;
        }
      }
    }
    else {
      phy_reg_write(param_1,0x1ec,40000);
      phy_reg_mod(param_1,0x2e4,0x3f00,0x800);
      if (bVar16) {
        bVar3 = *(char *)(param_1 + 0x16c) - 0x10;
        puVar14 = acphy_txgain_ipa_5g_2069rev0;
        if (bVar3 < 0x17) {
          puVar14 = (&PTR_acphy_txgain_ipa_5g_2069rev16_00559f00)[bVar3];
        }
      }
      else {
        switch(*(char *)(param_1 + 0x16c)) {
        case '\x04':
        case '\b':
          puVar14 = acphy_txgain_epa_5g_2069rev4;
          break;
        default:
          puVar14 = acphy_txgain_epa_5g_2069rev0;
          break;
        case '\x10':
          puVar14 = acphy_txgain_epa_5g_2069rev16;
          break;
        case '\x11':
        case '\x17':
        case '\x19':
          puVar14 = (undefined1 *)&acphy_txgain_epa_5g_2069rev17;
          if (*(char *)(*(long *)(param_1 + 0x138) + 0x355) != '\0') {
            bVar3 = *(byte *)(*(long *)(param_1 + 0x20) + 0xd7);
            iVar9 = (uint)bVar3 + (uint)bVar3 * 2;
            for (iVar13 = 0; iVar13 != iVar9; iVar13 = iVar13 + 3) {
              iVar5 = 0;
              do {
                iVar11 = iVar5 + iVar9;
                iVar10 = iVar5 + iVar13;
                iVar5 = iVar5 + 1;
                (&acphy_txgain_epa_5g_2069rev17)[iVar10] = (&acphy_txgain_epa_5g_2069rev17)[iVar11];
              } while (iVar5 != 3);
            }
            puVar14 = (undefined1 *)&acphy_txgain_epa_5g_2069rev17;
          }
          break;
        case '\x12':
        case '\x18':
        case '\x1a':
          puVar14 = acphy_txgain_epa_5g_2069rev18;
          break;
        case ' ':
        case '!':
        case '\"':
        case '#':
        case '%':
        case '&':
          puVar14 = acphy_txgain_epa_5g_2069rev33_37;
        }
      }
    }
  }
  else {
    if ((uVar8 & 0xc000) == 0) {
      phy_reg_write(param_1,0x1ec,2);
      puVar14 = (undefined1 *)&acphy_txgain_epa_2g_20691rev1;
      phy_reg_mod(param_1,0x2e4,0x3f00,0xf00);
      puVar6 = &acphy_txgain_ipa_2g_20691rev1;
    }
    else {
      phy_reg_write(param_1,0x1ec,40000);
      puVar14 = (undefined1 *)&acphy_txgain_epa_5g_20691rev1;
      phy_reg_mod(param_1,0x2e4,0x3f00,0x800);
      puVar6 = &acphy_txgain_ipa_5g_20691rev1;
    }
    if (bVar16) {
      puVar14 = (undefined1 *)puVar6;
    }
  }
  iVar13 = *(int *)(param_1 + 0x164);
  if (((iVar13 == 5) || (iVar13 == 2)) || (iVar13 == 6)) {
    uVar7 = 0x400;
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0) {
      uVar7 = 0;
    }
    phy_reg_mod(param_1,0x16c,0x400,uVar7);
  }
  wlc_phy_table_write_acphy(param_1,0x20,0x80,0,0x30,puVar14);
  if (*(int *)(param_1 + 0x164) == 0) {
    uVar12 = 0;
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      for (; (byte)uVar12 < *(byte *)(param_1 + 0x168); uVar12 = uVar12 + 1) {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar15 = 0x60, acphychipid == 0xaa06)))) {
          uVar15 = 0x59;
        }
        mod_radio_reg(param_1,(uVar12 & 0x7f) << 9 | uVar15,0x3000,0x1000);
      }
    }
    else {
      if (*(char *)(*(long *)(param_1 + 0x138) + 0x34a) != '\0') {
        iVar13 = 0;
        do {
          if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
             ((acphychipid == 0xa9c4 || (uVar12 = 99, acphychipid == 0xaa06)))) {
            uVar12 = 0x5c;
          }
          uVar15 = iVar13 << 9;
          mod_radio_reg(param_1,uVar12 | uVar15 & 0xffff,0xf000,0x6000);
          if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
             (uVar12 = 0x68, acphychipid == 0xaa06)) {
            uVar12 = 0x61;
          }
          iVar13 = iVar13 + 1;
          mod_radio_reg(param_1,uVar12 | uVar15 & 0xffff,0xf000,0x6000);
        } while (iVar13 != 2);
      }
      if (*(byte *)(param_1 + 0x16c) < 4) {
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar8 = 99, acphychipid == 0xaa06)))) {
          uVar8 = 0x5c;
        }
        mod_radio_reg(param_1,uVar8 | 0x400,0xf000,0x6000);
        if (((acphychipid == 0x4352) || (acphychipid == 0x4360)) ||
           ((acphychipid == 0xa9c4 || (uVar8 = 0x68, acphychipid == 0xaa06)))) {
          uVar8 = 0x61;
        }
        mod_radio_reg(param_1,uVar8 | 0x400,0xf000,0x6000);
      }
    }
  }
  cVar1 = *(char *)(*(long *)(param_1 + 0x138) + 0x411);
  if ((cVar1 == '\x10') || (cVar1 == '\t')) {
    local_2a = 0;
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
      local_2a = 0x49;
    }
    wlc_phy_table_write_acphy(param_1,7,1,0x18e,0x10,&local_2a);
  }
  iVar13 = *(int *)(param_1 + 0x164);
  if ((((iVar13 != 5) && (iVar13 != 2)) && (iVar13 != 6)) && (iVar13 != 3)) goto LAB_0019f792;
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000) {
    phy_reg_mod(param_1,0x419,1,1);
    goto LAB_0019f77b;
  }
  phy_reg_mod(param_1,0x419,1,0);
  lVar2 = *(long *)(param_1 + 0x138);
  if (*(char *)(lVar2 + 0x34c) == '\x01') {
    iVar13 = (*(ushort *)(lVar2 + 0x352) & 0x3fff) << 2;
  }
  else {
    iVar13 = *(int *)(param_1 + 0x164);
    if (((iVar13 == 5) || (iVar13 == 2)) || (iVar13 == 6)) {
      if (*(char *)(lVar2 + 0x342) != '\x04') goto LAB_0019f792;
      cVar1 = *(char *)(lVar2 + 0x343);
      iVar13 = 0x8f0;
      if ((cVar1 != '\x01') && (iVar13 = 0xa5c, cVar1 != '\x02')) {
        if ((cVar1 != '\x03') && (cVar1 != '\x04')) goto LAB_0019f77b;
        iVar13 = 0x160;
      }
    }
    else {
      if (iVar13 != 3) goto LAB_0019f792;
      if (*(char *)(lVar2 + 0x342) == '\n') {
        cVar1 = *(char *)(lVar2 + 0x343);
        if (cVar1 == '\0') {
          iVar13 = 0xc5c;
        }
        else {
          iVar13 = 0xd1c;
          if (((cVar1 != '\x01') && (iVar13 = 0xc0c, cVar1 != '\x02')) &&
             (iVar13 = 0xc24, cVar1 != '\x04')) goto LAB_0019f77b;
        }
      }
      else {
LAB_0019f77b:
        iVar13 = 0xffc;
      }
    }
  }
  phy_reg_mod(param_1,0x419,0xffc,iVar13);
LAB_0019f792:
  FUN_001906f4(param_1,0);
  FUN_00194e38(param_1,*(undefined1 *)(*(long *)(param_1 + 0x20) + 0xa5),0);
  uVar12 = *(uint *)(*(long *)(param_1 + 0x20) + 0x80);
  wlc_phy_hwaci_setup_acphy(param_1,uVar12 >> 1 & 1,0);
  wlc_phy_aci_w2nb_setup_acphy(param_1,uVar12 >> 2 & 1);
  osl_memset(local_68,0,0x38);
  FUN_0019cea1(param_1,local_68);
  FUN_00190029(param_1,*(undefined1 *)(param_1 + 0xfa2));
  phy_reg_mod(param_1,0x19e,2,(uVar4 >> 1 & 1) * 2);
  return;
}

