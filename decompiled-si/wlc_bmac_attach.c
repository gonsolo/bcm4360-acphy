
undefined4
wlc_bmac_attach(long *param_1,undefined2 param_2,short param_3,undefined4 param_4,undefined1 param_5
               ,undefined8 param_6,undefined8 param_7,int param_8)

{
  ushort *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  long *plVar5;
  char cVar6;
  undefined1 uVar7;
  short sVar8;
  ushort uVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  uint uVar13;
  long *plVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  uint uVar19;
  long lVar20;
  undefined8 uVar21;
  long lVar22;
  bool bVar23;
  bool bVar24;
  bool bVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined8 local_a8;
  long local_a0;
  long local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  long local_80;
  undefined2 local_78;
  undefined2 local_76;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  uint local_68;
  undefined4 local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_48 [12];
  undefined4 local_3c [3];
  
  local_3c[0] = 0;
  plVar14 = (long *)wlc_hw_attach(param_1,param_6,param_4,local_3c);
  if (plVar14 == (long *)0x0) {
    return local_3c[0];
  }
  param_1[4] = (long)plVar14;
  *(undefined1 *)((long)plVar14 + 0x102) = 0;
  *(undefined2 *)(plVar14 + 0x21) = 3;
  *(undefined2 *)((long)plVar14 + 0x10a) = 2;
  *(undefined2 *)((long)plVar14 + 0x104) = 7;
  *(undefined2 *)((long)plVar14 + 0x106) = 4;
  *(undefined1 *)((long)plVar14 + 0x1c) = param_5;
  *(undefined4 *)((long)plVar14 + 0x9c) = 0xb0e7a860;
  *(undefined4 *)((long)plVar14 + 0x1c4) = 0;
  *(undefined2 *)((long)plVar14 + 0x11c) = 0x1001;
  *(undefined1 *)((long)plVar14 + 0x1bc) = 0xff;
  plVar14[0x17] = *(long *)(*param_1 + 0x100);
  lVar18 = *(long *)(*param_1 + 0x108);
  plVar14[0x18] = lVar18;
  *(undefined4 *)(plVar14 + 0x19) = *(undefined4 *)(*param_1 + 0x110);
  if (param_8 != 0) {
    lVar15 = getvar(lVar18,"vendid");
    if (lVar15 != 0) {
      param_2 = bcm_strtoul(lVar15,0,0);
    }
    lVar15 = getvar(lVar18,"devid");
    if ((lVar15 != 0) && (sVar8 = bcm_strtoul(lVar15,0,0), sVar8 != -1)) {
      param_3 = sVar8;
    }
    cVar6 = wlc_chipmatch(param_2,param_3);
    if (cVar6 == '\0') {
      return 0xc;
    }
  }
  *(short *)((long)plVar14 + 0x82) = param_3;
  *(undefined2 *)(plVar14 + 0x10) = param_2;
  iVar10 = wlc_is_singleband_5g(param_3);
  plVar14[0x1d] = *(long *)((long)plVar14 + (-(ulong)(iVar10 == 0) & 0xfffffffffffffff8) + 0xf8);
  iVar10 = wlc_is_singleband_5g(*(undefined2 *)((long)plVar14 + 0x82));
  param_1[8] = *(long *)((long)param_1 + (-(ulong)(iVar10 == 0) & 0xfffffffffffffff8) + 0x58);
  lVar15 = si_setcore(plVar14[0x17],0x812,0);
  plVar14[0x1a] = lVar15;
  uVar11 = si_corerev(plVar14[0x17]);
  *(undefined4 *)((long)plVar14 + 0x84) = uVar11;
  wlc_tunables_override(*(undefined8 *)(*param_1 + 0x38),param_3,uVar11);
  lVar15 = plVar14[0x1a];
  param_1[3] = lVar15;
  lVar16 = plVar14[0x17];
  if (*(int *)(lVar16 + 0x3c) == 0x4306) {
    if ((2 < *(uint *)(lVar16 + 0x40)) &&
       (((*(short *)((long)plVar14 + 0x82) == 0x4324 || (*(short *)((long)plVar14 + 0x82) == 0x4321)
         ) && (*(int *)(lVar16 + 0x44) != 1)))) {
      return 0xd;
    }
  }
  else if ((*(int *)(lVar16 + 0x3c) == 0x4311) && (*(int *)(lVar16 + 0x40) == 0)) {
    return 0xd;
  }
  uVar13 = *(uint *)((long)plVar14 + 0x84);
  if (((0x1f < uVar13) || ((0xffffffb0U >> (uVar13 & 0x1f) & 1) == 0)) &&
     ((0x1f < uVar13 - 0x20 || ((0xff07U >> (uVar13 - 0x20 & 0x1f) & 1) == 0)))) {
    return 0xd;
  }
  si_clkctl_init();
  si_pcie_ltr_war(plVar14[0x17]);
  lVar16 = plVar14[0x17];
  if ((*(int *)(lVar16 + 0x3c) == 0x4350) && ((*(uint *)(lVar16 + 0x48) & 0x700000) == 0x300000)) {
    si_pcieltrenable(lVar16,1,1);
  }
  lVar16 = plVar14[0x17];
  if (((*(int *)(lVar16 + 4) == 1) && (*(int *)(lVar16 + 8) == 0x83c)) &&
     (*(uint *)(lVar16 + 0xc) < 5)) {
    si_pcieobffenable(lVar16,1,0);
  }
  FUN_001655c7(plVar14,0);
  wlc_bmac_corereset(plVar14,0xffffffff);
  cVar6 = wlc_bmac_validate_chip_access(plVar14);
  if (cVar6 == '\0') {
    return 0xe;
  }
  iVar10 = getintvar(lVar18,"boardrev");
  bVar25 = true;
  uVar9 = (ushort)iVar10;
  if (iVar10 == 0xff) {
    uVar9 = 1;
  }
  *(ushort *)((long)plVar14 + 0x8a) = uVar9;
  iVar10 = *(int *)(plVar14[0x17] + 0x28);
  if (uVar9 == 0) {
LAB_0016a8f1:
    bVar25 = false;
  }
  else if (0xff < uVar9) {
    if (((1 < (uVar9 >> 0xc) - 1) || (9 < (uVar9 & 0xf00) >> 8)) ||
       ((0x90 < (uVar9 & 0xf0) || ((uVar9 & 0xf00) == 0)))) goto LAB_0016a8f1;
    bVar25 = (uVar9 & 0xf) < 10;
  }
  if (*(int *)(plVar14[0x17] + 0x30) == 0x14e4) {
    if (iVar10 - 0x417U < 2) {
      bVar23 = uVar9 < 0x3f;
      bVar24 = uVar9 == 0x3f;
    }
    else {
      if (iVar10 == 0x40c) {
        return 0xf;
      }
      if (iVar10 != 0x421) goto LAB_0016a921;
      bVar23 = uVar9 < 0x50;
      bVar24 = uVar9 == 0x50;
    }
    if (bVar23 || bVar24) {
      return 0xf;
    }
  }
LAB_0016a921:
  if (!bVar25) {
    return 0xf;
  }
  uVar7 = getintvar(lVar18,"sromrev");
  *(undefined1 *)(plVar14 + 0x11) = uVar7;
  uVar11 = getintvar(lVar18,"boardflags");
  *(undefined4 *)((long)plVar14 + 0x8c) = uVar11;
  uVar11 = getintvar(lVar18,"boardflags2");
  *(undefined4 *)(plVar14 + 0x12) = uVar11;
  uVar7 = getintvar(lVar18,"antswctl2g");
  *(undefined1 *)((long)plVar14 + 0x1bd) = uVar7;
  uVar7 = getintvar(lVar18,"antswctl5g");
  *(undefined1 *)((long)plVar14 + 0x1be) = uVar7;
  if (*(int *)(plVar14[0x17] + 0x30) == 0x106b) {
    iVar10 = *(int *)(plVar14[0x17] + 0x28);
    if (iVar10 == 0x4e) {
      if (0x40 < *(ushort *)((long)plVar14 + 0x8a)) {
        *(uint *)((long)plVar14 + 0x8c) = *(uint *)((long)plVar14 + 0x8c) | 2;
      }
    }
    else {
      if (iVar10 == 0xe4) {
        bVar25 = *(ushort *)((long)plVar14 + 0x8a) < 0x1500;
        bVar23 = *(ushort *)((long)plVar14 + 0x8a) == 0x1500;
      }
      else {
        if (iVar10 != 0xef) goto LAB_0016a9fd;
        bVar25 = *(ushort *)((long)plVar14 + 0x8a) < 0x1201;
        bVar23 = *(ushort *)((long)plVar14 + 0x8a) == 0x1201;
      }
      if (bVar25 || bVar23) {
        *(uint *)((long)plVar14 + 0x8c) = *(uint *)((long)plVar14 + 0x8c) | 0x400000;
        *(undefined4 *)(plVar14 + 0x12) = 0;
      }
    }
  }
LAB_0016a9fd:
  if ((*(uint *)((long)plVar14 + 0x84) < 5) || ((*(byte *)((long)plVar14 + 0x8c) & 0x20) != 0)) {
    wlc_bmac_pllreq(plVar14,1,1);
  }
  if ((*(int *)(plVar14[0x17] + 4) == 1) && (cVar6 = si_pci_war16165(), cVar6 != '\0')) {
    *(undefined1 *)(param_1 + 0xc) = 1;
  }
  sVar8 = *(short *)((long)plVar14 + 0x82);
  if ((((((((sVar8 == 0x4319) || (sVar8 == 0x4324)) || (sVar8 == 0x4312)) ||
         ((sVar8 == 0x4328 || (sVar8 == 0x432b)))) || (sVar8 == 0x4314)) ||
       ((((sVar8 == 0x431b || (sVar8 == 0x4350)) ||
         ((sVar8 == 0x4353 || (((sVar8 == 0x576 || (sVar8 == -0x5663)) || (sVar8 == 0x4354)))))) ||
        ((sVar8 == 0x4346 || (sVar8 == 0x435f)))))) ||
      ((sVar8 == 0x4331 ||
       (((sVar8 == 0x4334 || (sVar8 == 0x4359)) ||
        ((sVar8 == 0x4374 || (((sVar8 == 0x4367 || (sVar8 == 0x4380)) || (sVar8 == 0x43a0))))))))))
     || (((sVar8 == 0x43ae || (sVar8 == 0x43b1)) || (sVar8 == 0x43a3)))) {
    *(undefined4 *)(plVar14 + 0x23) = 2;
  }
  else {
    *(undefined4 *)(plVar14 + 0x23) = 1;
  }
  iVar10 = *(int *)(plVar14[0x17] + 0x3c);
  if (((iVar10 == 0xa8df) || (iVar10 == 0xa8d5)) ||
     ((iVar10 == 0xa8d9 ||
      ((((iVar10 == 0xa8e3 || (iVar10 == 0xa87b)) || (iVar10 == 0xa8d1)) || (iVar10 == 0xa8db))))))
  {
    *(undefined4 *)(plVar14 + 0x23) = 1;
  }
  *(short *)(param_1 + 0x45) = (short)(int)plVar14[0x10];
  *(undefined2 *)((long)param_1 + 0x22a) = *(undefined2 *)((long)plVar14 + 0x82);
  *(long *)(*param_1 + 0x100) = plVar14[0x17];
  *(undefined4 *)(*param_1 + 0x14) = *(undefined4 *)((long)plVar14 + 0x84);
  *(char *)(*param_1 + 0x94) = (char)plVar14[0x11];
  *(undefined2 *)(*param_1 + 0x92) = *(undefined2 *)((long)plVar14 + 0x8a);
  *(undefined4 *)(*param_1 + 0x98) = *(undefined4 *)((long)plVar14 + 0x8c);
  *(int *)(*param_1 + 0x9c) = (int)plVar14[0x12];
  *(int *)(*param_1 + 0x44) = (int)plVar14[0x23];
  lVar16 = wlc_phy_shim_attach(plVar14,param_1[2],param_1);
  plVar14[0x1b] = lVar16;
  if (lVar16 == 0) {
    return 0x19;
  }
  local_a0 = plVar14[0x17];
  local_98 = plVar14[0x1b];
  local_8c = *(undefined4 *)((long)plVar14 + 0x84);
  local_78 = (undefined2)(int)plVar14[0x10];
  local_76 = *(undefined2 *)((long)plVar14 + 0x82);
  local_74 = *(undefined4 *)(plVar14[0x17] + 0x3c);
  local_70 = *(undefined4 *)(plVar14[0x17] + 0x40);
  local_6c = *(undefined4 *)(plVar14[0x17] + 0x44);
  local_68 = (uint)*(byte *)(plVar14 + 0x11);
  local_64 = *(undefined4 *)(plVar14[0x17] + 0x28);
  local_60 = (uint)*(ushort *)((long)plVar14 + 0x8a);
  local_5c = *(undefined4 *)(plVar14[0x17] + 0x30);
  local_58 = *(undefined4 *)((long)plVar14 + 0x8c);
  local_54 = (undefined4)plVar14[0x12];
  local_88 = *(undefined4 *)(plVar14[0x17] + 4);
  local_84 = *(undefined4 *)(plVar14[0x17] + 0xc);
  local_a8 = param_6;
  local_90 = param_4;
  local_80 = lVar18;
  lVar16 = wlc_phy_shared_attach(&local_a8);
  plVar14[0x1c] = lVar16;
  if (lVar16 == 0) {
    return 0x10;
  }
  *(undefined4 *)((long)plVar14 + 0x1ac) = 0x1000000;
  *(undefined4 *)(plVar14 + 0x38) = 0x1fe;
  uVar12 = -(uint)(*(uint *)((long)plVar14 + 0x84) < 0x28) & 0xfffffffe;
  uVar13 = uVar12 + 0x28;
  *(uint *)((long)param_1 + 0x6bc) = uVar13;
  if ((uVar13 & 2) == 0) {
    uVar13 = uVar12 + 0x2a;
  }
  uVar12 = 0;
  *(uint *)(param_1 + 0x103) = uVar13;
  do {
    if (*(uint *)(plVar14 + 0x23) <= uVar12) {
      if ((*(int *)(plVar14[0x17] + 0x3c) == 0x4331) &&
         (uVar9 = si_pcie_get_request_size(), 0x80 < uVar9)) {
        lVar15 = 0;
        do {
          plVar5 = *(long **)((long)plVar14 + lVar15 + 0x20);
          if (plVar5 != (long *)0x0) {
            (**(code **)(*plVar5 + 0x118))(plVar5,0x20,0x20);
          }
          lVar15 = lVar15 + 8;
        } while (lVar15 != 0x30);
        *(undefined1 *)((long)param_1 + 0x72c) = 1;
      }
      wlc_bmac_btc_wire_set(plVar14,0);
      lVar15 = plVar14[0x16];
      uVar7 = getintvar(lVar18,&DAT_006f6324);
      uVar21 = 1;
      *(undefined1 *)(lVar15 + 0x18) = uVar7;
      if ((*(short *)(plVar14[0x1d] + 0x1c) != 6) &&
         (uVar21 = 5, *(int *)(plVar14[0x1d] + 0x1c) != 0x3000a)) {
        uVar21 = 8;
      }
      wlc_bmac_btc_mode_set(plVar14,uVar21);
      wlc_coredisable(plVar14);
      iVar10 = *(int *)(plVar14[0x17] + 0x3c);
      if (((iVar10 == 0x4352) || (iVar10 == 0x4360)) || (iVar10 == 0xaa06)) {
        si_pmu_rfldo(plVar14[0x17],0);
      }
      if (*(int *)(plVar14[0x17] + 4) == 1) {
        si_pci_down();
      }
      si_register_intr_callback(plVar14[0x17],&LAB_00161fa8,&LAB_00161fc5,0,plVar14);
      wlc_bmac_xtal(plVar14,0);
      lVar18 = getvar(plVar14[0x18],"macaddr");
      if (lVar18 != 0) {
        bcm_ether_atoe(lVar18,plVar14 + 0x2f);
        if (((*(byte *)((long)plVar14 + 0x179) & *(byte *)(plVar14 + 0x2f) &
              *(byte *)((long)plVar14 + 0x17a) & *(byte *)((long)plVar14 + 0x17b) &
              *(byte *)((long)plVar14 + 0x17c) & *(byte *)((long)plVar14 + 0x17d)) != 0xff) &&
           ((((*(byte *)((long)plVar14 + 0x179) != 0 || (*(byte *)(plVar14 + 0x2f) != 0)) ||
             ((*(byte *)((long)plVar14 + 0x17a) != 0 ||
              ((*(byte *)((long)plVar14 + 0x17b) != 0 || (*(byte *)((long)plVar14 + 0x17c) != 0)))))
             ) || (*(byte *)((long)plVar14 + 0x17d) != 0)))) {
          lVar18 = wlc_bmac_led_attach(plVar14);
          plVar14[0x33] = lVar18;
          if (lVar18 != 0) {
            wlc_template_cfg_init(param_1,*(undefined4 *)((long)plVar14 + 0x84));
            return 0;
          }
          return 0x17;
        }
        return 0x16;
      }
      return 0x15;
    }
    iVar10 = wlc_is_singleband_5g(*(undefined2 *)((long)plVar14 + 0x82));
    if (iVar10 != 0) {
      uVar12 = 1;
    }
    wlc_setxband(plVar14,uVar12);
    *(uint *)(plVar14[0x1d] + 4) = uVar12;
    iVar10 = ~-(uint)(uVar12 == 0) + 2;
    *(int *)plVar14[0x1d] = iVar10;
    *(uint *)(param_1[8] + 4) = uVar12;
    *(int *)param_1[8] = iVar10;
    puVar4 = (undefined4 *)param_1[7];
    uVar11 = si_coreidx(plVar14[0x17]);
    *puVar4 = uVar11;
    if (0xc < *(uint *)((long)plVar14 + 0x84)) {
      uVar13 = osl_readl(lVar15 + 0x15c);
      iVar10 = *(int *)((long)plVar14 + 0x84);
      *(uint *)((long)plVar14 + 0xa4) = uVar13;
      if (iVar10 == 0x1a) {
        bVar25 = *(int *)(plVar14[0x17] + 0x40) == 0;
LAB_0016ae06:
        if (bVar25) goto LAB_0016ae08;
      }
      else {
        if (((((iVar10 != 0x1d) && (iVar10 != 0x21)) && (iVar10 != 0x22)) &&
            ((iVar10 != 0x1e && (iVar10 != 0x28)))) && ((iVar10 != 0x29 && (iVar10 != 0x2b)))) {
          bVar25 = iVar10 == 0x2c;
          goto LAB_0016ae06;
        }
LAB_0016ae08:
        *(uint *)((long)plVar14 + 0xa4) = uVar13 & 0x7fffffff;
      }
      *(undefined4 *)(plVar14 + 0x15) = *(undefined4 *)((long)plVar14 + 0xa4);
    }
    if (*(uint *)((long)plVar14 + 0x84) < 0x28) {
      plVar14[0x2a] = (long)(&DAT_0059c7e0 + (ulong)(*(uint *)((long)plVar14 + 0x84) - 4) * 0xc);
    }
    else {
      plVar14[0x2a] = (long)&DAT_0059c990;
    }
    wlc_bmac_ampdu_set(plVar14,1);
    puVar4 = (undefined4 *)plVar14[0x1d];
    lVar16 = wlc_phy_attach(plVar14[0x1c],lVar15,*puVar4,lVar18);
    *(long *)(puVar4 + 10) = lVar16;
    if (lVar16 == 0) {
      return 0x11;
    }
    if (*(short *)(plVar14[0x1d] + 0x1c) != 0xb) {
      wlc_bmac_set_btswitch(plVar14,0xffffffff);
    }
    wlc_phy_machwcap_set
              (*(undefined8 *)(plVar14[0x1d] + 0x28),*(undefined4 *)((long)plVar14 + 0xa4));
    lVar16 = plVar14[0x1d];
    wlc_phy_get_phyversion
              (*(undefined8 *)(lVar16 + 0x28),lVar16 + 0x1c,lVar16 + 0x1e,lVar16 + 0x20,
               lVar16 + 0x22);
    lVar16 = plVar14[0x1d];
    uVar7 = wlc_phy_get_encore(*(undefined8 *)(lVar16 + 0x28));
    *(undefined1 *)(lVar16 + 0x30) = uVar7;
    lVar16 = param_1[8];
    uVar7 = wlc_phy_get_encore(*(undefined8 *)(plVar14[0x1d] + 0x28));
    *(undefined1 *)(lVar16 + 0x18) = uVar7;
    lVar16 = plVar14[0x1d];
    uVar11 = wlc_phy_get_coreflags(*(undefined8 *)(lVar16 + 0x28));
    *(undefined4 *)(lVar16 + 0x18) = uVar11;
    lVar16 = plVar14[0x1d];
    sVar8 = (short)*(undefined4 *)(lVar16 + 0x1c);
    if (sVar8 == 0) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0x1ec;
    }
    else if (sVar8 == 2) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0x3c6;
    }
    else if (sVar8 == 4) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0x1f07ff;
    }
    else if (sVar8 == 5) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0x1f;
    }
    else if ((sVar8 == 6) || (sVar8 == 8)) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0xf;
    }
    else if (sVar8 == 7) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 3;
    }
    else if (sVar8 == 10) {
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0x4f;
    }
    else {
      if (sVar8 != 0xb) {
        return 0x12;
      }
      uVar19 = (uint)*(ushort *)(lVar16 + 0x1e);
      uVar13 = 0xff;
    }
    if ((uVar13 >> (uVar19 & 0x1f) & 1) == 0) {
      return 0x12;
    }
    *(undefined8 *)(param_1[8] + 0x10) = *(undefined8 *)(lVar16 + 0x28);
    *(short *)(param_1[8] + 8) = (short)*(undefined4 *)(plVar14[0x1d] + 0x1c);
    *(undefined2 *)(param_1[8] + 10) = *(undefined2 *)(plVar14[0x1d] + 0x1e);
    *(short *)(param_1[8] + 0xc) = (short)*(undefined4 *)(plVar14[0x1d] + 0x20);
    *(undefined2 *)(param_1[8] + 0xe) = *(undefined2 *)(plVar14[0x1d] + 0x22);
    *(undefined2 *)(plVar14[0x1d] + 0x14) = 0xf;
    *(undefined2 *)(plVar14[0x1d] + 0x16) = 0x3ff;
    plVar5 = (long *)*plVar14;
    puVar4 = *(undefined4 **)(*plVar5 + 0x38);
    osl_snprintf(local_48,8,&DAT_006f6316,(int)plVar14[3]);
    if (plVar14[4] == 0) {
      lVar16 = plVar14[2];
      uVar11 = dma_addrwidth(plVar14[0x17],plVar14[0x1a] + 0x200);
      cVar6 = wl_alloc_dma_resources(plVar5[2],uVar11);
      if (cVar6 == '\0') {
        return 0x13;
      }
      lVar17 = plVar14[0x1a];
      if (*(uint *)((long)plVar14 + 0x84) < 0xb) {
        lVar20 = lVar17 + 0x210;
      }
      else {
        lVar20 = lVar17 + 0x220;
      }
      lVar17 = dma_attach(lVar16,local_48,plVar14[0x17],lVar17 + 0x200,lVar20,*puVar4,puVar4[1],
                          puVar4[2],0,puVar4[3],*(undefined4 *)((long)plVar5 + 0x6bc),&wl_msg_level)
      ;
      if (lVar17 == 0) {
        return 0x13;
      }
      if (*(int *)(plVar14[0x17] + 4) == 1) {
        DAT_0059c9a0 = 1;
        DAT_0059c9a4 = 3;
        DAT_0059c9a2 = 3;
        DAT_0059c9a6 = 6;
        uVar21 = 1;
        DAT_0059c9ac = 3;
        DAT_0059c9aa = 3;
        DAT_0059c9ae = 3;
LAB_0016b188:
        FUN_0016a399(plVar14,uVar21,lVar17);
      }
      else if (*(int *)(plVar14[0x17] + 4) == 0) {
        uVar21 = 0;
        goto LAB_0016b188;
      }
      wlc_hw_set_di(plVar14,0,lVar17);
      lVar17 = plVar14[0x1a] + 0x220;
      if (10 < *(uint *)((long)plVar14 + 0x84)) {
        lVar17 = plVar14[0x1a] + 0x240;
      }
      lVar17 = dma_attach(lVar16,local_48,plVar14[0x17],lVar17,0,*puVar4,0,0,0xffffffff,0,0,
                          &wl_msg_level);
      if (lVar17 == 0) {
        return 0x13;
      }
      FUN_0016a399(plVar14,*(undefined4 *)(plVar14[0x17] + 4),lVar17);
      wlc_hw_set_di(plVar14,1,lVar17);
      lVar17 = plVar14[0x1a] + 0x240;
      if (10 < *(uint *)((long)plVar14 + 0x84)) {
        lVar17 = plVar14[0x1a] + 0x280;
      }
      lVar17 = dma_attach(lVar16,local_48,plVar14[0x17],lVar17,0,*puVar4,0,0,0xffffffff,0,0,
                          &wl_msg_level);
      if (lVar17 == 0) {
        return 0x13;
      }
      FUN_0016a399(plVar14,*(undefined4 *)(plVar14[0x17] + 4),lVar17);
      wlc_hw_set_di(plVar14,2,lVar17);
      if (*(uint *)((long)plVar14 + 0x84) == 4) {
        lVar20 = plVar14[0x17];
        uVar11 = puVar4[3];
        uVar27 = 0x30;
        lVar17 = plVar14[0x1a] + 0x260;
        lVar22 = plVar14[0x1a] + 0x270;
        uVar26 = puVar4[1];
        uVar2 = *puVar4;
      }
      else {
        uVar2 = *puVar4;
        lVar20 = plVar14[0x17];
        uVar11 = 0;
        uVar27 = 0;
        lVar17 = plVar14[0x1a] + 0x260;
        if (10 < *(uint *)((long)plVar14 + 0x84)) {
          lVar17 = plVar14[0x1a] + 0x2c0;
        }
        uVar26 = 0;
        lVar22 = 0;
      }
      lVar16 = dma_attach(lVar16,local_48,lVar20,lVar17,lVar22,uVar2,uVar26,uVar27,0xffffffff,uVar11
                          ,0,&wl_msg_level);
      if (lVar16 == 0) {
        return 0x13;
      }
      lVar17 = 0;
      FUN_0016a399(plVar14,*(undefined4 *)(plVar14[0x17] + 4),lVar16);
      wlc_hw_set_di(plVar14,3,lVar16);
      do {
        plVar5 = *(long **)((long)plVar14 + lVar17 + 0x20);
        if (plVar5 != (long *)0x0) {
          uVar21 = (**(code **)(*plVar5 + 0x108))(plVar5,"&txavail");
          *(undefined8 *)((long)plVar14 + lVar17 + 0x120) = uVar21;
        }
        lVar17 = lVar17 + 8;
      } while (lVar17 != 0x30);
    }
    lVar16 = plVar14[0x1d];
    osl_memset(lVar16 + 8,0,10);
    puVar1 = (ushort *)(lVar16 + 10);
    if (*(int *)(plVar14[0x1d] + 0x1c) == 0x10002) {
      *(ushort *)(lVar16 + 8) = *(ushort *)(lVar16 + 8) | 0x20;
    }
    if (((*(short *)(plVar14[0x1d] + 0x1c) == 2) && ((*(byte *)((long)plVar14 + 0x8c) & 2) != 0)) &&
       (*(short *)((long)plVar14 + 0xac) != 0)) {
      *(ushort *)(lVar16 + 8) = *(ushort *)(lVar16 + 8) | 0x40;
    }
    if ((*(short *)(plVar14[0x1d] + 0x1c) == 2) && (*(ushort *)(plVar14[0x1d] + 0x1e) < 3)) {
      if ((*(uint *)(lVar16 + 8) & 0x40) == 0) {
        *(ushort *)(lVar16 + 8) = (ushort)*(uint *)(lVar16 + 8) | 8;
      }
    }
    else {
      iVar10 = *(int *)(plVar14[0x17] + 0x3c);
      iVar3 = *(int *)(plVar14[0x17] + 0x44);
      if ((iVar3 == 9 || iVar3 == 0xb) && (iVar10 == 0x4331 || iVar10 == 0xa9a7)) {
        *(ushort *)(lVar16 + 8) = *(ushort *)(lVar16 + 8) | 8;
      }
    }
    if ((*(byte *)((long)plVar14 + 0x8c) & 0x20) != 0) {
      *(ushort *)(lVar16 + 8) = *(ushort *)(lVar16 + 8) | 0x400;
    }
    if ((*(short *)(plVar14[0x1d] + 0x20) == 0x2050) && (*(ushort *)(plVar14[0x1d] + 0x22) < 6)) {
      *puVar1 = *puVar1 | 4;
    }
    if ((*(short *)(plVar14[0x1d] + 0x1c) == 4) && (*(ushort *)(plVar14[0x1d] + 0x1e) < 2)) {
      *puVar1 = *puVar1 | 0x800;
      *(ushort *)(lVar16 + 8) = *(ushort *)(lVar16 + 8) | 0x200;
    }
    if ((*(short *)(plVar14[0x1d] + 0x1c) == 4) && (8 < *(byte *)(plVar14 + 0x11))) {
      *puVar1 = *puVar1 | 0x80;
    }
    if ((0x27 < *(uint *)((long)plVar14 + 0x84)) &&
       (iVar10 = si_chip_hostif(plVar14[0x17]), iVar10 == 2)) {
      *(ushort *)(lVar16 + 0xc) = *(ushort *)(lVar16 + 0xc) | 0x10;
    }
    uVar12 = uVar12 + 1;
  } while( true );
}

