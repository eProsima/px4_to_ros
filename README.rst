PX4-FastRTPS-ROS2
=================

This is a proof of concept aims to extend the `bridge PX4-FastRTPS <https://github.com/eProsima/Firmware.git>`_ to **ROS2** and test how the exchange of information works between nodes of PX4 and ROS2. The PoC has been implemented and tested in a **PIXracer** for the PX4 side and a couple of **PC running Ubuntu 16.04** for micro RTPS agent and the ROS2 node.

The PoC has been performed over a single message *sensor combined*. At the very beginning the message is received throuhg a uORB subscription in the PX4 side, on the micro RTPS client. Them it's sended through micro RTPS to the DDS world and finally is listened into a ROS2 node.

The same path is followed in reverse from ROS2 to PX4.

.. image:: doc/bridge-ROS2.png

Requierements
-------------

 - PX4-Fast RTPS brigde: its necessary work with the `eProsima PX4/Firmware fork <https://github.com/eProsima/Firmware.git>`_, please see the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_
 - Fast RTPS-ROS2: Install `ROS2<https://github.com/ros2/ros2/wiki/Linux-Development-Setup>`_ with the latest update of its packages from the master branch of `this repository<https://github.com/ros2/ros2>`_

PX4 side
--------

The code of the application that will run in to PX4 side will be founded in **microRTPS_client** folder. To use this code, please see the **PX4 Firmware** section in the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_

ROS2 side
---------

In order to run the ROS2 receiver node, you have to add two packages to your ROS2 worskpace. The package **px4_msgs** generates all the PX4 messages that are actually supported. The other package, **sensor_combined_listener**, contains a demo node which reads a message sent from PX4 through the microRTPS agent.

Compile the packages with ament using:

.. code-block:: bash

    ament build --symlink-install --only px4_msgs
    ament build --symlink-install --only sensor_combined_listener

Now, you can run the receiver application with:

.. code-block:: bash

    . ~/ros2_ws/install/local_setup.bash
    # . ~/ros2_ws/install_isolated/local_setup.bash  # if you built in isolation, use this instead of the above line
    sensor_combined_listener
