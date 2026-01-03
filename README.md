# AArch64 Relocation Visualizer

A specialized C++ tool designed to visualize the internal bitwise mechanics of **AArch64 ELF relocations**. Built to bridge the gap between high-level disassembly and low-level binary patching.

## Overview
This tool simulates how a linker or loader patches instructions at runtime. It focuses on the **ARM Architecture Procedure Call Standard (AAPCS64)** to demonstrate how specific relocation types—like `R_AARCH64_ADR_PREL_PG_HI21`—calculate address deltas and apply bitwise masks to instructions without corrupting the opcode.



## Key Features
* **Bit-Level Masking**: Visualizes the split immediate fields (`immlo` and `immhi`) for `ADRP` instructions.
* **Relocation Math**: Implements the standard formula: $Page(S + A) - Page(P)$.
* **Endianness Analysis**: Displays instructions in raw memory format (Little-Endian), providing a direct comparison to tools like **Rizin** and **Ghidra**.
* **Opcode Integrity**: Highlights active bits using custom masks to ensure instruction safety.

## Tech Stack
* **Language**: C++17 (Bitwise manipulation and Pointer casting).
* **Build System**: CMake.
* **Standard**: AAPCS64 (ARM 64-bit Architecture).

## How it Patches
When the tool processes a relocation, it follows these steps:

1. **Calculate Delta**: 
   `Target (0x40001234) >> 12` - `PC (0x40000000) >> 12` = `0x1` (Page Delta).
2. **Bit Splitting**:
   - `immlo`: `0x1 & 0x3` → shifted to bit 29.
   - `immhi`: `(0x1 >> 2)` → shifted to bit 5.
3. **Opcode Preservation**:
   The mask `0x9F00001F` ensures we only overwrite the green 'immediate' bits in the diagram above, leaving the `10010` opcode bits untouched.

## Getting Started

### Prerequisites
* GCC/G++ (version 9+)
* CMake (version 3.10+)


### Building from Source
```bash
mkdir build && cd build
cmake ..
make
./reloc_vis 
```
## AArch64 Relocation Visualizer v1.0
========================================<br>
Original   | Hex: 0x90000000 | Bin: 10010000 00000000 00000000 00000000<br>
Reloc Mask | Hex: 0x60fffe0  | Bin: .^^..... ........ ........ ...^^^^^ <br>
Patched    | Hex: 0xd0000000 | Bin: 11010000 00000000 00000000 00000000<br>

Memory View (Rizin Style):
Byte Order (LE): 00 00 00 90 
Byte Order (LE): 00 00 00 d0


