#ifndef PCI_H
#define PCI_H

#include <stdint.h>
#include <stddef.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC
#define PCI_ALL_BUSES 256

struct pci_device {
	uint32_t vendor;
	uint32_t device;
	uint32_t func;
};

void ScanAllBuses(void);
void checkDevice(uint8_t bus, uint8_t device);
void checkBus(void);
void Pci_To_Pci_Bridge(uint8_t bus, uint8_t device, uint8_t function);

#endif
