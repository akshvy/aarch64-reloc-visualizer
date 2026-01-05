#include "reloc_engine.hpp"
#include <stdexcept>

uint64_t RelocationVisualizer::calculate_delta(uint64_t S, uint64_t A, uint64_t P) {
    uint64_t target_page = (S + A) >> 12;
    uint64_t place_page = P >> 12;
    return target_page - place_page;
}

uint32_t RelocationVisualizer::patch_ldr64_lo12(uint32_t instr, uint64_t address) {
    // 1. Calculate the 12-bit offset
    uint64_t offset = address & 0xFFF;
    
    // 2. Scale the offset for LDR (64-bit uses 8-byte alignment)
    uint32_t scaled_offset = static_cast<uint32_t>(offset >> 3);
    
    // 3. Apply the mask and insert the scaled offset into bits [21:10]
    return (instr & LDR64_MASK) | (scaled_offset << 10);
}