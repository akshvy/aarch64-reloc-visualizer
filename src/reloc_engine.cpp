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