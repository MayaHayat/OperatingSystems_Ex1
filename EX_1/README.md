# Linux, Libraries, and Debugger
Authors:
Ilan
Maya Hayat

This exercise is divided into four main parts:

## Part A: Working with Debugger
In this part, we engaged with a debugger to identify and rectify two distinct bugs. The first bug involved attempting to access a location that wasn't pre-set, and the second was an infinite loop. We executed the code with and without the debugger, waited for a core dump, and utilized 'gdb' to precisely locate the errors.

## Part B: Utilizing a Built-in Library
The second segment required the creation of a program that takes three numbers representing the lengths of a triangle. The program scanned these lengths, determined whether it was a Pythagorean triangle, calculated the three angles, and displayed them. In case of an error, an appropriate message was printed.

## Part C: Creating a Dynamic Library
This section involved creating a dynamic library. Initially, we implemented four distinct functions found in the "libcodec.c" class. These functions encoded and decoded text, as well as managed memory. Subsequently, two additional classes were created to read from either Input.txt or Output.txt, encoding/decoding text based on user requirements. A makefile was developed to facilitate the creation of our dynamic library. It's important to note that users need to run "export LD_LIBRARY_PATH=.".

## Part D: Using Pipes to Compress into Zip
In the last part, we had to create a program that compresses a folder into a zip file. We had to implement this by using 2 pipes as was shown in class. After having created our Compressed.gpg file we had to create another program called myunzip which reverses the process.
When running the program, we must make all and then ./myzip folderName code(1234 for example)
