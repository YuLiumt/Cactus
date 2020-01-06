Evolution
==========

CoordGauge
-----------
.. c:var:: Variable

    :param scalar active_slicing_handle: Slicing and shift stuff

IllinoisGRMHD
--------------
.. c:var:: Variable

    :param gf rho_star: Evolved mhd variables
    :param gf tau: Evolved mhd variables
    :param gf mhd_st_x: Evolved mhd variables :math:`\tilde{S}_1`
    :param gf mhd_st_y: Evolved mhd variables :math:`\tilde{S}_2`
    :param gf mhd_st_z: Evolved mhd variables :math:`\tilde{S}_3`
    :param gf Ax: x-component of the vector potential
    :param gf Ay: y-component of the vector potential
    :param gf Az: z-component of the vector potential
    :param gf psi6phi: the em scalar potential
    :param gf rho_b: Primitive variables density
    :param gf P: Primitive variables pressure
    :param gf vx: Primitive variables three velocity :math:`v^1`
    :param gf vy: Primitive variables three velocity :math:`v^2`
    :param gf vz: Primitive variables three velocity :math:`v^3`
    :param gf Bx: B-field components defined at vertices.
    :param gf By: B-field components defined at vertices.
    :param gf Bz: B-field components defined at vertices.
    :param gf Bx_stagger: B-field components defined at staggered points.
    :param gf By_stagger: B-field components defined at staggered points.
    :param gf Bz_stagger: B-field components defined at staggered points.
    :param array rho_tab: Equation of state parameters
    :param array P_tab: Equation of state parameters
    :param array eps_tab: Equation of state parameters
    :param array k_tab: Equation of state parameters
    :param array gamma_tab: Equation of state parameters
    :param scalar n_poly: polytropic index
    :param gf gtxx: BSSN quantities, computed from ADM quantities
    :param gf gtxy: BSSN quantities, computed from ADM quantities
    :param gf gtxz: BSSN quantities, computed from ADM quantities
    :param gf gtyy: BSSN quantities, computed from ADM quantities
    :param gf gtyz: BSSN quantities, computed from ADM quantities
    :param gf gtzz: BSSN quantities, computed from ADM quantities
    :param gf gtupxx: BSSN quantities, computed from ADM quantities
    :param gf gtupxy: BSSN quantities, computed from ADM quantities
    :param gf gtupxz: BSSN quantities, computed from ADM quantities
    :param gf gtupyy: BSSN quantities, computed from ADM quantities
    :param gf gtupyz: BSSN quantities, computed from ADM quantities
    :param gf gtupzz: BSSN quantities, computed from ADM quantities
    :param gf phi_bssn: BSSN quantities, computed from ADM quantities
    :param gf psi_bssn: BSSN quantities, computed from ADM quantities
    :param gf lapm1: BSSN quantities, computed from ADM quantities
