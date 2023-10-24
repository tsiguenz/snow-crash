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

This script use preg_replace with the 'e' option who is a vulnerability.

We found on the internet that the /e modifier in the regular expression will cause PHP to eval our input and execute the second argument.

[x system('getflag');] does not work -_-
