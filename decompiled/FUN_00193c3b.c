
char * FUN_00193c3b(long param_1,ushort param_2,char param_3)

{
  ulong uVar1;
  ulong uVar2;
  char *pcVar3;
  undefined8 uVar4;
  char cVar5;
  char *pcVar6;
  ulong uVar7;
  uint uVar8;
  
  pcVar3 = (char *)(*(long *)(param_1 + 0x138) + 0x6c8);
  if ((param_2 & 0xc000) != 0) {
    pcVar3 = (char *)(*(long *)(param_1 + 0x138) + 0x7b8);
  }
  cVar5 = '\0';
  pcVar6 = pcVar3;
  do {
    if ((*pcVar6 == (char)param_2) && (*(ushort *)(pcVar6 + 2) == (param_2 & 0x3800)))
    goto LAB_00193c9b;
    cVar5 = cVar5 + '\x01';
    pcVar6 = pcVar6 + 0x50;
  } while (cVar5 != '\x03');
  pcVar6 = (char *)0x0;
LAB_00193c9b:
  if (pcVar6 == (char *)0x0) {
    if (param_3 == '\0') {
      return (char *)0x0;
    }
    uVar1 = *(ulong *)(pcVar3 + 8);
    uVar2 = *(ulong *)(pcVar3 + 0x58);
    uVar7 = uVar2;
    if (uVar2 >= uVar1) {
      uVar7 = uVar1;
    }
    uVar8 = (uint)(uVar2 < uVar1);
    if (*(ulong *)(pcVar3 + 0xa8) < uVar7) {
      uVar8 = 2;
    }
    pcVar6 = pcVar3 + (ulong)uVar8 * 0x50;
    osl_memset(pcVar6,0,0x50);
    *pcVar6 = (char)*(undefined2 *)(param_1 + 0x17e);
    *(undefined2 *)(pcVar6 + 2) = *(undefined2 *)(param_1 + 0x182);
  }
  if (param_3 != '\0') {
    pcVar6[0x45] = '\x02';
    uVar4 = wlc_phy_get_time_usec(param_1);
    *(undefined8 *)(pcVar6 + 8) = uVar4;
  }
  return pcVar6;
}

