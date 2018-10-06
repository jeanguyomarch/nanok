===============================================================================
Introduction
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

Please refer to the :doc:`nanokbs` page.


How to contribute to the development of NanoK?
-------------------------------------------------------------------------------

Please refer to the :doc:`dev` page.


.. _unikernel: https://en.wikipedia.org/wiki/Unikernel
.. _STM32F4-DISCOVERY: https://www.st.com/en/evaluation-tools/stm32f4discovery.html
