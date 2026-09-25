
void wlc_phy_txpower_sromlimit_get_acphy
               (long param_1,ushort param_2,undefined8 param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  char cVar5;
  byte bVar6;
  
  bVar3 = wlc_phy_get_chan_freq_range_acphy(param_1,param_2 & 0xff);
  lVar4 = (long)(int)(uint)bVar3;
  bVar1 = *(byte *)(param_1 + 0xe81 + lVar4);
  bVar6 = *(byte *)(param_1 + 0xe7c + lVar4);
  bVar2 = *(byte *)(param_1 + 0xe86 + lVar4);
  if (bVar1 < bVar6) {
    bVar6 = bVar1;
  }
  if (bVar2 < bVar6) {
    bVar6 = bVar2;
  }
  wlc_phy_txpwr_apply_srom11(param_1,(bVar3 - 1) + (bVar3 < 4),param_2,bVar6,param_3);
  cVar5 = *(char *)((long)(int)(uint)bVar3 + 0xe7c + param_1 + (long)(int)(uint)param_4 * 5) - bVar6
  ;
  if ('\0' < cVar5) {
    ppr_plus_cmn_val(param_3,(int)cVar5);
  }
  if (bVar3 < 5) {
    ppr_apply_max(param_3,(int)*(char *)((long)(int)(uint)bVar3 + 0xe7c +
                                        param_1 + (long)(int)(uint)param_4 * 5));
  }
  return;
}

