import asyncio
import tkinter as tk
from tkinter import messagebox
from bleak import BleakScanner, BleakClient

client = None


async def scan_devices():
    devices = await BleakScanner.discover()
    return devices


# This function is called when the connect button is clicked and handles the connection to the
# selected device from the listbox
async def connect_to_device(address):
    global client
    if client is not None:
        await client.disconnect()
    client = BleakClient(address)
    try:
        await client.connect()
        return True
    except Exception as e:
        print(f"Failed to connect to device: {e}")
        return False


# This function is called when the scan button is clicked and handles the scanning of devices
def handle_scan():
    devices_listbox.delete(0, tk.END)
    devices = asyncio.run(scan_devices())
    for device in devices:
        devices_listbox.insert(tk.END, f"{device.name} - {device.address}")


# This function is called when the connect button is clicked and handles the connection to the
# selected device from the listbox
def handle_connect():
    selected = devices_listbox.curselection()
    if not selected:
        messagebox.showerror("Error", "No device selected")
        return

    device_info = devices_listbox.get(selected[0])
    address = device_info.split(" - ")[1]
    connected = asyncio.run(connect_to_device(address))
    if connected:
        messagebox.showinfo("Success", "Connected to device")
    else:
        messagebox.showerror("Error", "Failed to connect to device")


# Creating the GUI
root = tk.Tk()
root.title("Whims Server")

devices_listbox = tk.Listbox(root, width=50, height=10)
devices_listbox.pack(pady=10)

scan_button = tk.Button(root, text="Scan", command=handle_scan)
scan_button.pack(pady=10)

connect_button = tk.Button(root, text="Connect", command=handle_connect)
connect_button.pack(pady=10)

root.mainloop()
