Mesh Refinement
================

CarpetRegrid2
--------------
.. c:var:: Variable

    :param scalar num_levels[10]: Number of refinement levels
    :param scalar position_x[10]: Positions of refined regions in x direction
    :param scalar position_y[10]: Positions of refined regions in y direction
    :param scalar position_z[10]: Positions of refined regions in z direction  
    :param array radius[10]: Radii of refined regions for each level
    :param array radius_x[10]: Radii of refined regions for each level in x direction
    :param array radius_y[10]: Radii of refined regions for each level in y direction
    :param array radius_z[10]: Radii of refined regions for each level in z direction
    :param gf level_mask: Requested refinement level for this grid point