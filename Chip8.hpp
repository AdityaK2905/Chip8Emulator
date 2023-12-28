#include <cstdint>
#include <chrono>
#include <random>


class Chip8 {
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64*32]{};
    uint16_t opcode{};


    //Randomness
    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

    void LoadROM(char const* filename);

    Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
    };


    //OPCODES

    //CLS - Clears Screen
    void OP_00E0();

    //RET - Return from subroutine
    void OP_00EE();

    //JP addr - Jump to location nnn
    void OP_1nnn();

    //2nnn - CALL addr, Call subroutine at address nnn

    void OP_2nnn();

    //3xkk - Skips next instruction if register Vx = kk
    void OP_3xkk();

    //4xkk - Skip next instruction if Vx != kk.
    void OP_4xkk();

    //5xy0 - Skips next instruction if register Vx = Vy
    void OP_5xy0();

    //6xkk - Set the value kk into the register Vx
    void OP_6xkk();

    //7xkk - Add the value of kk to the value in Register Vx
    void OP_7xkk();

    //8xy0 - Stores the value of register Vy into Vx, Vx = Vy
    void OP_8xy0();

    //8xy1 - Set Vx = Vx OR Vy
    void OP_8xy1();

    //8xy2 - Set Vx = Vx AND Vy
    void OP_8xy2();

    //8xy3 - Set Vx = Vx XOR Vy
    void OP_8xy3();

    //8xy4 - Set Vx = Vx+Vy, VF = 1 if result > 8 bits(>255), otherwise 0
    void OP_8xy4();

    //8xy5 - Set Vx = Vx-Vy, If VX > Vy, VF = 1. Otherwise, VF = 0 and Vx = Vy-Vx
    void OP_8xy5();

    //8xy6 - If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
    void OP_8xy6();

    //8xy7 - If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
    void OP_8xy7();

    //8xyE - If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
    void OP_8xyE();

    //9xy0 - If Vx != Vy, skip pc by two
    void OP_9xy0();

    //Annn - The value of register I is set to nnn
    void OP_Annn();

    //Bnnn - The program counter is set to nnn plus the value of V0.
    void OP_Bnnn();

    //Cxkk - The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx.
    void OP_Cxkk();

    //Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
    void OP_Dxyn();

    //Ex9E - Skip next instruction if key with the value of Vx is pressed.
    void OP_Ex9E();

    //ExA1 - Skip next instruction if key with the value of Vx is not pressed.
    void OP_ExA1();

    //Fx07 - The value of DT is placed into Vx.
    void OP_Fx07();

    //Fx0A - Wait for a key press, store the value of the key in Vx.
    void OP_Fx0A();

    //Fx15 - DT is set equal to the value of Vx.
    void OP_Fx15();

    //Fx18 - ST is set equal to the value of Vx.
    void OP_Fx18();

    //Fx1E - The values of I and Vx are added, and the results are stored in I.
    void OP_Fx1E();


};