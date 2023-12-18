#include "systemcalls.h"


/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    int status;
    status = system(cmd);
    if(status == -1)
        return false;
    if (WIFSIGNALED (status))
        return false;
    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    
    char *command[count + 1];
    int i;
    for(i = 0; i < count; i++) {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    
    va_end(args);

    pid_t pid = fork();

    if (pid == -1)
        return false;

    if (pid == 0)
    {
        execv(command[0], command);
        exit(-1);
    }
    else {
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return true;
        else
            return false;
    }
    return false;
}

bool do_exec_redirect(const char *outputfile, int count, ...) {

  va_list args;
  va_start(args, count);

  char *command[count+1];

  for(int i=0; i<count; i++) {
    command[i] = va_arg(args, char *); 
  }

  command[count] = NULL;

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return false;
  }

  if (pid == 0) {

    // Child process

    int out_fd = open(outputfile, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (out_fd < 0) {
      perror("open");
      _exit(EXIT_FAILURE);
    }

    if (dup2(out_fd, STDOUT_FILENO) < 0) {
      perror("dup2 stdout");
      _exit(EXIT_FAILURE);
    }

    if (dup2(out_fd, STDERR_FILENO) < 0) {  
      perror("dup2 stderr");
      _exit(EXIT_FAILURE);
    }

    if (out_fd > STDERR_FILENO) {
      close(out_fd);
    }

    execv(command[0], command);
    perror("execv");
    _exit(EXIT_FAILURE);

  } else {

    // Parent process

    int status;
    if (waitpid(pid, &status, 0) < 0) {
      perror("waitpid");
      return false;
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      return false;
    }

    return true;
  }
}