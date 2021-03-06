/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 20:55:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static const char	*g_args[] = {
	"up",
	"down",
	"increase",
	"decrease",
	"min",
	"max",
	NULL
};

static const char	*g_system_args[] = {
#ifdef __linux__

	"xbacklight + 10",
	"xbacklight - 10",
	"xbacklight + 10",
	"xbacklight - 10",
	"xbacklight = 100",
	"xbacklight = 10",
#else

	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 2 times' -e 'key code 144' -e 'end repeat' -e 'end tell'",
	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 2 times' -e 'key code 145' -e 'end repeat' -e 'end tell'",
	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 2 times' -e 'key code 144' -e 'end repeat' -e 'end tell'",
	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 2 times' -e 'key code 145' -e 'end repeat' -e 'end tell'",
	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 16 times' -e 'key code 145' -e 'end repeat' -e 'end tell'",
	"osascript -e 'tell application \"System Events\"' \
	-e 'repeat 16 times' -e 'key code 144' -e 'end repeat' -e 'end tell'",
#endif

	NULL
};

char				*backlight_callback(void *arg)
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
		return (strdup("I don't understand this backlight operation"));
	if (system(modifier))
		return (strdup("Fail backlight operation"));
	return (strdup("Success backlight operation"));
}
