
undefined8 wlc_phy_watchdog(long param_1)

{
  int *piVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char cVar6;
  short sVar7;
  ushort uVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  long lVar16;
  long lVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  bool bVar21;
  bool bVar22;
  undefined1 auStack_3c [3];
  char acStack_39 [9];
  
  if ((*(int *)(param_1 + 0x160) == 2) || (lVar17 = 0, *(int *)(param_1 + 0x160) == 0)) {
    lVar17 = *(long *)(param_1 + 0x138);
  }
  piVar1 = (int *)(*(long *)(param_1 + 0x20) + 0x34);
  *piVar1 = *piVar1 + 1;
  if (*(char *)(param_1 + 0x18c) == '\0') {
    return 0;
  }
  if (*(int *)(param_1 + 0x160) == 8) {
    wlc_lcnphy_noise_measure_stop(param_1);
  }
  sVar7 = *(short *)(param_1 + 0x1136);
  if (sVar7 != 0) {
    *(short *)(param_1 + 0x45a) = sVar7;
    *(short *)(param_1 + 0x45c) = sVar7;
  }
  sVar7 = *(short *)(param_1 + 0x113a);
  if (sVar7 != 0) {
    *(short *)(param_1 + 0x44c) = sVar7;
    *(short *)(param_1 + 0x448) = sVar7;
  }
  sVar7 = (short)*(undefined4 *)(param_1 + 0x1138);
  if (sVar7 != 0) {
    *(short *)(param_1 + 0x446) = sVar7;
    *(short *)(param_1 + 0x44a) = sVar7;
  }
  if ((*(uint *)(param_1 + 0x19c) & 0x206) != 0) {
code_r0x001bd023:
    if (*(int *)(param_1 + 0x160) == 4) {
      if (*(uint *)(param_1 + 0x164) < 3) goto code_r0x001bd048;
    }
    else if (*(int *)(param_1 + 0x160) != 7) goto code_r0x001bd048;
    *(undefined4 *)(param_1 + 0x2cc) = 2;
    goto code_r0x001bd048;
  }
  iVar12 = *(int *)(param_1 + 0x160);
  if (iVar12 == 4) {
    if (2 < *(uint *)(param_1 + 0x164)) {
code_r0x001bc749:
      if (*(int *)(param_1 + 0x2cc) != 0) {
        *(int *)(param_1 + 0x2cc) = *(int *)(param_1 + 0x2cc) + -1;
      }
    }
  }
  else if (iVar12 != 0xb) {
    if (iVar12 == 7) goto code_r0x001bc749;
    if ((iVar12 != 2) && (iVar12 != 6)) {
      if (iVar12 == 8) {
        bVar21 = *(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4313;
      }
      else {
        if (iVar12 == 5) goto code_r0x001bc75b;
        if (iVar12 != 10) goto code_r0x001bd023;
        bVar21 = *(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa886;
      }
      if (!bVar21) goto code_r0x001bd023;
    }
  }
code_r0x001bc75b:
  iVar12 = *(int *)(param_1 + 0x164);
  uVar8 = wlapi_bmac_read_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
  iVar20 = (uint)uVar8 - *(int *)(param_1 + 0x48c);
  *(uint *)(param_1 + 0x48c) = (uint)uVar8;
  iVar14 = *(int *)(param_1 + 0x160);
  if (iVar14 == 4) {
    if (*(uint *)(param_1 + 0x164) < 3) goto code_r0x001bc830;
code_r0x001bc7ae:
    sVar9 = wlapi_bmac_read_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x10c);
    sVar7 = *(short *)(param_1 + 0x300);
    *(short *)(param_1 + 0x300) = sVar9;
    iVar18 = (int)sVar9 - (int)sVar7;
    sVar10 = wlapi_bmac_read_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x158);
    sVar7 = *(short *)(param_1 + 0x3f0);
    *(short *)(param_1 + 0x3f0) = sVar10;
    sVar9 = *(short *)(param_1 + 0x302);
    iVar13 = (int)sVar10 - (int)sVar7;
    uVar8 = *(ushort *)(param_1 + 0x17e) & 0xc000;
    *(undefined2 *)(param_1 + 0x302) = 0;
    iVar14 = iVar20 - iVar13;
    if (uVar8 != 0) {
      iVar14 = iVar20;
    }
    iVar11 = -(int)sVar9;
    iVar19 = iVar18;
    if (uVar8 == 0) {
      iVar19 = iVar18 + sVar9;
    }
  }
  else {
    if ((iVar14 == 7) || (iVar14 == 0xb)) goto code_r0x001bc7ae;
code_r0x001bc830:
    iVar11 = 0;
    iVar18 = 0;
    iVar14 = 0;
    iVar13 = 0;
    iVar19 = 0;
  }
  if (*(int *)(param_1 + 0x160) == 4) {
    if (*(uint *)(param_1 + 0x164) < 3) goto code_r0x001bc863;
code_r0x001bc856:
    if (*(int *)(param_1 + 0x2cc) == 0) goto code_r0x001bc863;
  }
  else {
    if (*(int *)(param_1 + 0x160) == 7) goto code_r0x001bc856;
code_r0x001bc863:
    if (-1 < iVar20) {
      sVar7 = *(short *)(param_1 + 0x492 + (long)*(int *)(param_1 + 0x4a4) * 2);
      *(short *)(param_1 + 0x48a) = (short)*(undefined4 *)(param_1 + 0x488);
      iVar3 = *(int *)(param_1 + 0x160);
      uVar8 = ((short)*(undefined4 *)(param_1 + 0x490) - sVar7) + (short)iVar20;
      *(ushort *)(param_1 + 0x490) = uVar8;
      if (iVar3 == 4) {
        if ((2 < *(uint *)(param_1 + 0x164)) && (*(uint *)(param_1 + 0x164) < 0x10))
        goto code_r0x001bc8c9;
code_r0x001bc8ce:
        uVar8 = uVar8 >> 3;
      }
      else {
        if ((iVar3 != 7) && (iVar3 != 0xb)) goto code_r0x001bc8ce;
code_r0x001bc8c9:
        uVar8 = uVar8 >> 1;
      }
      *(ushort *)(param_1 + 0x488) = uVar8;
      iVar3 = *(int *)(param_1 + 0x4a4);
      iVar15 = iVar3 + 1;
      *(short *)(param_1 + 0x492 + (long)iVar3 * 2) = (short)iVar20;
      iVar4 = *(int *)(param_1 + 0x160);
      *(int *)(param_1 + 0x4a4) = iVar15;
      if (iVar4 == 4) {
        if ((2 < *(uint *)(param_1 + 0x164)) && (*(uint *)(param_1 + 0x164) < 0x10))
        goto code_r0x001bc921;
code_r0x001bc925:
        bVar22 = SBORROW4(iVar15,7);
        iVar3 = iVar3 + -6;
        bVar21 = iVar15 == 7;
      }
      else {
        if ((iVar4 != 7) && (iVar4 != 0xb)) goto code_r0x001bc925;
code_r0x001bc921:
        bVar22 = SBORROW4(iVar15,1);
        bVar21 = iVar3 == 0;
      }
      if (!bVar21 && bVar22 == iVar3 < 0) {
        *(undefined4 *)(param_1 + 0x4a4) = 0;
      }
    }
    iVar3 = *(int *)(param_1 + 0x160);
    if (iVar3 == 4) {
      if (2 < *(uint *)(param_1 + 0x164)) {
code_r0x001bc95b:
        if (-1 < iVar18) {
          sVar7 = *(short *)(param_1 + 0x2ea + (long)*(int *)(param_1 + 0x2fc) * 2);
          *(short *)(param_1 + 0x2e6) = (short)*(undefined4 *)(param_1 + 0x2e4);
          iVar3 = *(int *)(param_1 + 0x160);
          uVar8 = ((short)*(undefined4 *)(param_1 + 0x2e8) - sVar7) + (short)iVar18;
          *(ushort *)(param_1 + 0x2e8) = uVar8;
          if (iVar3 == 4) {
            if ((2 < *(uint *)(param_1 + 0x164)) && (*(uint *)(param_1 + 0x164) < 0x10))
            goto code_r0x001bc9bf;
code_r0x001bc9c4:
            uVar8 = uVar8 >> 3;
          }
          else {
            if ((iVar3 != 7) && (iVar3 != 0xb)) goto code_r0x001bc9c4;
code_r0x001bc9bf:
            uVar8 = uVar8 >> 1;
          }
          *(ushort *)(param_1 + 0x2e4) = uVar8;
          iVar3 = *(int *)(param_1 + 0x2fc);
          iVar15 = iVar3 + 1;
          *(short *)(param_1 + 0x2ea + (long)iVar3 * 2) = (short)iVar18;
          iVar4 = *(int *)(param_1 + 0x160);
          *(int *)(param_1 + 0x2fc) = iVar15;
          if (iVar4 == 4) {
            if ((2 < *(uint *)(param_1 + 0x164)) && (*(uint *)(param_1 + 0x164) < 0x10))
            goto code_r0x001bca17;
code_r0x001bca1b:
            bVar22 = SBORROW4(iVar15,7);
            iVar3 = iVar3 + -6;
            bVar21 = iVar15 == 7;
          }
          else {
            if ((iVar4 != 7) && (iVar4 != 0xb)) goto code_r0x001bca1b;
code_r0x001bca17:
            bVar22 = SBORROW4(iVar15,1);
            bVar21 = iVar3 == 0;
          }
          if (!bVar21 && bVar22 == iVar3 < 0) {
            *(undefined4 *)(param_1 + 0x2fc) = 0;
          }
        }
        if ((iVar14 < 0) || ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000)) {
          if ((iVar20 < 0) || ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0)) goto code_r0x001bcaad;
          if (-1 < iVar13) goto code_r0x001bca54;
        }
        else {
code_r0x001bca54:
          lVar16 = (long)*(int *)(param_1 + 0x400) + 0x1f8;
          sVar7 = *(short *)(param_1 + 6 + lVar16 * 2);
          *(undefined2 *)(param_1 + 0x3ec) = *(undefined2 *)(param_1 + 0x3ea);
          uVar8 = (*(short *)(param_1 + 0x3f2) - sVar7) + (short)iVar14;
          *(ushort *)(param_1 + 0x3f2) = uVar8;
          *(ushort *)(param_1 + 0x3ea) = uVar8 >> 1;
          iVar20 = *(int *)(param_1 + 0x400) + 1;
          *(short *)(param_1 + 6 + lVar16 * 2) = (short)iVar14;
          iVar14 = 0;
          if (iVar20 < 2) {
            iVar14 = iVar20;
          }
          *(int *)(param_1 + 0x400) = iVar14;
code_r0x001bcaad:
          if (-1 < iVar13) {
            lVar16 = (long)*(int *)(param_1 + 0x404) + 0x1f8;
            sVar7 = *(short *)(param_1 + 10 + lVar16 * 2);
            *(short *)(param_1 + 0x3ee) = (short)*(undefined4 *)(param_1 + 1000);
            uVar8 = ((short)*(undefined4 *)(param_1 + 0x3f4) - sVar7) + (short)iVar13;
            *(ushort *)(param_1 + 0x3f4) = uVar8;
            *(ushort *)(param_1 + 1000) = uVar8 >> 1;
            iVar14 = *(int *)(param_1 + 0x404) + 1;
            *(short *)(param_1 + 10 + lVar16 * 2) = (short)iVar13;
            iVar20 = 0;
            if (iVar14 < 2) {
              iVar20 = iVar14;
            }
            *(int *)(param_1 + 0x404) = iVar20;
          }
        }
        if ((iVar19 < 0) || ((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000)) {
          if ((-1 < iVar18) && ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) {
            if (iVar11 < 0) goto code_r0x001bcbd9;
            goto code_r0x001bcb30;
          }
        }
        else {
code_r0x001bcb30:
          iVar20 = *(int *)(param_1 + 0x418) + 1;
          lVar16 = (long)*(int *)(param_1 + 0x418) + 0x208;
          sVar7 = *(short *)(param_1 + 4 + lVar16 * 2);
          *(undefined2 *)(param_1 + 0x40c) = *(undefined2 *)(param_1 + 0x40a);
          uVar8 = (ushort)((uint)(ushort)((short)*(undefined4 *)(param_1 + 0x410) - sVar7) + iVar19)
          ;
          *(ushort *)(param_1 + 0x410) = uVar8;
          *(ushort *)(param_1 + 0x40a) = uVar8 >> 1;
          iVar14 = 0;
          if (iVar20 < 2) {
            iVar14 = iVar20;
          }
          *(short *)(param_1 + 4 + lVar16 * 2) = (short)iVar19;
          *(int *)(param_1 + 0x418) = iVar14;
        }
        if (-1 < iVar11) {
          lVar16 = (long)*(int *)(param_1 + 0x420) + 0x208;
          sVar7 = *(short *)(param_1 + 0xc + lVar16 * 2);
          *(short *)(param_1 + 0x40e) = (short)*(undefined4 *)(param_1 + 0x408);
          uVar8 = (*(short *)(param_1 + 0x412) - sVar7) + (short)iVar11;
          *(ushort *)(param_1 + 0x412) = uVar8;
          *(ushort *)(param_1 + 0x408) = uVar8 >> 1;
          iVar14 = *(int *)(param_1 + 0x420) + 1;
          *(short *)(param_1 + 0xc + lVar16 * 2) = (short)iVar11;
          iVar20 = 0;
          if (iVar14 < 2) {
            iVar20 = iVar14;
          }
          *(int *)(param_1 + 0x420) = iVar20;
        }
      }
    }
    else if ((iVar3 == 7) || (iVar3 == 0xb)) goto code_r0x001bc95b;
  }
