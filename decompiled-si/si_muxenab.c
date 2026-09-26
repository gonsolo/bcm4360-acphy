
void si_muxenab(long param_1,uint param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  undefined8 uVar8;
  bool bVar9;
  
  uVar4 = si_pmu_chipcontrol(param_1,1,0,0);
  uVar5 = FUN_00122a5d(param_1,0x28,0,0);
  uVar6 = *(uint *)(param_1 + 0x3c);
  if (uVar6 == 0x4360) {
LAB_00123672:
    uVar6 = uVar5 | 2;
    bVar9 = (param_2 & 1) == 0;
  }
  else {
    if (uVar6 < 0x4361) {
      if (uVar6 == 0x4336) {
        if ((param_2 & 1) == 0) {
          uVar4 = uVar4 & 0xfeffffff;
        }
        else {
          uVar4 = uVar4 | 0x1000000;
        }
        goto LAB_0012381c;
      }
      if (uVar6 < 0x4337) {
        if (uVar6 == 0x4330) {
          uVar4 = uVar4 & 0xfeffffff;
          uVar6 = uVar5 & 0xfffffff0;
          if ((param_2 & 8) == 0) {
            uVar6 = uVar5 & 0xfffffff0 | 8;
          }
          if ((param_2 & 1) != 0) {
            uVar4 = uVar4 | 0x1000000;
          }
          if ((param_2 & 2) != 0) {
            uVar6 = uVar6 | 1;
          }
          uVar5 = uVar6;
          if ((param_2 & 4) != 0) {
            uVar5 = uVar6 | 2;
          }
          uVar6 = uVar5 | 4;
          bVar9 = (param_2 & 0x10) == 0;
          goto LAB_00123725;
        }
        if (uVar6 != 0x4335) goto LAB_0012381c;
        if ((param_2 & 0xf) != 0) {
          uVar6 = (param_2 & 0xf) - 1;
          uVar7 = (ulong)(uVar6 & 0xff);
          iVar3 = *(int *)(&DAT_0050d5b4 + uVar7 * 8);
          cVar1 = (&DAT_0050d5b0)[uVar7 * 8];
          if (3 < (byte)uVar6) goto LAB_0012381c;
          si_gci_set_functionsel(param_1,iVar3,6);
          si_gci_set_functionsel(param_1,cVar1,6);
          if ((cVar1 == '\x06') && (iVar3 == 2)) {
            si_gci_chipcontrol(param_1,6,0x10,0x10);
          }
        }
        if (((param_2 & 0xf0) == 0) || (uVar6 = ((param_2 & 0xf0) >> 4) - 1, 2 < (byte)uVar6))
        goto LAB_0012381c;
        uVar8 = 10;
        uVar2 = (&DAT_0050d5d0)[uVar6 & 0xff];
      }
      else {
        if (uVar6 != 0x4350) {
          bVar9 = uVar6 == 0x4352;
          goto LAB_00123600;
        }
        if (((param_2 & 0xf) == 0) || (uVar6 = (param_2 & 0xf) - 1, 2 < (byte)uVar6))
        goto LAB_0012381c;
        uVar7 = (ulong)(uVar6 & 0xff);
        uVar2 = (&DAT_0050d5e0)[uVar7 * 8];
        si_gci_set_functionsel(param_1,*(undefined4 *)(&DAT_0050d5e4 + uVar7 * 8),2);
        uVar8 = 2;
      }
      si_gci_set_functionsel(param_1,uVar2,uVar8);
      goto LAB_0012381c;
    }
    if (0xa8eb < uVar6) {
      if (uVar6 != 0xa9c4) {
        bVar9 = uVar6 == 0xaa06;
LAB_00123600:
        if (!bVar9) goto LAB_0012381c;
      }
      goto LAB_00123672;
    }
    if (0xa8e9 < uVar6) {
      uVar4 = uVar4 & 0xfffffffe;
      if ((param_2 & 2) != 0) {
        uVar4 = uVar4 | 1;
      }
      goto LAB_0012381c;
    }
    if (uVar6 != 0xa887) goto LAB_0012381c;
    uVar5 = -(uint)((param_2 & 1) == 0) & 0x200;
    if ((param_2 & 0x1000) != 0) {
      uVar5 = uVar5 | 1;
    }
    if ((param_2 & 0x2000) != 0) {
      uVar5 = uVar5 | 2;
    }
    if ((param_2 & 0x20) != 0) {
      uVar5 = uVar5 | 4;
    }
    if ((param_2 & 0x40) != 0) {
      uVar5 = uVar5 | 8;
    }
    if ((char)param_2 < '\0') {
      uVar5 = uVar5 | 0x10;
    }
    if ((param_2 & 0x100) == 0) {
      uVar5 = uVar5 | 0x20;
    }
    if ((param_2 & 0x200) != 0) {
      uVar5 = uVar5 | 0x40;
    }
    if ((param_2 & 0x400) != 0) {
      uVar5 = uVar5 | 0x80;
    }
    if ((param_2 & 0x800) != 0) {
      uVar5 = uVar5 | 0x100;
    }
    if ((param_2 & 0x10) != 0) {
      uVar5 = uVar5 | 0x800;
    }
    uVar6 = uVar5 | 0x1000;
    bVar9 = (param_2 & 0x4000) == 0;
  }
LAB_00123725:
  if (!bVar9) {
    uVar5 = uVar6;
  }
LAB_0012381c:
  si_pmu_chipcontrol(param_1,1,0xffffffff,uVar4);
  FUN_00122a5d(param_1,0x28,0xffffffff,uVar5);
  return;
}

