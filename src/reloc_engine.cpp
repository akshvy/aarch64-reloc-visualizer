#include "reloc_engine.hpp"

uint64_t RelocationVisualizer::calculate_delta(uint64_t S, uint64_t A, uint64_t P) {
    uint64_t target_page = (S + A) >> 12;
    uint64_t place_page = P >> 12;
    return target_page - place_page;
}

uint32_t RelocationVisualizer::patch_adrp(uint32_t instr, uint64_t delta) {
    // ADRP immlo is bits [30:29], immhi is bits [23:5]
    uint32_t immlo = (delta & 0x3) << 29;
    uint32_t immhi = ((delta >> 2) & 0x7FFFF) << 5;
    
    // 0x9F00001F keeps the ADRP opcode but clears the immediate bits
    uint32_t mask = 0x9F00001F; 
    return (instr & mask) | immlo | immhi;
}