code_r0x001bcbd9:
  iVar14 = *(int *)(param_1 + 0x160);
  lVar16 = *(long *)(param_1 + 0x20);
  if (iVar14 == 0xb) {
    if ((*(byte *)(lVar16 + 0x80) & 1) != 0) {
      wlc_phy_desense_aci_engine_acphy(param_1);
    }
    if ((*(byte *)(*(long *)(param_1 + 0x20) + 0x80) & 6) != 0) {
      wlc_phy_hwaci_engine_acphy(param_1);
    }
    goto code_r0x001bd048;
  }
  iVar20 = *(int *)(lVar16 + 0x80);
  bVar21 = iVar12 - 3U < 3;
  if (iVar20 == 3) {
    if (iVar14 == 2) {
      if ((*(byte *)(param_1 + 0xc0c) & 1) == 0) {
        if (*(int *)(param_1 + 0x4ac) < (int)(uint)*(ushort *)(param_1 + 0x488)) {
          if (*(int *)(param_1 + 0x4b8) == 0) {
            wlapi_suspend_mac_and_wait(*(undefined8 *)(lVar16 + 0x20));
            if ((*(int *)(param_1 + 0x160) == 2) &&
               (cVar6 = wlc_phy_aci_scan_gphy(param_1), cVar6 != '\0')) {
              *(undefined4 *)(param_1 + 0xc00) = *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
              wlc_phy_aci_ctl_gphy(param_1,1);
              *(undefined4 *)(param_1 + 0x4b8) = 0;
            }
            else {
              *(int *)(param_1 + 0x4b8) = *(int *)(param_1 + 0x4b4) + 1;
            }
            wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
          }
          if (*(int *)(param_1 + 0x4b8) != 0) {
            *(int *)(param_1 + 0x4b8) = *(int *)(param_1 + 0x4b8) + -1;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x4b8) = 0;
        }
      }
      else if (((uint)(*(int *)(lVar16 + 0x34) - *(int *)(param_1 + 0xc00)) %
                *(uint *)(param_1 + 0xc04) == 0) &&
              ((int)(uint)*(ushort *)(param_1 + 0x488) < *(int *)(param_1 + 0x4a8))) {
        wlapi_suspend_mac_and_wait(*(undefined8 *)(lVar16 + 0x20));
        if ((*(int *)(param_1 + 0x160) == 2) &&
           (cVar6 = wlc_phy_aci_scan_gphy(param_1), cVar6 == '\0')) {
          *(undefined4 *)(param_1 + 0xc00) = 0;
          wlc_phy_aci_ctl_gphy(param_1,0);
        }
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      }
      goto code_r0x001bd048;
    }
    if (iVar14 == 5) {
      wlc_phy_aci_upd_lpphy(param_1);
      goto code_r0x001bd048;
    }
    if (iVar14 == 8) {
      if (*(int *)(lVar16 + 0x3c) == 0x4313) goto code_r0x001bd001;
    }
    else if ((iVar14 == 10) && (*(int *)(lVar16 + 0x3c) == 0xa886)) goto code_r0x001bd019;
    if (*(long *)(param_1 + 0x160) != 0x300000006) {
      if (((iVar14 != 7) && (iVar14 != 4)) || ((*(uint *)(param_1 + 0x19c) & 1) != 0))
      goto code_r0x001bd048;
      if ((*(uint *)(param_1 + 0x164) < 0x13) && (*(uint *)(param_1 + 0x164) != 0x10)) {
        if (((*(ushort *)(param_1 + 0x17e) & 0xc000) != 0xc000) &&
           ((*(uint *)(param_1 + 0x19c) & 0x20) == 0)) {
          if ((*(byte *)(param_1 + 0xc0c) & 1) == 0) {
            if (((*(uint *)(lVar16 + 0x34) & 1) != 0) ||
               ((int)((uint)*(ushort *)(param_1 + 0x2e4) + (uint)*(ushort *)(param_1 + 0x488)) <
                *(int *)(param_1 + 0x4ac))) goto code_r0x001bd048;
          }
          else if ((*(uint *)(lVar16 + 0x34) - *(int *)(param_1 + 0xc00)) %
                   *(uint *)(param_1 + 0xc04) != 0) goto code_r0x001bd048;
          if (iVar14 != 4) {
            if (iVar14 == 7) {
              wlc_phy_acimode_upd_htphy(param_1);
            }
          }
          else {
            wlc_phy_acimode_upd_nphy(param_1);
          }
        }
        goto code_r0x001bd048;
      }
      goto code_r0x001bcefa;
    }
  }
  else {
    if (iVar20 != 4) {
      if (iVar20 != 1) goto code_r0x001bd048;
      if (iVar14 != 4) {
        if (iVar14 == 7) {
          wlc_phy_noisemode_upd_htphy(param_1);
        }
        goto code_r0x001bd048;
      }
      if ((bVar21) || (0xf < *(uint *)(param_1 + 0x164))) {
        wlc_phy_noisemode_upd_nphy(param_1);
        goto code_r0x001bd048;
      }
      if (9 < *(uint *)(param_1 + 0x164) - 6) goto code_r0x001bd048;
      goto code_r0x001bcfba;
    }
    if ((iVar14 == 7) || (iVar14 == 4)) {
      uVar5 = *(uint *)(param_1 + 0x164);
      if ((0x12 < uVar5) || (uVar5 == 0x10)) {
code_r0x001bcefa:
        wlc_phy_aci_noise_measure_nphy(param_1,1);
        goto code_r0x001bd048;
      }
      if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) goto code_r0x001bd048;
      if ((bVar21) || (0xf < uVar5)) {
        wlc_phy_aci_noise_upd_nphy(param_1);
        goto code_r0x001bd048;
      }
      if (iVar14 != 4) {
        if (iVar14 == 7) {
          wlc_phy_aci_noise_upd_htphy(param_1);
        }
        goto code_r0x001bd048;
      }
      if (9 < uVar5 - 6) goto code_r0x001bd048;
      bVar21 = true;
      if (*(short *)(param_1 + 0x3d6) < 4) {
        bVar21 = 3 < *(short *)(param_1 + 0x3d4);
      }
      if ((*(byte *)(param_1 + 0xc0c) & 1) == 0) {
        if (((*(uint *)(lVar16 + 0x34) & 1) == 0) &&
           ((bVar21 ||
            (*(int *)(param_1 + 0x4ac) <=
             (int)((*(uint *)(param_1 + 0x2e4) & 0xffff) + (*(uint *)(param_1 + 0x488) & 0xffff)))))
           ) {
code_r0x001bcfb2:
          wlc_phy_acimode_upd_nphy(param_1);
        }
      }
      else if ((*(uint *)(lVar16 + 0x34) - *(int *)(param_1 + 0xc00)) % *(uint *)(param_1 + 0xc04)
               == 0) goto code_r0x001bcfb2;
code_r0x001bcfba:
      func_0x001b68b7(param_1);
      goto code_r0x001bd048;
    }
    if (*(long *)(param_1 + 0x160) != 0x300000006) {
      if (iVar14 != 8) {
        if ((iVar14 != 10) || (*(int *)(lVar16 + 0x3c) != 0xa886)) goto code_r0x001bd048;
code_r0x001bd019:
        wlc_lcn40phy_aci_upd(param_1);
        goto code_r0x001bd048;
      }
      if (*(int *)(lVar16 + 0x3c) != 0x4313) goto code_r0x001bd048;
code_r0x001bd001:
      wlc_lcnphy_aci_noise_measure(param_1);
      goto code_r0x001bd048;
    }
  }
  wlc_sslpnphy_noise_measure(param_1);
