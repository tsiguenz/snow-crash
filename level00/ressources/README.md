Search the first file owned by the user flag00 with find and print the content of the file:

```bash
cat $(find / -user flag00 -type f 2> /dev/null | sed '1!d')
```

Then we need to decode the output, I use [dCode](https://www.dcode.fr/en) with rot15 alogorithm.
