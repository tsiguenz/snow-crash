`su level01 -> x24ti5gi3x0ol2eh4esiuxias`

When we list the all users with `cat /etc/passwd`, the password field of flag01 was 42hDRfypTqqnw, different than the x of the others users.

```bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

As in the precedent level, the password was in a file named john, we want to try the famous password cracker John The Ripper, that's easily installed with: sudo apt-get install john -y

Use john to decrypt the password.
[(Docker image of john)](https://hub.docker.com/r/phocean/john_the_ripper_jumbo)

```bash
$ echo flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash > password
$ john --show password
-> flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash
```