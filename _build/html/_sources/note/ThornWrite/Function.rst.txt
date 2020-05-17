Functions
==========
find_closest
-------------
.. code-block:: c

    #include <cctk.h>
    #include <math.h>

    int find_closest(const cGH *cctkGH, const int *cctk_lsh,
                    const CCTK_REAL *cctk_delta_space, int ghost,
                    CCTK_REAL *coord, CCTK_REAL coord_min, int dir)
    {
        int i, ijk, min_i = -1;
        CCTK_REAL min = 1.e100;
        
        for(i=ghost; i<cctk_lsh[dir]-ghost; i++) {
            ijk = CCTK_GFINDEX3D(cctkGH, (dir==0)?i:0, (dir==1)?i:0, (dir==2)?i:0);

            if (fabs(coord[ijk] - coord_min) < min) {
                min = fabs(coord[ijk] - coord_min);
                min_i = i;
            }
        }
        return min_i;
    }