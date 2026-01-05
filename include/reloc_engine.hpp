#ifndef RELOC_ENGINE_HPP
#define RELOC_ENGINE_HPP

#include <cstdint>

class RelocationVisualizer {
public:
    // --- ADRP Constants ---
    static constexpr uint32_t ADRP_OPCODE_MASK = 0x9F000000;
    static constexpr uint32_t ADRP_OPCODE_VAL  = 0x90000000;
    static constexpr uint32_t ADRP_IMM_MASK    = 0x9F00001F; // Preserves opcode, clears immediate

    // --- LDR64 (Load Register) Constants ---
    static constexpr uint32_t LDR64_OPCODE_MASK = 0xFFC00000;
    static constexpr uint32_t LDR64_OPCODE_VAL  = 0xF9400000;
    static constexpr uint32_t LDR64_IMM_MASK    = 0xFFC003FF; // Clears bits [21:10]

    // --- Verification Logic ---
    static bool is_adrp(uint32_t instr) {
        return (instr & ADRP_OPCODE_MASK) == ADRP_OPCODE_VAL;
    }

    static bool is_ldr64(uint32_t instr) {
        return (instr & LDR64_OPCODE_MASK) == LDR64_OPCODE_VAL;
    }

    // --- Core Logic Functions ---
    static uint64_t calculate_delta(uint64_t S, uint64_t A, uint64_t P);
    static uint32_t patch_adrp(uint32_t instr, uint64_t delta);
    static uint32_t patch_ldr64_lo12(uint32_t instr, uint64_t address);
};

#endif