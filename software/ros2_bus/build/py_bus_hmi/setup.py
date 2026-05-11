from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'py_bus_hmi'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
	(
		os.path.join('share', package_name, 'web'),
		glob('py_bus_hmi/web/*'),
	),
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
		'web_visu_node = py_bus_hmi.web_visu_node:main',
        ],
    },
)
