# HW 4 - Whack-a-mole and Race Conditions

* Author: Leo Haener-Pope
* Class: CS452 Section #002
* Semester: Fall 2026

## Overview

This is a simple whack-a-mole style program that utilizes multithreading, mutexes, and the previous deq we have made.

## Reflection

This was a nice assignment for getting more used to multi-threaded programming in c. I think I have a decent understanding of multi-threaded programming, though I am definitely not confident at doing it, especially in c. It gave me a deeper understanding with using mutexes, and the c library functions for the multithreading and mutex functionality.

It was a pretty straightforward assignment, which was nice because I think the subject it covers can definitely get super complicated easy. I ran into problems using the fltk library for getting the window pop up. It was working okay when I first started the assingment, after I changed a line in the small makefile (see Compiling and Using), however, it started to not work, which was weird because the DISPLAY commands + valgrind worked fine for me in the terminal. It may be something with the code I wrote, but it also might just be something weird with the Ubuntu WSL I am using on my computer. I still had fun with this assignment though.

## Compiling and Using

Make the program first using `make`

To run the program (with fltk properly set up) you can just use `make run`

If ftlk is not properly set up or not working (which is was I had to deal with a lot) run `DISPLAY= make run`

Note that I also changed in the small makefile `ldflags=-pthread $(shell fltk-config --ldflags) # old: ldflags=-pthread -lX11 -lfltk`, this was able to get the window to actually pop up for me.

## Testing

Run valgrind to test the program and check for leaks

`make`

`DISPLAY = ./vg ./wam'

Or with fltk properly installed (which I had trouble doing) you should be able to run `make valgrind`

## Results

I had a lot of trouble using the fltk resource with this project. I had it running pretty well in the beginning of the project. I do not know what happened, or if there is something weird with the code that I created, but now when I try to run the new window it just creates a blank window.

Though, when just using the DISPLAY commands, the program is able to run, also running and passing valgrind tests.

## References

Gemini was helpful for trying to get the fltk working, and also explaining c library functions/syntax