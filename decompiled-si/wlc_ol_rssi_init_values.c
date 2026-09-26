
void wlc_ol_rssi_init_values(long *param_1,char param_2)

{
  long *plVar1;
  long lVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c;
  char local_2b;
  char local_2a;
  char local_29;
  char local_28;
  char local_27;
  char local_26;
  char local_25;
  char local_24;
  ushort local_23;
  undefined2 local_21;
  short local_1f;
  
  if (param_1 != (long *)0x0) {
    plVar1 = (long *)*param_1;
    lVar2 = plVar1[0x5f];
    if ((((((*(byte *)(*plVar1 + 0xec) & 1) != 0) && (lVar2 != 0)) &&
         (*(char *)(lVar2 + 0x22) != '\0')) &&
        ((*(char *)(lVar2 + 8) != '\0' && (plVar1[0xb2] == 0)))) &&
       ((plVar1[0x37] == 0 || (*(char *)(plVar1[0x37] + 10) == '\0')))) {
      lVar2 = *(long *)(*(long *)(plVar1[4] + 0xe8) + 0x28);
      local_38 = 3;
      local_34 = 0;
      local_30 = 0xf;
      local_2c = 1;
      local_2b = (char)*(undefined4 *)(*(long *)(*param_1 + 0x40) + 0xf4);
      local_2a = *(char *)(*(long *)(*(long *)(*param_1 + 0x2f8) + 0x328) + 5);
      local_29 = *(char *)(*(long *)(lVar2 + 0x20) + 0xa8);
      local_28 = *(char *)(*(long *)(lVar2 + 0x20) + 0xa7);
      uVar4 = *(uint *)(*(long *)(lVar2 + 0x138) + 0x8dc);
      local_23 = (ushort)uVar4;
      local_21 = (undefined2)*(undefined4 *)(lVar2 + 0x210);
      local_1f = *(short *)(lVar2 + 0x17e);
      local_27 = *(char *)(lVar2 + 0x212);
      local_26 = *(char *)(lVar2 + 0x213);
      local_25 = *(char *)(lVar2 + 0x214);
      local_24 = *(char *)(lVar2 + 0x215);
      if (DAT_006f349c != '\x01') {
        DAT_006f349c = '\x01';
        param_2 = '\x01';
      }
      if (local_2b != DAT_006f349d) {
        param_2 = '\x01';
        DAT_006f349d = local_2b;
      }
      if (local_2a != DAT_006f349e) {
        param_2 = '\x01';
        DAT_006f349e = local_2a;
      }
      if (local_29 != DAT_006f349f) {
        param_2 = '\x01';
        DAT_006f349f = local_29;
      }
      if (local_28 != DAT_006f34a0) {
        param_2 = '\x01';
        DAT_006f34a0 = local_28;
      }
      uVar4 = (uVar4 & 0xffff) - (uint)DAT_006f34a5;
      uVar5 = (int)uVar4 >> 0x1f;
      if (10 < (int)((uVar4 ^ uVar5) - uVar5)) {
        param_2 = '\x01';
        DAT_006f34a5 = local_23;
      }
      if (local_1f != DAT_006f34a9) {
        param_2 = '\x01';
        DAT_006f34a9 = local_1f;
      }
      if (local_27 != DAT_006f34a1) {
        param_2 = '\x01';
        DAT_006f34a1 = local_27;
      }
      if (local_26 != DAT_006f34a2) {
        param_2 = '\x01';
        DAT_006f34a2 = local_26;
      }
      if (local_25 != DAT_006f34a3) {
        param_2 = '\x01';
        DAT_006f34a3 = local_25;
      }
      cVar3 = local_24;
      if ((local_24 != DAT_006f34a4) || (cVar3 = DAT_006f34a4, param_2 != '\0')) {
        DAT_006f34a4 = cVar3;
        FUN_0017fcad(param_1,&local_38,0x1b);
      }
    }
  }
  return;
}

