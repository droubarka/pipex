# Pipex

**Pipex** reproduces the behavior of shell piping (`|`), executing a chain of commands with input/output redirection using `pipe()`, `fork()`, `execve()`, and `dup2()`.

## Usage

### Cloning the Repository
To get started with the project, clone the repository to your local machine:
```shell
git clone https://github.com/droubarka/pipex.git
```

### Running the Program
```shell
cd ./pipex
make bonus
```

#### Basic Usage
```shell
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```

Equivalent to the shell command:
```shell
< infile cmd1 | cmd2 | ... | cmdN > outfile
```

Example:
```shell
./pipex /etc/passwd "grep -P [\w/]*/nologin$" "cut -d: -f1" nologin.txt
```
- Extracts users with `/nologin` shells and writes their usernames to `nologin.txt`.

#### Here Document Mode (Interactive Input)
```shell
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
- Reads from standard input until `LIMITER` is encountered, then pipes through the commands.
