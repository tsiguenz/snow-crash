Search the first file owned by the user flag00 with find and print the content of the file:

```bash
cat $(find / -user flag00 -type f 2> /dev/null | sed '1!d')
```

We obtain the string: cdiiddwpgswtgt, which is not the password. As it's a cybersecurity project, we suspect this is a simple encryption.

The website dcode.fr provides a cipher identifier that test multiple encryption methods, and we find that this message is surely encrypted with Caesar Cipher, with a right-shift of 15, which gives us: nottoohardhere