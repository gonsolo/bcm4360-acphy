
undefined4
wlc_bmac_process_ucode_sr
          (undefined2 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
          undefined8 param_5)

{
  undefined4 uVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  undefined8 uVar6;
  
  lVar2 = osl_malloc(param_2,0x1d0);
  uVar1 = 0x1e;
  if (lVar2 != 0) {
    osl_memset(lVar2,0,0x1d0);
    lVar3 = si_attach(param_1,param_2,param_3,param_4,param_5,lVar2 + 0xc0,lVar2 + 200);
    *(long *)(lVar2 + 0xb8) = lVar3;
    uVar1 = 0xb;
    if (lVar3 != 0) {
      if (*(uint *)(lVar2 + 0x84) < 0xc) {
        uVar6 = 4;
        iVar5 = 8;
      }
      else {
        uVar6 = 0;
        iVar5 = (-(uint)(*(uint *)(lVar2 + 0x84) < 0x12) & 0xfffffffc) + 0xc;
      }
      uVar4 = si_setcore(lVar3,0x812,0);
      *(undefined8 *)(lVar2 + 0xd0) = uVar4;
      si_core_reset(*(undefined8 *)(lVar2 + 0xb8),iVar5,uVar6);
      FUN_001614f0(lVar2);
      si_detach(*(undefined8 *)(lVar2 + 0xb8));
      uVar1 = 0;
    }
    osl_mfree(param_2,lVar2,0x1d0);
  }
  return uVar1;
}

