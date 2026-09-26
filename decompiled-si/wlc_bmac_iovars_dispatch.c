
uint wlc_bmac_iovars_dispatch
               (long *param_1,uint param_2,undefined8 param_3,long param_4,uint param_5,
               uint *param_6)

{
  long *plVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  long lVar10;
  ulong uVar11;
  undefined4 *puVar12;
  char *pcVar13;
  undefined8 uVar14;
  undefined1 local_58 [4];
  int local_54;
  undefined4 local_44;
  uint local_40;
  uint local_3c [3];
  
  local_3c[0] = 0;
  local_40 = 0;
  if ((3 < param_5) && (osl_memcpy(local_3c,param_4,4), 7 < param_5)) {
    osl_memcpy(&local_40,param_4 + 4,4);
  }
  if (param_2 == 0x58) {
    lVar10 = param_1[0x18];
    pcVar13 = "wpsled";
LAB_00167fb2:
    lVar10 = getvar(lVar10,pcVar13);
    if (lVar10 == 0) {
      *param_6 = 0xffffffff;
      return 0xffffffe2;
    }
  }
  else {
    if (0x58 < param_2) {
      if (param_2 == 0x67) {
        if ((ushort)local_3c[0] < 2) {
          *(ushort *)((long)param_1 + 0x1aa) = (ushort)local_3c[0];
          if ((local_3c[0] & 1) == 0) {
            uVar14 = 0;
          }
          else {
            uVar14 = 0x20;
          }
          wlc_bmac_mhf(param_1,2,0x20,uVar14,3);
          return 0;
        }
        return 0xffffffe9;
      }
      if (param_2 < 0x68) {
        if (param_2 == 0x61) {
          osl_memcpy(local_58,param_6,0x10);
          iVar9 = local_54 + 0xc;
          puVar12 = (undefined4 *)osl_malloc(param_1[2],iVar9);
          if (puVar12 == (undefined4 *)0x0) {
            return 0xffffffe5;
          }
          osl_memcpy(puVar12,param_6,iVar9);
          if ((ushort)((ushort)*puVar12 >> 0xc) == 1) {
            if (*(short *)((long)puVar12 + 2) == 2) {
              wlc_handle_clm_dload
                        (*(undefined8 *)(*param_1 + 0x1a0),puVar12 + 8,puVar12[7],puVar12[6],
                         puVar12[4],puVar12[3]);
            }
            osl_mfree(param_1[2],puVar12,iVar9);
            return 0;
          }
          osl_mfree(param_1[2],puVar12,iVar9);
          return 0xffffffff;
        }
        if (param_2 < 0x62) {
          if (param_2 != 0x5a) {
            if (param_2 == 0x5b) {
              *(bool *)(param_1 + 0x35) = local_3c[0] != 0;
              return 0;
            }
            return 0xffffffe2;
          }
          uVar6 = (uint)*(byte *)(param_1 + 0x35);
        }
        else {
          if (param_2 == 100) {
            *param_6 = 0x5b0;
            return 0;
          }
          if (param_2 == 0x66) {
            uVar6 = (uint)*(ushort *)((long)param_1 + 0x1aa);
          }
          else {
            if (param_2 != 0x62) {
              return 0xffffffe2;
            }
            uVar6 = (uint)*(byte *)(*param_1 + 0x6da);
          }
        }
      }
      else if (param_2 == 0x74) {
        uVar6 = *(uint *)(param_1 + 0x38);
      }
      else if (param_2 < 0x75) {
        if (param_2 != 0x6e) {
          if (param_2 != 0x6f) {
            if (param_2 == 0x68) {
              lVar10 = 0;
              uVar6 = 0;
              do {
                plVar1 = *(long **)((long)param_1 + lVar10 + 0x20);
                if (plVar1 != (long *)0x0) {
                  iVar9 = (**(code **)(*plVar1 + 0x168))();
                  uVar6 = uVar6 + iVar9;
                }
                lVar10 = lVar10 + 8;
              } while (lVar10 != 0x30);
              *param_6 = uVar6;
              return 0;
            }
            return 0xffffffe2;
          }
          if (2 < local_3c[0] + 1) {
            return 0xffffffe3;
          }
          if ((*(short *)(param_1[0x1d] + 0x1c) == 0xb) &&
             (*(char *)((long)param_1 + 0x10c) == '\0')) {
            return 0xfffffffc;
          }
          uVar6 = wlc_bmac_set_btswitch(param_1,(int)(char)local_3c[0]);
          return uVar6;
        }
        iVar9 = *(int *)(param_1[0x17] + 0x3c);
        if ((((iVar9 != 0xa9a7) && (iVar9 != 0x4331)) ||
            (((iVar9 = *(int *)(param_1[0x17] + 0x28), iVar9 != 0x10e &&
              (((iVar9 != 0xe4 && (iVar9 != 0x5c6)) && (iVar9 != 0xef)))) && (iVar9 != 0x10f)))) &&
           (*(short *)(param_1[0x1d] + 0x1c) != 0xb)) {
          return 0xffffffe9;
        }
        if (*(short *)(param_1[0x1d] + 0x1c) == 0xb) {
          if (*(char *)((long)param_1 + 0x10c) == '\0') {
            return 0xfffffffc;
          }
          uVar4 = wlc_phy_get_femctrl_bt_wlan_ovrd(*(undefined8 *)(param_1[0x1d] + 0x28));
          *(undefined1 *)((long)param_1 + 0x1bc) = uVar4;
        }
        uVar6 = (uint)*(char *)((long)param_1 + 0x1bc);
      }
      else {
        if (param_2 != 0x78) {
          if (param_2 != 0x79) {
            if (param_2 == 0x75) {
              *(uint *)(param_1 + 0x38) = local_3c[0];
              return 0;
            }
            return 0xffffffe2;
          }
          sVar5 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
          if (sVar5 == 4) {
            if (*(uint *)((long)param_1 + 0x84) < 0x10) {
              return 0xffffffe9;
            }
          }
          else if ((sVar5 != 7) && (sVar5 != 0xb)) {
            return 0xffffffe9;
          }
          if (local_3c[0] != 0) {
            wlc_bmac_ifsctl_edcrs_set(param_1,*(short *)(*(long *)(*param_1 + 0x40) + 8) == 7);
            return 0;
          }
          if (sVar5 == 0xb) {
            FUN_00162e6d(param_1,0);
            return 0;
          }
          FUN_00163019(param_1,0x38,0);
          return 0;
        }
        sVar5 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
        if (sVar5 == 4) {
          if (*(uint *)((long)param_1 + 0x84) < 0x10) {
            return 0xffffffe9;
          }
        }
        else if ((sVar5 != 7) && (sVar5 != 0xb)) {
          return 0xffffffe9;
        }
        uVar11 = wlc_bmac_read_shm(param_1,0x5a);
        sVar5 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
        if (sVar5 == 0xb) {
          uVar11 = uVar11 & 0xf00;
        }
        else {
          if (sVar5 != 7) {
            uVar6 = (uint)((uVar11 & 0xffff) >> 3) & 1;
            goto LAB_00167fc9;
          }
          uVar11 = uVar11 & 0x38;
        }
        uVar6 = (uint)(uVar11 != 0);
      }
      goto LAB_00167fc9;
    }
    if (param_2 == 0x16) {
      lVar10 = param_1[0x17];
      if (*(int *)(lVar10 + 4) != 1) {
        return 0xffffffe9;
      }
      if (*(int *)(lVar10 + 8) != 0x820) {
        return 0xffffffe9;
      }
      uVar14 = 1;
      uVar6 = 0x114;
LAB_00168165:
      uVar6 = si_pciereg(lVar10,uVar6,0,0,uVar14);
      goto LAB_00167fc9;
    }
    if (param_2 < 0x17) {
      if (param_2 == 0xc) {
        uVar6 = si_gpioin(param_1[0x17]);
        goto LAB_00167fc9;
      }
      if (param_2 < 0xd) {
        if (param_2 != 2) {
          if (param_2 != 3) {
            return 0xffffffe2;
          }
          si_gpiotimerval(param_1[0x17],0xffffffff,local_3c[0]);
          return 0;
        }
        uVar6 = si_gpiotimerval(param_1[0x17],0,0);
        goto LAB_00167fc9;
      }
      if (param_2 == 0x14) {
        bVar2 = si_pcieclkreq(param_1[0x17],0,0);
        uVar6 = si_pcielcreg(param_1[0x17],0,0);
        uVar7 = si_pcie_get_L1substate(param_1[0x17]);
        uVar6 = (uVar7 & 3) << 2 | uVar6 & 3 | (bVar2 & 1) << 8;
        goto LAB_00167fc9;
      }
      if (0x14 < param_2) {
        uVar6 = si_pcielcreg(param_1[0x17],0,0);
        si_pcielcreg(param_1[0x17],3,uVar6 & 0xfffffffc | local_3c[0] & 3);
        si_pcieclkreq(param_1[0x17],1,(int)(local_3c[0] & 0x100) >> 8);
        si_pcie_set_L1substate(param_1[0x17],(int)(local_3c[0] & 0xc) >> 2);
        return 0;
      }
      if (param_2 != 0xe) {
        return 0xffffffe2;
      }
      lVar10 = param_1[0x18];
      pcVar13 = "wpsgpio";
      goto LAB_00167fb2;
    }
    if (param_2 == 0x26) {
      if (param_5 < 8) {
        return 0xfffffff2;
      }
      if ((int)local_3c[0] < 0) {
        return 0xfffffffe;
      }
      if ((int)local_40 < 0) {
        return 0xfffffffe;
      }
      uVar6 = si_pcieserdesreg(param_1[0x17],local_3c[0],local_40,0,0);
      goto LAB_00167fc9;
    }
    if (param_2 < 0x27) {
      if (param_2 != 0x20) {
        if (param_2 == 0x21) {
          if (param_5 < 8) {
            return 0xfffffff2;
          }
          if ((int)local_3c[0] < 0) {
            return 0xfffffffe;
          }
          lVar10 = param_1[0x17];
          uVar14 = 2;
          uVar6 = local_40;
          uVar7 = local_3c[0];
        }
        else {
          if (param_2 != 0x17) {
            return 0xffffffe2;
          }
          if (*(int *)(param_1[0x17] + 4) != 1) {
            return 0xffffffe9;
          }
          if (*(int *)(param_1[0x17] + 8) != 0x820) {
            return 0xffffffe9;
          }
          uVar6 = 0x11c1;
          if (local_3c[0] != 0xffffffff) {
            uVar6 = local_3c[0];
          }
          lVar10 = param_1[0x17];
          uVar14 = 1;
          local_3c[0] = uVar6 & 0x11c1;
          uVar6 = local_3c[0];
          uVar7 = 0x114;
        }
        si_pciereg(lVar10,uVar7,1,uVar6,uVar14);
        return 0;
      }
      if (param_5 < 4) {
        return 0xfffffff2;
      }
      if ((int)local_3c[0] < 0) {
        return 0xfffffffe;
      }
      lVar10 = param_1[0x17];
      uVar14 = 2;
      uVar6 = local_3c[0];
      goto LAB_00168165;
    }
    if (param_2 == 0x44) {
      uVar8 = wl_intrsoff(*(undefined8 *)(*param_1 + 0x10));
      cVar3 = si_is_sprom_available(param_1[0x17]);
      if (cVar3 == '\0') {
        cVar3 = si_is_otp_disabled(param_1[0x17]);
        uVar6 = (-(uint)(cVar3 == '\0') & 7) - 0x1e;
      }
      else {
        cVar3 = si_is_sprom_enabled();
        if (cVar3 == '\0') {
          si_sprom_enable(param_1[0x17],1);
        }
        iVar9 = srom_read(param_1[0x17],*(undefined4 *)(param_1[0x17] + 4),param_1[0x1a],param_1[2],
                          *param_6,param_6[1],param_6 + 2,0);
        uVar6 = ~-(uint)(iVar9 == 0);
        if (cVar3 == '\0') {
          si_sprom_enable(param_1[0x17],0);
        }
      }
      wl_intrsrestore(*(undefined8 *)(*param_1 + 0x10),uVar8);
      return uVar6;
    }
    if (param_2 != 0x52) {
      if (param_2 != 0x27) {
        return 0xffffffe2;
      }
      if (param_5 < 0xc) {
        return 0xfffffff2;
      }
      if ((int)local_3c[0] < 0) {
        return 0xfffffffe;
      }
      if (-1 < (int)local_40) {
        if (*(int *)(param_1[0x17] + 4) == 1) {
          osl_memcpy(&local_44,param_4 + 8,4);
          si_pcieserdesreg(param_1[0x17],local_3c[0],local_40,1,local_44);
          return 0;
        }
        return 0xffffffe9;
      }
      return 0xfffffffe;
    }
    lVar10 = getvar(param_1[0x18],"customvar1");
    if (lVar10 == 0) {
      *param_6 = 0;
      return 0;
    }
  }
  uVar6 = bcm_strtoul(lVar10,0,0);
LAB_00167fc9:
  *param_6 = uVar6;
  return 0;
}

