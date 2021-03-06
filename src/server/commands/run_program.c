/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 20:56:20 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "server/config.h"

static const char	*g_args[] = {
	"editor",
	"browser",
	"terminal",
	"file manager",
	"clean",
	NULL
};

static const char	*g_system_args[] = {
#ifdef __linux__

	PROGRAM_EDITOR,
	PROGRAM_BROWSER,
	PROGRAM_TERMINAL,
	PROGRAM_FILEMANAGER
	"echo only for UNIT Factory computers",
#else

	"open -a \"" PROGRAM_EDITOR "\"",
	"open -a \"" PROGRAM_BROWSER"\"",
	"open -a \"" PROGRAM_TERMINAL"\"",
	"open -a \"" PROGRAM_FILEMANAGER"\"",
	"rm -f ~/Library/*42_cache*",
#endif

	NULL
};

char				*run_program(void *arg)
{
	char		*str;
	const char	*modifier;
	int			i;

	str = (char*)arg;
	modifier = NULL;
	i = -1;
	while (g_args[++i])
	{
		if (strstr(str, g_args[i]))
		{
			modifier = g_system_args[i];
			break ;
		}
	}
	if (!modifier)
		return (strdup("I don't understand this run program operation"));
	if (system(modifier))
		return (strdup("Fail run program operation"));
	return (strdup("Success run program operation"));
}
