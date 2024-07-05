from flask import Flask, jsonify
from bleak import BleakScanner
import asyncio

app = Flask(__name__)


async def scan_devices():
    devices = await BleakScanner.discover()
    device_list = [{'address': device.address, 'name': device.name} for device in devices]
    return device_list


@app.route('/scan')
def scan():
    devices = asyncio.run(scan_devices())
    for device in devices:
        print(f"Discovered device: {device}")
    return jsonify(devices)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
