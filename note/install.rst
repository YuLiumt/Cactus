Install
=======

`Users <http://lists.einsteintoolkit.org/mailman/listinfo/users>`_ of the Einstein Toolkit are encouraged to `register <http://einsteintoolkit.org/join.html>`_ to become one of its.

Required Software
-----------------

The main requirements are:

* Client tools for Source Code Repositories: CVS, SVN and git
* Compilers: C, C++ and Fortran 90
* MPI implementation: This is needed for the Carpet driver
* Standard development tools: Perl, etc.

Linux
^^^^^^^^
.. code-block:: bash

    # On Debian/Ubuntu/Mint use this command:
    $ sudo apt-get install -y subversion gcc git numactl libgsl-dev libpapi-dev python libhwloc-dev make libopenmpi-dev libhdf5-openmpi-dev libfftw3-dev libssl-dev liblapack-dev g++ curl gfortran patch pkg-config libhdf5-dev libjpeg-turbo?-dev
    # On Fedora use this command:
    $ sudo dnf install -y libjpeg-turbo-devel gcc git lapack-devel make subversion gcc-c++ which papi-devel python hwloc-devel openmpi-devel hdf5-openmpi-devel openssl-devel libtool-ltdl-devel numactl-devel gcc-gfortran findutils hdf5-devel fftw-devel patch gsl-devel pkgconfig
    $ module load mpi/openmpi-x86_64 # You will have to repeat the module load command each time you would like to compile or run the code.
    # On Centos use this command:
    $ sudo yum install -y epel-release
    $ sudo yum install -y libjpeg-turbo-devel gcc git lapack-devel make subversion gcc-c++ which papi-devel hwloc-devel openmpi-devel hdf5-openmpi-devel openssl-devel libtool-ltdl-devel numactl-devel gcc-gfortran hdf5-devel fftw-devel patch gsl-devel

Mac
^^^^^
On Mac, please first

1. Install Xcode from the Apple App Store. In addition agree to Xcode license in Terminal

    .. code-block:: bash

        $ sudo xcodebuild -license

2. install `MacPorts <https://www.macports.org/install.php>`_ for your version of the Mac operating system, if you did not already install it 

3. Next, please install the following packages, using the commands:

    .. code-block:: bash

        $ sudo port -N install pkgconfig gcc9 openmpi-gcc9 fftw-3 gsl jpeg zlib hdf5 +fortran +gfortran openssl ld64 +ld64_xcode
        $ sudo port select mpi openmpi-gcc9-fortran


GetComponents Tools
-------------------

A script called GetComponents is used to fetch the components of the Einstein Toolkit. You may download and make it executable it as follows:

.. code-block:: bash

    $ cd ~/
    $ curl -kLO https://raw.githubusercontent.com/gridaphobe/CRL/ET_2019_03/GetComponents
    $ chmod u+x GetComponents

Below checks out Cactus, the Einstein Toolkit thorns, the Simulation Factory and example parameter files into a directory named Cactus.

.. code-block:: bash

    $ ./GetComponents --parallel https://bitbucket.org/einsteintoolkit/manifest/raw/ET_2019_03/einsteintoolkit.th

.. error::

    * Some versions of svn might show problems with the parallel checkout. If you see errors like (svn: E155037: Previous operation has not finished), try without the --parallel option.
    * svn: E155004: Could not update module <Thorn>
    
        .. code-block:: bash

            $ cd <Thorn_Path>
            $ svn cleanup

The traditional way of compiling Cactus
-----------------------------------------
The traditional way of compiling Cactus without SimFactory.

.. code-block:: bash

    $ make ET-config options=<*.cfg> THORNLIST=<thornlist>

This creates a configuration called "ET", but any other name could be chosen here.

Once the configuration is done, the compilation process is simply

.. code-block:: bash

    $ make -j <number of processes> ET

