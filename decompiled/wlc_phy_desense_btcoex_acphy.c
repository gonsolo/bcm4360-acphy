
void wlc_phy_desense_btcoex_acphy(long param_1,int param_2)

{
  int iVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x138);
  iVar1 = *(int *)(lVar2 + 0x8b0);
  osl_memset(lVar2 + 0x8b4,0,9);
  *(int *)(lVar2 + 0x8b0) = param_2;
  *(bool *)(lVar2 + 0x8bc) = 0 < param_2;
  switch(param_2) {
  case 1:
    *(undefined1 *)(lVar2 + 0x8b8) = 1;
    *(undefined1 *)(lVar2 + 0x8b9) = 3;
    *(undefined1 *)(lVar2 + 0x8ba) = 0;
    break;
  case 2:
    *(undefined1 *)(lVar2 + 0x8b8) = 0;
    *(undefined1 *)(lVar2 + 0x8b9) = 0;
    *(undefined1 *)(lVar2 + 0x8ba) = 1;
    break;
  case 3:
    *(undefined1 *)(lVar2 + 0x8b8) = 0;
    *(undefined1 *)(lVar2 + 0x8b9) = 2;
    *(undefined1 *)(lVar2 + 0x8ba) = 1;
    *(undefined1 *)(lVar2 + 0x8bb) = 2;
    break;
  case 4:
    *(undefined1 *)(lVar2 + 0x8b8) = 1;
    *(undefined1 *)(lVar2 + 0x8b9) = 2;
    *(undefined1 *)(lVar2 + 0x8ba) = 1;
    *(undefined1 *)(lVar2 + 0x8bb) = 3;
    break;
  case 5:
    *(undefined1 *)(lVar2 + 0x8b8) = 3;
    *(undefined1 *)(lVar2 + 0x8b9) = 0;
    *(undefined1 *)(lVar2 + 0x8ba) = 1;
    *(undefined1 *)(lVar2 + 0x8bb) = 0xd;
    break;
  case 6:
    *(undefined1 *)(lVar2 + 0x8b8) = 3;
    *(undefined1 *)(lVar2 + 0x8b9) = 4;
    *(undefined1 *)(lVar2 + 0x8ba) = 1;
    *(undefined1 *)(lVar2 + 0x8bb) = 0x18;
  }
  if (((*(ushort *)(param_1 + 0x17e) & 0xc000) == 0) && ((*(uint *)(param_1 + 0x19c) & 0x206) == 0))
  {
    if ((0 < param_2) && (param_2 != iVar1)) {
      wlc_phy_desense_aci_reset_params_acphy(param_1,0,0,0);
    }
    FUN_0019b279(param_1,1);
  }
  return;
}

