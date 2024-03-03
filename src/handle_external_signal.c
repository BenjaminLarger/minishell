//TO IMPLMENT
//ctrl-c => display new prompt line
// ctrl-D => exit the shelle
// Ctrl-\ => sends a SIGQUIT

/* FUNCTIONS TO USE
sigaction(): These functions are used to set up signal handlers for catching and
handling signals such as SIGINT (Ctrl-C) and SIGQUIT (Ctrl-).
int sigemptyset(sigset_t *set); => initialize signal_set, which indicate
that none signal is stocked
int sigaddset(sigset_t *set, int signum); => add signum signal to *set 
void rl_replace_line (const char *string, int clear_undo) => send a new prompt to
the command line (*string), can clear history (bool) */

#include <signal.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

/* The variable value may change unexpectedly. It prevents the compiler to put
the variable inside the hidden memory. The variable may be modified by signals
handler, which are external to the normal flow of the program execution.
It is initialized to 0, which means that the flag is not set.
(Indicating that SIGQUIT should remain blocked.)
 SIGQUIT = End of a processus (ctrl-\)
 The global variable is a flage to indicate that the program should unblock
 the SIGQUIT signal.
 0 => blocked // 1 => unblocked */

volatile int	g_unblock_sigquit = 0;

/* The logic behind blocking and unblocking signals is symmetric.
When you block a signal, it prevents the associated signal handler from
being invoked when that signal is raised.
Conversely, when you unblock a signal, it allows the signal handler
to be invoked again when the signal is raised.
Therefore, the actions required to block and unblock a signal are
essentially the inverse of each other. */

// Function to block SIGQUIT (ctrl-\)
void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	if (signal == SIGQUIT) // kill(pid1, SIGUSR1);
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n"); //replace to send a new prompt
}

// Function to unblock SIGQUIT (ctrl-\)
void	unblock_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
	g_unblock_sigquit = 1;
	unblock_signal(SIGINT);
}
/* The sigaction struct is used to specify the action to be taken when a
signal is received.
 bzero ensures that any fields not explicity set will have a default value of
 zero.
 act.sa_handler = &sigint_handler;: Specifies the signal handler function
 to be called when the SIGINT signal (Ctrl-C) is received.
 sigaction(SIGINT, &act, NULL);: Associates the specified action (act) with
 the SIGINT signal. */

void set_signal_action(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act)); //ft_
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

int	signal_handling(pid_t	pid1)
{
	set_signal_action();
	block_signal(SIGQUIT);
//	Boucle infinie pour avoir le temps de faire ctrl-\ et
//	ctrl-c autant de fois que ça nous chante.
	while(pid1)
	{
//		Bloque le signal SIGINT le temps de lire la variable
//		globale.
		block_signal(SIGINT);
//		Si la routine de gestion de SIGINT a indiqué qu'elle a
//		été invoquée dans la variable globale
		if (g_unblock_sigquit == 1)
		{
//			SIGINT (ctrl-c) a été reçu.
			//printf("\n\e[36mSIGINT detected. Unblocking SIGQUIT\e[0m\n");
			//process control c
			printf("control c caught\n");
			//kill(pid1, SIGINT);
			g_unblock_sigquit = 0;
//			Débloque SIGINT et SIGQUIT
			unblock_signal(SIGINT);
			//unblock_signal(SIGQUIT);
		}
//		Sinon, on débloque SIGINT et on continue la boucle
		else
			unblock_signal(SIGINT);
		sleep(1);
	}
	return (0);
}
