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
  0x0804858c <+0>:	push   %ebp
  0x0804858d <+1>:	mov    %esp,%ebp
  0x0804858f <+3>:	and    $0xfffffff0,%esp
  0x08048592 <+6>:	sub    $0x10,%esp
  0x08048595 <+9>:	call   0x8048380 <getuid@plt>
  0x0804859a <+14>:	cmp    $0x1092,%eax
  0x0804859f <+19>:	je     0x80485cb <main+63>
  0x080485a1 <+21>:	call   0x8048380 <getuid@plt>
  0x080485a6 <+26>:	mov    $0x80486c8,%edx
  0x080485ab <+31>:	movl   $0x1092,0x8(%esp)
  0x080485b3 <+39>:	mov    %eax,0x4(%esp)
  0x080485b7 <+43>:	mov    %edx,(%esp)
  0x080485ba <+46>:	call   0x8048360 <printf@plt>
  0x080485bf <+51>:	movl   $0x1,(%esp)
  0x080485c6 <+58>:	call   0x80483a0 <exit@plt>
  0x080485cb <+63>:	movl   $0x80486ef,(%esp)
  0x080485d2 <+70>:	call   0x8048474 <ft_des>
  0x080485d7 <+75>:	mov    $0x8048709,%edx
  0x080485dc <+80>:	mov    %eax,0x4(%esp)
  0x080485e0 <+84>:	mov    %edx,(%esp)
  0x080485e3 <+87>:	call   0x8048360 <printf@plt>
  0x080485e8 <+92>:	leave  
  0x080485e9 <+93>:	ret    
End of assembler dump.

```