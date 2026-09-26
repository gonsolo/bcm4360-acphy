
undefined8 *
si_gpio_handler_register
          (long param_1,undefined4 param_2,undefined1 param_3,undefined8 param_4,undefined8 param_5)

{
  undefined8 *puVar1;
  
  if ((10 < *(int *)(param_1 + 0x14)) &&
     (puVar1 = (undefined8 *)osl_malloc(*(undefined8 *)(param_1 + 0x58),0x28),
     puVar1 != (undefined8 *)0x0)) {
    osl_memset(puVar1,0,0x28);
    *(undefined4 *)(puVar1 + 3) = param_2;
    puVar1[2] = param_4;
    *(undefined1 *)(puVar1 + 1) = param_3;
    *puVar1 = param_5;
    puVar1[4] = *(undefined8 *)(param_1 + 0x98);
    *(undefined8 **)(param_1 + 0x98) = puVar1;
    return puVar1;
  }
  return (undefined8 *)0x0;
}

