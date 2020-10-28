/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/19 21:44:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# define BUFF_READ 4194304

enum				e_mapper
{
	MAPPER_NAME,
	MAPPER_POSITION,
	MAPPER_SPEED,
	MAPPER_STATIC,
	MAPPER_TEXTURE,
	MAPPER_SPAWN,
	MAPPER_CAMDIR,
	MAPPER_MAX
};

enum				e_mtl
{
	MTL_COMMENT,
	MTL_NEW,
	MTL_NS,
	MTL_KA,
	MTL_KD,
	MTL_KS,
	MTL_KE,
	MTL_NI,
	MTL_D,
	MTL_ILLUM,
	MTL_MAP_KD,
	MTL_MAX
};

enum				e_pstate
{
	PS_OBJ,
	PS_VERTEXS,
	PS_TXT_VERTEXS,
	PS_END_VERTEXS,
	PS_FACES,
	PS_COMMENT,
	PS_MTLLIB,
	PS_USEMTL,
	PS_MAX
};

enum				e_scene_id
{
	SCENE_FAMAS,
	SCENE_AK47,
	SCENE_SAWED_OFF,
	SCENE_GLOCK_18,
	SCENE_AUG,
	SCENE_UMP45,
	SCENE_MAG7,
	SCENE_GALIL,
	SCENE_NEGEV,
	SCENE_TEC9,
	SCENE_PHYSIC,
	SCENE_CUBE,
	SCENE_AXIS,
	SCENE_PENTE_NORD,
	SCENE_PENTE_SUD,
	SCENE_PENTE_OUEST,
	SCENE_PENTE_EST,
	SCENE_MAP_TEST,
	SCENE_UGLY,
	SCENE_MOON,
	SCENE_STAR,
	SCENE_MAGE,
	SCENE_LOOT,
	SCENE_GOULE,
	SCENE_START_ROOM,
	SCENE_DUST,
	SCENE_MAX
};

struct				s_mtl
{
	char	*name;
	char	color[4];
	float	alpha;
	bool	textured;
};

struct				s_face
{
	int				x;
	int				y;
	int				z;
	int				tx;
	int				ty;
	int				tz;
	int				color;
	bool			textured;
};

struct				s_triangle
{
	t_vec3d		points[3];
	t_vec2d		txt[3];
	t_vec3d		normal;
	t_mesh		*mesh;
	float		scale;
	int			color;
	int			sp;
	char		face_i;
	bool		textured;
	bool		voxel;
};

struct				s_mesh
{
	t_dynarray		tris;
	t_dynarray		deps;
	t_dynarray		faces;
	t_corp			corp;
	int				m_pos[3];
	char			*name;
	float			yaw;
	float			pitch;
	int				index;
	bool			textured;
	bool			phy;
	unsigned char	type;
};

struct				s_map
{
	t_dynarray		meshs;
	t_dynarray		txts;
	t_dynarray		pool;
	t_dynarray		txt_pool;
	t_dynarray		mtls;
	t_mesh			cam;
	t_vec3d			spawn;
	t_vec2d			cam_dir;
	bool			*stats;
	bool			*stats_cpy;
	int				cmtl;
	int				nmesh;
	int				index;
	t_collide		*cam_floor;
	t_collide		*cam_wall;
	t_collide		*cam_roof;
	bool			init;
};

struct				s_parser
{
	char			**lines;
	char			**toks;
	char			*file;
	char			state;
	char			tstate;
	int				tri;
};

int					check_line(t_env *env, t_mesh *m, char **stats);
t_mesh				*find_mesh(t_map *map, char **line, bool *prop);

char				*read_file(int fd, int *len);
char				*maps_paths(unsigned int index);
void				init_states(char states[PS_MAX][PS_MAX]);
int					parse_map(t_map *map,
						char *path, char states[PS_MAX][PS_MAX]);
int					load_face(char **toks, t_map *map, t_face *face);

int					load_map_config(t_env *env, t_map *map, char *map_path);

bool				check_float(char *tok);
bool				check_number(char *tok);

/*
** Lines functions
*/
int					new_mesh(t_map *map, char **toks);
int					new_vertex(t_map *map, char **toks);
int					new_txt_vertex(t_map *map, char **toks);
int					new_face(t_map *map, char **toks);
int					vertex_end(t_map *map, char **toks);
int					comment(t_map *map, char **toks);
int					mtllib(t_map *map, char **toks);
int					usemtl(t_map *map, char **toks);

/*
** Materials
*/
int					parse_mtl(char *file_name, t_dynarray *mtls);
int					get_material_color(t_mesh *m);

int					mtl_new(char **toks, t_dynarray *mtl);
int					mtl_color(char **toks, t_dynarray *mtl);
int					mtl_alpha(char **toks, t_dynarray *mtl);
int					mtl_map_texture(char **toks, t_dynarray *mtls);

int					get_spawn_position(t_map *map, char **line);
int					get_cam_direction(t_map *map, char **line);

/*
** Parser tools
*/
int					cross_whitespaces(char *line, int *i);
int					cross_float(char *line, int *i);
t_vec3d				read_vec3d(char *tok, char start_sep, char end_sep);
t_vec2d				read_vec2d(char *tok, char start_sep, char end_sep);
int					assign_triangle_texture(t_mesh *m, void *ptr);
void				swap_bytes(char *a, char *b);
int					get_line_type(char *c, t_parser *p, char s[PS_MAX][PS_MAX]);
int					get_faces(t_triangle *n, t_map *map, t_face *f, t_mesh *m);

/*
** Mapper functions
*/
int					mapper_texture(t_env *env, t_mesh *m, char *tok);
int					mapper_position(t_env *env, t_mesh *m, char *tok);
int					mapper_speed(t_env *env, t_mesh *m, char *tok);
int					mapper_static(t_env *env, t_mesh *m, char *tok);
int					mapper_deps(t_env *env, t_mesh *m, char *tok);

int					check_deps_cycle(t_dynarray *meshs);

t_map				**current_map(void);

#endif
