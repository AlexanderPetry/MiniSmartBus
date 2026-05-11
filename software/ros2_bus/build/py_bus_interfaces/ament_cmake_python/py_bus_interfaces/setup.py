from setuptools import find_packages
from setuptools import setup

setup(
    name='py_bus_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('py_bus_interfaces', 'py_bus_interfaces.*')),
)
