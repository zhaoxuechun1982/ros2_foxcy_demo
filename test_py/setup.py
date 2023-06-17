from setuptools import setup

package_name = 'test_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jimmy',
    maintainer_email='zhaoxuechun1982@sina.com',
    description='Demo of testing in cpp',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'demo = test_py.demo:main',
        ],
    },
)
