
void phy_reg_write_array(undefined8 param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  int iVar4;
  
  do {
    if (param_3 < 1) {
      return;
    }
    iVar4 = param_3 + -2;
    puVar3 = param_2 + 2;
    uVar2 = *param_2 & 0xe000;
    uVar1 = param_2[1] & 0x1fff;
    if (uVar2 == 0x6000) {
      phy_reg_or(param_1,uVar1,param_2[2]);
    }
    else if (uVar2 < 0x6001) {
      if (uVar2 == 0x2000) {
        phy_reg_and(param_1,uVar1,*puVar3);
      }
      else if (uVar2 == 0x4000) {
        phy_reg_write(param_1,uVar1,*puVar3);
      }
      else if (uVar2 == 0) {
        phy_reg_mod(param_1,uVar1,*puVar3,param_2[3]);
LAB_001b7cb5:
        puVar3 = param_2 + 3;
        iVar4 = param_3 + -3;
      }
    }
    else if (uVar2 == 0xa000) {
      and_radio_reg(param_1,uVar1,*puVar3);
    }
    else if (uVar2 < 0xa001) {
      if (uVar2 == 0x8000) {
        mod_radio_reg(param_1,uVar1,*puVar3,param_2[3]);
        goto LAB_001b7cb5;
      }
    }
    else if (uVar2 == 0xc000) {
      write_radio_reg(param_1,uVar1,*puVar3);
    }
    else if (uVar2 == 0xe000) {
      or_radio_reg(param_1,uVar1,*puVar3);
    }
    param_2 = puVar3 + 1;
    param_3 = iVar4 + -1;
  } while( true );
}