code_r0x001bd048:
  if (*(uint *)(*(long *)(param_1 + 0x20) + 0x34) % *(uint *)(*(long *)(param_1 + 0x20) + 0x74) == 0
     ) {
    wlc_phyreg_enter(param_1);
    wlapi_update_bt_chanspec
              (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),*(undefined2 *)(param_1 + 0x17e),
               *(uint *)(param_1 + 0x19c) >> 1 & 1,*(uint *)(param_1 + 0x19c) >> 2 & 1);
    wlc_phyreg_exit(param_1);
    if ((*(int *)(param_1 + 0x160) == 5) && (*(uint *)(param_1 + 0x164) < 2)) {
      wlc_phy_radio_2062_check_vco_cal(param_1);
    }
  }
  if ((*(uint *)(param_1 + 0x19c) & 0x20e) == 0) {
    func_0x001bbd36(param_1,1,*(undefined1 *)(param_1 + 0x17e));
  }
  if ((*(char *)(param_1 + 399) != '\0') &&
     (5 < (uint)(*(int *)(*(long *)(param_1 + 0x20) + 0x34) - *(int *)(param_1 + 400)))) {
    *(undefined1 *)(param_1 + 399) = 0;
  }
  if ((((*(int *)(param_1 + 0xc44) == 0) ||
       (*(uint *)(*(long *)(param_1 + 0x20) + 0x74) <=
        (uint)(*(int *)(*(long *)(param_1 + 0x20) + 0x34) - *(int *)(param_1 + 0xc44)))) &&
      ((*(byte *)(param_1 + 0x19c) & 2) == 0)) && (cVar6 = func_0x001b7fe4(param_1), cVar6 != '\0'))
  {
    *(undefined4 *)(param_1 + 0xc44) = *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
  }
  if ((*(uint *)(param_1 + 0x19c) & 0x20f) == 0) {
    if ((*(int *)(param_1 + 0x160) == 0xb) &&
       (*(char *)(*(long *)(param_1 + 0x138) + 0x912) != '\0')) {
      wlc_phy_hirssi_elnabypass_engine(param_1);
    }
    if (*(int *)(param_1 + 0x160) == 10) {
      wlc_lcn40phy_update_cond_backoff_boost(param_1);
    }
    bVar21 = false;
    if (*(int *)(param_1 + 0x160) == 2) {
      if (((*(char *)(param_1 + 0x199) == '\0') &&
          (*(uint *)(*(long *)(param_1 + 0x20) + 0x7c) <=
           (uint)(*(int *)(*(long *)(param_1 + 0x20) + 0x34) - *(int *)(lVar17 + 0x470)))) &&
         (1 < *(uint *)(param_1 + 0x164))) {
        bVar21 = true;
        wlc_phy_cal_measurelo_gphy(param_1);
      }
      else {
        bVar21 = false;
      }
      if ((*(uint *)(*(long *)(param_1 + 0x20) + 0x34) % *(uint *)(*(long *)(param_1 + 0x20) + 0x78)
           == 0) && (*(char *)(param_1 + 0x220) == '\0')) {
        wlc_phy_cal_txpower_stats_clr_gphy(param_1);
      }
      lVar16 = *(long *)(param_1 + 0x20);
      if ((((*(uint *)(lVar16 + 0x78) <= (uint)(*(int *)(lVar16 + 0x34) - *(int *)(lVar17 + 0x46c)))
           && ((*(byte *)(lVar16 + 100) & 8) != 0)) && (!bVar21)) &&
         (*(char *)(param_1 + 0x16c) == '\b')) {
        bVar21 = true;
        wlapi_suspend_mac_and_wait(*(undefined8 *)(lVar16 + 0x20));
        wlc_phy_cal_radio2050_nrssioffset_gmode1(param_1);
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      }
      lVar16 = *(long *)(param_1 + 0x20);
      if (((*(uint *)(lVar16 + 0x78) <= (uint)(*(int *)(lVar16 + 0x34) - *(int *)(lVar17 + 0x468)))
          && (!bVar21)) && ((*(byte *)(lVar16 + 100) & 8) != 0)) {
        wlapi_suspend_mac_and_wait(*(undefined8 *)(lVar16 + 0x20));
        wlc_phy_cal_radio2050_nrssislope(param_1);
        if ((*(ulong *)(param_1 + 0x168) & 0xffffff0000) == 0x820500000) {
          uVar2 = *(undefined2 *)(param_1 + 0x17e);
          wlc_phy_chanspec_set(param_1,(-(uint)((byte)uVar2 < 8) & 0xc) + 0x1001);
          wlc_phy_chanspec_set(param_1,uVar2);
        }
        bVar21 = true;
        wlapi_enable_mac(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
      }
    }
    if (((*(int *)(param_1 + 0x160) == 4) && (!bVar21)) &&
       ((*(char *)(param_1 + 0x199) == '\0' &&
        ((lVar17 = *(long *)(param_1 + 0x20), *(int *)(lVar17 + 0x3c) != 0xa8e5 ||
         ((*(byte *)(param_1 + 0x19d) & 1) == 0)))))) {
      if ((*(char *)(param_1 + 0xf89) != '\x03') &&
         ((*(char *)(param_1 + 0xf89) != '\0' &&
          (*(uint *)(lVar17 + 0x7c) <=
           (uint)(*(int *)(lVar17 + 0x34) - *(int *)(*(long *)(param_1 + 0xf58) + 0xc0)))))) {
        wlc_phy_cal_perical(param_1,2);
        if (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0xa8e5) {
          *(undefined4 *)(*(long *)(param_1 + 0xf58) + 0xc0) =
               *(undefined4 *)(*(long *)(param_1 + 0x20) + 0x34);
        }
      }
      wlc_phy_txpwr_papd_cal_nphy(param_1);
      wlc_phy_radio205x_check_vco_cal_nphy(param_1);
    }
    if ((((*(int *)(param_1 + 0x160) == 0xb) || (*(int *)(param_1 + 0x160) == 7)) && (!bVar21)) &&
       (((*(char *)(param_1 + 0x199) == '\0' && (*(char *)(param_1 + 0xf89) != '\x03')) &&
        ((*(char *)(param_1 + 0xf89) != '\0' &&
         ((*(int *)(*(long *)(param_1 + 0xf58) + 200) == 0 &&
          (*(uint *)(*(long *)(param_1 + 0x20) + 0x7c) <=
           (uint)(*(int *)(*(long *)(param_1 + 0x20) + 0x34) -
                 *(int *)(*(long *)(param_1 + 0xf58) + 0xc0)))))))))) {
      wlc_phy_cal_perical(param_1,2);
    }
    if (*(int *)(param_1 + 0x160) == 5) {
      lVar17 = *(long *)(param_1 + 0x138);
      if ((((*(char *)(param_1 + 0xc20) != '\0') ||
           (cVar6 = wlc_lpphy_txrxiq_cal_reqd(param_1), cVar6 != '\0')) &&
          (*(char *)(param_1 + 0xc28) == '\0')) && (*(char *)(param_1 + 0x199) == '\0')) {
        wlc_phy_periodic_cal_lpphy(param_1);
      }
      if ((((1 < *(uint *)(param_1 + 0x164)) &&
           ((*(char *)(lVar17 + 0x30) == '\x01' ||
            (cVar6 = wlc_lpphy_papd_cal_reqd(param_1), cVar6 != '\0')))) &&
          (*(char *)(param_1 + 0xc28) == '\0')) && (*(char *)(param_1 + 0x199) == '\0')) {
        wlc_phy_papd_cal_txpwr_lpphy(param_1,*(undefined1 *)(lVar17 + 0x30));
      }
    }
    iVar12 = *(int *)(*(long *)(param_1 + 0xf58) + 200);
    if (iVar12 != 0) {
      *(int *)(*(long *)(param_1 + 0xf58) + 200) = iVar12 + -1;
    }
    if (*(code **)(param_1 + 0x100) != (code *)0x0) {
      (**(code **)(param_1 + 0x100))(param_1);
    }
    if (((*(int *)(param_1 + 0x160) == 4) && (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) == 0x4324))
       && ((*(int *)(*(long *)(param_1 + 0x20) + 0x40) - 3U < 2 &&
           ((*(uint *)(param_1 + 0x19c) & 0x20e) == 0)))) {
      wlc_phy_txpwr_update_baseidx_nphy(param_1);
    }
    iVar12 = wlapi_bmac_btc_mode_get(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    if (iVar12 != 0) {
      wlapi_bmac_btc_period_get
                (*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),auStack_3c,acStack_39);
      if ((acStack_39[0] != *(char *)(param_1 + 0xfa2)) &&
         (*(code **)(param_1 + 0xf8) != (code *)0x0)) {
        (**(code **)(param_1 + 0xf8))(param_1,acStack_39[0]);
      }
      *(short *)(param_1 + 0xfa4) = (short)_auStack_3c;
      *(char *)(param_1 + 0xfa2) = acStack_39[0];
    }
    if (*(int *)(param_1 + 0x160) == 0xb) {
      wlc_phy_stop_bt_toggle_acphy(param_1);
    }
    if (((*(int *)(param_1 + 0x160) == 8) && ((*(uint *)(param_1 + 0x19c) & 0x20f) == 0)) &&
       (*(int *)(*(long *)(param_1 + 0x20) + 0x3c) != 0x4313)) {
      wlc_lcnphy_noise_measure(param_1);
    }
    if ((*(int *)(param_1 + 0x160) == 7) && (*(uint *)(*(long *)(param_1 + 0x20) + 0x34) % 10 == 0))
    {
      wlc_phy_tempsense_htphy(param_1);
    }
  }
  return 0;
}

