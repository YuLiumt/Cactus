Analysis
=========
SphericalSurface
-----------------
Variable
^^^^^^^^^
.. c:var:: sf_info[nsurfaces]

    Surface information

    :Variable:
        * sf_area: proper area (covariant quantities)

            .. math::

                A := \int \sqrt{q} dS

        * sf_mean_radius: average coordinate radius (coordinate-dependent quantities)

            .. math::

                 M := \int \frac{h}{A} dS

        * sf_min_radius sf_max_radius: minimum and maximum coordinate radius

        * sf_centroid_x sf_centroid_y sf_centroid_z: 

            .. math::

                D^{i} := \int \frac{x^{i}}{A} dS

        * sf_quadrupole_xx sf_quadrupole_xy sf_quadrupole_xz sf_quadrupole_yy sf_quadrupole_yz sf_quadrupole_zz

            .. math::

                Q^{ij} := \int \frac{y^{i} y^{j}}{A} dS \text{ with } y^{i} := x^{i} - D^{i}

        * sf_min_x sf_min_y sf_min_z sf_max_x sf_max_y sf_max_z: bounding box

.. c:var:: sf_maxreflevel[nsurfaces]

    the finest reflevel that contains the entire surface and store the result so that other thorns can decide which reflevel to use

.. c:var:: sf_origin[nsurfaces]

    :Variable:

        * sf_origin_x sf_origin_y sf_origin_z

Function
^^^^^^^^^
.. py:function:: sf_IdFromName(CCTK_INT IN fallbackid, CCTK_POINTER_TO_CONST IN name)

    simple translation function from user-friendly name to numerical Id.

    :param int fallbackid: index of surface
    :param char name: name of surface
    :Error: -1 if no name matches