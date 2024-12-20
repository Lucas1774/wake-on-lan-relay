# Wake-On-Lan Relay

This software is designed to be installed on an always-on device, acting as an entry point to your local network. It allows you to wake a device from anywhere in the world.  
This is particularly useful for routers that fail to maintain DHCP leases for powered-off devices, causing port forwarding configurations to stop working and making direct port forward of the device to be waken not possible. On a LAN, Magic Packets are broadcast, bypassing this limitation.

## Installation

- Update the four placeholder constants in the code. The MAC address should match the device you want to wake.  
- Install the software on a device or board with a Wi-Fi adapter, ensuring it stays powered on.  
  - Note: Some devices only support 2.4 GHz Wi-Fi. If your router can split 2.4 and 5 GHz signals, make sure the device connects to the correct one.
- To enable Wake-On-WAN, expose the web server to the internet.  
  - The simplest method is forwarding the server's port (default: `80`).  
  - If your ISP uses CG-NAT, this can block external access. In such cases, consider configuring a VPN in your device to tunnel into your local network.
- Configure a DHCP lease in your router for the device running this software to ensure it retains a static local IP.
- Wi-Fi adapters often shut down with their host devices. If this happens, the target device will need an Ethernet connection to the LAN to receive Magic Packets.
- Ensure the device you want to wake has proper BIOS and operating system power settings to support Wake-On-LAN. Incorrect settings can block Magic Packets or prevent wake-up.

## Setup Example

I installed this software on an ESP32 chip, powered by the same PSU that powers my PC, using a USB port on the motherboard.  
I'm encrypting the server endpoint as a very basic but effective security measure.  
I port-forwarded the web server through my router settings, and created a DHCP lease so it keeps its local IP address consistent.  
If your ISP gives you a dynamic IP address, you can use a DDNS to keep the URL of your device consistent.  

### Wake on WAN after power cut

A power cut can interfere with this setup in two different ways:
- When power comes back, your ISP will most likely assign your router a new public IP address. There are a couple of options to have this not matter:
  - Make sure you can access the network interface of a device in the LAN, for example, with a VPN in an always-on device, to retrieve the new IP.
  - Use a DDNS with a script to keep the domain name link updated, even if the device that runs the script (on boot, for example, when the power comes back) turns itself off after the fact.
- In the specific case that your always-on-device is plugged into a PC motherboard, it is likely that it won't be powered up until the PC is turned on at least once. Some BIOS allow to automatically turn the device on after a power shortage. It is possible to combine this with a script or setting to shut down after.  
