
void wlc_phy_desense_aci_reset_params_acphy(long param_1,char param_2,char param_3,char param_4)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x138);
  if (param_3 != '\0') {
    osl_memset(lVar1 + 0x6c8,0,0xf0);
  }
  if (param_4 == '\0') {
    if (param_3 == '\0') {
      if (*(long *)(lVar1 + 0x8a8) != 0) {
        osl_memset(*(long *)(lVar1 + 0x8a8) + 0x1c,0,0x14);
        osl_memset(*(long *)(lVar1 + 0x8a8) + 0x30,0,0x14);
        *(undefined1 *)(*(long *)(lVar1 + 0x8a8) + 0x44) = 0;
        *(undefined1 *)(*(long *)(lVar1 + 0x8a8) + 0x45) = 1;
        osl_memset(*(long *)(lVar1 + 0x8a8) + 0x10,0,9);
      }
      goto LAB_0019baae;
    }
  }
  else {
    osl_memset(lVar1 + 0x7b8,0,0xf0);
  }
  *(undefined8 *)(lVar1 + 0x8a8) = 0;
LAB_0019baae:
  if (param_2 != '\0') {
    FUN_0019b279(param_1,1);
  }
  return;
}

