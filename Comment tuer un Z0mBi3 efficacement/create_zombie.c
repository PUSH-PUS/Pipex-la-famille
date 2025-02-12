/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_zombie.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:23:01 by nkiefer           #+#    #+#             */
/*   Updated: 2025/01/05 09:23:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
        printf("Fils : Termine !\n");
    }
    else if (pid > 0)
    {
        printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
        while (1) // Boucle infinie, le père ne termine jamais !
            wait(pid);
    }
    return (0);
}
