
long wlc_get_txh_info(long *param_1,long param_2,int *param_3)

{
  undefined2 uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long local_30;
  
  if ((param_3 != (int *)0x0) && (param_2 != 0)) {
    if (*(uint *)(*param_1 + 0x14) < 0x28) {
      puVar6 = (undefined2 *)osl_pktdata(param_1[1]);
      if (puVar6 != (undefined2 *)0x0) {
        param_3[10] = 0;
        param_3[0xb] = 0;
        param_3[0xc] = 0;
        *(undefined2 *)(param_3 + 1) = puVar6[0x26];
        *param_3 = *(int *)(puVar6 + 0x21);
        *(undefined2 *)((long)param_3 + 6) = *puVar6;
        uVar1 = puVar6[1];
        *(undefined2 **)(param_3 + 0xe) = puVar6 + 0x13;
        param_3[5] = 0x70;
        *(undefined2 **)(param_3 + 6) = puVar6;
        *(undefined2 *)(param_3 + 2) = uVar1;
        *(undefined2 **)(param_3 + 0x10) = puVar6 + 0x38;
        *(undefined2 **)(param_3 + 8) = puVar6 + 0x3b;
        *(undefined2 *)((long)param_3 + 10) = puVar6[4];
        *(undefined2 *)(param_3 + 3) = puVar6[5];
        *(ushort *)(param_3 + 0x12) = (ushort)puVar6[0x46] >> 4;
        sVar3 = pkttotlen(param_1[1],param_2);
        *(undefined2 *)((long)param_3 + 0xe) = 0;
        *(short *)((long)param_3 + 0x12) = sVar3 + -0x76;
        *(undefined2 *)(param_3 + 4) = puVar6[0x23];
      }
    }
    else {
      local_30 = 0;
      iVar4 = wlc_pkt_get_vht_hdr(param_1,param_2,&local_30);
      uVar7 = osl_pktdata(param_1[1],param_2);
      param_3[0xc] = iVar4;
      uVar8 = 0;
      if (iVar4 != 0) {
        uVar8 = uVar7;
      }
      *(undefined8 *)(param_3 + 10) = uVar8;
      *param_3 = (uint)*(ushort *)(local_30 + 0x10) << 8;
      *(undefined2 *)(param_3 + 1) = *(undefined2 *)(local_30 + 0xc);
      uVar2 = *(ushort *)(local_30 + 2);
      *(ushort *)((long)param_3 + 6) = uVar2;
      uVar1 = *(undefined2 *)(local_30 + 4);
      *(long *)(param_3 + 6) = local_30;
      *(undefined2 *)(param_3 + 2) = uVar1;
      uVar5 = (-(uint)((uVar2 & 1) == 0) & 0x68) + 0x14;
      param_3[5] = uVar5;
      *(ulong *)(param_3 + 8) = (ulong)uVar5 + local_30;
      sVar3 = pkttotlen(param_1[1],param_2);
      *(short *)((long)param_3 + 0x12) = (sVar3 - (short)param_3[5]) - (short)iVar4;
      *(long *)(param_3 + 0xe) = *(long *)(param_3 + 8) + 4;
      *(long *)(param_3 + 0x10) = local_30 + 0x1a;
      *(undefined2 *)((long)param_3 + 10) = *(undefined2 *)(local_30 + 0x14);
      *(undefined2 *)(param_3 + 3) = *(undefined2 *)(local_30 + 0x16);
      *(undefined2 *)((long)param_3 + 0xe) = *(undefined2 *)(local_30 + 0x18);
      *(undefined1 *)(param_3 + 4) = *(undefined1 *)(local_30 + 0x21);
      *(undefined1 *)((long)param_3 + 0x11) = *(undefined1 *)(local_30 + 0x20);
      *(ushort *)(param_3 + 0x12) = *(ushort *)(local_30 + 0xe) >> 4;
    }
  }
  return local_30;
}

