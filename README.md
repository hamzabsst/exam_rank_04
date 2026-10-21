# Exam Rank 04 practice

C practice for 42 Exam Rank 04, focused on pipelines, process creation, file descriptors, and expression parsing. These are study implementations, not a claim of an official exam result.

## Exercises

| Directory | Focus |
| --- | --- |
| `1/picoshell/` | Execute commands connected by pipes |
| `1/popen/` | `ft_popen`: launch a process and return a read/write pipe descriptor |
| `2/vbc/` | Parse and evaluate arithmetic with addition, multiplication, and parentheses |

Each exercise has a `subject.txt`. Some folders also contain test or provided code and previously built binaries.

## Work with the sources

Requirements: a C compiler and a POSIX environment for the process exercises. There is no root Makefile.

The `ft_popen` source defines a function rather than an application entry point. Compile it as an object, then link it with your own test driver:

```sh
cc -Wall -Wextra -Werror -c 1/popen/ft_popen.c -o ft_popen.o
```

Read the local subject and source before choosing the entry point for each other exercise; avoid compiling provided code and a replacement implementation together if they define the same symbols.

## Study approach

Start from the required function signatures, draw the pipe/descriptor relationships, and test cleanup and error paths as well as successful execution. For `vbc`, compare normal expressions and invalid input with the subject's examples.

Rebuild sources locally instead of relying on committed `a.out` files. These practice files are not a substitute for the current official subject or independent verification.
