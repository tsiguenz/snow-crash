`su level09 -> 25749xKZ8L7DkSCwJkT9dyv6f`

We have two files, `token` that we can read, and `level09` an executable ran by flag09.

```bash
$ cat -A token
f4kmm6p|=M-^B^?pM-^BnM-^CM-^BDBM-^CDu{^?M-^LM-^I$
$ ./level09 ./token
.0vrojt
$ ./level09 aaaa
abcd
$ ltrace ./level09
__libc_start_main(0x80487ce, 1, 0xbffff7d4, 0x8048aa0, 0x8048b10 <unfinished ...>
ptrace(0, 0, 1, 0, 0xb7e2fe38)                                                        = -1
puts("You should not reverse this"You should not reverse this
)                                                   = 28
+++ exited (status 1) +++
```

We cannot reverse engineed `level09` so we will have to test it manually. At fitst it seems to transform our input by shift progressing the input `aaaa -> abcd`.

We think the solution is to reverse transform what's written in `token`
We did it by hand and programmatically using [main.c](main.c).

To avoid problems with non printable characters copy the file `token` in host with scp and do

```bash
$ vim /tmp/main.c
$ cd /tmp
$ gcc main.c && ./a.out /home/user/level09/token
f3iji1ju5yuevaus41q1afiuq
$ ./level09 f3iji1ju5yuevaus41q1afiuq | cat -A
f4kmm6p|=M-^B^?pM-^BnM-^CM-^BDBM-^CDu{^?M-^LM-^I$
```

Then try to connect with this

```bash
$ su flag09 -> f3iji1ju5yuevaus41q1afiuq
$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```
