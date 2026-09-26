
undefined8 si_coded_devpathvar(undefined8 param_1,undefined8 param_2,int param_3,undefined8 param_4)

{
  int iVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  char local_98 [48];
  undefined1 local_68 [56];
  
  iVar1 = si_devpath(param_1,local_98,0x10);
  if (iVar1 == 0) {
    iVar1 = osl_strlen(local_98);
    if (local_98[iVar1 + -1] == '/') {
      iVar1 = iVar1 + -1;
    }
    iVar4 = 0;
    do {
      osl_snprintf(local_68,0x10,"devpath%d",iVar4);
      lVar3 = getvar(0,local_68);
      if (((lVar3 != 0) &&
          (iVar2 = osl_strlen(lVar3),
          iVar1 == iVar2 - (uint)(*(char *)(lVar3 + -1 + (long)iVar2) == '/'))) &&
         (iVar2 = osl_memcmp(lVar3,local_98,(long)iVar1), iVar2 == 0)) {
        osl_snprintf(param_2,(long)param_3,"%d:%s",iVar4,param_4);
        return param_2;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 0x20);
  }
  return 0;
}

