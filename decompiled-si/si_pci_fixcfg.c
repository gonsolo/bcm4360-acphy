
undefined8 si_pci_fixcfg(long param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  ushort uVar4;
  long lVar5;
  undefined8 uVar6;
  
  if ((*(int *)(param_1 + 0x3c) == 0x4321) && (*(uint *)(param_1 + 0x40) < 2)) {
    FUN_00122a5d(param_1,0x28,0xffffffff,(-(uint)(*(uint *)(param_1 + 0x40) == 0) & 0x300) + 0xa4);
  }
  iVar1 = *(int *)(param_1 + 8);
  uVar2 = *(undefined4 *)(param_1 + 0x1c0);
  if (iVar1 == 0x83c) {
    uVar6 = 0x83c;
  }
  else if (iVar1 == 0x820) {
    uVar6 = 0x820;
  }
  else {
    lVar5 = 0;
    if (iVar1 != 0x804) goto LAB_00122c1c;
    uVar6 = 0x804;
  }
  lVar5 = si_setcore(param_1,uVar6,0);
  lVar5 = lVar5 + 0x800;
LAB_00122c1c:
  uVar6 = 0xffffffff;
  uVar3 = *(uint *)(param_1 + 0x1c0);
  if (lVar5 != 0) {
    uVar4 = osl_readw(lVar5);
    if (uVar4 >> 0xc != (ushort)uVar3) {
      osl_writew((uint)(uVar4 & 0xfff) | (uVar3 & 0xf) << 0xc,lVar5);
    }
    si_setcoreidx(param_1,uVar2);
    pcicore_hwup(*(undefined8 *)(param_1 + 0x90));
    uVar6 = 0;
  }
  return uVar6;
}

