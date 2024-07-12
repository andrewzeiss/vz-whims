import asyncio
import tkinter as tk
import datetime
from bleak import BleakScanner, BleakClient
from PIL import Image, ImageTk


haptic_uuid = '0000ffe1-0000-1000-8000-00805f9b34fb'

haptic_on = bytearray([0x01])


def get_timestamp():
    return datetime.datetime.now().strftime("[%H:%M:%S] ")


class BLEManager:
    def __init__(self, name):
        self.name = name
        self.client = None

    async def connect(self):
        self.client = BleakClient(self.name)
        await self.client.connect()

    async def send_haptic(self):
        if self.client and self.client.is_connected:
            await self.client.write_gatt_char(haptic_uuid, haptic_on)

    async def disconnect(self):
        if self.client:
            await self.client.disconnect()
            self.client = None


class App:
    def __init__(self, root, name):
        self.root = root
        self.ble_manager = BLEManager(name)

        self.image = Image.open("chrome.png")
        # not sure why LANCZOS is not defined but it works
        self.resized_image = self.image.resize((600, 300), Image.LANCZOS)
        self.chrome_img = ImageTk.PhotoImage(self.resized_image)
        # same here, not sure why there is an error, but it works
        self.chrome_label = tk.Label(self.root, image=self.chrome_img)
        self.chrome_label.pack(pady=10)

        self.status_box = tk.Listbox(self.root, width=60, height=15)
        self.status_box.pack(pady=10)

        self.connect_button = tk.Button(self.root, text="Connect", command=self.connect_to_arduino)
        self.connect_button.pack(pady=10)

        self.send_haptic_button = tk.Button(self.root, text="Send Haptic", command=self.send_haptic)
        self.send_haptic_button.pack(pady=10)

        self.disconnect_button = tk.Button(self.root, text="Disconnect", command=self.disconnect_from_arduino)
        self.disconnect_button.pack(pady=10)

    def connect_to_arduino(self):
        asyncio.run(self.ble_manager.connect())
        self.status_box.insert(tk.END, get_timestamp() + "Connected to Arduino!")

    def send_haptic(self):
        asyncio.run(self.ble_manager.send_haptic())
        self.status_box.insert(tk.END, get_timestamp() + "Sent haptic!")

    def disconnect_from_arduino(self):
        asyncio.run(self.ble_manager.disconnect())
        self.status_box.insert(tk.END, get_timestamp() + "Disconnected from Arduino!")


if __name__ == "__main__":
    root = tk.Tk()
    root.title("WHIMS Server")
    app = App(root, "Arduino")
    root.mainloop()

#
# async def run():
#     status_box.insert(tk.END, get_timestamp() + "Looking for Arduino...")
#     found = False
#     devices = await BleakScanner.discover()
#     for d in devices:
#         if d.name is None:
#             continue
#         elif "Arduino" in d.name:
#             status_box.insert(tk.END, get_timestamp() + "Arduino found!")
#             found = True
#             async with BleakClient(d.address) as client:
#                 status_box.insert(tk.END, get_timestamp() + "Connected to Arduino!")
#                 await client.write_gatt_char(haptic_uuid, haptic_on)
#
#
# def handle_run():
#     loop = asyncio.get_event_loop()
#     if loop.is_running():
#         loop.create_task(run())
#     else:
#         loop.run_until_complete(run())

#
# # Creating the GUI
# root = tk.Tk()
# root.title("WHIMS Server")
# image = Image.open("chrome.png")
# # not sure why LANCZOS is not defined but it works
# resized_image = image.resize((600, 300), Image.LANCZOS)
# chrome_img = ImageTk.PhotoImage(resized_image)
# # same here, not sure why there is an error, but it works
# chrome_label = tk.Label(root, image=chrome_img)
# chrome_label.pack(pady=10)
#
# status_box = tk.Listbox(root, width=60, height=15)
# status_box.pack(pady=10)
#
# start_button = tk.Button(root, text="Start", command=handle_run)
# start_button.pack(pady=10)
#
# root.mainloop()
