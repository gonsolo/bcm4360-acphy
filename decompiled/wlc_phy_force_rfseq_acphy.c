
void wlc_phy_force_rfseq_acphy(undefined8 param_1,undefined1 param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  undefined8 uVar5;
  ushort uVar6;
  
  switch(param_2) {
  case 0:
    uVar6 = 1;
    uVar5 = 1;
    break;
  case 1:
    uVar6 = 2;
    uVar5 = 2;
    break;
  case 2:
    uVar6 = 0x20;
    uVar5 = 0x20;
    break;
  case 3:
    uVar6 = 4;
    uVar5 = 4;
    break;
  case 4:
    uVar6 = 8;
    uVar5 = 8;
    break;
  case 5:
    uVar6 = 0x10;
    uVar5 = 0x10;
    break;
  default:
    goto switchD_001988fe_default;
  }
  uVar1 = phy_reg_read(param_1,0x400);
  uVar2 = phy_reg_read(param_1,0x19e);
  phy_reg_mod(param_1,0x19e,2,2);
  phy_reg_mod(param_1,0x19e,1,1);
  phy_reg_or(param_1,0x400,3);
  phy_reg_or(param_1,0x402,uVar5);
  for (iVar4 = 0x30d49; (uVar3 = phy_reg_read(param_1,0x403), (uVar3 & uVar6) != 0 && (iVar4 != 9));
      iVar4 = iVar4 + -10) {
    osl_delay(10);
  }
  phy_reg_write(param_1,0x400,uVar1);
  phy_reg_write(param_1,0x19e,uVar2);
switchD_001988fe_default:
  return;
}

