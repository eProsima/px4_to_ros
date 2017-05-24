PX4-FastRTPS-ROS2
=================

This is a proof of concept aims to extend the `bridge PX4-FastRTPS <https://github.com/eProsima/Firmware.git>`_ to **ROS2** and test how the exchange of information works between nodes of PX4 and ROS2. The PoC has been implemented and tested in a **PIXracer** for the PX4 side and a couple of **PC running Ubuntu 16.04** for micro RTPS agent and the ROS2 node.

The PoC has been performed over a single message *sensor combined*. At the very beginning the message is received throuhg a uORB subscription in the PX4 side, on the micro RTPS client. Them it's sended through micro RTPS to the DDS world and finally is listened into a ROS2 node.

The same path is followed in reverse from ROS2 to PX4.

.. image:: doc/bridge-ROS2.png

Latency test
------------

It's available a latency test to estimate the time taken to get a message to ROS2 from PX4. Please follow the instructions bellow for eaach section.

Requierements
-------------

 - PX4-Fast RTPS brigde: its necessary work with the `eProsima PX4/Firmware fork <https://github.com/eProsima/Firmware.git>`_, please see the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_
 - Fast RTPS-ROS2: ++JAVIER++

PX4 side: micro RTPS client
---------------------------

The code of the application that will run in to PX4 side will be found in **microRTPS_client** folder. To use this code, please see the **PX4 Firmware** section in the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_

For perform the latency test please use the **latency/microRTPS_client** folder content instead.

Fast RTPS side: micro RTPS agent
--------------------------------

The code of the application that will run as micro RTPS agent will be found in **microRTPS_agent** folder. To use this code, please see the **Fast RTPS (Raspberry PI application)** section in the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_

For perform the latency test please use the **latency/microRTPS_agent** folder content instead.
