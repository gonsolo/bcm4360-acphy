
void wlc_phy_hirssi_elnabypass_engine(long param_1)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  short sVar5;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    sVar5 = (short)*(undefined4 *)(lVar1 + 0x914);
    iVar4 = *(short *)(lVar1 + 0x916) + -1;
    if (iVar4 < 0) {
      iVar4 = -1;
    }
    cVar3 = *(char *)(lVar1 + 0x910);
    *(short *)(lVar1 + 0x916) = (short)iVar4;
  }
  else {
    sVar5 = *(short *)(lVar1 + 0x916);
    iVar4 = *(short *)(lVar1 + 0x914) + -1;
    if (iVar4 < 0) {
      iVar4 = -1;
    }
    cVar3 = *(char *)(lVar1 + 0x911);
    *(short *)(lVar1 + 0x914) = (short)iVar4;
  }
  if (cVar3 == '\0') {
    return;
  }
  if (sVar5 < 0) {
    cVar3 = func_0x00193240(param_1);
    if (cVar3 != '\0') {
      sVar5 = (short)*(undefined4 *)(lVar1 + 0x908);
      bVar2 = true;
      goto code_r0x0019c5e6;
    }
  }
  else {
    sVar5 = sVar5 + -1;
    if (sVar5 == -1) {
      cVar3 = func_0x00193240(param_1);
      bVar2 = true;
      if (cVar3 == '\0') goto code_r0x0019c5e6;
      sVar5 = (short)*(undefined4 *)(lVar1 + 0x908);
    }
  }
  bVar2 = false;
code_r0x0019c5e6:
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    *(short *)(lVar1 + 0x914) = sVar5;
  }
  else {
    *(short *)(lVar1 + 0x916) = sVar5;
  }
  if (bVar2) {
    wlc_phy_hirssi_elnabypass_set_ucode_params_acphy(param_1);
    wlc_phy_hirssi_elnabypass_apply_acphy(param_1);
  }
  return;
}

