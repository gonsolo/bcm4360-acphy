
undefined8 wlc_bmac_set_ctrl_bt_shd0(long param_1,char param_2)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0xb8);
  if (*(int *)(lVar2 + 4) == 1) {
    if (((*(int *)(lVar2 + 0x3c) == 0xa9a7) || (*(int *)(lVar2 + 0x3c) == 0x4331)) &&
       (((iVar1 = *(int *)(lVar2 + 0x28), iVar1 == 0x10e ||
         (((iVar1 == 0xe4 || (iVar1 == 0x5c6)) || (iVar1 == 0xef)))) || (iVar1 == 0x10f)))) {
      si_chipcontrl_btshd0_4331(lVar2,param_2 != '\0');
    }
    iVar1 = *(int *)(*(long *)(param_1 + 0xb8) + 0x3c);
    if (((iVar1 == 0xa9c4) || (iVar1 == 0x4360)) || ((iVar1 == 0xaa06 || (iVar1 == 0x4352)))) {
      si_corereg(*(long *)(param_1 + 0xb8),0,0x28,0x1000008,0);
    }
  }
  return 0;
}

