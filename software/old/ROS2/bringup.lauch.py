from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess


def generate_launch_description():
    nav2_params_file = '/home/admin/ros2_bus/src/py_bus_nav/config/nav2_params.yaml'
    map_yaml_file = '/home/admin/ros2_bus/src/py_bus_nav/maps/empty_map.yaml'

    map_to_odom_broadcaster = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='map_to_odom_broadcaster',
        arguments=[
            '--x', '0', '--y', '0', '--z', '0',
            '--roll', '0', '--pitch', '0', '--yaw', '0',
            '--frame-id', 'map',
            '--child-frame-id', 'odom'
        ],
        output='screen',
    )

    odom_to_base_link_broadcaster = Node(
    package='tf2_ros',
    executable='static_transform_publisher',
    name='odom_to_base_link_broadcaster',
    arguments=[
        '--x', '0', '--y', '0', '--z', '0',
        '--roll', '0', '--pitch', '0', '--yaw', '0',
        '--frame-id', 'odom',
        '--child-frame-id', 'base_link'
    ],
    output='screen',
    )

    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[
            {'yaml_filename': map_yaml_file},
            {'use_sim_time': False}
        ]
    )

    planner_server = Node(
        package='nav2_planner',
        executable='planner_server',
        name='planner_server',
        output='screen',
        parameters=[nav2_params_file]
    )

    controller_server = Node(
        package='nav2_controller',
        executable='controller_server',
        name='controller_server',
        output='screen',
        parameters=[nav2_params_file]
    )

    behavior_server = Node(
        package='nav2_behaviors',
        executable='behavior_server',
        name='behavior_server',
        output='screen',
        parameters=[nav2_params_file]
    )

    bt_navigator = Node(
        package='nav2_bt_navigator',
        executable='bt_navigator',
        name='bt_navigator',
        output='screen',
        parameters=[nav2_params_file]
    )

    smoother_server = Node(
        package='nav2_smoother',
        executable='smoother_server',
        name='smoother_server',
        output='screen',
        parameters=[nav2_params_file]
    )

    lifecycle_manager_navigation = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_navigation',
        output='screen',
        parameters=[{
            'use_sim_time': False,
            'autostart': True,
            'node_names': [
                'map_server',
                'planner_server', 
                'controller_server', 
                'behavior_server', 
                'bt_navigator',
                'smoother_server'
            ]
        }]
    )

    camera_node = Node(
        package='camera_ros',
        executable='camera_node',
        name='camera',
        output='screen',
    )

    object_detection = Node(
        package='py_bus_perception_logic',
        executable='object_detection',
        name='object_detection',
        output='screen',
        parameters=[{
            'image_topic': '/camera/image_raw',
            'model_path': '/home/admin/ros2_bus/src/py_bus_perception_logic/py_bus_perception_logic/models/yolov8n.pt',
            'show_window': False,
        }],
    )

    imu_node = Node(
        package='py_bus_localisation_hw',
        executable='imu_node',
        name='imu_node',
        output='screen',
    )

    uwb_node = Node(
        package='py_bus_localisation_hw',
        executable='uwb_node',
        name='uwb_node',
        output='screen',
    )

    pose_estimator = Node(
        package='py_bus_localisation_logic',
        executable='pose_estimator',
        name='pose_estimator',
        output='screen',
    )

    rosbridge = Node(
        package='rosbridge_server',
        executable='rosbridge_websocket',
        name='rosbridge',
        output='screen',
        parameters=[{'port': 9090}]
    )

    web_visu_node = Node(
        package='py_bus_hmi',
        executable='web_visu_node',
        name='web_visu_node',
        output='screen',
    )

    driver_node = Node(
        package='py_bus_driver',
        executable='driver_node',
        name='driver_node',
        output='screen',
    )

    activate_script = ExecuteProcess(
        cmd=['bash', '-c', '/home/admin/ros2_bus/scripts/activate_nav2.sh'],
        output='screen',
        name='nav2_activation'
    )

    cmd_vel_to_ackermann = Node(
        package='py_bus_driver',
        executable='cmd_vel_to_ackermann',
        name='cmd_vel_to_ackermann',
        output='screen',
        parameters=[{
            'input_topic': '/cmd_vel',
            'input_type': 'twist_stamped',
            'output_topic': '/auto_cmd',
            'wheelbase_m': 0.3,
            'max_speed_kmh': 2.0,
            'max_steering_deg': 30.0,
            'speed_scale': 1.0,
            'deadband_linear': 0.01,
            'deadband_angular': 0.01,
            'publish_debug': True,
        }]
    )

    drive_mode_arbiter = Node(
        package='py_bus_driver',
        executable='drive_mode_arbiter',
        name='drive_mode_arbiter',
        output='screen',
        parameters=[{
            'manual_topic': '/manual_cmd',
            'auto_topic': '/auto_cmd',
            'mode_topic': '/drive_mode',
            'output_topic': '/esp32_cmd',
            'default_mode': 'manual',
            'command_timeout_sec': 0.5,
            'publish_rate_hz': 20.0,
            'publish_debug': True,
        }]
    )

    return LaunchDescription([
        lifecycle_manager_navigation,
        #activate_script,
        map_to_odom_broadcaster,
        odom_to_base_link_broadcaster,
        map_server,
        planner_server,
        controller_server,
        behavior_server,
        bt_navigator,
        smoother_server,
        camera_node,
        object_detection,
        imu_node,
        uwb_node,
        pose_estimator,
        rosbridge,
        web_visu_node,
        driver_node,
        cmd_vel_to_ackermann,
        drive_mode_arbiter,
        
    ])