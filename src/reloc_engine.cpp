#include "reloc_engine.hpp"
#include <stdexcept>

// 1. Calculate Page Delta for ADRP
uint64_t RelocationVisualizer::calculate_delta(uint64_t S, uint64_t A, uint64_t P) {
    uint64_t target_page = (S + A) >> 12;
    uint64_t place_page = P >> 12;
    return target_page - place_page;
}

// 2. Patch ADRP Instruction
uint32_t RelocationVisualizer::patch_adrp(uint32_t instr, uint64_t delta) {
    if (!is_adrp(instr)) {
        throw std::invalid_argument("Provided instruction is not a valid AArch64 ADRP opcode.");
    }

    // Split 21-bit delta into immlo [30:29] and immhi [23:5]
    uint32_t immlo = (delta & 0x3) << 29;
    uint32_t immhi = ((delta >> 2) & 0x7FFFF) << 5;
    
    return (instr & ADRP_IMM_MASK) | immlo | immhi;
}

// 3. Patch LDR (Load Register) 64-bit Offset
uint32_t RelocationVisualizer::patch_ldr64_lo12(uint32_t instr, uint64_t address) {
    if (!is_ldr64(instr)) {
        throw std::invalid_argument("Instruction is not a valid AArch64 LDR (unsigned offset) opcode.");
    }

    // AArch64 LDR (Unsigned Immediate) stores the offset scaled by size
    // For 64-bit (8 bytes), we store (Offset / 8)
    uint64_t offset = address & 0xFFF; // Extract lower 12 bits
    uint32_t scaled_offset = static_cast<uint32_t>(offset >> 3); // Divide by 8
    
    // Insert scaled offset into bits [21:10]
    return (instr & LDR64_IMM_MASK) | (scaled_offset << 10);
}