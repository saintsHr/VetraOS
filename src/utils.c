void wait(unsigned int ticks){
    for (unsigned int i = 0; i < ticks * 100000; i++){
        __asm__ volatile("nop")
    }
}