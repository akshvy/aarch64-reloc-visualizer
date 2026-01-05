#include "reloc_engine.hpp"
#include <stdexcept>

uint64_t RelocationVisualizer::calculate_delta(uint64_t S, uint64_t A, uint64_t P) {
    uint64_t target_page = (S + A) >> 12;
    uint64_t place_page = P >> 12;
    return target_page - place_page;
}

uint32_t RelocationVisualizer::patch_adrp(uint32_t instr, uint64_t delta) {
    // New Professional Check: Verify it's an ADRP instruction
    if (!is_adrp(instr)) {
        throw std::invalid_argument("Provided instruction is not a valid AArch64 ADRP opcode.");
    }

    uint32_t immlo = (delta & 0x3) << 29;
    uint32_t immhi = ((delta >> 2) & 0x7FFFF) << 5;
    
    return (instr & ADRP_IMM_MASK) | immlo | immhi;
}
uint32_t RelocationVisualizer::patch_ldr64_lo12(uint32_t instr, uint64_t address) {
    // 1. Calculate the 12-bit offset
    uint64_t offset = address & 0xFFF;
    
    // 2. Scale the offset for LDR (64-bit uses 8-byte alignment)
    uint32_t scaled_offset = static_cast<uint32_t>(offset >> 3);
    
    // 3. Apply the mask and insert the scaled offset into bits [21:10]
    return (instr & LDR64_MASK) | (scaled_offset << 10);
}

uint32_t RelocationVisualizer::patch_ldr64_lo12(uint32_t instr, uint64_t address) {
    if (!is_ldr64(instr)) {
        throw std::invalid_argument("Instruction is not a valid AArch64 LDR (unsigned offset) opcode.");
    }

    // 1. Get the lower 12 bits (page offset)
    uint64_t offset = address & 0xFFF; 
    
    // 2. Scale for 8-byte alignment (LDR Xn, [Xm, #imm])
    // The immediate stored is actually offset / 8
    uint32_t scaled_offset = static_cast<uint32_t>(offset >> 3);
    
    // 3. Insert scaled offset into bits [21:10]
    return (instr & LDR64_IMM_MASK) | (scaled_offset << 10);
}