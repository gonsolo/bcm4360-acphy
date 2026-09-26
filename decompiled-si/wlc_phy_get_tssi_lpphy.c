
void wlc_phy_get_tssi_lpphy(long param_1,char *param_2,char *param_3)

{
  char cVar1;
  ushort uVar2;
  short sVar3;
  char cVar4;
  char local_38 [24];
  
  uVar2 = phy_reg_read(param_1,0x4a4);
  if (((uVar2 & 0xc000) != 0) && (sVar3 = phy_reg_read(param_1,0x4ab), sVar3 < 0)) {
    *param_2 = (char)sVar3;
    cVar1 = wlc_phy_tpc_isenabled_lpphy(param_1);
    cVar4 = '\0';
    if (cVar1 != '\0') {
      ppr_get_dsss(*(undefined8 *)(param_1 + 0x1c8),0,1,local_38);
      cVar4 = local_38[0];
    }
    *param_3 = cVar4 + *param_2;
    return;
  }
  *param_2 = '\0';
  *param_3 = '\0';
  return;
}

