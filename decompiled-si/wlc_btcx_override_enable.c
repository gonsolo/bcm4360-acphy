
void wlc_btcx_override_enable(long param_1)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  
  if (((*(byte *)(*(long *)(param_1 + 0x20) + 0x2f) & 0x20) != 0) &&
     ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0)) {
    lVar6 = *(long *)(param_1 + 0x148) + 0x6b4;
    uVar2 = osl_readw(lVar6);
    osl_writew(uVar2 | 3,lVar6);
    lVar6 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar3 = osl_readw(lVar6);
    osl_writew(uVar3 & 0xff3f,lVar6);
    osl_writew(1,*(long *)(param_1 + 0x148) + 0x6f0);
    osl_readw(*(long *)(param_1 + 0x148) + 0x6f2);
    cVar1 = wlapi_is_eci_coex_enabled(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    if (cVar1 != '\0') {
      iVar5 = 0;
      osl_writew(1,*(long *)(param_1 + 0x148) + 0x6f0);
      do {
        uVar4 = osl_readw(*(long *)(param_1 + 0x148) + 0x6f2);
        if ((uVar4 & 0xf0) == 0) break;
        iVar5 = iVar5 + 1;
        osl_delay(100);
      } while (iVar5 != 5000);
    }
    lVar6 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar2 = osl_readw(lVar6);
    iVar5 = 0;
    osl_writew(uVar2 | 0x80,lVar6);
    while( true ) {
      uVar4 = osl_readw(*(long *)(param_1 + 0x148) + 0x6b6);
      if (((uVar4 & 1) == 0) || (iVar5 == 0x1f5)) break;
      iVar5 = iVar5 + 1;
      osl_delay(100);
    }
    lVar6 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar2 = osl_readw(lVar6);
    osl_writew(uVar2 | 0xc0,lVar6);
  }
  return;
}

