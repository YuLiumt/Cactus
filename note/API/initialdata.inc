Initial Data
=============
ADMBase
--------
.. c:var:: Variable

    :param gf gxx: ADM 3-metric :math:`g_{11}`
    :param gf gxy: ADM 3-metric :math:`g_{12}`
    :param gf gxz: ADM 3-metric :math:`g_{13}`
    :param gf gyy: ADM 3-metric :math:`g_{22}`
    :param gf gyz: ADM 3-metric :math:`g_{23}`
    :param gf gzz: ADM 3-metric :math:`g_{33}`
    :param gf kxx: ADM 3-metric :math:`k_{11}`
    :param gf kxy: ADM 3-metric :math:`k_{12}`
    :param gf kxz: ADM 3-metric :math:`k_{13}`
    :param gf kyy: ADM 3-metric :math:`k_{22}`
    :param gf kyz: ADM 3-metric :math:`k_{23}`
    :param gf kzz: ADM 3-metric :math:`k_{33}`  
    :param gf alp: ADM lapse function :math:`\alpha`
    :param gf betax: ADM shift function :math:`\beta^1`
    :param gf betay: ADM shift function :math:`\beta^2`
    :param gf betaz: ADM shift function :math:`\beta^3`
    :param gf dtalp: Time derivative of ADM lapse function :math:`\alpha`
    :param gf dtbetax: Time derivative of ADM shift function :math:`\beta^1`
    :param gf dtbetay: Time derivative of ADM shift function :math:`\beta^2`
    :param gf dtbetaz: Time derivative of ADM shift function :math:`\beta^3`


TmunuBase
----------
.. c:var:: Variable

    :param gf eTtt: Stress-energy tensor :math:`T_{00}`
    :param gf eTtx: Stress-energy tensor :math:`T_{01}`
    :param gf eTty: Stress-energy tensor :math:`T_{02}`
    :param gf eTtz: Stress-energy tensor :math:`T_{03}`
    :param gf eTxx: Stress-energy tensor :math:`T_{11}`
    :param gf eTxy: Stress-energy tensor :math:`T_{12}`
    :param gf eTxz: Stress-energy tensor :math:`T_{13}`
    :param gf eTyy: Stress-energy tensor :math:`T_{22}`
    :param gf eTyz: Stress-energy tensor :math:`T_{23}`
    :param gf eTzz: Stress-energy tensor :math:`T_{33}`

HydroBase
----------
.. c:var:: Variable

    :param gf rho: rest mass density
    :param gf press: gas pressure
    :param gf eps: specific internal energy
    :param gf vel[3]: velocity :math:`v^i`
    :param gf w_lorentz: Lorentz Factor
    :param gf Y_e: Electron Fraction
    :param gf Abar: Average atomic mass [atomic mass unit]
    :param gf temperature: Temperature [MeV]
    :param gf entropy: Specific Entropy [k_b/baryon]
    :param gf Bvec[3]: Magnetic field components :math:`B^i`
    :param gf Avec[3]: Vector potential
    :param gf Aphi: Electric potential for Lorentz Gauge