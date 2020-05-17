CactusUtils
============

NaNChecker
-----------
Thorn NaNChecker reports NaN values found in CCTK grid variables. The NaNChecker thorn can also mark the positions (in grid index points) of all the NaNs found for a given list of CCTK grid functions in a mask array and save this array to an HDF5 ﬁle.

Parameter
^^^^^^^^^^
* How often to check for NaNs

    >>> NaNChecker::check_every = 128 # Every coarse grid step

* Groups and/or variables to check for NaNs

    >>> NaNChecker::check_vars = "all"
    [1mWARNING level 1 from host ubuntu process 0
    while executing schedule bin NaNChecker_NaNCheck, routine NaNChecker::NaNChecker_NaNCheck_Check
    in thorn NaNChecker, file /home4/yuliu/Cactus/arrangements/CactusUtils/NaNChecker/src/NaNCheck.cc:875:
    ->[0m There were 142 NaN/Inf value(s) found in variable 'HYDROBASE::rho'

* What to do if a NaN was found

    >>> NaNChecker::action_if_found = "terminate"
    [1mWARNING level 1 from host ubuntu process 0
    while executing schedule bin CCTK_POSTSTEP, routine NaNChecker::NaNChecker_TakeAction
    in thorn NaNChecker, file /home4/yuliu/Cactus/arrangements/CactusUtils/NaNChecker/src/NaNCheck.cc:251:
    ->[0m 'action_if_found' parameter is set to 'terminate' - scheduling graceful termination of Cactus

* Tracking and Visualizing NaNs Positions

    >>> NaNChecker::out_NaNmask = "no"

SystemStatistics
-----------------
Thorn SystemStatistics collects information about the system on which a Cactus process is running and stores it in Cactus variables. These variables can then be output and reduced using the standard Cactus methods such as IOBasic and IOScalar.

Output
^^^^^^^
* Run memory statistics in MB

    >>> IOBasic::outInfo_vars  = "SystemStatistics::maxrss_mb{reductions = 'maximum'}"
    >>> IOScalar::outScalar_vars = "SystemStatistics::process_memory_mb"
    -------------------------------
    Iteration      Time | *axrss_mb
                        |   maximum
    -------------------------------
            0     0.000 |       166
           32     1.000 |       172
           64     2.000 |       172
           96     3.000 |       172
    [systemstatistics-process_memory_mb.maximum.asc]

    .. figure:: ./picture/systemstatistics.png
    
       

TerminationTrigger
-------------------
This thorn watches the elapsed walltime. If only n minutes are left before the some limit set by the user, it triggers termination of the simulation.

Parameter
^^^^^^^^^^
* Walltime in HOURS allocated for this job

    >>> TerminationTrigger::max_walltime = 1

* When to trigger termination in MINUTES

    >>> TerminationTrigger::on_remaining_walltime = 1

* Output remaining wall time every n minutes

    >>> TerminationTrigger::output_remtime_every_minutes = 5

* Create an empty termination file at startup

    >>> TerminationTrigger::create_termination_file = yes