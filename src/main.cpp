#include <iostream>
#include <iomanip>
#include <bitset>
#include "reloc_engine.hpp"

void display_comparison(std::string label, uint32_t instr) {
    // Fix the label width for alignment
    std::cout << std::left << std::setw(10) << label << " | ";
    
    // Hex View (Professional 0x prefix)
    std::cout << "Hex: 0x" << std::hex << std::setw(8) << std::setfill('0') << instr << " | ";
    
    // Binary View with bit grouping (for readability)
    std::cout << "Bin: ";
    for (int i = 31; i >= 0; i--) {
        std::cout << ((instr >> i) & 1);
        if (i % 8 == 0 && i != 0) std::cout << " "; // Space every 8 bits
    }
    std::cout << std::dec << std::endl;
}

void display_byte_view(uint32_t instr) {
    // Treat the 32-bit int as an array of 4 individual bytes
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&instr);
    
    std::cout << "Byte Order (LE): ";
    for (int i = 0; i < 4; ++i) {
        // Output each byte in hex with a space
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    uint32_t original = 0x90000000; 
    uint64_t delta = 0x2;           
    
    uint32_t patched = RelocationVisualizer::patch_adrp(original, delta);
    
    std::cout << "AArch64 Relocation Patch Visualization\n";
    std::cout << "========================================\n";
    
    display_comparison("Original", original);
    display_byte_view(original);
    
    std::cout << "----------------------------------------\n";
    
    display_comparison("Patched", patched);
    display_byte_view(patched);
    
    return 0;
}