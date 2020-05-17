Multi-domain grid
==================
Setup of a multi-domain grid

    >>> int nz = 3 ; 	// Number of domains
    >>> int nr = 7 ; 	// Number of collocation points in r in each domain
    >>> int nt = 5 ; 	// Number of collocation points in theta in each domain
    >>> int np = 8 ; 	// Number of collocation points in phi in each domain
    >>> int symmetry_theta = SYM ; // symmetry with respect to the equatorial plane
    >>> int symmetry_phi = NONSYM ; // no symmetry in phi
    >>> bool compact = true ; // external domain is compactified
    >>> // Multi-domain grid construction:
    >>> Mg3d mgrid(nz, nr, nt, np, symmetry_theta, symmetry_phi, compact) ;
    >>> cout << mgrid << endl ; 
