enter_regin:
    jne LOCK, #0, enter_regin
    tsl R, LOCK
    jne R, #0, enter_regin