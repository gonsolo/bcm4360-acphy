
void wlc_phy_hirssi_elnabypass_set_ucode_params_acphy(long param_1)

{
  long lVar1;
  ushort uVar2;
  char cVar4;
  short sVar3;
  char cVar5;
  byte bVar6;
  uint uVar7;
  undefined8 uVar8;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (*(char *)(lVar1 + 0x912) != '\0') {
    if ((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) {
      cVar5 = *(char *)(lVar1 + 0x910);
      cVar4 = (char)((uint)*(undefined4 *)(lVar1 + 0x914) >> 8);
    }
    else {
      cVar5 = *(char *)(lVar1 + 0x911);
      cVar4 = (char)((ushort)*(undefined2 *)(lVar1 + 0x916) >> 8);
    }
    if (cVar5 == '\0') {
      uVar7 = 500;
      uVar8 = 0x527;
      sVar3 = 0x32;
    }
    else {
      if (cVar4 < '\0') {
        cVar5 = *(char *)(lVar1 + 0x90e);
        uVar7 = (uint)*(ushort *)(lVar1 + 0x90a);
        uVar8 = 0x527;
      }
      else {
        cVar5 = *(char *)(lVar1 + 0x90f);
        uVar8 = 0x529;
        uVar7 = *(uint *)(lVar1 + 0x90c);
      }
      sVar3 = (short)cVar5;
      uVar2 = *(ushort *)(param_1 + 0x17e) & 0x3800;
      bVar6 = 1;
      if (uVar2 != 0x1000) {
        bVar6 = (uVar2 != 0x1800) * '\x02' + 2;
      }
      uVar7 = bVar6 * uVar7;
    }
    wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x32,sVar3);
    wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x180,uVar8);
    wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x182,uVar7 & 0xffff);
  }
  return;
}

