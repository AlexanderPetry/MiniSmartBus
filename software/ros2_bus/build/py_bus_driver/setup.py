from setuptools import find_packages, setup

package_name = 'py_bus_driver'

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
    maintainer_email='admin@todo.todo',
    description='TODO: Package description',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
		'driver_node = py_bus_driver.driver_node:main',
		'cmd_vel_to_ackermann = py_bus_driver.cmd_vel_to_ackermann:main',
		'drive_mode_arbiter = py_bus_driver.drive_mode_arbiter:main',
        ],
    },
)
