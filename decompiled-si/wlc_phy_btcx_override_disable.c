
void wlc_phy_btcx_override_disable(long param_1)

{
  ushort uVar1;
  uint uVar2;
  long lVar3;
  
  if ((*(byte *)(*(long *)(param_1 + 0x20) + 0x2f) & 0x20) != 0) {
    lVar3 = *(long *)(param_1 + 0x148) + 0x6b4;
    uVar1 = osl_readw(lVar3);
    osl_writew(uVar1 | 3,lVar3);
    lVar3 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar2 = osl_readw(lVar3);
    osl_writew(uVar2 & 0xff3f,lVar3);
  }
  return;
}

