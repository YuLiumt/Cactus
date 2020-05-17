I/O
====

IOUtil
-----------
Thorns providing IO methods typically have string parameters which list the variables which should be output, how frequently (i.e. how many iterations between output), and where the output should go.

.. digraph:: foo

    "IOUtil" -> "CarpetSlab";
    "IOUtil" -> "PUGHSlab";

Parameter
^^^^^^^^^^
* The name of the directory to be used for output.

    >>> IO::out_dir = $parfile

* How often, in terms of iterations, each of the Cactus I/O methods will write output.

    >>> IO::out_every = 2
    ------------------------------
    it |          | *::coarse_dx |
       |    t     | scalar value |
    ------------------------------
     0 |    0.000 |   0.25000000 |
     2 |    2.000 |   0.25000000 |
     4 |    4.000 |   0.25000000 |
     6 |    6.000 |   0.25000000 |
     8 |    8.000 |   0.25000000 |

* writing to file is performed only by processor zero. This processor gathers all the output data from the other processors and then writes to a single ﬁle.

    >>> IO::out_mode = "onefile"

* Every processor writes its own chunk of data into a separate output ﬁle.

    >>> IO::out_mode = "proc"

.. note::

    For a run on multiple processors, scalar, 1D, and 2D output will always be written from only processor zero (that is, required data from all other processors will be sent to processor zero, which then outputs all the gathered data). For full-dimensional output of grid arrays this may become a quite expensive operation since output by only a single processor will probably result in an I/O bottleneck and delay further computation. For this reason Cactus offers different I/O modes for such output which can be controlled by the *IO::out_mode* parameter, in combination with *IO::out_unchunked* and *IO::out_proc_every*.

* Checkpointing

    >>> IO::checkpoint_ID = "yes"             # Checkpoint initial data
    INFO (CarpetIOHDF5): Dumping initial checkpoint at iteration 0, simulation time 0
    >>> IO::checkpoint_every = 1              # How often to checkpoint
    >>> IO::checkpoint_on_terminate = "yes"   # Checkpoint after last iteration
    INFO (CarpetIOHDF5): Dumping termination checkpoint at iteration 2432, simulation time 47.5
    >>> IO::checkpoint_dir = "../checkpoints" # Output directory for checkpoint files
    [checkpoint.chkpt.it_0.file_0.h5]
    [checkpoint.chkpt.it_0.file_1.h5]
    . . .
    [checkpoint.chkpt.it_128.file_0.h5]
    . . .

* Recover

    >>> IO::recover_dir = "../checkpoints" # Directory to look for recovery files
    >>> IO::recover = "autoprobe"

Warning
^^^^^^^^^^
* No driver thorn activated to provide storage for variables

    >>> ActiveThorns = "CarpetSlab"
    AMR driver provided by Carpet
    >>> ActiveThorns = "PUGHSlab"
    Driver provided by PUGH


IOBasic
-----------
Thorn IOBasic provides I/O methods for outputting scalar values in ASCII format into files and for printing them as runtime information to screen.

* This method outputs the information into ASCII files named "<scalar_name>.{asc|xg}" (for CCTK_SCALAR variables) and "<var_name>_<reduction>.{asc|xg}" (for CCTK_GF and CCTK_ARRAY variables where reduction would stand for the type of reduction operations (eg. minimum, maximum, L1, and L2 norm)
* This method prints the data as runtime information to stdout. The output occurs as a table with columns containing the current iteration number, the physical time at this iteration, and more columns for scalar/reduction values of each variable to be output.

Reduction Operations
^^^^^^^^^^^^^^^^^^^^^^
* The minimum of the values

    .. math:: \min :=\min _{i} a_{i}

* The maximum of the values

    .. math:: \max :=\max _{i} a_{i}

* The norm1 of the values

    .. math:: \frac{\Sigma\left|a_{i}\right|}{count}

* The norm2 of the values

    .. math:: \sqrt{\frac{\sum_{i}\left|a_{i}\right|^{2}}{count}}

Parameter
^^^^^^^^^^
* Print the information of CCTK_SCALAR variables

    >>> IOBasic::outInfo_vars = "grid::coarse_dx"
    -------------------------------
    it  |          | *::coarse_dx |
        |    t     | scalar value |
    -------------------------------
      0 |    0.000 |   0.25000000 |

* Print the information of CCTK_GF and CCTK_ARRAY variables with the type of reduction

    >>> IOBasic::outInfo_vars = "wavetoy::phi"  
    >>> IOBasic::outInfo_reductions = "minimum maximum"
    ----------------------------------------------
    it  |          | WAVETOY::phi                |
        |    t     | minimum      | maximum      |
    ----------------------------------------------
      0 |    0.000 | 7.104375e-13 |   0.99142726 |
    >>> IOBasic::outInfo_vars = "wavetoy::phi{reductions = 'norm2'}"  
    -------------------------------
    it  |          | WAVETOY::phi |
        |    t     | norm2        |
    -------------------------------
      0 |    0.000 |   0.10894195 |

* Outputs CCTK_SCALAR variabless into ASCII files

    >>> IOBasic::outScalar_vars = "grid::coarse_dx"
    [~/simulations/example/output-0000/example/coarse_dx.xg]
    "Parameter file /home4/yuliu/simulations/example/output-0000/example.par
    "Created Sep 05 2019 05:05:37-0400
    "x-label time
    "y-label GRID::coarse_dx
    "coarse_dx v time
    0.0000000000000	0.2500000000000

Warning
^^^^^^^^^^
* WARNING[L1,P0] (IOBasic): Unknown reduction operator 'minimum'. Maybe you forgot to activate thorn LocalReduce? (Driver provided by Carpet)

    >>> ActiveThorns = "CarpetIOBasic CarpetReduce"

IOASCII
------------
Thorn IOASCII provides I/O methods for 1D, 2D, and 3D output of grid arrays and grid functions into files in ASCII format.

Parameter
^^^^^^^^^^
* Outputs CCTK_GF and CCTK_ARRAY variables into ASCII files

    >>> IOASCII::out1D_every = 1 
    >>> IOASCII::out1D_style = "gnuplot f(x)"
    >>> IOASCII::out1D_vars = "wavetoy::phi"
    [~/simulations/example1/output-0000/example1/phi_x_[1][1].asc]
    #Parameter file /home4/yuliu/simulations/example/output-0000/example.par
    #Created Sep 07 2019 03:55:52-0400
    #x-label x
    #y-label WAVETOY::phi (y = 0.1500000000000, z = 0.1500000000000), (yi = 1, zi = 1)
    #Time = 0.0000000000000
    -0.1500000000000		0.9914272633971
    0.1500000000000		0.9914272633971
    0.4500000000000		0.9689242170281
    0.7500000000000		0.9254388283880
    . . .

Warning
^^^^^^^^^^
* The aliased function 'Hyperslab_GetList' (required by thorn 'IOASCII') has not been provided by any active thorn ! (Driver provided by Carpet)

    >>> ActiveThorns = "CarpetIOASCII"
