
undefined1 wlc_sslpnphy_btcx_override_enable(long param_1)

{
  bool bVar1;
  char cVar2;
  ushort uVar3;
  uint uVar4;
  ulong uVar5;
  undefined1 uVar6;
  int iVar7;
  long lVar8;
  
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0xc000) {
    phy_reg_write_array(param_1,&DAT_00568700,8);
  }
  if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) &&
     ((*(byte *)(*(long *)(param_1 + 0x20) + 0x2f) & 0x20) != 0)) {
    lVar8 = *(long *)(param_1 + 0x148) + 0x6b4;
    uVar3 = osl_readw(lVar8);
    osl_writew(uVar3 | 3,lVar8);
    lVar8 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar4 = osl_readw(lVar8);
    osl_writew(uVar4 & 0xff3f,lVar8);
    cVar2 = wlapi_is_eci_coex_enabled(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20));
    if (cVar2 == '\0') {
LAB_00257d63:
      uVar6 = 1;
    }
    else {
      bVar1 = false;
      iVar7 = 0;
      osl_writew(3,*(long *)(param_1 + 0x148) + 0x6f0);
      do {
        uVar3 = osl_readw(*(long *)(param_1 + 0x148) + 0x6f2);
        if ((uVar3 & 0x4000) == 0) {
          if (bVar1) goto LAB_00257d63;
          bVar1 = true;
        }
        else {
          if ((uVar3 & 0xf) == 0) goto LAB_00257d63;
          bVar1 = false;
        }
        iVar7 = iVar7 + 1;
        osl_delay(100);
      } while (iVar7 != 5000);
      uVar6 = 0;
    }
    lVar8 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar3 = osl_readw(lVar8);
    iVar7 = 0;
    osl_writew(uVar3 | 0x80,lVar8);
    while( true ) {
      uVar5 = osl_readw(*(long *)(param_1 + 0x148) + 0x6b6);
      if ((uVar5 & 1) == 0) break;
      if (iVar7 == 0x1f5) {
        uVar6 = 0;
        break;
      }
      iVar7 = iVar7 + 1;
      osl_delay(100);
    }
    lVar8 = *(long *)(param_1 + 0x148) + 0x6b8;
    uVar3 = osl_readw(lVar8);
    osl_writew(uVar3 | 0xc0,lVar8);
  }
  else {
    uVar6 = 1;
  }
  return uVar6;
}

