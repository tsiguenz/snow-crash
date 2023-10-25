`su level13 -> g1qKMiRpXf53AWhDaU7FEkczr`

We have an executable file, ran by flag13.

```bash
$ ./level13 
UID 2013 started us but we we expect 4242
$ ltrace ./level13 
__libc_start_main(0x804858c, 1, 0xbffff7d4, 0x80485f0, 0x8048660 <unfinished ...>
getuid()                                                        = 2013
getuid()                                                        = 2013
printf("UID %d started us but we we expe"..., 2013UID 2013 started us but we we expect 4242
)             = 42
exit(1 <unfinished ...>
+++ exited (status 1) +++
```

So the executable wants to be executed by the user with UID 4242, but this user doesn't exist (as seen with `cat /etc/passwd`)

It seems difficult to change our UID, or create another user with this UID, so let's look more into the executable with gdb.

```bash
$ gdb ./level13 
(gdb) disas main
Dump of assembler code for function main:
 0x0804858c <+0>: push   %ebp
 0x0804858d <+1>: mov    %esp,%ebp
 0x0804858f <+3>: and    $0xfffffff0,%esp
 0x08048592 <+6>: sub    $0x10,%esp
 0x08048595 <+9>: call   0x8048380 <getuid@plt>
 0x0804859a <+14>: cmp    $0x1092,%eax
 0x0804859f <+19>: je     0x80485cb <main+63>
 0x080485a1 <+21>: call   0x8048380 <getuid@plt>
 0x080485a6 <+26>: mov    $0x80486c8,%edx
 0x080485ab <+31>: movl   $0x1092,0x8(%esp)
 0x080485b3 <+39>: mov    %eax,0x4(%esp)
 0x080485b7 <+43>: mov    %edx,(%esp)
 0x080485ba <+46>: call   0x8048360 <printf@plt>
 0x080485bf <+51>: movl   $0x1,(%esp)
 0x080485c6 <+58>: call   0x80483a0 <exit@plt>
 0x080485cb <+63>: movl   $0x80486ef,(%esp)
 0x080485d2 <+70>: call   0x8048474 <ft_des>
 0x080485d7 <+75>: mov    $0x8048709,%edx
 0x080485dc <+80>: mov    %eax,0x4(%esp)
 0x080485e0 <+84>: mov    %edx,(%esp)
 0x080485e3 <+87>: call   0x8048360 <printf@plt>
 0x080485e8 <+92>: leave  
 0x080485e9 <+93>: ret    
End of assembler dump.
```

# Solution 1

After some fails trying to modify `$0x1092` to `7dd` (4242->2013) i tried to modify the eax register, so that it contains 4242 when it arrives to the if statement.

```bash
$ gdb ./level13 
(gdb) disas main
Dump of assembler code for function main:
   0x08048595 <+9>: call   0x8048380 <getuid@plt>
   0x0804859a <+14>: cmp    $0x1092,%eax
(gdb) b *0x0804859a
Breakpoint 1 at 0x804859a
(gdb) r
Starting program: /home/user/level13/level13 
Breakpoint 1, 0x0804859a in main ()
(gdb) set $eax=0x1092
(gdb) c
Continuing.
your token is 2A31L79asukciNyi8uppkEuSx
```

# Solution 2

We can see the binary file is dynamically linked to some functions like getuid:

```bash
level13@SnowCrash:~$ file ./level13 
./level13: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xde91cfbf70ca6632d7e4122f8210985dea778605, not stripped
level13@SnowCrash:~$ nm ./level13 | grep getuid
         U getuid@@GLIBC_2.0
```

## Bypass the getuid function from libc to our getuid

Create a getuid function:

```bash
level13@SnowCrash:/tmp$ cat main.c
int getuid(void){
        return 4242;
}
```

Create a shared library:

```bash
gcc main.c -shared -o libtmp.so
```

Add our library to LD_PRELOAD to have the priority:

```bash
level13@SnowCrash:/tmp$ export LD_PRELOAD=/tmp/libtmp.so
```

Copy the binary to drop the setuid bit and execute it:

```bash
level13@SnowCrash:/tmp$ cp /home/user/level13/level13 .
level13@SnowCrash:/tmp$ ./level13
your token is 2A31L79asukciNyi8uppkEuSx
```
