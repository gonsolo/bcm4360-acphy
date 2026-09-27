
void wlc_fatal_error(long *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  
  uVar3 = 0;
  piVar1 = (int *)(*(long *)(*param_1 + 0xa0) + 0x2ec);
  *piVar1 = *piVar1 + 1;
  uVar2 = wlc_hrt_gptimer_get();
  if (param_1[0x5f] != 0) {
    uVar3 = *(undefined1 *)(*(long *)(param_1[0x5f] + 0x338) + 8);
    wlc_set_ps_ctrl();
  }
  wl_init(param_1[2]);
  wlc_hrt_gptimer_set(param_1,uVar2);
  if (param_1[0x5f] != 0) {
    *(undefined1 *)(*(long *)(param_1[0x5f] + 0x338) + 8) = uVar3;
    wlc_set_ps_ctrl();
  }
  return;
}

