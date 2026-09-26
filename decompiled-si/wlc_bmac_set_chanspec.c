
void wlc_bmac_set_chanspec(long *param_1,ushort param_2,char param_3,undefined8 param_4)

{
  char cVar1;
  long lVar2;
  long lVar3;
  char cVar4;
  short sVar5;
  ushort uVar6;
  undefined4 uVar7;
  ulong uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  
  cVar1 = *(char *)((long)param_1 + 0x185);
  if (cVar1 == '\0') {
    FUN_001655c7(param_1,0);
  }
  *(ushort *)((long)param_1 + 0x11c) = param_2;
  if (1 < *(uint *)(param_1 + 0x23)) {
    bVar12 = (param_2 & 0xc000) == 0xc000;
    uVar8 = (ulong)bVar12;
    if (*(uint *)(param_1[0x1d] + 4) != (uint)bVar12) {
      if (*(char *)((long)param_1 + 0x10c) == '\0') {
        wlc_setxband(param_1,uVar8);
      }
      else {
        wlc_phy_chanspec_radio_set(*(undefined8 *)(param_1[uVar8 + 0x1e] + 0x28),param_2);
        lVar2 = *param_1;
        cVar4 = si_iscoreup(param_1[0x17]);
        if (cVar4 == '\0') {
          si_core_reset(param_1[0x17],0,0);
          *(undefined4 *)(param_1 + 0x2d) = 0;
          *(undefined1 *)((long)param_1 + 0x164) = 0;
          *(undefined4 *)(param_1 + 0x2e) = 0;
          *(undefined4 *)((long)param_1 + 0x174) = 0;
          wlc_bmac_mctrl(param_1,0xffffffff,0x4000400);
        }
        uVar7 = wl_intrsoff(*(undefined8 *)(*param_1 + 0x10));
        lVar3 = param_1[0x1d];
        sVar5 = (short)*(undefined4 *)(lVar3 + 0x1c);
        if ((sVar5 != 0xb) && ((sVar5 != 4 || (*(ushort *)(lVar3 + 0x1e) < 3)))) {
          wlc_phy_switch_radio(*(undefined8 *)(lVar3 + 0x28),0);
        }
        if (*(uint *)((long)param_1 + 0x84) < 0x11) {
          osl_readl(param_1[0x1a] + 0x120);
        }
        if (*(short *)(param_1[0x1d] + 0x1c) != 0xb) {
          wlc_bmac_core_phy_clk(param_1,0);
        }
        wlc_setxband(param_1,uVar8);
        if (*(char *)((long)param_1 + 0x10c) != '\0') {
          sVar5 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
          if (((sVar5 == 2) || (sVar5 == 0)) && (4 < *(uint *)((long)param_1 + 0x84))) {
            iVar10 = 0;
            uVar9 = (int)((uint)(sVar5 == 0) << 0x1f) >> 0x1f & 0x20;
            while (iVar10 = iVar10 + 1, iVar10 != 6) {
              lVar3 = param_1[0x17];
              if ((*(int *)(lVar3 + 4) == 2) && (*(int *)((long)param_1 + 0x84) == 9)) {
                si_core_cflags_wo(lVar3,0x20,uVar9);
                osl_delay(0x40);
                si_core_cflags(param_1[0x17],0,0);
              }
              else {
                si_core_cflags(lVar3,0x20,uVar9);
                osl_delay(0x40);
              }
              iVar11 = 0x199;
              while( true ) {
                uVar8 = si_core_sflags(param_1[0x17],0,0);
                if (((uVar8 & 4) != 0) || (iVar11 == 9)) break;
                iVar11 = iVar11 + -10;
                osl_delay(10);
              }
              if (7 < *(uint *)((long)param_1 + 0x84)) break;
              uVar8 = si_core_sflags(param_1[0x17],0,0);
              if ((uVar8 & 4) != 0) break;
              si_core_cflags(param_1[0x17],0x20,~-(*(short *)(param_1[0x1d] + 0x1c) == 0) & 0x20);
              osl_delay(200);
            }
          }
          if (*(short *)(param_1[0x1d] + 0x1c) != 0xb) {
            wlc_bmac_core_phy_clk(param_1,1);
          }
          FUN_001672ac(param_1,param_2,1);
          if (*(int *)((long)param_1 + 0x94) != 0) {
            *(undefined4 *)((long)param_1 + 0x94) = 0x8000;
          }
          wl_intrsrestore(*(undefined8 *)(lVar2 + 0x10),uVar7);
        }
      }
    }
  }
  wlc_phy_initcal_enable(*(undefined8 *)(param_1[0x1d] + 0x28),param_3 == '\0');
  if (*(char *)((long)param_1 + 0x10c) == '\0') {
    if (*(char *)((long)param_1 + 0x186) != '\0') {
      wlc_phy_txpower_limit_set(*(undefined8 *)(param_1[0x1d] + 0x28),param_4,param_2);
    }
    wlc_phy_chanspec_radio_set(*(undefined8 *)(param_1[0x1d] + 0x28),param_2);
    goto LAB_00168a0e;
  }
  sVar5 = *(short *)((long)param_1 + 0x82);
  if ((((sVar5 == 0x43ae) || (sVar5 == 0x43a0)) || (sVar5 == 0x43a3)) || (sVar5 == 0x43b1)) {
LAB_001689d4:
    wlc_phy_chanspec_set(*(undefined8 *)(param_1[0x1d] + 0x28),param_2);
  }
  else {
    uVar6 = wlc_phy_chanspec_get(*(undefined8 *)(param_1[0x1d] + 0x28));
    if (param_2 != uVar6) goto LAB_001689d4;
  }
  wlc_phy_txpower_limit_set(*(undefined8 *)(param_1[0x1d] + 0x28),param_4,param_2);
  wlc_bmac_mute(param_1,param_3,0);
LAB_00168a0e:
  if (cVar1 == '\0') {
    FUN_001655c7(param_1,2);
  }
  return;
}

