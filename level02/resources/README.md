`su level02 -> f2av5il02puano7naaf6adaaf`

We have a file named level02.pcap, which is a file format that contains the packet data generated when listening on a network.

This is a packet capture where we can find a tcp connection between a client and a server.

Open this file with wireshark and put together the packets to reconstruct the message and find the password.

Analyze -> Follow -> TCP Stream -> Password: ft_wandr...NDRel.L0L

su flag02 -> ft_wandr...NDRel.L0L doesn't work, so let's look back at the TCP Stream as Hex Dump
We know that non-printable characters are replaced by dots, so the 3 dots are, in fact, the 7f code, the delete character meaning either Backspace or Delete was pressed.
So we transform the password as if . represents a press of Backspace: ft_wandr...NDRel.L0L -> ft_waNDReL0L

su flag02 -> ft_waNDReL0L
getflag -> kooda2puivaav1idi4f57q8iq