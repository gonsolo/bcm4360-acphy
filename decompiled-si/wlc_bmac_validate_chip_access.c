
/* WARNING: Type propagation algorithm not settling */

uint wlc_bmac_validate_chip_access(long param_1)

{
  long lVar1;
  undefined7 uVar2;
  short sVar3;
  undefined8 uVar4;
  int local_44;
  int local_40 [4];
  
  lVar1 = *(long *)(param_1 + 0xd0);
  wlc_bmac_copyfrom_objmem(param_1,0,local_40 + 1,4,0x10000);
  local_40[0] = -0x55aaaa56;
  wlc_bmac_copyto_objmem(param_1,0,local_40,4,0x10000);
  wlc_bmac_copyfrom_objmem(param_1,0,&local_44,4,0x10000);
  if (local_44 == local_40[0]) {
    local_40[0] = 0x55aaaa55;
    wlc_bmac_copyto_objmem(param_1,0,local_40,4,0x10000);
    wlc_bmac_copyfrom_objmem(param_1,0,&local_44,4,0x10000);
    if (local_44 == local_40[0]) {
      wlc_bmac_copyto_objmem(param_1,0,local_40 + 1,4,0x10000);
      if (10 < *(uint *)(param_1 + 0x84)) {
LAB_00163d6f:
        osl_writel(0,lVar1 + 0x18c);
        uVar4 = osl_readl(lVar1 + 0x120);
        uVar2 = (undefined7)((ulong)uVar4 >> 8);
        return (uint)CONCAT71(uVar2,(int)uVar4 != -0x7bfffc00) &
               (uint)CONCAT71(uVar2,(int)uVar4 != 0x4000400) ^ 1;
      }
      osl_writew(0xaaaa,lVar1 + 0x18c);
      osl_writel(0xccccbbbb,lVar1 + 0x18c);
      sVar3 = osl_readw(lVar1 + 0x604);
      if (sVar3 == -0x4445) {
        local_40[1] = 0xbbbb;
        sVar3 = osl_readw(lVar1 + 0x606);
        if (sVar3 == -0x3334) {
          local_40[1] = 0xcccc;
          goto LAB_00163d6f;
        }
      }
    }
  }
  return 0;
}

