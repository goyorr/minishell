#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	//fd[0] read
	//fd[0] write
	int save_out;
	int file_d;
	//if next node is pipe fork then send res to parent ?
//pipe
//change stdin to fd[0]
//greo
//switch back
	int fd[2];
	pipe(fd);
if(fork())
{

	save_out = dup(fileno(stdin));
	dup2(fd[1], 1);
	char *ppp[] = {"ls", NULL, NULL};
	execve("/bin/ls", ppp, ppp);
}
	wait(0);
	char *ppp[] = {"wc", "-l", NULL};
	close(fd[1]);
	dup2(fd[0], 0);
	execve("/usr/bin/wc", ppp, ppp);
}