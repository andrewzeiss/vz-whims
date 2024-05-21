"""
Failed to build pybluez
Installing collected packages: pyobjc-core, pyobjc-framework-Cocoa, pybluez
    Running setup.py install for pybluez ... done
  DEPRECATION: pybluez was installed using the legacy 'setup.py install' method, because a wheel could not be built for it. A possible replacement is to fix the wheel build issue reported above. You can find discussion regarding this at https://github.com/pypa/pip/issues/8368.
"""

import bluetooth

nearby_devices = bluetooth.discover_devices(lookup_names=True)
for addr, name in nearby_devices:
    print(f"Address: {addr}, Name: {name}")
