
long FUN_00110244(long param_1)

{
  ushort uVar1;
  long lVar2;
  ushort *puVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  long lVar7;
  
  do {
    lVar2 = FUN_0010f9b6(param_1,0);
    if (lVar2 == 0) {
      return 0;
    }
    puVar3 = (ushort *)osl_pktdata(*(undefined8 *)(param_1 + 0x30),lVar2);
    uVar1 = *puVar3;
    uVar5 = *(int *)(param_1 + 0xf0) + (uint)uVar1;
    if (*(ushort *)(param_1 + 0xe4) < uVar5) {
      uVar5 = (uint)*(ushort *)(param_1 + 0xe4);
    }
    osl_pktsetlen(*(undefined8 *)(param_1 + 0x30),lVar2,uVar5);
    uVar5 = ((uint)uVar1 - (uint)*(ushort *)(param_1 + 0xe4)) + *(int *)(param_1 + 0xf0);
    lVar7 = lVar2;
    if ((int)uVar5 < 1) {
      return lVar2;
    }
    do {
      lVar4 = FUN_0010f9b6(param_1,0);
      if (lVar4 == 0) break;
      osl_pktsetnext(lVar7,lVar4);
      uVar6 = (uint)*(ushort *)(param_1 + 0xe4);
      if ((int)uVar5 <= (int)(uint)*(ushort *)(param_1 + 0xe4)) {
        uVar6 = uVar5;
      }
      osl_pktsetlen(*(undefined8 *)(param_1 + 0x30),lVar4,uVar6);
      uVar5 = uVar5 - *(ushort *)(param_1 + 0xe4);
      lVar7 = lVar4;
    } while (0 < (int)uVar5);
    if ((*(byte *)(param_1 + 0xc) & 4) != 0) {
      return lVar2;
    }
    osl_pktfree(*(undefined8 *)(param_1 + 0x30),lVar2,0);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  } while( true );
}

