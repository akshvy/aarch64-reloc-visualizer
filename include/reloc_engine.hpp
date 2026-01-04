#ifndef RELOC_ENGINE_HPP
#define RELOC_ENGINE_HPP

#include <cstdint>

class RelocationVisualizer {
public:
    // AArch64 ADRP specific constants
    static constexpr uint32_t ADRP_OPCODE_MASK = 0x9F000000;
    static constexpr uint32_t ADRP_OPCODE_VAL  = 0x90000000;
    static constexpr uint32_t ADRP_IMM_MASK    = 0x9F00001F; // Preserves opcode, clears immediate

    // Verification Logic
    static bool is_adrp(uint32_t instr) {
        return (instr & ADRP_OPCODE_MASK) == ADRP_OPCODE_VAL;
    }

    static uint64_t calculate_delta(uint64_t S, uint64_t A, uint64_t P);
    static uint32_t patch_adrp(uint32_t instr, uint64_t delta);
};

#endif