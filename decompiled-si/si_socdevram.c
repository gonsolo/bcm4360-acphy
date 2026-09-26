
void si_socdevram(long param_1,char param_2,char *param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;
  undefined4 local_44;
  
  if ((*(code **)(param_1 + 0x78) == (code *)0x0) ||
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) != *(int *)(param_1 + 0x68))
     ) {
    local_44 = 0;
  }
  else {
    local_44 = (**(code **)(param_1 + 0x78))(*(undefined8 *)(param_1 + 0x70));
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1c0);
  if (param_2 == '\0') {
    *param_5 = '\0';
    *param_4 = '\0';
    *param_3 = '\0';
  }
  lVar8 = si_setcore(param_1,0x80e,0);
  if (lVar8 != 0) {
    cVar3 = si_iscoreup(param_1);
    if (cVar3 == '\0') {
      si_core_reset(param_1,0,0);
    }
    uVar4 = si_corerev(param_1);
    if (9 < uVar4) {
      uVar5 = osl_readl(lVar8 + 8);
      uVar6 = 0;
      while( true ) {
        if ((byte)((uVar5 & 0xf000) >> 0xc) <= (byte)uVar6) break;
        osl_writel(uVar6 | 0x200,lVar8 + 0x10);
        uVar7 = osl_readl(lVar8 + 0x40);
        if (param_2 == '\0') {
          if (((byte)uVar6 == 0) && ((uVar7 & 0x2000) != 0)) {
            *param_3 = '\x01';
            if ((uVar7 & 0x4000) != 0) {
              *param_4 = '\x01';
            }
            if ((uVar7 & 0x1000000) != 0) {
              *param_5 = '\x01';
            }
          }
        }
        else {
          uVar7 = uVar7 & 0xfeff9fff;
          if (*param_3 != '\0') {
            uVar2 = uVar7 | 0x2000;
            if (*param_4 != '\0') {
              uVar2 = CONCAT22((short)(uVar7 >> 0x10),(short)(uVar7 | 0x2000)) | 0x4000;
            }
            uVar7 = uVar2;
            if (0xf < uVar4) {
              if (*param_5 != '\0') {
                uVar7 = uVar2 | 0x1000000;
              }
            }
          }
          osl_writel(uVar7,lVar8 + 0x40);
        }
        uVar6 = uVar6 + 1;
      }
    }
    if (cVar3 == '\0') {
      si_core_disable(param_1,0);
    }
    si_setcoreidx(param_1,uVar1);
  }
  if ((*(code **)(param_1 + 0x80) != (code *)0x0) &&
     (*(int *)(param_1 + 0x1c8 + (ulong)*(uint *)(param_1 + 0x1c0) * 4) == *(int *)(param_1 + 0x68))
     ) {
    (**(code **)(param_1 + 0x80))(*(undefined8 *)(param_1 + 0x70),local_44);
  }
  return;
}

