
void si_detach(undefined *param_1)

{
  undefined *puVar1;
  long lVar2;
  undefined *local_30 [2];
  undefined8 local_20;
  
  local_20 = 0;
  local_30[0] = param_1;
  osl_memcpy(&local_20,local_30,8);
  puVar1 = local_30[0];
  if (local_30[0] != (undefined *)0x0) {
    if (*(int *)(local_30[0] + 4) == 0) {
      lVar2 = 0;
      do {
        if (*(long *)(puVar1 + lVar2 + 0xc0) != 0) {
          osl_reg_unmap();
          *(undefined8 *)(puVar1 + lVar2 + 0xc0) = 0;
        }
        lVar2 = lVar2 + 8;
      } while (lVar2 != 0x100);
    }
    srom_var_deinit(local_20);
    nvram_exit(local_20);
    if (*(int *)(local_30[0] + 4) == 1) {
      if (*(long *)(puVar1 + 0x90) != 0) {
        pcicore_deinit();
      }
      *(undefined8 *)(puVar1 + 0x90) = 0;
    }
    if (puVar1 != &DAT_006f07c0) {
      osl_mfree(*(undefined8 *)(puVar1 + 0x58),puVar1,0x7d8);
    }
  }
  return;
}

