#ifndef NET_H
#define NET_H

struct net_device {
	char interface_name[32]; /* eth0, wlan0 or lo */
	uint32_t mac_address[6]; /* MAC ADDRESS OF THE DEVICE */
	int flags; /* BITMASK indicating the interface's state (IFF_UP, IFF_PROMISC) */
	int statistics[]; /* Counters for transmitted and received packets, errors, etc. */
	int *private_data; /* Pointer to a private data structure that the driver uses to store its own state */
	int function_pointers[]; /* Set of functions that the network stack can call to interact with the driver */
	void* ndo_open(); /* Called when the interface is brought up (ifup). The driver should allocate resources, enable interrupts, and get the hardware ready for operation */
	void* ndo_stop(); /* Called when the interface is brought down (ifdown). The driver must disable interrupts and free resources. */
	void* ndo_start_xmit(); /* Called by network stack to send a packed. The driver must take the sk_buff and queue it for transmission on the hardware.  */
	void* ndo_set_mac_address(); /* Called when a user wants to change the device's MAC address  */
};

#endif
