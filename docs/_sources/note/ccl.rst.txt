Cactus Configuration Language
================================
Configuration language which tells the flesh all it needs to know about the thorns.

CCL files are (mostly) case independent, and may contain comments introduced by the hash # character, which indicates that the rest of the line is a comment. If the last non-blank character of a line in a CCL file is a backslash \\, the following line is treated as a continuation of the current line.

The interface.ccl File
^^^^^^^^^^^^^^^^^^^^^^^^^
The *interface.ccl* file is used to declare

* an *implementation* name
* inheritance relationships between thorns
* Thorn variables
* Global functions, both provided and used

The schedule.ccl File
^^^^^^^^^^^^^^^^^^^^^^^^^
The flesh knows about everything in *schedule.ccl* files, and handles sorting scheduled routines into an order which is consistent with the BEFORE and AFTER clauses in all the schedule groups. The flesh also handles repeatedly calling scheduled routines which are scheduled with a WHILE clause. In addition, the flesh determines when storage is turned on/off for grid scalars, functions, and arrays and when grid arrays and functions are synchronised, based on the STORAGE: and SYNC: statements in schedule blocks.

.. figure:: picture/Schedule_Bin.png

The param.ccl File
^^^^^^^^^^^^^^^^^^^^^^^^^
The flesh and thorns are controlled by a parameter file; parameters must be declared along with their allowed values.