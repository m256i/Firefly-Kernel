#include <cstdlib/stdio.h>
#include <stl/array.h>
#include <x86_64/libk++/ios.h>
#include <x86_64/libk++/iostream.h>

#include <x86_64/drivers/ps2.hpp>
#include <x86_64/drivers/serial.hpp>
// #include <x86_64/drivers/vbe.hpp>
#include <x86_64/drivers/vga.hpp>
#include <x86_64/init/init.hpp>
#include <x86_64/int/interrupt.hpp>
#include <x86_64/multiboot2.hpp>

[[maybe_unused]] constexpr short MAJOR_VERSION = 0;
[[maybe_unused]] constexpr short MINOR_VERSION = 0;
constexpr const char *VERSION_STRING = "0.0";

namespace firefly::kernel::main {
firefly::drivers::vga::cursor cout;

firefly::drivers::vga::cursor &internal_cursor_handle() {
    return cout;
}

void write_ff_info() {
    using firefly::drivers::vga::clear;
    clear();
    firefly::kernel::main::cout << "FireflyOS\nVersion: " << VERSION_STRING << "\nContributors:";

    firefly::std::array<const char *, 3> arr = {
        "Lime\t  ", "JohnkaS", "V01D-NULL"
    };

    for (size_t i = 0; i < arr.max_size(); i++) {
        if (i % 2 == 0) {
            firefly::kernel::main::cout << "\n\t";
        }
        firefly::kernel::main::cout << arr[i] << "  ";
    }
    firefly::kernel::main::cout << "\n";
}
}  // namespace firefly::kernel::main

extern "C" [[noreturn]] void kernel_main(uint64_t magic, uint64_t mb2_proto_struct) {
    using firefly::drivers::vga::color;
    using firefly::drivers::vga::cursor;

    firefly::drivers::vga::init();
    firefly::kernel::main::cout = { color::white, color::black, 0, 0 };
    firefly::kernel::main::write_ff_info();
    firefly::drivers::ps2::init();
    firefly::kernel::core::interrupt::init();
    firefly::kernel::kernel_init(magic, mb2_proto_struct);

    firefly::kernel::io::SerialPort port = { firefly::kernel::io::SerialPort::COM1, firefly::kernel::io::SerialPort::BAUD_BASE };
    port.send_chars("Hello world!");

    while (true) {
        auto key = firefly::drivers::ps2::get_scancode();
        if (!key.has_value()) {
            continue;
        }
        firefly::drivers::ps2::handle_input(*key, firefly::libkern::get_cursor_handle());
    }
}
