Compile
===========

Add all the source files to your *make.code.defn* file.

You need to compile the code, i.e. Create a configuration.

The command you need to run is the following:

.. code-block:: bash

    make name DEBUG=yes

Pass in the option *DEBUG=yes* to enable debugging, this is very handy.

Now that you have configured your configuration, let's build it.

Each configuration has a ThornList which lists the thorns to be compiled in. When this list changes, only those thorns directly affected by the change are recompiled.