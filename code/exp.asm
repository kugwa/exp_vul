global  save_user_mode_rflags
global  return_to_user_mode

save_user_mode_rflags:
    pushf
    pop     rax
    ret

return_to_user_mode:
    mov     rcx, rdi
    mov     r11, rsi
    mov     rsp, rdx
    swapgs
    o64 sysret
