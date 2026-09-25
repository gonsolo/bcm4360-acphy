
void wlc_phy_txpwrctrl_enable_acphy(long param_1,byte param_2)

{
  char cVar1;
  long lVar2;
  undefined1 uVar3;
  ushort uVar4;
  byte bVar5;
  
  lVar2 = *(long *)(param_1 + 0x138);
  if (param_2 < 2) {
    *(byte *)(param_1 + 4000) = param_2;
  }
  if (param_2 == 0) {
    bVar5 = 0;
    uVar4 = phy_reg_read(param_1,0x70);
    if ((uVar4 & 0xe000) == 0xe000) {
      for (; bVar5 < *(byte *)(param_1 + 0x168); bVar5 = bVar5 + 1) {
        uVar3 = FUN_001913ee(param_1,(uint)bVar5);
        *(undefined1 *)(lVar2 + 0x45a + (long)(int)(uint)bVar5) = uVar3;
      }
    }
    phy_reg_mod(param_1,0x70,0xe000,0);
  }
  else {
    phy_reg_mod(param_1,0x70,0xe000,0xe000);
    for (bVar5 = 0; bVar5 < *(byte *)(param_1 + 0x168); bVar5 = bVar5 + 1) {
      cVar1 = *(char *)(lVar2 + 0x45a + (long)(int)(uint)bVar5);
      if (cVar1 != -0x80) {
        FUN_00190114(param_1,cVar1);
      }
    }
  }
  return;
}

