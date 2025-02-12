#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

main()
{
        int pid;
        int i = 1;
        int nbre  = 5;   //** Nombre de zombies à créer 
        int vcrea = 2;   //** Vitesse de création des zombies, en seconde
        int vdest = 5;   //** Vitesse de destruction des zombies, en seconde
        int tpsZ  = 20;  //** Temps d'attente pour observer les zombies, en seconde
        int tpsP  = 5;   //** Temps d'attente pour observer le père, en seconde

        printf ("------------------------------------------------------------------------\n");
        printf ("--                     Lancement de l'invasion                        --\n");
        printf ("------------------------------------------------------------------------\n");

        for (i; i <= nbre; i++)
        {
                pid = fork();

                if (pid == 0) // processus fils
                {
                        printf("* Zombie %d dit : Ceeeervau.....\n", i);
                        exit(1);
                }
                else // processus pere
                {
                        sleep(vcrea);
                }
        }

        printf ("------------------------------------------------------------------------\n"     );
        printf ("  Vous avez %d processus zombies qui se baladent sur votre système.     \n", i-1);
        printf ("  Ils vont errer pendant %d sec, vous pouvez les observer avec ps -aux. \n",tpsZ);
        printf ("------------------------------------------------------------------------\n"     );

        // Temps d'attente, en seconde, pour observer les zombies
        sleep(tpsZ);

        // Le père fait ensuite appel à wait() et récupère ces fils terminés
        for (i; i > 1; i--)
        {
                sleep(vdest);
                wait(0);
                printf("* Le zombie %d a disparu \n", i-1);
        }

        printf ("------------------------------------------------------------------------\n");
        printf ("  L'invasion zombie est terminé.\n"                                        );
        printf ("  Le processus père est encore observable %d secondes.\n", tpsP            );
        printf ("------------------------------------------------------------------------\n");

        // Le père reste encore x secondes pour l'observer
        sleep(tpsP);


        // Fin du script, le père se termine

}
