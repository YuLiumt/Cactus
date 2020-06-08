I/O
====

In Carpet, a local grid (a "cuboid" that has a uniform spacing in each axis, and lives on a single processor) has a number of attributes:

* **reflevel** - This is an integer specifing the grid's "refinement level" in the Berger-Oliger algorithm.
* **map** - This is an integer specifying the "map" (grid patch) at this refinement level.
* **component** - This is an integer specifying one of the local grids in this map/patch.

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

CarpetIOBasic
---------------
This thorn provides info output for Carpet.

Parameter
^^^^^^^^^^
* Variables to output in scalar form

    >>> IOBasic::outInfo_vars = "ADMBase::gxx"
    -----------------------------------------------
    Iteration      Time |              ADMBASE::gxx
                        |      minimum      maximum
    -----------------------------------------------
            0     0.000 |    1.0000000    1.0000000

Warning
^^^^^^^^^^
* Reduction operator "maximum" does not exist (maybe there is no reduction thorn active?)

    >>> ActiveThorns = "CarpetReduce"

CarpetIOScalar
---------------
This thorn provides scalar output for Carpet.

Parameter
^^^^^^^^^^
* Variables to output in scalar form

    >>> IOScalar::outScalar_vars = ""

* Write one file per group instead of per variable

    >>> IOScalar::one_file_per_group = yes

CarpetIOASCII
---------------
This thorn provides ASCII output for Carpet. The CarpetIOASCII I/O methods can output any type of CCTK grid variables (grid scalars, grid functions, and grid arrays of arbitrary dimension); data is written into separate ﬁles named "<varname>.asc".

It reproduces most of the functionality of thorn IOASCII from the standard CactusBase arrangement. Where possible the names of parameters and their use is identical. However, this thorn outputs considerably more information than the standard IOASCII thorn. Information about, e.g., the reﬁnement level and the index position of the output are also given. All the output can be visualized using gnuplot.

Parameter
^^^^^^^^^^
* Variables to output in 1D ASCII file format

    >>> IOASCII::out1D_vars = "ADMBase::gxx"
    [~/simulations/example/output-0000/example/gxx.x.asc]
    # 1D ASCII output created by CarpetIOASCII
    # created on ubuntu by yuliu on Sep 10 2019 at 03:33:33-0400
    # parameter filename: "/home4/yuliu/simulations/example/output-0000/example.par"
    #
    # gxx x (gxx)
    #
    # iteration 0   time 0
    # time level 0
    # refinement level 0   multigrid level 0   map 0   component 0
    # column format: 1:it	2:tl	3:rl 4:c 5:ml	6:ix 7:iy 8:iz	9:time	10:x 11:y 12:z	13:data
    . . .
    >>> IOASCII::out2D_vars = "ADMBase::gxx"
    [~/simulations/example/output-0000/example/gxx.xy.asc]
    # 2D ASCII output created by CarpetIOASCII
    # created on ubuntu by yuliu on Sep 10 2019 at 04:14:22-0400
    # parameter filename: "/home4/yuliu/simulations/example/output-0000/example.par"
    #
    # gxx x y (gxx)
    #
    # iteration 0   time 0
    # time level 0
    # refinement level 0   multigrid level 0   map 0   component 0
    # column format: 1:it	2:tl	3:rl 4:c 5:ml	6:ix 7:iy 8:iz	9:time	10:x 11:y 12:z	13:data
    0	0	0 0 0	0 0 12	0	-12 -12 0	1
    0	0	0 0 0	1 0 12	0	-11 -12 0	1
    0	0	0 0 0	2 0 12	0	-10 -12 0	1
    . . . 
    0	0	0 0 0	0 1 12	0	-12 -11 0	1
    0	0	0 0 0	1 1 12	0	-11 -11 0	1
    0	0	0 0 0	2 0 12	0	-10 -11 0	1
    . . .
    0	0	0 0 0	0 2 12	0	-12 -10 0	1
    0	0	0 0 0	1 2 12	0	-11 -10 0	1
    0	0	0 0 0	2 2 12	0	-10 -10 0	1
    >>> IOASCII::out3D_vars = "ADMBase::gxx"
    [~/simulations/example/output-0000/example.par]
    # 3D ASCII output created by CarpetIOASCII
    # created on ubuntu by yuliu on Sep 10 2019 at 04:19:51-0400
    # parameter filename: "/home4/yuliu/simulations/example/output-0000/example.par"
    #
    # gxx x y z (gxx)
    #
    # iteration 0   time 0
    # time level 0
    # refinement level 0   multigrid level 0   map 0   component 0
    # column format: 1:it   2:tl    3:rl 4:c 5:ml   6:ix 7:iy 8:iz  9:time  10:x 11:y 12:z  13:data
    0       0       0 0 0   0 0 0   0       -12 -12 -12     1
    0       0       0 0 0   1 0 0   0       -11 -12 -12     1
    0       0       0 0 0   2 0 0   0       -10 -12 -12     1
    . . .
    0       0       0 0 0   0 1 0   0       -12 -11 -12     1
    0       0       0 0 0   1 1 0   0       -11 -11 -12     1
    0       0       0 0 0   2 1 0   0       -10 -11 -12     1
    . . .
    0       0       0 0 0   0 2 0   0       -12 -10 -12     1
    0       0       0 0 0   1 2 0   0       -11 -10 -12     1
    0       0       0 0 0   2 2 0   0       -10 -10 -12     1
    . . .
    0       0       0 0 0   0 0 1   0       -12 -12 -11     1
    0       0       0 0 0   1 0 1   0       -11 -12 -11     1
    0       0       0 0 0   2 0 1   0       -10 -12 -11     1
    . . .
    0       0       0 0 0   0 1 0   0       -12 -11 -11     1
    0       0       0 0 0   1 1 0   0       -11 -11 -11     1
    0       0       0 0 0   2 1 0   0       -10 -11 -11     1
    . . .
    0       0       0 0 0   0 2 0   0       -12 -10 -11     1
    0       0       0 0 0   1 2 0   0       -11 -10 -11     1
    0       0       0 0 0   2 2 0   0       -10 -10 -11     1
    . . .
    0       0       0 0 0   0 0 1   0       -12 -12 -10     1
    0       0       0 0 0   1 0 1   0       -11 -12 -10     1
    0       0       0 0 0   2 0 1   0       -10 -12 -10     1
    . . .
    0       0       0 0 0   0 1 0   0       -12 -11 -10     1
    0       0       0 0 0   1 1 0   0       -11 -11 -10     1
    0       0       0 0 0   2 1 0   0       -10 -11 -10     1
    . . .
    0       0       0 0 0   0 2 0   0       -12 -10 -10     1
    0       0       0 0 0   1 2 0   0       -11 -10 -10     1
    0       0       0 0 0   2 2 0   0       -10 -10 -10     1

