#pragma once

/* All mesh types */
/* Implemented this way for possible gpu mesh generation */
enum class CellShape : u8 {
	none = 0,
	custom = 1,
	cube = 2,
	stairs_x = 3,
	stairs_y = 4,
	stairs_z = 5,
	stairs_x_inv = 6,
	stairs_y_inv = 7,
	stairs_z_inv = 8,
	fluid = 9
};
