from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="cpp_parameters",
            executable="minimal_parameters_node",
            name="custom_minimal_parameters_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"my_parameters": "earth"}
            ]
        )
    ])