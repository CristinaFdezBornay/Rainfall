# LEVEL 0

## 💡 Explanation

In this level we have to:
1. When launching the program `./level0` it segfaults; so there's not much we can do there.
2. We have a look to what the program does by opening it on GDB. We can see that there is an `atoi`, then a comparison and a jump if not.
3. By running it on the debugger we see that it properly calls `atoi`, which runs and then calls to `strtol` which segfaults at the instruction `movzx  eax,BYTE PTR [edx]` which segfaults because it is trying to fetch a byte from the address `edx`, but this is set to 0 => we can think that it is trying to make an `atoi` from an empty string; since it does not ask for an input we are going to try to pass it as an argument.
4. We launch again GDB but sending some argument to the program. Since we know that it is calling `atoi`, let's pass its a number.
5. By doing so and following the execution, we can already see that we have the number passed as an argument on the top of the stack right before calling to `atoi`. This time it manages to not segfault on the `atoi` and reach the comparison.
6. Now the blocking instruction is `cmp    eax,0x1a7` followed by `jne    0x8048f58 <main+152>` meaning that if `eax` (which is actually the output from `atoi`) is not equal to 0x1a7 (423 in decimal) the program will jump to `main+152`, which is actually the end of the main and there's not much going on there.
7. Now, we try by passing `423` as an argument to the program; this time, it evaluates to true in the compare so it does not jump. If we go on a couple of steps more we can see that there's a call to `execv` and on the top of the stack we have `/bin/sh`. Voilà!! It opens a terminal when reaching this point!!
8. Last but not least, we have to execute it outside of GDB to be able to use the SUID and execute SH as the user level1. Once we do this, we'll have to cat the password.

## 👾 Commands

To find the solution:
```
cd /tmp
gdb /home/user/level0/level0
gdb --args /home/user/level0/level0 123
gdb --args /home/user/level0/level0 423
```

To find the flag:
- `./level0 423`
- `cd /home/user/level1/level1`
- `cat .pass`

## 🔍 Resources

- [Introduction à gdb](https://beta.hackndo.com/introduction-a-gdb/#dans-gdb)
- [Assembleur - Notions de base](https://beta.hackndo.com/assembly-basics/)
- [Fonctionnement de la pile](https://beta.hackndo.com/stack-introduction/)
- [Have done the Corewar project also helped A LOT!](https://github.com/CristinaFdezBornay/Corewar)
