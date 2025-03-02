1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

The shell uses waitpid() in a loop to wait for all child processes created for piped commands. After forking and executing commands in execute_pipeline(), the parent process iterates over the array and calls for each child. If waitpid() is forgotten, child processes would become zombie processes, and the shell would return to the prompt before they finish execution, potentially leading to resource leaks and unpredictable behavior.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

It redirects standard input/output to the  pipe ends but does not automatically close the original file descriptors. If unused pipe ends are left open, it can cause deadlocks because processes may wait for an EOF that never arrives. Closing the unused pipe ends makes sure to avoid file descriptor leaks.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

If it was implemented as an external command, it would execute in a child process, and any chdir() call in that child process would not affect the parent shell. Cd must be built-in so it executes within the shell process itself.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would dynamically allocate the pipe array based on the number of commands. I would also use malloc() and free() to allocate and release memory for the pipes, ensuring efficient memory management. The trade offs to consider would be the complexity with error handling, scalability, and performance to be affected since we have a lot of memory allocation calls. 
