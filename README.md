# simple_shell
<h1>Description</h1>

A simple UNIX command interpreter that replicates functionalities of the simple shell (sh): 

Basics of programming, Basics of C, and Basics of thinking like an engineer implemented.

Additional functions are also included.

This program was entirely written in C as a milestone project for ALX Africa Software Engineering.

<h2>Installation</h2>

Clone this repository into your working directory. Files should be compiled with GCC and the following flags: -Wall -Wextra -Werror -pedantic -std=gnu89

<h3>Usage</h3>

After compilation, the resulting program can run stand-alone, either in interactive or non-interactive mode.

<h4>Interactive Mode</h4>

In interactive mode, simply run the program and wait for the prompt to appear. 

From there, you can type commands freely, exiting with either the "exit" command or ctrl-D.

<h5>Non-Interactive Mode</h5>

In non-interactive mode, echo your desired command and pipe it into the program like this:

```echo "cd" | ./shell```

In non-interactive mode, the program will exit after finishing your desired command(s).

<h6>Included Built-Ins</h6>

Our shell has support for the following built-in commands:

| Command | Definition |
|---|---|
| env | Print the environment. | 
| cd [dir] | Change the directory. |
| unsetenv [var]	| Remove an environment variable. | 
| help [built-in]	| Read documentation for a built-in | 
| exit [n]	| Exit the shell, with an optional exit status, n. | 
| setenv [var][value]	| Set an environment variable and value. If the variable exists, the value will be updated. | 

<details>
<summary>Authors</summary>

* [**@Richard Miruka**](https://github.com/RichardMiruka)
* [**@Ndungu George**](https://github.com/Ndungugeorge)
</details>
