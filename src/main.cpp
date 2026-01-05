#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include "reloc_engine.hpp"

// Utility to print binary and hex (Existing)
void display_comparison(std::string label, uint32_t instr) {
    std::cout << std::left << std::setw(12) << label << " | ";
    std::cout << "Hex: 0x" << std::hex << std::setw(8) << std::setfill('0') << instr << " | ";
    std::cout << "Bin: ";
    for (int i = 31; i >= 0; i--) {
        std::cout << ((instr >> i) & 1);
        if (i % 8 == 0 && i != 0) std::cout << " ";
    }
    std::cout << std::dec << std::endl;
}

// Step 3: Bit-Diff Visualizer
// This function compares two instructions and marks the changed bits with '|'
void display_bit_diff(uint32_t original, uint32_t patched) {
    std::cout << std::left << std::setw(12) << "Bit Change" << " | ";
    std::cout << std::string(17, ' ') << " | Bin: "; // Space to align with 'Bin:'
    
    for (int i = 31; i >= 0; i--) {
        bool bit_orig = (original >> i) & 1;
        bool bit_patch = (patched >> i) & 1;
        
        if (bit_orig != bit_patch) {
            std::cout << "|"; // Mark changed bit
        } else {
            std::cout << "."; // No change
        }
        if (i % 8 == 0 && i != 0) std::cout << " ";
    }
    std::cout << std::endl;
}

void display_byte_view(uint32_t instr) {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&instr);
    std::cout << "Byte Order (LE): ";
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    // Shared Test Data
    uint64_t target_addr = 0x40001238; 
    uint64_t pc = 0x40000000;          

    std::cout << "AArch64 Relocation Visualizer v1.0\n";
    std::cout << "========================================\n\n";

    // --- CASE 1: ADRP (Page Relocation) ---
    uint32_t adrp_orig = 0x90000000; // ADRP X0, 0
    uint64_t adrp_delta = RelocationVisualizer::calculate_delta(target_addr, 0, pc);
    uint32_t adrp_patch = RelocationVisualizer::patch_adrp(adrp_orig, adrp_delta);

    std::cout << "[1] ADRP Page Patching\n";
    display_comparison("Original", adrp_orig);
    display_comparison("Patched", adrp_patch);
    display_bit_diff(adrp_orig, adrp_patch); // Shows only immediate bits changed
    display_byte_view(adrp_patch);
    std::cout << "----------------------------------------\n\n";

    // --- CASE 2: LDR LO12 (Offset Relocation) ---
    uint32_t ldr_orig = 0xF9400000; // LDR X0, [X0]
    uint32_t ldr_patch = RelocationVisualizer::patch_ldr64_lo12(ldr_orig, target_addr);

    std::cout << "[2] LDR LO12 Offset Patching\n";
    display_comparison("Original", ldr_orig);
    display_comparison("Patched", ldr_patch);
    display_bit_diff(ldr_orig, ldr_patch); // Visualizes the scaled immediate shift
    display_byte_view(ldr_patch);
    
    return 0;
}