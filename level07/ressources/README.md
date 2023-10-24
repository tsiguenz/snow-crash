`su level07 -> wiok45aaoguiboiki2tuin6ub`

```bash
$ ltrace ./level07
__libc_start_main(0x8048514, 1, 0xbffff774, 0x80485b0, 0x8048620 <unfinished ...>
getegid()                                                                             = 2007
geteuid()                                                                             = 2007
setresgid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                   = 0
setresuid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                   = 0
getenv("LOGNAME")                                                                     = "level07"
asprintf(0xbffff6c4, 0x8048688, 0xbfffff46, 0xb7e5ee55, 0xb7fed280)                   = 18
system("/bin/echo level07 "level07
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                = 0
+++ exited (status 0) +++

```

