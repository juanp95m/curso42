# Exam Practice Validator

This workspace contains exercises and testing scripts (`.sh`) for Exam Rank 03 (or similar 42 school exams). You can use the provided scripts to validate your C solutions against various test cases.

## How to use the `.sh` test scripts

Each exercise's directory contains a bash script (e.g., `powerset.sh`) alongside the `.c` files. The scripts are designed to compile a given `.c` file and run it against several test cases defined in the subject.

### Running a test script
To test a specific `.c` file, navigate to the exercise directory and pass the path to your source file as an argument to the testing script.

For example, to test your `powerset` solution:
```bash
cd level_2/powerset
./powerset.sh powerset_solved.c
```
This will compile `powerset_solved.c` into an executable, execute the predefined tests (such as valid inputs, empty inputs, or wrong argument numbers), and print the respective outputs to the terminal. Finally, it cleans up the executable.

### What it tests
The scripts automatically perform the following checks:
1. **Compilation:** Compiles your code with standard 42 flags (`-Wall -Wextra -Werror`).
2. **Subject Examples:** Runs the basic examples provided in the `subject.txt`.
3. **Edge Cases:** Includes hidden/extra tests specifically designed to break vulnerable algorithms, such as:
   - Calling the program with NO arguments (should not segfault).
   - Calling with empty strings (e.g. `""`).
   - For `powerset`: `0 1 -1` cases or targets that don't exist.
   - For `filter`/`gnl`: specific input pipes, stdin vs file behavior.

## How to add custom tests or use it for new exercises

If you are practicing a new exercise or want to add a new edge case:

1. **Modify the existing script:** Open the respective `.sh` file and look for the commands running `./$NAME`. You can add new combinations by appending `echo` statements and additional `./$NAME <your_args> | cat -e` commands before the final `rm $NAME` cleanup step.
2. **Create a script for a new exercise:**
   You can easily duplicate any of these `.sh` files for a new exercise. A basic template looks like this:
   ```bash
   #!/bin/bash
   NAME=$(basename "$1" .c)
   
   # 1. Compile
   cc -Wall -Wextra -Werror "$1" -o $NAME
   
   # 2. Run your tests
   echo "Testing basic case"
   ./$NAME "arg1" "arg2" | cat -e
   
   # Add your edge-case tests here
   # ./$NAME "" | cat -e
   
   # 3. Clean up
   rm $NAME
   ```
   Remember to always `chmod +x your_script.sh` to make it executable.
