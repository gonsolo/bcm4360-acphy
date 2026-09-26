
void wlc_beacon_phytxctl(long *param_1,uint param_2,ushort param_3)

{
  undefined2 uVar1;
  ushort uVar2;
  short sVar3;
  ushort uVar4;
  uint uVar5;
  undefined8 uVar6;
  long lVar7;
  uint uVar8;
  
  if (0x27 < *(uint *)(*param_1 + 0x14)) {
    uVar8 = param_2 & 0xfff8ffff | 0x10000;
    uVar1 = wlc_acphy_txctl0_calc(param_1,uVar8,0);
    wlc_bmac_write_shm(param_1[4],0xcc,uVar1);
    uVar1 = wlc_acphy_txctl1_calc(param_1,uVar8,0);
    wlc_bmac_write_shm(param_1[4],0xce,uVar1);
    uVar1 = wlc_acphy_txctl2_calc(param_1,uVar8);
    lVar7 = param_1[4];
    uVar6 = 0xd0;
    goto LAB_00135d11;
  }
  uVar8 = param_2 & 0x3000000;
  uVar2 = wlc_bmac_read_shm(param_1[4],0x54);
  uVar4 = 3;
  if (((uVar8 != 0x2000000) && (uVar4 = 2, uVar8 != 0x1000000)) && (uVar4 = 1, uVar8 == 0)) {
    uVar5 = param_2 & 0x7f;
    if (((uVar5 == 4) || (uVar5 == 2)) || (uVar5 == 0xb)) {
      uVar4 = 0;
    }
    else {
      uVar4 = (ushort)(uVar5 != 0x16);
    }
  }
  uVar4 = uVar2 & 0xfffc | uVar4;
  if (uVar8 == 0) {
    uVar2 = (ushort)param_2 & 0xff;
  }
  else {
    uVar2 = wlc_rate_rspec2rate(param_2);
  }
  lVar7 = *(long *)((long)param_1 + (-(ulong)((param_3 & 0xc000) == 0) & 0xfffffffffffffff8) + 0x58)
  ;
  sVar3 = (short)*(undefined4 *)(lVar7 + 8);
  if (((sVar3 == 7) || (sVar3 == 4)) &&
     ((uVar8 == 0 &&
      ((((uVar8 = param_2 & 0x7f, uVar8 == 4 || (uVar8 == 2)) || (uVar8 == 0xb)) || (uVar8 == 0x16))
      )))) {
    uVar4 = uVar2 * 0x1400 | uVar4;
  }
  wlc_bmac_write_shm(param_1[4],0x54,uVar4);
  sVar3 = (short)*(undefined4 *)(lVar7 + 8);
  if ((sVar3 == 6) || (sVar3 == 4)) {
LAB_00135cdd:
    if ((sVar3 != 8) && (sVar3 != 5)) {
      param_2 = param_2 & 0xfff8ffff | 0x10000;
    }
  }
  else if (sVar3 != 8) {
    if (((sVar3 != 10) && (sVar3 != 0xb)) && ((sVar3 != 7 && (sVar3 != 5)))) {
      return;
    }
    goto LAB_00135cdd;
  }
  uVar1 = wlc_phytxctl1_calc(param_1,param_2,param_3);
  lVar7 = param_1[4];
  uVar6 = 0xb0;
LAB_00135d11:
  wlc_bmac_write_shm(lVar7,uVar6,uVar1);
  return;
}

