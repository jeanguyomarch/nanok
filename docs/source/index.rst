===============================================================================
NanoK Documentation
===============================================================================

.. contents::


What is NanoK?
-------------------------------------------------------------------------------

NanoK is a nanoscopic kernel for micro-controllers. It aims at providing an
efficient runtime tasks abstraction for hardware that does not come with many
resources. It is not a standalone kernel: it must be compiled with the
application that will run on the selected hardware. This allows the kernel to
be tuned finely for a given usage. As such, NanoK can be seen as a `unikernel`_


What hardware does NanoK support?
-------------------------------------------------------------------------------

.. WARNING::

   NanoK is still in an omega development phase. It is highly experimental and
   shall not be used for anything but its own development.

* `STM32F4-DISCOVERY`_: ST's discovery board with an STM324f variant.


How to build NanoK?
-------------------------------------------------------------------------------

As stated earlier, NanoK must be compiled with the application that will run on
the targeted hardware. As such, NanoK's build shall be driven by the
application. Given this requirement, NanoK should not be built on its own. So,
NanoK does not provide a build system out-of-the-box. This may seem shocking at
first, but this allows an more in-depth integration with the application. Third
parties will be able to tweak NanoK more easily.

Instead, NanoK provides an exhaustive and comprehensive **description of its
sources**, as well as a small (python3) script ``nanokbs`` that allows to
generate a build sytem from an input template file. Third-parties will be able
to write the template that better suit their needs. A basic `ninja`_ build
template is provided by NanoK for its testing. It can be used as an example.


How to contribute to the development of NanoK?
-------------------------------------------------------------------------------

Please refer to the :doc:`dev` page.


.. toctree::
   dev
   unit

.. _unikernel: https://en.wikipedia.org/wiki/Unikernel
.. _STM32F4-DISCOVERY: https://www.st.com/en/evaluation-tools/stm32f4discovery.html
.. _ninja: https://ninja-build.org
