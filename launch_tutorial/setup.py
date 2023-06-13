import os
from glob import glob
from setuptools import setup

package_name = 'launch_tutorial'

setup(
    name=package_name,
    version='0.0.2',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        #(os.path.join('share', package_name, 'launch'), 
        #   glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
        (os.path.join('share', package_name, 'launch'),
           glob(os.path.join('launch', '*.launch.py'))),
        (os.path.join('share', package_name, 'config'),
           glob(os.path.join('config', '*.yaml'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jimmy',
    maintainer_email='zhaoxuechun1982@sina.com',
    description='Example of python launch using substitutions, event handles and manageing large projects',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
