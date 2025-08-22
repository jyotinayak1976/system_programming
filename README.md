syscalldemo.c does this.
1) Gets your PID using syscall #39.

2) Opens /etc/hostname (a tiny file that always exists in Linux/WSL).

3) Reads its content.

4) Writes it to stdout.

5) Closes the file.
