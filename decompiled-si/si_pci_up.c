
void si_pci_up(long param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  bool bVar6;
  
  if (*(int *)(param_1 + 4) != 1) {
    return;
  }
  iVar2 = *(int *)(param_1 + 8);
  if ((((iVar2 == 0x820) && (*(int *)(param_1 + 0x3c) == 0x4311)) && (*(uint *)(param_1 + 0x40) < 2)
      ) || (((iVar2 == 0x820 || (iVar2 == 0x804)) &&
            ((iVar3 = *(int *)(param_1 + 0x3c), iVar3 == 0x4321 ||
             ((iVar2 == 0x820 && ((iVar3 == 0x4716 || (iVar3 == 0x4748)))))))))) {
    FUN_00121d9c(param_1,0);
  }
  if ((*(int *)(param_1 + 4) == 1) &&
     ((*(int *)(param_1 + 8) == 0x83c || (*(int *)(param_1 + 8) == 0x820)))) {
    pcicore_up(*(undefined8 *)(param_1 + 0x90),3);
    if (*(int *)(param_1 + 0x3c) == 0x4311) {
      bVar6 = *(int *)(param_1 + 0x40) == 2;
    }
    else {
      bVar6 = *(int *)(param_1 + 0x3c) == 0x4312;
    }
    if (bVar6) {
      lVar4 = param_1;
      for (uVar5 = 0; uVar5 < *(uint *)(param_1 + 0x1c4); uVar5 = uVar5 + 1) {
        piVar1 = (int *)(lVar4 + 0x1c8);
        lVar4 = lVar4 + 4;
        if (*piVar1 == 0x812) goto LAB_00122207;
      }
      uVar5 = 0x21;
LAB_00122207:
      sb_set_initiator_to(param_1,3,uVar5);
    }
  }
  return;
}

