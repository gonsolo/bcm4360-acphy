
void wlc_phy_hirssi_elnabypass_init_acphy(long param_1)

{
  long lVar1;
  
  lVar1 = *(long *)(param_1 + 0x138);
  *(undefined2 *)(lVar1 + 0x914) = 0xffff;
  *(undefined2 *)(lVar1 + 0x916) = 0xffff;
  if (*(char *)(lVar1 + 0x912) == '\0') {
    *(undefined1 *)(lVar1 + 0x910) = 0;
    *(undefined1 *)(lVar1 + 0x911) = 0;
  }
  else {
    *(undefined1 *)(lVar1 + 0x910) = *(undefined1 *)(lVar1 + 0x906);
    *(undefined1 *)(lVar1 + 0x911) = *(undefined1 *)(lVar1 + 0x906);
    if (*(char *)(*(long *)(param_1 + 0x20) + 0x31) != '\0') {
      wlc_phy_hirssi_elnabypass_set_ucode_params_acphy();
      wlapi_bmac_write_shm(*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x20),0x184,0);
    }
  }
  return;
}

