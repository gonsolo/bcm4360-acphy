
void wlc_phy_stopplayback_acphy(long param_1)

{
  long lVar1;
  ushort uVar2;
  byte bVar3;
  
  lVar1 = *(long *)(param_1 + 0x138);
  uVar2 = phy_reg_read(param_1,0x464);
  if ((uVar2 & 1) == 0) {
    if ((uVar2 & 2) != 0) {
      phy_reg_and(param_1,0x382,0x7fff);
    }
  }
  else {
    phy_reg_or(param_1,0x460,2);
  }
  phy_reg_and(param_1,0x460,0xfffb);
  bVar3 = 0;
  if (*(char *)(lVar1 + 10) != '\0') {
    for (; bVar3 < *(byte *)(param_1 + 0x168); bVar3 = bVar3 + 1) {
      FUN_0019d224(param_1,lVar1 + 2 + (ulong)bVar3 * 2,bVar3);
    }
    *(undefined1 *)(lVar1 + 10) = 0;
  }
  wlc_phy_resetcca_acphy(param_1);
  return;
}

