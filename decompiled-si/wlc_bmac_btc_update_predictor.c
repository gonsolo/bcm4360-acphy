
void wlc_bmac_btc_update_predictor(long param_1)

{
  ushort uVar1;
  long lVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  
  lVar2 = *(long *)(param_1 + 0xd0);
  uVar1 = *(ushort *)(*(long *)(param_1 + 0xb0) + 0x1a);
  if (uVar1 != 0) {
    uVar6 = wlc_bmac_read_shm(param_1,uVar1 + 8);
    if ((short)uVar6 != 0) {
      iVar7 = osl_readl(lVar2 + 0x180);
      do {
        sVar3 = wlc_bmac_read_shm(param_1,uVar1 + 0x18);
        uVar4 = wlc_bmac_read_shm(param_1,uVar1 + 0x1a);
        sVar5 = wlc_bmac_read_shm(param_1,uVar1 + 0x18);
      } while (sVar3 != sVar5);
      wlc_bmac_write_shm(param_1,uVar1 + 0x1c,
                         ((uint)(iVar7 - CONCAT22(uVar4,sVar3)) / (uVar6 & 0xffff) + 1) *
                         (uVar6 & 0xffff) + CONCAT22(uVar4,sVar3) & 0xffff);
    }
  }
  return;
}

