#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//TO IMPLMENT
//ctrl-c => display new prompt line
// ctrl-D => exit the shelle
// Ctrl-\ => sends a SIGQUIT

//FUNCTIONS TO USE
//sigaction(): These functions are used to set up signal handlers for catching and handling signals such as SIGINT (Ctrl-C) and SIGQUIT (Ctrl-).
//sigemptyset(): initialize signal_set, which indicate that none signal is stocked ¡
//sigaddset : add a signal

//Step 1
//include headers
#include <signal.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

// Variable globale partagée entre le programme
// principal et la routine SIGINT. La routine mettra
// cette variable à 1 lorsqu'on fait ctrl-c.
// Déclarée volatile pour éviter quelle se retrouve
// dans la mémoire cache à cause du compilateur
volatile int	g_unblock_sigquit = 0;

// Fonction pour bloquer le signal spécifié
void	block_signal(int signal)
{
//	L'ensemble des signaux à bloquer
	sigset_t	sigset;

//	Initialise l'ensemble à 0
	sigemptyset(&sigset);
//	Ajoute le signal à l'ensemble
	sigaddset(&sigset, signal);
//	Ajoute les signaux de l'ensemble aux
//	signaux bloqués pour ce processus
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

// Fonction pour débloquer le signal spécifié
void	unblock_signal(int signal)
{
//	L'ensemble des signaus à débloquer
	sigset_t	sigset;

//	Initialise l'ensemble à 0
	sigemptyset(&sigset);
//	Ajoute le signal à l'ensemble
	sigaddset(&sigset, signal);
//	Retire les signaux de l'ensemble des
//	signaux bloqués pour ce processus
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

// Routine de gestion du signal SIGINT
void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
//	Bloque les autres signaux SIGINT pour
//	protéger la variable globale le temps
//	de la modifier
	block_signal(SIGINT);
	g_unblock_sigquit = 1;
	unblock_signal(SIGINT);
}

void set_signal_action(void)
{
//	Déclaration de la structure sigaction
	struct sigaction	act;

//	Initialiser la structure à 0.
	bzero(&act, sizeof(act));
//	Nouvelle routine de gestion de signal
	act.sa_handler = &sigint_handler;
//	Applique la nouvelle routine à SIGINT (ctrl-c)
	sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
//	Change l'action par défaut de SIGINT (ctrl-c)
	set_signal_action();
//	Bloque le signal SIGQUIT (ctrl-\)
	block_signal(SIGQUIT);
//	Boucle infinie pour avoir le temps de faire ctrl-\ et
//	ctrl-c autant de fois que ça nous chante.
	while(1)
	{
//		Bloque le signal SIGINT le temps de lire la variable
//		globale.
		block_signal(SIGINT);
//		Si la routine de gestion de SIGINT a indiqué qu'elle a
//		été invoquée dans la variable globale
		if (g_unblock_sigquit == 1)
		{
//			SIGINT (ctrl-c) a été reçu.
			printf("\n\e[36mSIGINT detected. Unblocking SIGQUIT\e[0m\n");
//			Débloque SIGINT et SIGQUIT
			unblock_signal(SIGINT);
			unblock_signal(SIGQUIT);
		}
//		Sinon, on débloque SIGINT et on continue la boucle
		else
			unblock_signal(SIGINT);
		sleep(1);
	}
	return (0);
}
