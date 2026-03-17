
# Advantages of using ENUM for BUILTINS in Tokenizer structure (lexer.c, parser.c)

Here is why using an integer (enum) check is conceptually better than string comparison (ft_strcmp) for your shell's architecture:

1. You are recycling work you already did
Your Lexer has already spent time analyzing the text to figure out that "echo" is a BUILTIN and specifically ECHO. If you only pass the string "echo" to the executor, you are throwing away that specific knowledge. The executor then has to start from zero and re-read the letters to figure out what the Lexer already knew. It is inefficient to calculate the same thing twice.

2. Integer comparison is instantaneous (CPU cycles)

ft_strcmp: The computer has to fetch the string from memory, loop through it character by character ('e', 'c', 'h', 'o'), and stop at the null terminator. If you have 7 builtins, you might have to run this loop 7 times for one command to find a match.
Enum check: The computer compares two numbers (e.g., is 9 == 9?). This happens in a single CPU instruction. It is arguably the fastest operation a processor can do.
3. Cleaner Executor Logic
If you use strings, your executor usually becomes a messy chain of if... else if... else if.
If you use the enum, your executor logic acts like a switchboard: "If type is ECHO, call do_echo. If type is CD, call do_cd." It abstracts the text away and focuses purely on the action.

4. Safety
String comparisons involve pointers. If for some reason a bug elsewhere makes your string pointer NULL or points to garbage memory, ft_strcmp will crash your shell (Segmentation Fault). An integer in a struct is just a value; checking it will never cause a crash, making your control flow more robust.