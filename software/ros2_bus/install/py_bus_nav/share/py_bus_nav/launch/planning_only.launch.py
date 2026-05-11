from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory('py_bus_nav')
    map_file = os.path.join(pkg_share, 'maps', 'empty_map.yaml')
    params_file = os.path.join(pkg_share, 'config', 'nav2_params.yaml')

    lifecycle_nodes = ['map_server', 'planner_server']

    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[
            {'yaml_filename': map_file},
            {'use_sim_time': False}
        ]
    )

    planner_server = Node(
        package='nav2_planner',
        executable='planner_server',
        name='planner_server',
        output='screen',
        parameters=[params_file]
    )

    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_planning',
        output='screen',
        parameters=[
            {'use_sim_time': False},
            {'autostart': True},
            {'node_names': lifecycle_nodes}
        ]
    )


   map_odom_publisher = Node(
       package='tf2_ros',
       executable='static_transform_publisher',
       name='static_transform_publisher_map_odom',
       output='screen',
       arguments=[
            '--x', '0',
            '--y', '0',
            '--z', '0',
            '--yaw', '0',
            '--pitch', '0',
            '--roll', '0',
            '--frame-id', 'map',
            '--child-frame-id', 'odom',
       ]
   )



    return LaunchDescription([
        map_server,
        planner_server,
        lifecycle_manager,
	map_odom_publisher,   
 ])
