/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/21 17:52:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# include <AL/al.h>
# include <AL/alc.h>
# include <sndfile.h>

# define VOLUME		0.2f
# define PITCH		1.0f
# define SA_BUFFER	42

enum	e_sample_id
{
	SA_TITLE_SCREEN_S,
	SA_TITLE_SCREEN_L,
	SA_GAME1,
	SA_GAME2,
	SA_GAME3,
	SA_GAME4,
	SA_GAMEOVER,
	SA_MAPED,
	SA_AK47_RELOAD,
	SA_AK47_FIRE,
	SA_AUG_RELOAD,
	SA_AUG_FIRE,
	SA_FAMAS_RELOAD,
	SA_FAMAS_FIRE,
	SA_GALIL_RELOAD,
	SA_GALIL_FIRE,
	SA_GLOCK_RELOAD,
	SA_GLOCK_FIRE,
	SA_MAG7_RELOAD,
	SA_MAG7_FIRE,
	SA_NEGEV_RELOAD,
	SA_NEGEV_FIRE,
	SA_SAWED_OFF_FILL,
	SA_SAWED_OFF_PUMP,
	SA_SAWED_OFF_FIRE,
	SA_TEC9_RELOAD,
	SA_TEC9_FIRE,
	SA_UMP45_RELOAD,
	SA_UMP45_FIRE,
	SA_DOUBLEKILL,
	SA_TRIPLEKILL,
	SA_RAMPAGE,
	SA_GODLIKE,
	SA_WICKEDSICK,
	SA_DEATHMONSTER,
	SA_LEVITATION,
	SA_BUTTON,
	SA_PUT,
	SA_TAKE,
	SA_STEP,
	SA_LAVA,
	SA_DOOR,
	SA_CHANGE,
	SA_LNUKE,
	SA_LAMMOS,
	SA_LCASH,
	SA_LGODSTART,
	SA_LGODEND,
	SA_PLAYER_DAMAGE,
	SA_CMP_INTRO,
	SA_SNOW,
	SA_CMP_DOOR,
	SA_CMP_BUTTON,
	SA_CMP_BEEP,
	SA_CMP_BOOM,
	SA_MAX
};

typedef struct	s_sample
{
	ALuint		buffer;
	ALshort		*sample;
	SNDFILE		*file;
	SF_INFO		infos;
	ALenum		format;
	ALsizei		sample_rate;
	ALsizei		nb_samples;
	float		length;
}				t_sample;

typedef struct	s_sound_param
{
	bool		fork;
	bool		no_sound;
	bool		overall;
	bool		play;
	bool		sound;
	bool		stop;
	int			start;
	int			end;
	float		volume;
	float		pitch;
	t_vec3d		pos;
}				t_sparam;

typedef struct	s_sound
{
	ALCdevice	*device;
	ALCcontext	*context;
	t_sample	*samples;
	ALuint		ambient;
	float		volume;
	float		pitch;
	t_dynarray	*sounds;
	t_dynarray	*fork;
}				t_sound;

int				sound_system(t_env *env, int source, t_sparam param);
void			delete_sources(t_dynarray *sounds);

int				sound_manager(t_env *env, int source);

int				init_sound(t_env *env, t_dynarray *s, ALuint *sources, int i);

t_sparam		sp_fork(float volume, float pitch, t_vec3d pos);
t_sparam		sp_no_sound(int start, int end);
t_sparam		sp_overall(int start, int end, t_sparam p);
t_sparam		sp_play(float volume, float pitch, t_vec3d pos);
t_sparam		sp_stop(void);
t_sparam		sp_volume(float volume, float pitch);

int				fork_sound(t_env *env, int source, t_sparam param);
int				play_sound(t_env *env, int source, t_sparam param);
int				sound_volume(t_env *env, int source, t_sparam param);
int				stop_sound(t_env *env, int source);

char			*samples_paths(unsigned int index);

#endif
