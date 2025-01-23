# Minishell

A simple shell implementation that mimics basic bash functionality.

## Features

### Signal Handling
- `Ctrl+C` (SIGINT) - Creates a new line
- `Ctrl+D` (EOF) - Exits the shell
- `Ctrl+\` (SIGQUIT) - Does not terminate the shell

### Command Line Features
- Command history
- Environment variable expansion
- Quote handling (`"` and `'`)
- Metacharacter support

### Command Execution
- Executes commands with arguments
- Handles built-in commands:
  - `echo` (with -n option)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### Redirection and Pipes
- Input redirection (`<`)
- Output redirection (`>`)
- Append output (`>>`)
- Heredoc (`<<`)
- Pipe operator (`|`)

### Compilation

To compile the program, use the following command:

```bash
make
```

### Running the Program

To run the program, use the following command:

```bash
./minishell
```