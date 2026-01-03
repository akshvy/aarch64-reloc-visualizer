#ifndef RELOC_ENGINE_HPP
#define RELOC_ENGINE_HPP

#include <cstdint>

class RelocationVisualizer {
public:
    // Core math: Page(S + A) - Page(P)
    static uint64_t calculate_delta(uint64_t S, uint64_t A, uint64_t P);
    
    // Patching: Apply 21-bit mask for ADRP
    static uint32_t patch_adrp(uint32_t instr, uint64_t delta);
};

#endif // RELOC_ENGINE_HPP