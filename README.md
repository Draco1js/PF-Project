# PF Lab Project-1

This is the main repository for the PF Lab Project, anyone contributing needs to verify your github account with me.

Please look up how to make a pull request, DO NOT commit directly to the repository.

### To run this project:

- Make sure you have some form of gcc installed for whatever platform you are using
- run `make` in your console
- That's it!

### Explanation for debugging purposes:


The `Makefile` file is a script that automatically takes all the source files from the `src` directory, and the headers from the `include` directory, and dumps all the object files into the `build` directory, it then creates an executable called `hotel` and automatically runs it for you.


Whenever you're working on this project, and need a method to be available in another file to use, make sure you are mentioning it in the respective header file of the exact name, in a similar format to the already-present methods.