* Write one file per group instead of per variable

    >>> IOASCII::out3D_vars = "ADMBase::gxx"
    >>> IOASCII::one_file_per_group = yes
    [~/simulations/example/output-0000/example/admbase-metric.xyz.asc]
    # 3D ASCII output created by CarpetIOASCII
    # created on ubuntu by yuliu on Sep 10 2019 at 04:28:57-0400
    # parameter filename: "/home4/yuliu/simulations/example/output-0000/example.par"
    #
    # ADMBASE::METRIC x y z (admbase-metric)
    #
    # iteration 0   time 0
    # time level 0
    # refinement level 0   multigrid level 0   map 0   component 0
    # column format: 1:it   2:tl    3:rl 4:c 5:ml   6:ix 7:iy 8:iz  9:time  10:x 11:y 12:z  13:data
    # data columns: 13:gxx 14:gxy 15:gxz 16:gyy 17:gyz 18:gzz
    >>> IOASCII::out3D_vars = "ADMBase::gxx"
    >>> IOASCII::one_file_per_group = no
    [~/simulations/example/output-0000/example/gxx.xyz.asc]

CarpetIOHDF5
---------------
Thorn CarpetIOHDF5 provides HDF5-based output to the Carpet mesh refinement driver in Cactus. The CarpetIOHDF5 I/O method can output any type of CCTK grid variables (grid scalars, grid functions, and grid arrays of arbitrary dimension); data is written into separate ﬁles named "<varname>.h5". **HDF5 is highly recommended over ASCII for performance and storage-size reasons.**

.. note::

    The default is to output distributed grid variables in parallel, each processor writing a file <varname>.file\_<processor ID>.h5. Unchunked means that an entire Cactus grid array (gathered across all processors) is stored in a single HDF5 dataset whereas chunked means that all the processor-local patches of this array are stored as separate HDF5 datasets (called chunks). Consequently, for unchunked data all interprocessor ghostzones are excluded from the output. In contrast, for chunked data the interprocessor ghostzones are included in the output. When visualising chunked datasets, they probably need to be recombined for a global view on the data. This needs to be done within the visualisation tool.

Parameter
^^^^^^^^^^
* Variables to output in CarpetIOHDF5 file format. The variables must be given by their fully qualiﬁed variable or group name.

    >>> IOHDF5::out_vars = "ADMBase::gxx"

* Parallel (chunked) Output of Grid Variables or unchunked of Grid Variables.

    >>> IO::out_mode = "onefile"  
    >>> IO::out_unchunked = 1
    [gxx.h5]
    >>> IO::out_mode = "proc"
    [gxx.file_0.h5]
    [gxx.file_1.h5]
    [gxx.file_2.h5]
    . . .

* Do checkpointing with CarpetIOHDF5

    >>> IOHDF5::checkpoint = "yes"