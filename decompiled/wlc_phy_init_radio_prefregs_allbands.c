
uint wlc_phy_init_radio_prefregs_allbands(undefined8 param_1,long param_2)

{
  undefined2 *puVar1;
  uint uVar2;
  ulong uVar3;
  
  uVar3 = 0;
  do {
    uVar2 = (int)uVar3 + 1;
    puVar1 = (undefined2 *)(param_2 + uVar3 * 4);
    write_radio_reg(param_1,*puVar1,puVar1[1]);
    uVar3 = (ulong)uVar2;
  } while (*(short *)(param_2 + (ulong)uVar2 * 4) != -1);
  return uVar2;
}

