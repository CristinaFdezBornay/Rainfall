# LEVEL 8

## 💡 Explanation

In this level we have to:
1. In this level we have to have a PhD in assembly and gdb, then it's fine.
2. Checking the assembler we soon see that there is a call to `fgets` and then there are some weird long instructions. Using GDB we check that those intructions are comparing what we input to `fgets` with the strings "auth ", "reset", "service", and "login".
3. Then, we have to test every input to see what they do. Check the source to understand it. The interesting point if that when we "login" there is an if condition that if we get inside, it does `system("/bin/bash")`. Well, there is where we have to get.
4. Testing the "auth ", we realize that it actually expects more input, like "auth XXXXX", and it is going to malloc and strcpy the "XXXXX" and save the pointer. The first time we call it gives 0x804a008.
5. The next interesting point is that every time we input "service" it calls `strdup`(we don't really care about the args), the point is that it returns a new pointer with an offset of 10 bytes from the last pointer that we allocated using malloc.
6. Now, back to what we have to do to get inside of the if condition... THE KEY OF EVERYTHING IS HERE: `0x80486e7 <main+387>: mov eax, DWORD PTR [eax+0x20]`, followed by `test   eax,eax`!!!!!!!!!!!!! So it checks that the address 20 bytes after eax (which at that moment points to the ouput of the call to "auth") is not empty!! Voilà
7. Conclusion, if we call to "auth XXXX" it'll call `malloc` (1st time) and get the address 0x804a008. Then, we do "service", so `strdup` calls `malloc` (2nd time) which returns a pointer to 0x804a018, and next another time to "service" so we get the 3rd call to `malloc`, pointing to 0x804a028. Therefore, when we get to the instruction we explained before, it test that the "auth" pointer 0x804a008 + 20 = 0x804a028, is not empty, which is not because we just `strdup` on it! So, it opens the shell!

## 👾 Commands

To execute the solution:
```
level8@RainFall:/tmp$ /home/user/level8/level8
(nil), (nil) 
auth nopuedomaaaasss
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

## 🔍 Resources

- [A quoi sert l'instruction test eax,eax ?](https://www.developpez.net/forums/d25009/autres-langages/assembleur/x86-32-bits-64-bits/quoi-sert-l-instruction-test-eax-eax/)
- [x86 Instruction Set Reference - REP/REPE/REPZ/REPNE/REPNZ](https://c9x.me/x86/html/file_module_x86_id_279.html)
- [What do the assembly instructions 'seta' and 'setb' do after repz cmpsb?](https://stackoverflow.com/questions/44630262/what-do-the-assembly-instructions-seta-and-setb-do-after-repz-cmpsb)

