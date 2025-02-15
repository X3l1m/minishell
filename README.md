# Minishell

Minishell is a simple Unix shell implementation written in C. It simulates the functionality of a basic shell by parsing user input, executing commands, and handling redirections and pipes. This project is designed to understand the inner workings of a shell and the interaction between system processes.

## Features

- **Command Execution**: Execute system commands.
- **Pipes and Redirections**: Handle pipes (`|`), input (`<`), and output (`>`) redirections.
- **Environment Variables**: Support for setting and using environment variables.
- **Custom Built-in Commands**: Implement basic built-in commands like `cd`, `exit`, and `echo`.
- **Signal Handling**: Properly handle signals such as `Ctrl+C` and `Ctrl+D`.

## Requirements

- **C Compiler**: GCC or Clang
- **Make**: For building the project
- **Linux Environment**: Designed to work in Unix-like systems

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
```

### 2. Build the Project

Run the following command to build the shell:

```bash
make
```

### 3. Run the Shell

Once the build is complete, you can start your custom shell:

```bash
./minishell
```

You can now use your custom shell just like a regular terminal!

## Usage

Here are some basic commands you can use with the shell:

- **Running Commands**: Type any command (e.g., `ls`, `pwd`) and press Enter.
- **Change Directory**: Use `cd` to navigate between directories.
- **Exit**: Type `exit` to close the shell.
- **Pipes**: Use `|` to pipe commands together, like `echo "Hello" | grep "Hello"`.
- **Redirection**: Use `>` to redirect output, e.g., `echo "Hello" > file.txt`.
