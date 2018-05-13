#ifndef PC_ARCH_COMPILER__
#define PC_ARCH_COMPILER__

/* Override __syscall__ and __syscall_handler__ so they don't mark the
 * implementations as "noreturn". Noreturn is a wished behavior on real
 * hardware, but for the PC simulation, absolutely NOT! */
#define __syscall__ static inline
#define __syscall_handler__ KAPI

#endif /* ! PC_ARCH_COMPILER__ */
