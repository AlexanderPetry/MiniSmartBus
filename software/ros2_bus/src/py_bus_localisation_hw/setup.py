from setuptools import find_packages, setup

package_name = 'py_bus_localisation_hw'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    package_data={'': ['py.typed']},
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='admin',
    maintainer_email='alexanderpetry2@gmail.com',
    description='TODO: Reading IMU data adn formatting it to ROS2 datatype',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
		'imu_node = py_bus_localisation_hw.imu_node:main',
	        'uwb_node = py_bus_localisation_hw.uwb_node:main',        	
	],
    },
)
