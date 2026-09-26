
uint wlc_phy_hirssi_elnabypass_status_acphy(long param_1)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
    uVar2 = *(uint *)(*(long *)(param_1 + 0x138) + 0x914);
  }
  else {
    uVar2 = (uint)*(ushort *)(*(long *)(param_1 + 0x138) + 0x916);
  }
  uVar3 = ~uVar2 >> 0xf & 1;
  if (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0') {
    bVar4 = true;
    if (-1 < (char)(~uVar2 >> 8)) {
      sVar1 = wlapi_bmac_read_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x184);
      bVar4 = sVar1 == -0x2153;
    }
    uVar3 = (uint)bVar4;
  }
  return uVar3;
}

