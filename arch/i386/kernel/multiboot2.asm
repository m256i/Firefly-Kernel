%ifndef MULTIBOOT2_ASM
%define MULTIBOOT2_ASM

; Magic
%define MULTIBOOT2_HEADER_MAGIC 0xe85250d6

; Tags
%define GRUB_MULTIBOOT_ARCHITECTURE_I386 0
%define MULTIBOOT_HEADER_TAG_END  0
%define MULTIBOOT_HEADER_TAG_OPTIONAL 1
%define MULTIBOOT_HEADER_TAG_FRAMEBUFFER 5
%define MULTIBOOT_HEADER_TAG_OPTIONAL 1
%define MULTIBOOT_HEADER_TAG_ADDRESS 2
%define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS 3


%endif