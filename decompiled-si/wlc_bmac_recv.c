
bool wlc_bmac_recv(undefined8 *param_1,uint param_2,char param_3,int *param_4)

{
  long lVar1;
  long lVar2;
  long lVar3;
  ushort uVar4;
  short sVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  undefined4 local_3c [3];
  
  uVar8 = 0xffffffff;
  if (param_3 != '\0') {
    uVar8 = *(uint *)(*(long *)(*(long *)*param_1 + 0x38) + 0x38);
  }
  uVar7 = 0;
  lVar2 = 0;
  lVar3 = 0;
  do {
    lVar1 = (**(code **)(*(long *)param_1[(ulong)param_2 + 4] + 0xd0))();
    lVar6 = lVar3;
    if (lVar1 == 0) break;
    lVar6 = lVar1;
    if (lVar2 != 0) {
      osl_pktsetlink(lVar2,lVar1);
      lVar6 = lVar3;
    }
    uVar7 = uVar7 + 1;
    lVar2 = lVar1;
    lVar3 = lVar6;
  } while (uVar7 < uVar8);
  (**(code **)(*(long *)param_1[(ulong)param_2 + 4] + 0xd8))();
  wlc_bmac_read_tsf(param_1,local_3c,0);
  while (lVar6 != 0) {
    lVar2 = osl_pktlink(lVar6);
    osl_pktsetlink(lVar6,0);
    lVar3 = osl_pktdata(param_1[2],lVar6);
    *(undefined4 *)(lVar3 + 0x18) = local_3c[0];
    wlc_phy_rssi_compute(*(undefined8 *)(param_1[0x1d] + 0x28),lVar3);
    if (*(uint *)((long)param_1 + 0x84) < 0x28) {
      uVar4 = *(ushort *)(lVar3 + 0x16);
      *(ushort *)(lVar3 + 0x16) =
           ~-(ushort)((uVar4 & 0x800) == 0) & 0xc000 | (ushort)((int)(uVar4 & 0x7f8) >> 3) |
           (-(ushort)((uVar4 & 0x1000) == 0) & 0xf800) + 0x1800;
    }
    sVar5 = (short)*(undefined4 *)(param_1[0x1d] + 0x1c);
    if (((sVar5 == 2) || (sVar5 == 0)) || (sVar5 == 5)) {
      uVar4 = 1;
      if ((*(ushort *)(lVar3 + 0x16) & 0xc000) != 0xc000) {
        uVar4 = *(ushort *)(lVar3 + 4) & 1;
      }
      *(ushort *)(lVar3 + 4) = *(ushort *)(lVar3 + 4) & 0xfffc | uVar4;
    }
    wlc_recv(*param_1);
    lVar6 = lVar2;
  }
  *param_4 = *param_4 + uVar7;
  return uVar8 <= uVar7;
}

