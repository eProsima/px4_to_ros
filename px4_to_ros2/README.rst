PX4-FastRTPS-ROS2
=================

This proof of concept aims to extend the `bridge PX4-FastRTPS <https://github.com/eProsima/Firmware.git>`_ to **ROS2** and test how the exchange of information works between nodes of PX4 and ROS2. The PoC has been implemented and tested in a **PIXracer** for the PX4 side and a couple of **PC running Ubuntu 16.04** for the micro RTPS agent and ROS2 node.

The PoC has been performed over a single message, *sensor combined*. At the very beginning the message is received through an uORB subscription in the PX4 side, on the micro RTPS client. Then it's sended through micro RTPS to the DDS world and finally is received by a ROS2 node.

The same path is followed in reverse from ROS2 to PX4.

.. image:: doc/bridge-ROS2.png

Latency test
------------

There is available a latency test to estimate the time taken to get a message to ROS2 from PX4. Please follow the instructions below for each section.

Requierements
-------------

 - PX4-Fast RTPS brigde: it is necessary to work with the `eProsima PX4/Firmware fork <https://github.com/eProsima/Firmware.git>`_, please see the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_
 - Fast RTPS-ROS2: install `ROS2<https://github.com/ros2/ros2/wiki/Linux-Development-Setup>`_ with the latest update of its packages from the master branch of `this repository<https://github.com/ros2/ros2>`_

PX4 side: micro RTPS client
---------------------------

The code of the application that will run in the PX4 side can be found in **microRTPS_client** folder. To use this code, please see the **PX4 Firmware** section in the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_

To perform the latency test please use the **latency/microRTPS_client** folder content instead.

Fast RTPS side: micro RTPS agent
--------------------------------

The code of the application that will run as micro RTPS agent can be found in **microRTPS_agent** folder. To use this code, please see the **Fast RTPS (Raspberry PI application)** section in the `README <https://github.com/eProsima/Firmware/blob/micrortps/README_eprosima.rst>`_

For perform the latency test please use the **latency/microRTPS_agent** folder content instead.

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

If you want to test the latency, run this other node instead of the *sensor_combined_listener*. Note: this application is not printing any information on the screen for performance purposes.

.. code-block:: bash

    . ~/ros2_ws/install/local_setup.bash
    # . ~/ros2_ws/install_isolated/local_setup.bash  # if you built in isolation, use this instead of the above line
    sensor_combined_latency
