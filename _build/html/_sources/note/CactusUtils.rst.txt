CactusUtils
============

..

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