
void FUN_00194b87(undefined8 param_1,char param_2)

{
  ulong uVar1;
  char cVar2;
  undefined8 uVar3;
  
  cVar2 = '\0';
  do {
    osl_delay(10);
    if ((((acphychipid == 0x4352) || (acphychipid == 0x4360)) || (acphychipid == 0xa9c4)) ||
       (uVar3 = 0x91d, acphychipid == 0xaa06)) {
      uVar3 = 0x90b;
    }
    uVar1 = read_radio_reg(param_1,uVar3);
  } while (((uVar1 & 0x100) == 0) && (cVar2 = cVar2 + '\x01', cVar2 != 'd'));
  if (param_2 == '\x01') {
    osl_delay(0x78);
  }
  return;
}

