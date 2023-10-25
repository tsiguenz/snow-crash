`su level00 -> level00`

Search the first file owned by the user flag00 with find and print the content of the file:

```bash
$ find / -user flag00 -type f 2> /dev/null
/usr/sbin/john
/rofs/usr/sbin/john
$ cat /usr/sbin/john
cdiiddwpgswtgt
```

We obtain the string: `cdiiddwpgswtgt`, which is not the password. As it's a cybersecurity project, we suspect this is a simple encryption.

The website `dcode.fr` provides a cipher identifier that test multiple encryption methods, and we find that this message is surely encrypted with Caesar Cipher, with a right-shift of 15, which gives us: `nottoohardhere`

```bash
$ su flag00 -> nottoohardhere
$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```