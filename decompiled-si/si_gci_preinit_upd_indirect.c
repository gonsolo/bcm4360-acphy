
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint si_gci_preinit_upd_indirect(undefined4 param_1,uint param_2,uint param_3)

{
  _DAT_18000c40 = param_1;
  _DAT_18000e00 = ~param_3 & _DAT_18000e00 | param_2;
  return _DAT_18000e00;
}

