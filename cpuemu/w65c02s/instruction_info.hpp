#ifndef CPUEMU__W65C02S__INSTRUCTION_INFO_HPP
#define CPUEMU__W65C02S__INSTRUCTION_INFO_HPP

#include <map>
#include <string>

#include <common/types.hpp>

#include "instruction.hpp"

namespace emu::w65c02s
{

struct InstructionInfo
{
    // Minimum number of cycles the instruction will take to complete
    const Byte minCycleCost;
    // Maximum number of cycles the instruction will take to complete
    const Byte maxCycleCost;
    // Number of bytes used by the instruction in the program sequence
    const Byte instructionLength;
    // Human-readable name of the opcode for the instruction
    const std::string name;
};

const std::map<Instruction, InstructionInfo> InstructionInfoData = {
    // Instruction              // Min cost // Max cost // Size // Name
    {Instruction::ADC_IMM,      {2,         3,          2,      "ADC #"         }},
<<<<<<< HEAD
    {Instruction::ADC_ZP,       {3,         4,          2,      "ADC zp"        }},
    {Instruction::ADC_ZP_X,     {4,         5,          2,      "ADC zp,X"      }},
    {Instruction::ADC_ABS,      {4,         5,          3,      "ADC a"         }},
    {Instruction::ADC_ABS_X,    {4,         6,          3,      "ADC a,X"       }},
    {Instruction::ADC_ABS_Y,    {4,         6,          3,      "ADC a,Y"       }},
    {Instruction::ADC_ZP_IND,   {5,         6,          2,      "ADC (zp)"      }},
    {Instruction::ADC_ZP_X_IND, {6,         7,          2,      "ADC (zp,X)"    }},
    {Instruction::ADC_ZP_IND_Y, {5,         7,          2,      "ADC (zp),Y"    }},
    {Instruction::AND_IMM,      {2,         2,          2,      "AND #"         }},
    {Instruction::AND_ZP,       {3,         3,          2,      "AND zp"        }},
    {Instruction::AND_ZP_X,     {4,         4,          2,      "AND zp,X"      }},
    {Instruction::AND_ABS,      {4,         4,          3,      "AND a"         }},
    {Instruction::AND_ABS_X,    {4,         5,          3,      "AND a,X"       }},
    {Instruction::AND_ABS_Y,    {4,         5,          3,      "AND a,Y"       }},
    {Instruction::AND_ZP_IND,   {5,         5,          2,      "AND (zp)"      }},
    {Instruction::AND_ZP_X_IND, {6,         6,          2,      "AND (zp,X)"    }},
    {Instruction::AND_ZP_IND_Y, {5,         6,          2,      "AND (zp),Y"    }},
    {Instruction::LDA_IMM,      {2,         2,          2,      "LDA #"         }},
    {Instruction::LDX_IMM,      {2,         2,          2,      "LDX #"         }},
    {Instruction::LDY_IMM,      {2,         2,          2,      "LDY #"         }},
    {Instruction::SED,          {2,         2,          1,      "SED"           }},
    {Instruction::CLD,          {2,         2,          1,      "CLD"           }},
=======
    {Instruction::ADC_ABS,      {4,         5,          3,      "ADC a"         }},
    {Instruction::ADC_ABS_X,    {4,         6,          3,      "ADC a,X"       }},
    {Instruction::ADC_ABS_Y,    {4,         6,          3,      "ADC a,Y"       }},
    {Instruction::ADC_ZP,       {3,         4,          2,      "ADC zp"        }},
    {Instruction::ADC_ZP_IND,   {5,         6,          2,      "ADC (zp)"      }},
    {Instruction::ADC_ZP_X,     {4,         5,          2,      "ADC zp,X"      }},
    {Instruction::ADC_ZP_X_IND, {6,         7,          2,      "ADC (zp,X)"    }},
    {Instruction::ADC_ZP_IND_Y, {5,         7,          2,      "ADC (zp),Y"    }},
    {Instruction::AND_IMM,      {2,         3,          2,      "AND #"         }},
    {Instruction::AND_ABS,      {4,         5,          3,      "AND a"         }},
    {Instruction::AND_ABS_X,    {4,         6,          3,      "AND a,X"       }},
    {Instruction::AND_ABS_Y,    {4,         6,          3,      "AND a,Y"       }},
    {Instruction::AND_ZP,       {3,         4,          2,      "AND zp"        }},
    {Instruction::AND_ZP_IND,   {5,         6,          2,      "AND (zp)"      }},
    {Instruction::AND_ZP_X,     {4,         5,          2,      "AND zp,X"      }},
    {Instruction::AND_ZP_X_IND, {6,         7,          2,      "AND (zp,X)"    }},
    {Instruction::AND_ZP_IND_Y, {5,         7,          2,      "AND (zp),Y"    }},
    {Instruction::LDA_IMM,      {2,         2,          2,      "LDA #"         }},
    {Instruction::LDX_IMM,      {2,         2,          2,      "LDX #"         }},
    {Instruction::LDY_IMM,      {2,         2,          2,      "LDY #"         }},
>>>>>>> 062dc59ed7d23f89192f71d9cae0ddf59c003d66
};

}

#endif//CPUEMU__W65C02S__INSTRUCTION_INFO_HPP