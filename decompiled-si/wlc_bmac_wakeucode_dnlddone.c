
undefined1  [16] wlc_bmac_wakeucode_dnlddone(long param_1)

{
  undefined1 auVar1 [16];
  undefined8 uStack_18;
  
  wlc_bmac_write_shm(param_1,0x16,*(undefined2 *)(param_1 + 0x84));
  if (*(char *)(param_1 + 0x102) != '\0') {
    FUN_00163456(param_1,*(char *)(param_1 + 0x102));
  }
  wlc_bmac_write_shm(param_1,0x44,*(undefined2 *)(param_1 + 0x108));
  wlc_bmac_write_shm(param_1,0x46,*(undefined2 *)(param_1 + 0x10a));
  FUN_001634a6(param_1,*(long *)(param_1 + 0xe8) + 8);
  wlc_bmac_mctrl(param_1,0x40000000,0x40000000);
  FUN_001655c7(param_1,2);
  FUN_00163509(param_1);
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uStack_18;
  return auVar1 << 0x40;
}

