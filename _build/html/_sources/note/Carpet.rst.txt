CarpetTracker
--------------
Object coordinates are updated by CarpetTracker, which provides a simple interface to the object trackers PunctureTracker and NSTracker in order to have the refined region follow the moving objects.

.. digraph:: foo

   "CarpetTracker" -> "SphericalSurface";
   "CarpetTracker" -> "CarpetRegrid2";

Parameter
^^^^^^^^^^
* Spherical surface index or name which is the source for the location of the refine regions. (Maximum number of tracked surfaces less than 10)

    >>> CarpetTracker::surface[0] = 0
    <surface index>
    >>> CarpetTracker::surface_name[0] = "Righthand NS"
    <surface name>

CarpetInterp/CarpetInterp2
---------------------------
This thorn provides a parallel interpolator for Carpet.


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

CarpetSlab
-----------
This thorn provides hyperslabbing for Carpet.

CarpetReduce
-------------
This thorn provides parallel reduction operators for Carpet.

CarpetMask
-----------
Remove unwanted regions from Carpet's reduction operations.