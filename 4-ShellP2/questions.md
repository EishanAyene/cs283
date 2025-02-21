1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  We use fork to create a new child process before calling execvp because it replaces the process’s memory with a new program. If we call it directly, it would replace the process itself, making it impossible to continue managing child processes or handling multiple commands.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If the system call fails, it returns -1. Mine checks the return value of fork and returns an error message.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  It finds it by searching for the command in the directories specified by the PATH environment variable. It tries each directory in PATH  until it finds a file matching the given name.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  It ensures that it waits for the child process to complete before continuing execution. This prevents the creation of zombie processes, which happens when a child exits but the parent does not retrieve its exit status.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  It provides the exit status of the child process from the code returned by calling wait(). This information is important because it helps the shell determine the success of a child process.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  It handles quoted arguments by tracking whether the parser is inside a quoted section. This is necessary to ensure that spaces within quotes are treated as part of a single argument rather than separators between arguments.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  I added checking for quoted arguments and did not face any unexpected challenges

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  They are a basic form of communication used to notify a process about events. Signals differ from other forms of IPC because they are mainly used for simple notifcations and they can't transfer large amounts of data.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGSKILL immedietly terminates a process and can not be blocked. It is used when you need to forcefully terminate an unresponsive process.SIGTERM requests a process to terminate so it can be blocked. It is used to gracefully stop a process. SIGINT interupts a process. It is used when running a long script and you want to stop it.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  The process is paused. It can't be ignored like SIGINT because it's implemented to be an unconditional stop signal.
