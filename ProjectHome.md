## Introduction ##

This projects contains modifications to the linux driver of the Ralink USB wireless adapter. In particular it enables injection of frames in monitor mode. The driver should work on all devices that use the RT2870 chipset.

**When injecting the first 6 bytes of the packet are dropped. You must include 6 dummy bytes before each frame you inject.** For example, in scapy you have to use sendp(RadioTap()/"123456"/p) where p is the packet you want to inject. This is ugly, if you have a patch for this feel free to send it.

## Getting Started ##

First download the source:

`hg clone https://rt2870linux.googlecode.com/hg/ rt2870linux`

Enter the directory rt2870linux and type `make` to compile the source. Now plug in the wireless device. Under backtrack 4 the module rt2800usb and rt2800lib will be automatically loaded. These are incorrect and must be removed. You can inspect the relevant loaded modules with the following command: `lsmod | grep rt2`.

You can remove these unwanted modules with the commands: `rmmod rt2800usb` and `rmmod rt2800lib`. For convenience you can blacklist these modules by editing /etc/modprobe.d/blacklist so they will never be loaded automatically.

The driver expect the config file `/etc/Wireless/RT2870STA/RT2870STA.dat` to exists, otherwise it will fair to initialize. Create this file by copying the file `RT2870STA.dat` in the root of the project to `/etc/Wireless/RT2870STA/RT2870STA.dat`.

Now enter `./reload` to load the newly compiled driver. Once this is done you can configure it with the normal ifconfig and iwconfig commands. The name of the device will be `ra0`. To connect to a network use `wpa_passphrase` and `wpa_supplicant`. I have noticed that setting the essid with iwconfig doesn't work properly, however this is not an issue, simply use wpa\_supplicant and it will associate to the network.

Once associated to the wireless network, get an IP address by executing `dhclient ra0` or a similar DHCP client.

## Motivation ##

Belkin N Wireless model F5D8053 v3 is a USB wireless adapter I still have lying around, and one I mainly use to simulate a client machine in an attack scenario. In particular I will connect with this device to the wireless network, and then use the wireless adapter of my laptop to attack the client. In reality both wireless adapters are running on the same computers, which makes testing, executing and debugging attacks easier.

Getting the device to work correctly is not a trivial task, and therefor I'm sharing my knowledge on this subject. Hopefully this will enable you to quickly configure and use the wireless adapter.