If everything is compiled correctly, the executable *cactus_ET* will be created under *./exe/*.

The typical procedure for running is

.. code-block:: bash

    $ mpirun -np <num procs> ./exe/cactus_ET <parameter file>

SimFactory Tools
-------------------
SimFactory needs to be configured before it can be used. The recommended way to do this is to use the setup command. SimFactory contains general support for specific operating systems commonly used on workstations or laptops, including Mac OS, Ubuntu, Cent OS and Scientific Linux. To configure SimFactory for one of these, you need to find the suitable files in *simfactory/mdb/optionlists* and *simfactory/mdb/runscripts* and specify their names on the sim setup command line.

.. code-block:: bash

    # for Debian
    $ ./simfactory/bin/sim setup-silent --optionlist=debian.cfg --runscript debian.sh
    # for Ubuntu, Mint
    $ ./simfactory/bin/sim setup-silent --optionlist=ubuntu.cfg --runscript debian.sh
    # for Fedora (you may have to log out and back in if you have just intalled mpich to make the module command work)
    $ module load mpi
    $ ./simfactory/bin/sim setup-silent --optionlist=fedora.cfg --runscript debian.sh
    # OSX+MacPorts
    $ ./simfactory/bin/sim setup-silent --optionlist=osx-macports.cfg --runscript osx-macports.run
    # OSX+Homebrew
    $ ./simfactory/bin/sim setup-silent --optionlist=osx-homebrew.cfg --runscript generic-mpi.run

.. note::

    Generally, configuring SimFactory means providing an optionlist, for specifying library locations and build options, a submit script for using the batch queueing system, and a runscript, for specifying how Cactus should be run, e.g. which mpirun command to use.

Follow the on-screen prompts. This will output your choices in the configuration file *simfactory/etc/defs.local.ini*. 

.. note::

    It is likely that you will have to further customise this file. You can see some possible option settings in *simfactory/etc/defs.local.ini.example*.

SimFactory needs to have a machine definition for every machine that it is run on. If you are using a machine that SimFactory already has a definition for, such as a well-known supercomputer used by others in the Cactus community, then no additional setup is required. If, however, you are running SimFactory on an individual laptop or on an unsupported supercomputer, the setup command will also create a new machine definition for the local machine in *./repos/simfactory2/mdb/machines/<hostname>.ini*. You may also have to add extra information to this file.

.. note::
    A machine consists of a certain number of nodes, each of which consists of a certain number of cores.

    The user chooses the total number of threads (–procs). The user can also choose the number of threads per process (–num-threads) and the number of threads per core (–num-smt). Additionally, the user can also specify the number of cores per node (–ppn) and the number of threads per node (–ppn-used). The number of nodes is always chosen automatically.
    
    Note that nodes and cores are requested from the queuing system, while processes and threads are started by SimFactory.

    For more details you can see `<https://simfactory.bitbucket.io/simfactory2/userguide/processterminology.html>`_

.. note::

    The main SimFactory binary is called “sim” and is located in simfactory/bin. You can execute SimFactory explicitly as ./simfactory/bin/sim, but we recommend that you set up a shell alias in your shell startup file so that you can just use the command “sim”. For bash users this file is .bashrc on Linux. Add the following to the shell startup file:

    .. code-block:: bash

        $ alias sim=./simfactory/bin/sim

Building the Einstein Toolkit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Assuming that SimFactory has been successfully set up on your machine, you should be able to build the Einstein Toolkit with

.. code-block:: bash

    $ ./simfactory/bin/sim build --mdbkey make 'make -j2' --thornlist ../einsteintoolkit.th | cat

The most important argument to this command is the *--thornlist* option, as this tells Cactus which thorns from your source tree you want to include in the configuration.

.. note::

    Note that, typically, one will not be compiling all the thorns provided with the ET. Compilation is time-consuming, and different configurations also take a significant amount of disk space. One therefore typically builds a thornlist that is as small as possible, including only the required thorns. Care should be taken, though, as there are often non-trivial dependencies between thorns. If one thorn which is required by another thorn is not mentioned in the thornlist, compilation will abort (with the corresponding error message).

Running the Einstein Toolkit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Simulations must always be created before they can be submitted or run. Since it is very common to want to create a simulation and immediately submit or run it, SimFactory provides the *create-run* and *create-submit* commands. These commands create the simulation and then either run or submit it immediately.

.. note::

    If you are working on a laptop or workstation, you can run SimFactory simulations directly in your terminal without going via a queuing system. However, if you are running SimFactory on a supercomputer with a queuing system, you cannot run simulations directly using the run command - they must instead be submitted to the queuing system, such as the PBS queuing system.

SimFactory needs to know a name for the simulation as well as what parameter file to use. You can either specify the name on the command line and give the parameter file with the *--parfile* option.

example

.. code-block:: bash

    $ ./simfactory/bin/sim create-run static_tov --parfile=par/static_tov_small_short.par --procs=2 --num-threads=1 --ppn-used=2  --walltime=8:0:0 | cat

It is often useful to use a parameter file script, rather than a parameter file, as a basic description of a simulation. For example, when performing a convergence test, many parameters might change between simulations, and changing them all manually is tedious and error-prone. 

A parameter file script is a file with a “.rpar” extension which, when executed, generates a file in the same place but with a “.par” extension. You can write a parameter file script in any language.

We provide examples in python.
"""""""""""""""""""""""""""""""
::

    #!/usr/bin/env python

    import sys
    import re
    from string import Template

    dtfac = 0.5

    lines = """
    Time::dtfac                   = $dtfac
    """

    data = open(re.sub(r'(.*)\.rpar$', r'\1.par', sys.argv[0]), 'w')
    data.write(Template(lines).substitute(locals()))

These parameter file scripts look like standard Cactus parameter files but with \$var variable replacements (in this case for the dtfac variable). You can define new variables and do calculations in the header and use the variables in the main body.

If you want to use the Cactus $parfile syntax, you need to escape the $

::

    IO::out_dir = $$parfile