===============================================================================
NanoK Development
===============================================================================

Installing the build dependencies
-------------------------------------------------------------------------------

NanoK requires python3 (probably at least 3.4, but this was not tested so
earlier python3 versions may work). It relies on the `hjson`_ and `jinja2`_
packages. Assuming that ``pip3`` is your pip program for python3, run the
following to install the python dependencies for the current user:

.. code:: sh

   pip3 install --user -r env/requirements.txt

Then, you need to install the following programs:

* `ninja`_: the fast incremental and parallel build-system;
* `gcc`_: the GNU Compiler Collection with **C11** support;
* `diff`_: to compare files.

You can install the right packages using this one-liner, depending on your
GNU/Linux distribution. It must be run from the top-source directory of NanoK:

+---------------+------------------------------------------------------------+
| Distribution  | Command                                                    |
+===============+============================================================+
| Debian/Ubuntu | ``cat env/debian_packages.txt | xargs sudo apt install``   |
+---------------+------------------------------------------------------------+

If you plan to develop for the STM32f4 platform, you will need to install the
following tools:

* the ``arm-none-eabi-`` GCC toolchain. You may find it `here
  <https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads>`_;
* the `st-link`_ utility, to flash and debug your applications on the hardware
  target.

See :file:`scripts/gen-disco.sh` to have an idea of the build and installation
procedure of these tools.


Building the Core Unit Tests
-------------------------------------------------------------------------------

The core services provided by NanoK are written in a platform-agnostic module.
This allows them to be tested on a Linux-hosted platform, so the underlying
logic of NanoK can be unit-tested without the burden of maintaining hardware
tests. As such, NanoK is first developed on a Linux-hosted platform, and then
implemented on a physical platform.

You should first make sure you are able to compile and run the core test suite
on a Linux platform. First generate the appropriate build system, then use the
generated ``build.ninja`` to perform the tasks. Assuming a POSIX shell, run the
following:

.. code:: sh

   sh ./scripts/gen-unit-tests.sh
   ninja check


To better understand what the tests do, and how to maintain them, please refer
to the :doc:`unit` page.


Developping on the STM32f4
-------------------------------------------------------------------------------

As previously mentioned, you will need the install the `st-link`_ utility. Run
the following:

.. code:: sh

   git clone https://github.com/texane/stlink.git
   make -C stlink release
   sudo make -C stlink/build/Release install


Note that this will install ``st-link`` on your system. This is required
because udev rules are distributed.

Then, run the following to compile, flash and start to run the test application:

.. code:: sh

   ./scripts/gen-disco.sh
   ninja gdb-test-run

This will compile the application and uploaded through a GDB server interface.
You can now drive the application:

.. code:: gdb

   load
   continue


Development Workflow
-------------------------------------------------------------------------------

NanoK is hosted on `GitHub <https://github.com/jeanguyomarch/nanok>`_, and
`git`_ is the source control management software used for its development.

The branch ``master`` is the stable development branch. All work shall be done
in branches. When a feature, bugfix or any other kind of modification to the
sources of NanoK is ready, a `pull request
<https://services.github.com/on-demand/github-cli/open-pull-request-github>`_
shall be initiated with the ``master`` branch as being the destination. The
commits will be rebased onto ``master`` and submitted to the `continuous
integration server <https://travis-ci.org/jeanguyomarch/nanok>`_. Once all the
tests pass, the pull request containing your changes will be rebased onto
``master``.


Coding Guidelines
-------------------------------------------------------------------------------

NanoK is written in C11 with GNU extensions.

.. todo


.. _hjson: https://pypi.org/project/hjson/
.. _jinja2: https://pypi.org/project/Jinja2/
.. _ninja: https://ninja-build.org
.. _gcc: https://www.gnu.org/software/gcc/
.. _diff: https://www.gnu.org/software/diffutils/
.. _st-link: https://github.com/texane/stlink.git
.. _git: https://git-scm.com/
