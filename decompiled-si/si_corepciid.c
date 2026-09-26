
undefined8
si_corepciid(long param_1,uint param_2,undefined2 *param_3,undefined2 *param_4,undefined1 *param_5,
            undefined1 *param_6,char *param_7,undefined1 *param_8)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  bool bVar8;
  
  uVar3 = *(uint *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4);
  if ((uVar3 == 0x504) || (uVar1 = 1, uVar3 == 0x819)) {
    uVar1 = 2;
  }
  if ((uVar1 <= param_2) || ((iVar2 = si_corevendor(param_1), iVar2 != 0x4bf && (iVar2 != 0x4243))))
  {
    return 0xffffffff;
  }
  if (uVar3 == 0x817) {
LAB_00122944:
    uVar6 = 0;
    cVar4 = '\x10';
    uVar5 = 3;
    uVar7 = 0xc;
    uVar3 = 0x4716;
  }
  else {
    if (uVar3 < 0x818) {
      if (uVar3 == 0x807) {
        uVar6 = 0;
        cVar4 = '\0';
        uVar5 = 3;
        uVar7 = 7;
        uVar3 = 0x4712;
        goto LAB_00122a2a;
      }
      if (uVar3 < 0x808) {
        if (uVar3 == 0x800) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 1;
          uVar7 = 5;
          uVar3 = 0x800;
          goto LAB_00122a2a;
        }
        if (uVar3 < 0x801) {
          if (uVar3 == 0x504) {
LAB_00122958:
            uVar6 = 0x80;
            uVar5 = 3;
            uVar7 = 0xc;
            uVar3 = 0x471a;
            cVar4 = (-(param_2 == 0) & 0xf0U) + 0x20;
            goto LAB_00122a2a;
          }
          if (uVar3 == 0x505) {
            uVar6 = 0;
            cVar4 = '0';
            uVar5 = 3;
            uVar3 = 0x472a;
            uVar7 = 0xc;
            goto LAB_00122a2a;
          }
        }
        else {
          if (uVar3 == 0x804) goto LAB_001228fe;
          if (uVar3 == 0x806) {
            uVar6 = 0;
            cVar4 = '\0';
            uVar5 = 0;
            uVar7 = 2;
            uVar3 = 0x4713;
            goto LAB_00122a2a;
          }
          bVar8 = uVar3 == 0x803;
LAB_001228af:
          if (bVar8) goto LAB_001228f0;
        }
      }
      else if (uVar3 < 0x810) {
        if (0x80d < uVar3) {
LAB_001228f0:
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0;
          uVar7 = 5;
          goto LAB_00122a2a;
        }
        if (uVar3 == 0x808) goto LAB_00122944;
        if (uVar3 == 0x80b) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0;
          uVar7 = 0x10;
          uVar3 = 0x4718;
          goto LAB_00122a2a;
        }
      }
      else {
        if (uVar3 == 0x812) {
          uVar6 = 0;
          uVar3 = si_d11_devid(param_1);
          cVar4 = '\0';
          uVar5 = 0x80;
          uVar7 = 2;
          goto LAB_00122a2a;
        }
        bVar8 = uVar3 == 0x816;
LAB_0012288d:
        if (bVar8) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0x30;
          uVar7 = 0xb;
          goto LAB_00122a2a;
        }
      }
    }
    else {
      if (uVar3 == 0x81f) {
        uVar6 = 0;
        cVar4 = '\0';
        uVar5 = 0;
        uVar7 = 2;
        uVar3 = 0x471f;
        goto LAB_00122a2a;
      }
      if (0x81f < uVar3) {
        if (uVar3 == 0x82d) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0;
          uVar7 = 2;
          uVar3 = 0x4715;
          goto LAB_00122a2a;
        }
        if (uVar3 < 0x82e) {
          if (uVar3 != 0x820) {
            bVar8 = uVar3 == 0x82c;
            goto LAB_0012288d;
          }
        }
        else {
          if (uVar3 == 0x834) {
            uVar6 = 0;
            cVar4 = '\0';
            uVar5 = 1;
            uVar7 = 4;
            uVar3 = 0x4711;
            goto LAB_00122a2a;
          }
          if (uVar3 != 0x83c) {
            bVar8 = uVar3 == 0x82e;
            goto LAB_001228af;
          }
        }
LAB_001228fe:
        uVar6 = 1;
        cVar4 = '\0';
        uVar5 = 4;
        uVar7 = 6;
        goto LAB_00122a2a;
      }
      if (uVar3 == 0x81a) {
        uVar6 = 0;
        cVar4 = '\0';
        uVar5 = 3;
        uVar7 = 0xc;
        uVar3 = 0x471b;
        goto LAB_00122a2a;
      }
      if (uVar3 < 0x81b) {
        if (uVar3 == 0x818) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 3;
          uVar7 = 0xc;
          uVar3 = 0x4717;
          goto LAB_00122a2a;
        }
        if (uVar3 == 0x819) goto LAB_00122958;
      }
      else {
        if (uVar3 == 0x81d) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 1;
          uVar7 = 1;
          uVar3 = 0x471d;
          goto LAB_00122a2a;
        }
        if (0x81d < uVar3) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0;
          uVar7 = 0xfe;
          uVar3 = 0x471e;
          goto LAB_00122a2a;
        }
        if (uVar3 == 0x81c) {
          uVar6 = 0;
          cVar4 = '\0';
          uVar5 = 0x80;
          uVar7 = 7;
          uVar3 = 0x4719;
          goto LAB_00122a2a;
        }
      }
    }
    cVar4 = -1;
    uVar6 = 0;
    uVar5 = 0xff;
    uVar7 = uVar5;
  }
LAB_00122a2a:
  *param_3 = 0x14e4;
  *param_4 = (short)uVar3;
  *param_5 = uVar7;
  *param_6 = uVar5;
  *param_7 = cVar4;
  *param_8 = uVar6;
  return 0;
}

