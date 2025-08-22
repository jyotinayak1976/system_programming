#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>   // For syscall numbers
#include <fcntl.h>         // For O_RDONLY flags

// Get process ID via syscall
pid_t get_pid_direct() {
    long ret;
    __asm__ volatile (
        "syscall"
        : "=a" (ret)
        : "a" (39)               // SYS_getpid = 39 on x86-64
        : "rcx", "r11", "memory"
    );
    return (pid_t)ret;
}

// Generic syscall wrapper (simpler for file ops)
long my_syscall(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile (
        "syscall"
        : "=a" (ret)
        : "a" (n), "D" (a1), "S" (a2), "d" (a3)
        : "rcx", "r11", "memory"
    );
    return ret;
}

int main() {
    // 1. Get PID
    pid_t pid = get_pid_direct();
    printf("PID (via raw syscall): %d\n", pid);

    // 2. Open file (this file must exist, e.g., /etc/hostname)
    const char *filename = "/etc/hostname";
    int fd = my_syscall(2, (long)filename, O_RDONLY, 0);  // SYS_open = 2
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // 3. Read from file
    char buf[128];
    long nread = my_syscall(0, fd, (long)buf, sizeof(buf)-1); // SYS_read = 0
    if (nread < 0) {
        perror("read failed");
        return 1;
    }
    buf[nread] = '\0';

    // 4. Write to stdout
    my_syscall(1, 1, (long)buf, nread); // SYS_write = 1

    // 5. Close file
    my_syscall(3, fd, 0, 0); // SYS_close = 3

    return 0;
}
