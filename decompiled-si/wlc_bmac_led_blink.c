
void wlc_bmac_led_blink(long param_1,int param_2,ushort param_3,ushort param_4)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  uint *puVar9;
  uint local_98 [34];
  
  lVar1 = *(long *)(param_1 + 0x198);
  *(uint *)((long)param_2 * 0x18 + 0x14 + lVar1) = (uint)param_4;
  *(uint *)((long)param_2 * 0x18 + 0x10 + lVar1) = (uint)param_3;
  local_98[0] = 1000;
  uVar4 = 0;
  for (lVar3 = lVar1 + 8; uVar6 = (uint)uVar4, lVar3 != lVar1 + 0x308; lVar3 = lVar3 + 0x18) {
    if ((*(uint *)(lVar3 + 8) == 0) && (*(int *)(lVar3 + 0xc) == 0)) {
      *(undefined1 *)(lVar3 + 0x15) = 1;
      uVar7 = uVar4;
    }
    else {
      uVar2 = *(uint *)(lVar3 + 8);
      uVar8 = *(uint *)(lVar3 + 0xc);
      while (uVar8 != 0) {
        uVar5 = uVar2 % uVar8;
        uVar2 = uVar8;
        uVar8 = uVar5;
      }
      uVar7 = (ulong)(uVar6 + 1);
      local_98[uVar4] = uVar2;
    }
    uVar4 = uVar7;
  }
  puVar9 = local_98;
  uVar2 = local_98[0];
  for (uVar8 = 1; puVar9 = puVar9 + 1, uVar8 < uVar6; uVar8 = uVar8 + 1) {
    uVar4 = (ulong)*puVar9;
    while (uVar5 = (uint)uVar4, uVar5 != 0) {
      uVar4 = (ulong)uVar2 % uVar4;
      uVar2 = uVar5;
    }
  }
  uVar8 = 10;
  if (9 < uVar2) {
    uVar8 = uVar2;
  }
  *(uint *)(lVar1 + 0x310) = uVar8;
  if (((uVar6 != 0) && (*(char *)(lVar1 + 800) != '\0')) && (*(char *)(lVar1 + 0x321) == '\0')) {
    wlc_bmac_led_blink_event(param_1,0);
    wlc_bmac_led_blink_event(param_1,1);
  }
  return;
}

