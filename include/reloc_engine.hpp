#ifndef RELOC_ENGINE_HPP
#define RELOC_ENGINE_HPP

#include <cstdint>

class RelocationVisualizer {
public:
    // AArch64 ADRP specific constants
    static constexpr uint32_t ADRP_OPCODE_MASK = 0x9F000000;
    static constexpr uint32_t ADRP_OPCODE_VAL  = 0x90000000;
    static constexpr uint32_t ADRP_IMM_MASK    = 0x9F00001F; // Preserves opcode, clears immediate

    // Inside class RelocationVisualizer
    static constexpr uint32_t LDR64_MASK = 0xFFC003FF; // Clears the 12-bit immediate field
    static constexpr uint32_t LDR64_OPCODE_VAL = 0xF9400000; // Base for LDR (unsigned offset)
    static uint32_t patch_ldr64_lo12(uint32_t instr, uint64_t address);

    // Verification Logic
    static bool is_adrp(uint32_t instr) {
        return (instr & ADRP_OPCODE_MASK) == ADRP_OPCODE_VAL;
    }

    static uint64_t calculate_delta(uint64_t S, uint64_t A, uint64_t P);
    static uint32_t patch_adrp(uint32_t instr, uint64_t delta);

    // Inside class RelocationVisualizer
    static constexpr uint32_t LDR64_IMM_MASK = 0xFFC003FF; // Clears bits [21:10]
    static constexpr uint32_t LDR64_OPCODE_MASK = 0xFFC00000;
    static constexpr uint32_t LDR64_OPCODE_VAL  = 0xF9400000;

    // New verification check
    static bool is_ldr64(uint32_t instr) {
      return (instr & LDR64_OPCODE_MASK) == LDR64_OPCODE_VAL;
   }

    static uint32_t patch_ldr64_lo12(uint32_t instr, uint64_t address);
    };

#endif