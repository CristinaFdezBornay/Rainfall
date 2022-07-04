# LEVEL 7

## 💡 Explanation

In this level we have to:
1. Have a look at the binary: in the function main there're several calls to `malloc` and then a couple of `strcpy`, which we already know we can exploit; the interesting part comes with a call to `fopen` and to `fgets` on the file `/home/user/level8/.pass`. The problem is that the content is saved on the variable `c` that is never printed... Also, at the end of the main there's a `puts` which prints "~~".
2. As in the previous exercises, there is a function `m` that is never called in the main but which retrieves the variable `c` and prints it. There we go!!
3. Now, let's build an exploit to call to `m` before leaving the main. To do so, we are going to modify the address of the funtion `puts` in the GOT table to make it point to `m`.
4. When we launch the binary it segfaults, to fix this we have to pass two arguments to it. By running the program in the debugger we see that the first argument is used for the first `stecpy` and the second is for the second call.
5. What we are going to do is to overflow the buffer using the first call to `strcpy` to strategically place the address of the pointer to `puts`, so when the second `strcpy` is called it will put on that address the content that we send to it, which in this case will be the address of `m`.
6. To build the exploit we have to check the address where the first `strcpy` copies the first argument (0x804a018) and where the second goes (0x804a038). It gives an offset of 20 bytes, then we check the address of the pointer to `puts` (0x08049928 => \x28\x99\x04\x08) and the address of `m` (0x080484f4 => \xf4\x84\x04\x08). Therefore, the two arguments should look like: (1)[RANDOM 20 BYTES][ADDRESS OF THE PUTS POINTER], and (2)[ADDRESS OF M].

## 👾 Commands

To find the solution:
```
[VM]  objdump -s -j .got.plt /home/user/level7/level7
[VM]  objdump -R /home/user/level7/level7
```

To execute the solution:
- `./level7 $(python -c 'print "a"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')`
