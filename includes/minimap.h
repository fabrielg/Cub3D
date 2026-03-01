#ifndef MINIMAP_H
# define MINIMAP_H

# define MINIMAP_SCALE	4

# define CURSOR_COLOR		0xFFFFFF
# define VOID_COLOR			0x3C3C3C
# define WALL_COLOR			0x777777
# define DOOR_OPEN_COLOR		0x888888
# define DOOR_CLOSE_COLOR	0x676767
# define FLOOR_COLOR			0xAAAAAA

void	render_minimap(t_libx *libx, t_player *p, t_map *map);
void	render_cursor(t_libx *libx, t_player *p);

#endif
