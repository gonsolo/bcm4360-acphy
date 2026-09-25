
void wlc_phy_aci_updsts_acphy(long param_1)

{
  long lVar1;
  bool bVar2;
  
  bVar2 = false;
  lVar1 = *(long *)(*(long *)(param_1 + 0x138) + 0x8a8);
  if ((lVar1 != 0) && (bVar2 = true, *(char *)(lVar1 + 0x18) == '\0')) {
    bVar2 = *(char *)(lVar1 + 0x47) != '\0';
  }
  wlapi_high_update_phy_mode(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),bVar2);
  return;
}

