
undefined1  [16] si_is_sprom_available(long param_1)

{
  undefined4 uVar1;
  byte bVar2;
  uint uVar3;
  ulong in_RAX;
  long lVar4;
  bool bVar5;
  undefined1 auVar6 [16];
  undefined8 uStack_28;
  
  if (*(int *)(param_1 + 0x14) < 0x1f) {
    uVar3 = *(uint *)(param_1 + 0x3c);
    in_RAX = (ulong)uVar3;
    if (uVar3 == 0x4350) {
LAB_00120408:
      bVar2 = (byte)(*(uint *)(param_1 + 0x48) >> 6);
    }
    else {
      if (0x4350 < uVar3) {
        if (uVar3 < 0xa8dd) {
          if ((0xa8da < uVar3) || (uVar3 == 0xa87b)) {
LAB_00120412:
            bVar2 = (byte)(*(uint *)(param_1 + 0x48) >> 1) ^ 1;
            goto LAB_0012041d;
          }
          if (uVar3 < 0xa87c) {
            uVar3 = uVar3 - 0xa867;
          }
          else {
            if (uVar3 == 0xa8d1) goto LAB_00120412;
            if (uVar3 < 0xa8d1) goto LAB_001203b4;
            uVar3 = uVar3 - 0xa8d5;
          }
          in_RAX = (ulong)uVar3;
          if (uVar3 < 2) goto LAB_00120408;
        }
        else {
          if (uVar3 == 0xa8ea) goto LAB_001203ec;
          if (0xa8ea < uVar3) {
            if (uVar3 == 0xa9a4) goto LAB_00120412;
            if (uVar3 != 0xa9a7) {
              bVar5 = uVar3 == 0xa962;
LAB_001203b2:
              if (!bVar5) goto LAB_001203b4;
            }
LAB_001203d8:
            bVar2 = (byte)(*(uint *)(param_1 + 0x48) >> 1);
            goto LAB_0012041d;
          }
          if (uVar3 == 0xa8df) goto LAB_00120408;
          if (uVar3 == 0xa8e7) {
            in_RAX = 0;
            bVar5 = (*(uint *)(param_1 + 0x48) & 6) == 2;
            goto LAB_00120421;
          }
        }
LAB_001203b4:
        bVar5 = true;
        goto LAB_00120421;
      }
      if (uVar3 == 0x4324) {
LAB_001203ec:
        uVar3 = (*(uint *)(param_1 + 0x48) & 0x400080) - 0x80;
        in_RAX = (ulong)uVar3;
        bVar5 = uVar3 == 0;
        goto LAB_00120421;
      }
      if (uVar3 < 0x4325) {
        if (uVar3 != 0x4313) {
          if (uVar3 < 0x4314) {
            if (uVar3 != 0x10f6) {
              if (uVar3 == 0x4312) {
                in_RAX = 0;
                bVar5 = (*(uint *)(param_1 + 0x48) & 3) != 2;
                goto LAB_00120421;
              }
              goto LAB_001203b4;
            }
          }
          else if ((uVar3 != 0x4319) && (uVar3 != 0x4322)) {
            bVar5 = uVar3 == 0x4315;
            goto LAB_0012031c;
          }
          goto LAB_00120408;
        }
      }
      else {
        if (uVar3 == 0x4330) {
          bVar2 = (byte)(*(uint *)(param_1 + 0x48) >> 7);
          goto LAB_0012041d;
        }
        if (0x4330 < uVar3) {
          if (uVar3 == 0x4335) {
            in_RAX = 0;
            bVar5 = (*(uint *)(param_1 + 0x48) & 0x60) == 0x20;
            goto LAB_00120421;
          }
          if (uVar3 != 0x4336) {
            bVar5 = uVar3 == 0x4331;
            goto LAB_001203b2;
          }
          goto LAB_001203d8;
        }
        if (uVar3 != 0x4325) {
          bVar5 = uVar3 == 0x4329;
LAB_0012031c:
          if (!bVar5) goto LAB_001203b4;
        }
      }
      bVar2 = (byte)*(undefined4 *)(param_1 + 0x48);
    }
  }
  else {
    bVar5 = false;
    if ((*(byte *)(param_1 + 0x1b) & 0x40) == 0) goto LAB_00120421;
    uVar1 = *(undefined4 *)(param_1 + 0x1c0);
    lVar4 = si_setcoreidx(param_1,0);
    bVar2 = osl_readl(lVar4 + 400);
    in_RAX = si_setcoreidx(param_1,uVar1);
  }
LAB_0012041d:
  bVar5 = (bool)(bVar2 & 1);
LAB_00120421:
  auVar6._1_7_ = (undefined7)(in_RAX >> 8);
  auVar6[0] = bVar5;
  auVar6._8_8_ = uStack_28;
  return auVar6;
}

