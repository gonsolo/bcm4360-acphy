
long si_getdevpathvar(undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  undefined1 local_58 [48];
  
  FUN_00122522(param_1,local_58,param_2);
  lVar1 = getvar(0,local_58);
  if (lVar1 == 0) {
    lVar2 = si_coded_devpathvar(param_1,local_58,0x30,param_2);
    if (lVar2 != 0) {
      lVar1 = getvar(0,local_58);
    }
  }
  return lVar1;
}

