
void FUN_001986fc(long param_1,char param_2)

{
  long lVar1;
  undefined2 uVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  
  sVar5 = 0x6d4;
  sVar4 = 0x6da;
  lVar1 = *(long *)(param_1 + 0x138);
  for (uVar3 = 0; uVar3 < *(byte *)(param_1 + 0x168); uVar3 = uVar3 + 1) {
    if (*(int *)(param_1 + 0x164) == 0) {
      if (param_2 == '\0') {
        uVar2 = 0xffff;
      }
      else {
        uVar2 = *(undefined2 *)(lVar1 + 0x902);
      }
      phy_reg_write(param_1,sVar4,uVar2);
    }
    else if (param_2 == '\0') {
      phy_reg_or(param_1,sVar5,0x4000);
    }
    else {
      phy_reg_and(param_1,sVar5,0xbfff);
    }
    sVar4 = sVar4 + 0x200;
    sVar5 = sVar5 + 0x200;
  }
  return;
}

