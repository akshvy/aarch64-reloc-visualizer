#include <iostream>
#include <iomanip>
#include <bitset>
#include "reloc_engine.hpp"

void display_comparison(std::string label, uint32_t instr) {
    std::cout << std::left << std::setw(10) << label << " | ";
    
    // Hex View (like Rizin)
    std::cout << "Hex: 0x" << std::hex << std::setw(8) << std::setfill('0') << instr << " | ";
    
    // Binary View (for bit-precision)
    std::bitset<32> bits(instr);
    std::cout << "Bin: " << bits << std::dec << std::endl;
}

int main() {
    uint32_t original = 0x90000000; // ADRP X0, 0
    uint64_t delta = 0x2;           // Example page delta
    
    uint32_t patched = RelocationVisualizer::patch_adrp(original, delta);
    
    std::cout << "AArch64 Relocation Patch Visualization\n";
    std::cout << "========================================\n";
    display_comparison("Original", original);
    display_comparison("Patched", patched);
    
    return 0;
}