#ifndef MULTIBOOT_H
#define MULTIBOOT_H

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
};

struct multiboot_info {
    uint32_t total_size;
    uint32_t reserved;
    struct multiboot_tag tags[0];
};

struct multiboot_header {
    uint32_t magic;
    uint32_t architecture;
    uint32_t header_length;
    uint32_t checksum;
} __attribute__((section(".multiboot")));

struct multiboot_elf_symbols {
    uint32_t type; /* 9 */
    uint32_t size;
    uint16_t num;
    uint16_t entsize;
    uint16_t shndx;
    uint16_t reserved;
    char section_headers[];
};

struct multiboot_memory_map {
    uint32_t type; /* 6 */
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    uint8_t entries[];
};

struct multiboot_bootloader_name {
    uint32_t type; /* 2 */
    uint32_t size;
    char string[];
};

struct multiboot_vbe_info {
    uint32_t type; /* 7 */
    uint32_t size; /* 784 */
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint8_t vbe_control_info[512];
    uint8_t vbe_mode_info[256];
};

struct multiboot_framebuffer {
    uint32_t type; /* 8 */
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint8_t reserved;
    uint8_t color_info[];
    uint32_t framebuffer_palette_num_colors;
    uint16_t framebuffer_palette;
    uint8_t red_value;
    uint8_t green_value;
    uint8_t blue_value;
    uint8_t framebuffer_red_field_position;
    uint8_t framebuffer_red_mask_size;
    uint8_t framebuffer_green_field_position;
    uint8_t framebuffer_green_mask_size;
    uint8_t framebuffer_blue_field_position;
    uint8_t framebuffer_blue_mask_size;

};

#endif
