#include "cpu.hpp"

#include <cassert>

#include "instruction.hpp"

namespace emu::w65c02s
{

CPU::CPU() :
    _PC(0xFFFF),
    _S(0xFF),
    _A(0xFF),
    _X(0xFF),
    _Y(0xFF),
    _TMP(0xFF),
    _AD(0xFFFF),
    _DB(0xFF),
    _rnw(true),
    _rdy(true),
    _resb(true),
    _sync(false),
    __cyclesWithResetPulledDown(false),
    __currentResetCycle(1),
    __syncNext(true)
{
    _updateSync();
}

void CPU::step(int64_t nCycles)
{
    while (nCycles-- > 0) tick();
}

void CPU::tick()
{
    if (!_resb)
    {
        __cyclesWithResetPulledDown++;
        if (__cyclesWithResetPulledDown > 2) return;
    }
    else // if (_resb)
    {
        if (__cyclesWithResetPulledDown >= 2)
        {
            __currentResetCycle = 1;
        }
        __cyclesWithResetPulledDown = 0;
    }
    
    if (__currentResetCycle != 0)
    {
        _continueReset();
    }
    else
    {
        if (_sync)
        {
            // Read the fetched byte as the next opcode
            _IR = _DB;
            _TCU = 0;
        }

        // Set read flag up by default
        _rnw = true;
        _decodeAndExecute();        
    }

    if (!_resb) __syncNext = (__cyclesWithResetPulledDown >= 2);
    _updateSync();
}

void CPU::_updateSync()
{
    _sync = __syncNext;
    __syncNext = false;
}

void CPU::_decodeAndExecute()
{
    // Decode
    uint16_t cycleId = _CycleId((Instruction)_IR, _TCU++);

    // Execute
    switch (cycleId)
    {

    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ////                                    ////
    ////       █████╗ ██████╗  ██████╗      ////
    ////      ██╔══██╗██╔══██╗██╔════╝      ////
    ////      ███████║██║  ██║██║           ////
    ////      ██╔══██║██║  ██║██║           ////
    ////      ██║  ██║██████╔╝╚██████╗      ////
    ////      ╚═╝  ╚═╝╚═════╝  ╚═════╝      ////
    ////                                    ////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    //
    // Immediate operand
    //

    case _CycleId<Instruction::ADC_IMM,      0x00>():                   /////////////////
        _AD = _PC++;                                                    // Fetch operand
        break;

    case _CycleId<Instruction::ADC_IMM,      0x01>():                   //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_IMM,      0x02>():                   //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Zero-page address
    //

    case _CycleId<Instruction::ADC_ZP,    0x00>():                      ///////////////////////////
        _AD = _PC++;                                                    // Fetch target ZP address
        break;

    case _CycleId<Instruction::ADC_ZP,    0x01>():                      /////////////////
        _AD.h = 0x00;                                                   // Fetch ZP byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::ADC_ZP,    0x02>():                      //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ZP,    0x03>():                      //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Zero-page address, indexed by X
    //

    case _CycleId<Instruction::ADC_ZP_X,    0x00>():                    ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::ADC_ZP_X,    0x01>():                    /////////////////////////
        _TMP = _DB + _X;                                                // Index ZP address by X
        break;

    case _CycleId<Instruction::ADC_ZP_X,    0x02>():                    ////////////////////////
        _AD.h = 0x00;                                                   // Fetch addressed byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::ADC_ZP_X,    0x03>():                    //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ZP_X,    0x04>():                    //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Absolute address
    //

    case _CycleId<Instruction::ADC_ABS,      0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::ADC_ABS,      0x01>():                   /////////////////////////////////////
        _TMP = _DB;                                                     // Save low byte of target address
        _AD = _PC++;                                                    // Fetch high byte of target address
        break;

    case _CycleId<Instruction::ADC_ABS,      0x02>():                   ////////////////////////////////
        _AD.l = _TMP;                                                   // Fetch addressed byte
        _AD.h = _DB;
        break;

    case _CycleId<Instruction::ADC_ABS,      0x03>():                   //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ABS,      0x04>():                   //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Absolute address, indexed by X
    //

    case _CycleId<Instruction::ADC_ABS_X,    0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::ADC_ABS_X,    0x01>():                   /////////////////////////////////////////
        _AD = _PC++;                                                    // Fetch high byte of target address
        _TMP = _DB + _X;                                                // Index low byte of target address by X
        break;

    case _CycleId<Instruction::ADC_ABS_X,    0x02>():                   /////////////////////////////////
        _AD.l = _TMP;                                                   // Fetch byte at indexed address
        _AD.h = _DB;

        // If indexing did not incur a page-cross, skip next step
        if (_X <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::ADC_ABS_X,    0x03>():                   /////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::ADC_ABS_X,    0x04>():                   //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ABS_X,    0x05>():                   //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Absolute address, indexed by Y
    //

    case _CycleId<Instruction::ADC_ABS_Y,    0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::ADC_ABS_Y,    0x01>():                   /////////////////////////////////////////
        _AD = _PC++;                                                    // Fetch high byte of target address
        _TMP = _DB + _Y;                                                // Index low byte of target address by Y
        break;

    case _CycleId<Instruction::ADC_ABS_Y,    0x02>():                   ////////////////////////
        _AD.l = _TMP;                                                   // Fetch addressed byte
        _AD.h = _DB;

        // If indexing did not incur a page-cross, skip next step
        if (_Y <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::ADC_ABS_Y,    0x03>():                   /////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::ADC_ABS_Y,    0x04>():                   //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ABS_Y,    0x05>():                   //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Zero-page address, indirect
    //

    case _CycleId<Instruction::ADC_ZP_IND,    0x00>():                  ///////////////////////////
        _AD = _PC++;                                                    // Fetch target ZP address
        break;

    case _CycleId<Instruction::ADC_ZP_IND,    0x01>():                  /////////////////////
        _AD.h = 0x00;                                                   // Fetch ZP low byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::ADC_ZP_IND,    0x02>():                  //////////////////////
        _AD.l++;                                                        // Fetch ZP high byte
        _TMP = _DB;
        break;

    case _CycleId<Instruction::ADC_ZP_IND,    0x03>():                  ///////////////////////
        _AD.h = _DB;                                                    // Fetch indirect byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::ADC_ZP_IND,    0x04>():                  //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ZP_IND,    0x05>():                  //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Zero-page address indexed by X, indirect
    //

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x00>():                ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x01>():                /////////////////////////
        _TMP = _DB + _X;                                                // Index ZP address by X
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x02>():                ////////////////////////////
        _AD.h = 0x00;                                                   // Fetch addressed low byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x03>():                /////////////////////////////
        _AD.l++;                                                        // Fetch addressed high byte
        _TMP = _DB;
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x04>():                ///////////////////////
        _AD.h = _DB;                                                    // Fetch indirect byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x05>():                //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ZP_X_IND,    0x06>():                //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;



    //
    // Zero-page address indirect, indexed by Y
    //

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x00>():                ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x01>():                /////////////////////
        _AD.h = 0x00;                                                   // Fetch ZP low byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x02>():                /////////////////////////////////
        _AD.l++;                                                        // Fetch ZP high byte
        _TMP = _DB + _Y;                                                // Save ZP low byte indexed by Y
        break;

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x03>():                /////////////////////////////
        _AD.h = _DB;                                                    // Fetch addressed byte
        _AD.l = _TMP;

        // If indexing did not incur a page-cross, skip next step
        if (_Y <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x04>():                ////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x05>():                //////////////
        if (!_P.d)          // Binary mode                              // Do addtion
        {
            _doAdcBinary(_A, _DB, _TMP);
			_A = _TMP;;
            _fetchInstruction();
        }
        else //if (_P.d)    // Decimal mode
        {
            _doAdcDecimal(_A, _DB, _TMP);
        }
        break;

    case _CycleId<Instruction::ADC_ZP_IND_Y,    0x06>():                //////////////////////////////////////
        assert(_P.d);                                                   // Decimal mode only: set Z,V,N flags

        _setZvnFromAdcResult(_A, _DB, _TMP);
		_A = _TMP;
        _fetchInstruction();
        break;

#undef ADC_BINARY
#undef ADC_DECIMAL_COMPUTE
#undef ADC_DECIMAL_SET_ZVN




    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ////                                    ////
    ////      █████╗ ███╗   ██╗██████╗      ////
    ////     ██╔══██╗████╗  ██║██╔══██╗     ////
    ////     ███████║██╔██╗ ██║██║  ██║     ////
    ////     ██╔══██║██║╚██╗██║██║  ██║     ////
    ////     ██║  ██║██║ ╚████║██████╔╝     ////
    ////     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝      ////
    ////                                    ////
    ////////////////////////////////////////////
    ////////////////////////////////////////////

    //
    // Immediate operand
    //

    case _CycleId<Instruction::AND_IMM,      0x00>():                   /////////////////
        _AD = _PC++;                                                    // Fetch operand
        break;

    case _CycleId<Instruction::AND_IMM,      0x01>():                   //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Zero-page address
    //

    case _CycleId<Instruction::AND_ZP,    0x00>():                      ///////////////////////////
        _AD = _PC++;                                                    // Fetch target ZP address
        break;

    case _CycleId<Instruction::AND_ZP,    0x01>():                      /////////////////
        _AD.h = 0x00;                                                   // Fetch ZP byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::AND_ZP,    0x02>():                      //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Zero-page address, indexed by X
    //

    case _CycleId<Instruction::AND_ZP_X,    0x00>():                    ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::AND_ZP_X,    0x01>():                    /////////////////////////
        _TMP = _DB + _X;                                                // Index ZP address by X
        break;

    case _CycleId<Instruction::AND_ZP_X,    0x02>():                    ////////////////////////
        _AD.h = 0x00;                                                   // Fetch addressed byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::AND_ZP_X,    0x03>():                    //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Absolute address
    //

    case _CycleId<Instruction::AND_ABS,      0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::AND_ABS,      0x01>():                   /////////////////////////////////////
        _TMP = _DB;                                                     // Save low byte of target address
        _AD = _PC++;                                                    // Fetch high byte of target address
        break;

    case _CycleId<Instruction::AND_ABS,      0x02>():                   ////////////////////////////////
        _AD.l = _TMP;                                                   // Fetch addressed byte
        _AD.h = _DB;
        break;

    case _CycleId<Instruction::AND_ABS,      0x03>():                   //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Absolute address, indexed by X
    //

    case _CycleId<Instruction::AND_ABS_X,    0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::AND_ABS_X,    0x01>():                   /////////////////////////////////////////
        _AD = _PC++;                                                    // Fetch high byte of target address
        _TMP = _DB + _X;                                                // Index low byte of target address by X
        break;

    case _CycleId<Instruction::AND_ABS_X,    0x02>():                   /////////////////////////////////
        _AD.l = _TMP;                                                   // Fetch byte at indexed address
        _AD.h = _DB;

        // If indexing did not incur a page-cross, skip next step
        if (_X <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::AND_ABS_X,    0x03>():                   /////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::AND_ABS_X,    0x04>():                   //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Absolute address, indexed by Y
    //

    case _CycleId<Instruction::AND_ABS_Y,    0x00>():                   ////////////////////////////////////
        _AD = _PC++;                                                    // Fetch low byte of target address
        break;

    case _CycleId<Instruction::AND_ABS_Y,    0x01>():                   /////////////////////////////////////////
        _AD = _PC++;                                                    // Fetch high byte of target address
        _TMP = _DB + _Y;                                                // Index low byte of target address by Y
        break;

    case _CycleId<Instruction::AND_ABS_Y,    0x02>():                   ////////////////////////
        _AD.l = _TMP;                                                   // Fetch addressed byte
        _AD.h = _DB;

        // If indexing did not incur a page-cross, skip next step
        if (_Y <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::AND_ABS_Y,    0x03>():                   /////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::AND_ABS_Y,    0x04>():                   //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Zero-page address, indirect
    //

    case _CycleId<Instruction::AND_ZP_IND,    0x00>():                  ///////////////////////////
        _AD = _PC++;                                                    // Fetch target ZP address
        break;

    case _CycleId<Instruction::AND_ZP_IND,    0x01>():                  /////////////////////
        _AD.h = 0x00;                                                   // Fetch ZP low byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::AND_ZP_IND,    0x02>():                  //////////////////////
        _AD.l++;                                                        // Fetch ZP high byte
        _TMP = _DB;
        break;

    case _CycleId<Instruction::AND_ZP_IND,    0x03>():                  ///////////////////////
        _AD.h = _DB;                                                    // Fetch indirect byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::AND_ZP_IND,    0x04>():                  //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Zero-page address indexed by X, indirect
    //

    case _CycleId<Instruction::AND_ZP_X_IND,    0x00>():                ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::AND_ZP_X_IND,    0x01>():                /////////////////////////
        _TMP = _DB + _X;                                                // Index ZP address by X
        break;

    case _CycleId<Instruction::AND_ZP_X_IND,    0x02>():                ////////////////////////////
        _AD.h = 0x00;                                                   // Fetch addressed low byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::AND_ZP_X_IND,    0x03>():                /////////////////////////////
        _AD.l++;                                                        // Fetch addressed high byte
        _TMP = _DB;
        break;

    case _CycleId<Instruction::AND_ZP_X_IND,    0x04>():                ///////////////////////
        _AD.h = _DB;                                                    // Fetch indirect byte
        _AD.l = _TMP;
        break;

    case _CycleId<Instruction::AND_ZP_X_IND,    0x05>():                //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;



    //
    // Zero-page address indirect, indexed by Y
    //

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x00>():                ////////////////////
        _AD = _PC++;                                                    // Fetch ZP address
        break;

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x01>():                /////////////////////
        _AD.h = 0x00;                                                   // Fetch ZP low byte
        _AD.l = _DB;
        break;

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x02>():                /////////////////////////////////
        _AD.l++;                                                        // Fetch ZP high byte
        _TMP = _DB + _Y;                                                // Save ZP low byte indexed by Y
        break;

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x03>():                /////////////////////////////
        _AD.h = _DB;                                                    // Fetch addressed byte
        _AD.l = _TMP;

        // If indexing did not incur a page-cross, skip next step
        if (_Y <= _TMP) _TCU++;
        break;

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x04>():                ////////////////////////////////
        _AD.h++;                                                        // In case of a page-cross only
        break;                                                          // "Cross" the page

    case _CycleId<Instruction::AND_ZP_IND_Y,    0x05>():                //////////////
        // AND_BINARY;
        _fetchInstruction();
        break;





    case _CycleId<Instruction::ASL_ABS,      0x00>():
        break;
    case _CycleId<Instruction::ASL_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::ASL_ACC,      0x00>():
        break;
    case _CycleId<Instruction::ASL_ZP,       0x00>():
        break;
    case _CycleId<Instruction::ASL_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::BBR0,         0x00>():
        break;
    case _CycleId<Instruction::BBR1,         0x00>():
        break;
    case _CycleId<Instruction::BBR2,         0x00>():
        break;
    case _CycleId<Instruction::BBR3,         0x00>():
        break;
    case _CycleId<Instruction::BBR4,         0x00>():
        break;
    case _CycleId<Instruction::BBR5,         0x00>():
        break;
    case _CycleId<Instruction::BBR6,         0x00>():
        break;
    case _CycleId<Instruction::BBR7,         0x00>():
        break;
    case _CycleId<Instruction::BBS0,         0x00>():
        break;
    case _CycleId<Instruction::BBS1,         0x00>():
        break;
    case _CycleId<Instruction::BBS2,         0x00>():
        break;
    case _CycleId<Instruction::BBS3,         0x00>():
        break;
    case _CycleId<Instruction::BBS4,         0x00>():
        break;
    case _CycleId<Instruction::BBS5,         0x00>():
        break;
    case _CycleId<Instruction::BBS6,         0x00>():
        break;
    case _CycleId<Instruction::BBS7,         0x00>():
        break;
    case _CycleId<Instruction::BCC,          0x00>():
        break;
    case _CycleId<Instruction::BCS,          0x00>():
        break;
    case _CycleId<Instruction::BEQ,          0x00>():
        break;
    case _CycleId<Instruction::BNE,          0x00>():
        break;
    case _CycleId<Instruction::BPL,          0x00>():
        break;
    case _CycleId<Instruction::BMI,          0x00>():
        break;
    case _CycleId<Instruction::BVC,          0x00>():
        break;
    case _CycleId<Instruction::BVS,          0x00>():
        break;
    case _CycleId<Instruction::BRA,          0x00>():
        break;
    case _CycleId<Instruction::BIT_ABS,      0x00>():
        break;
    case _CycleId<Instruction::BIT_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::BIT_IMM,      0x00>():
        break;
    case _CycleId<Instruction::BIT_ZP,       0x00>():
        break;
    case _CycleId<Instruction::BIT_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::BRK,          0x00>():
        break;
    case _CycleId<Instruction::CLC,          0x00>():
        break;
    case _CycleId<Instruction::CLD,          0x00>():
        _P.d = 0;
        break;
    case _CycleId<Instruction::CLD,          0x01>():
        _fetchInstruction();
        break;
    case _CycleId<Instruction::CLI,          0x00>():
        break;
    case _CycleId<Instruction::CLV,          0x00>():
        break;
    case _CycleId<Instruction::CMP_ABS,      0x00>():
        break;
    case _CycleId<Instruction::CMP_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::CMP_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::CMP_IMM,      0x00>():
        break;
    case _CycleId<Instruction::CMP_ZP,       0x00>():
        break;
    case _CycleId<Instruction::CMP_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::CMP_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::CMP_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::CMP_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::CPX_ABS,      0x00>():
        break;
    case _CycleId<Instruction::CPX_IMM,      0x00>():
        break;
    case _CycleId<Instruction::CPX_ZP,       0x00>():
        break;
    case _CycleId<Instruction::CPY_ABS,      0x00>():
        break;
    case _CycleId<Instruction::CPY_IMM,      0x00>():
        break;
    case _CycleId<Instruction::CPY_ZP,       0x00>():
        break;
    case _CycleId<Instruction::DEC_ABS,      0x00>():
        break;
    case _CycleId<Instruction::DEC_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::DEC_ZP,       0x00>():
        break;
    case _CycleId<Instruction::DEC_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::DEC_ACC,      0x00>():
        break;
    case _CycleId<Instruction::DEX,          0x00>():
        break;
    case _CycleId<Instruction::DEY,          0x00>():
        break;
    case _CycleId<Instruction::EOR_ABS,      0x00>():
        break;
    case _CycleId<Instruction::EOR_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::EOR_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::EOR_IMM,      0x00>():
        break;
    case _CycleId<Instruction::EOR_ZP,       0x00>():
        break;
    case _CycleId<Instruction::EOR_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::EOR_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::EOR_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::EOR_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::INC_ABS,      0x00>():
        break;
    case _CycleId<Instruction::INC_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::INC_ZP,       0x00>():
        break;
    case _CycleId<Instruction::INC_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::INC_ACC,      0x00>():
        break;
    case _CycleId<Instruction::INX,          0x00>():
        break;
    case _CycleId<Instruction::INY,          0x00>():
        break;
    case _CycleId<Instruction::JMP_ABS,      0x00>():
        break;
    case _CycleId<Instruction::JMP_ABS_IND,  0x00>():
        break;
    case _CycleId<Instruction::JMP_ABS_X_IND,0x00>():
        break;
    case _CycleId<Instruction::JSR,          0x00>():
        break;
    case _CycleId<Instruction::LDA_ABS,      0x00>():
        break;
    case _CycleId<Instruction::LDA_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::LDA_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::LDA_IMM,      0x00>():
        _AD = _PC++;
        break;
    case _CycleId<Instruction::LDA_IMM,      0x01>():
        _A = _DB;
        _fetchInstruction();
        break;
    case _CycleId<Instruction::LDA_ZP,       0x00>():
        break;
    case _CycleId<Instruction::LDA_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::LDA_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::LDA_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::LDA_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::LDX_ABS,      0x00>():
        break;
    case _CycleId<Instruction::LDX_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::LDX_IMM,      0x00>():
        _AD = _PC++;
        break;
    case _CycleId<Instruction::LDX_IMM,      0x01>():
        _X = _DB;
        _fetchInstruction();
        break;
    case _CycleId<Instruction::LDX_ZP,       0x00>():
        break;
    case _CycleId<Instruction::LDX_ZP_Y,     0x00>():
        break;
    case _CycleId<Instruction::LDY_ABS,      0x00>():
        break;
    case _CycleId<Instruction::LDY_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::LDY_IMM,      0x00>():
        _AD = _PC++;
        break;
    case _CycleId<Instruction::LDY_IMM,      0x01>():
        _Y = _DB;
        _fetchInstruction();
        break;
    case _CycleId<Instruction::LDY_ZP,       0x00>():
        break;
    case _CycleId<Instruction::LDY_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::LSR_ABS,      0x00>():
        break;
    case _CycleId<Instruction::LSR_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::LSR_ACC,      0x00>():
        break;
    case _CycleId<Instruction::LSR_ZP,       0x00>():
        break;
    case _CycleId<Instruction::LSR_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::NOP,          0x00>():
        break;
    case _CycleId<Instruction::ORA_ABS,      0x00>():
        break;
    case _CycleId<Instruction::ORA_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::ORA_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::ORA_IMM,      0x00>():
        break;
    case _CycleId<Instruction::ORA_ZP,       0x00>():
        break;
    case _CycleId<Instruction::ORA_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::ORA_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::ORA_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::ORA_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::PHA,          0x00>():
        break;
    case _CycleId<Instruction::PHP,          0x00>():
        break;
    case _CycleId<Instruction::PHX,          0x00>():
        break;
    case _CycleId<Instruction::PHY,          0x00>():
        break;
    case _CycleId<Instruction::PLA,          0x00>():
        break;
    case _CycleId<Instruction::PLP,          0x00>():
        break;
    case _CycleId<Instruction::PLX,          0x00>():
        break;
    case _CycleId<Instruction::PLY,          0x00>():
        break;
    case _CycleId<Instruction::RMB0,         0x00>():
        break;
    case _CycleId<Instruction::RMB1,         0x00>():
        break;
    case _CycleId<Instruction::RMB2,         0x00>():
        break;
    case _CycleId<Instruction::RMB3,         0x00>():
        break;
    case _CycleId<Instruction::RMB4,         0x00>():
        break;
    case _CycleId<Instruction::RMB5,         0x00>():
        break;
    case _CycleId<Instruction::RMB6,         0x00>():
        break;
    case _CycleId<Instruction::RMB7,         0x00>():
        break;
    case _CycleId<Instruction::SMB0,         0x00>():
        break;
    case _CycleId<Instruction::SMB1,         0x00>():
        break;
    case _CycleId<Instruction::SMB2,         0x00>():
        break;
    case _CycleId<Instruction::SMB3,         0x00>():
        break;
    case _CycleId<Instruction::SMB4,         0x00>():
        break;
    case _CycleId<Instruction::SMB5,         0x00>():
        break;
    case _CycleId<Instruction::SMB6,         0x00>():
        break;
    case _CycleId<Instruction::SMB7,         0x00>():
        break;
    case _CycleId<Instruction::ROL_ABS,      0x00>():
        break;
    case _CycleId<Instruction::ROL_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::ROL_IMM,      0x00>():
        break;
    case _CycleId<Instruction::ROL_ZP,       0x00>():
        break;
    case _CycleId<Instruction::ROL_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::ROR_ABS,      0x00>():
        break;
    case _CycleId<Instruction::ROR_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::ROR_IMM,      0x00>():
        break;
    case _CycleId<Instruction::ROR_ZP,       0x00>():
        break;
    case _CycleId<Instruction::ROR_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::RTI,          0x00>():
        break;
    case _CycleId<Instruction::RTS,          0x00>():
        break;
    case _CycleId<Instruction::SBC_ABS,      0x00>():
        break;
    case _CycleId<Instruction::SBC_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::SBC_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::SBC_IMM,      0x00>():
        break;
    case _CycleId<Instruction::SBC_ZP,       0x00>():
        break;
    case _CycleId<Instruction::SBC_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::SBC_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::SBC_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::SBC_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::SEC,          0x00>():
        break;
    case _CycleId<Instruction::SED,          0x00>():
        _P.d = 1;
        break;
    case _CycleId<Instruction::SED,          0x01>():
        _fetchInstruction();
        break;
    case _CycleId<Instruction::SEI,          0x00>():
        break;
    case _CycleId<Instruction::STA_ABS,      0x00>():
        break;
    case _CycleId<Instruction::STA_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::STA_ABS_Y,    0x00>():
        break;
    case _CycleId<Instruction::STA_ZP,       0x00>():
        break;
    case _CycleId<Instruction::STA_ZP_IND,   0x00>():
        break;
    case _CycleId<Instruction::STA_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::STA_ZP_X_IND, 0x00>():
        break;
    case _CycleId<Instruction::STA_ZP_IND_Y, 0x00>():
        break;
    case _CycleId<Instruction::STX_ABS,      0x00>():
        break;
    case _CycleId<Instruction::STX_ZP,       0x00>():
        break;
    case _CycleId<Instruction::STX_ZP_Y,     0x00>():
        break;
    case _CycleId<Instruction::STY_ABS,      0x00>():
        break;
    case _CycleId<Instruction::STY_ZP,       0x00>():
        break;
    case _CycleId<Instruction::STY_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::STZ_ABS,      0x00>():
        break;
    case _CycleId<Instruction::STZ_ABS_X,    0x00>():
        break;
    case _CycleId<Instruction::STZ_ZP,       0x00>():
        break;
    case _CycleId<Instruction::STZ_ZP_X,     0x00>():
        break;
    case _CycleId<Instruction::STP,          0x00>():
        break;
    case _CycleId<Instruction::TRB_ABS,      0x00>():
        break;
    case _CycleId<Instruction::TRB_ZP,       0x00>():
        break;
    case _CycleId<Instruction::TSB_ABS,      0x00>():
        break;
    case _CycleId<Instruction::TSB_ZP,       0x00>():
        break;
    case _CycleId<Instruction::TAX,          0x00>():
        break;
    case _CycleId<Instruction::TAY,          0x00>():
        break;
    case _CycleId<Instruction::TSX,          0x00>():
        break;
    case _CycleId<Instruction::TXA,          0x00>():
        break;
    case _CycleId<Instruction::TXS,          0x00>():
        break;
    case _CycleId<Instruction::TYA,          0x00>():
        break;
    case _CycleId<Instruction::WAI,          0x00>():
        break;
    default:
        break;
    }
}

inline uint16_t CPU::_CycleId(Instruction ins, Byte timing)
{
    return (static_cast<uint16_t>(ins) << 8) + timing;
}

void CPU::_fetchInstruction()
{
    _AD = _PC++;
    __syncNext = true;
}

void CPU::_continueReset()
{
    _rnw = true;

    switch(__currentResetCycle++)
    {
    case 1:
        _resetSequence_cycle1();
        break;
    case 2:
        _resetSequence_cycle2();
        break;
    case 3:
        _resetSequence_cycle3();
        break;
    case 4:
        _resetSequence_cycle4();
        break;
    case 5:
        _resetSequence_cycle5();
        break;
    case 6:
        _resetSequence_cycle6();
        break;
    case 7:
        _resetSequence_cycle7();
        __currentResetCycle = 0;
        break;
    }
}

void CPU::_resetSequence_cycle1()
{
    _AD.h = 0xFF;           // Fetch reset vector low byte
    _AD.l = 0xFC;
}

void CPU::_resetSequence_cycle2()
{
    _AD.l = 0xFD;           // Fetch reset vector high byte
    _PC.l = _DB;            // Write reset vector low byte
}

void CPU::_resetSequence_cycle3()
{
    _PC.h = _DB;            // Write reset vector high byte
}

void CPU::_resetSequence_cycle4()
{
    _S = 0xFF;              // Init stack
}

void CPU::_resetSequence_cycle5()
{
    _P.i = 1;               // Interrupt disable
    _P.d = 0;               // Decimal mode
    _P.b = 1;               // Break
    _P.u = 1;               // User flag
}

void CPU::_resetSequence_cycle6()
{
    // ???
}

void CPU::_resetSequence_cycle7()
{
    _fetchInstruction();
}

inline void CPU::_doAdcBinary(Byte& op1, Byte& op2, Byte& res)
{
    _TMP = (op1 + op2 + _P.c) & 0xFF;
    _P.c = (res < op2);
    _setZvnFromAdcResult(op1, op2, res);
}

inline void CPU::_doAdcDecimal(Byte& op1, Byte& op2, Byte& res)
{
    res = ((op1 & 0x0F) + (op2 & 0x0F) + _P.c);     // Add lower nibbles of operands
    uint8_t c = res >= 10 ? 1 : 0;                  // Decimal carry from lower nibble addition

    uint8_t higher  = (op1  >> 4)                   // Take higher nibble of op1, make it lower
                    + (op2 >> 4)                    // Add higher nibble of op2 made lower
                    +   c;                          // Add decimal carry from lower nibble addition
    _P.c = higher >= 10 ? 1 : 0;                    // Set processor carry

    // Shift BCD result back to higher nibble, OR it with BCD lower nibble to get final result
    res = ((higher % 10) << 4) | (res % 10);
}

inline void CPU::_setZnFrom(Byte value)
{
    _P.z = (value == 0x00);
    _P.n = ((value &  0x80) > 0);
}

inline void CPU::_setZvnFromAdcResult(Byte op1, Byte op2, Byte res)
{
    _setZnFrom(res);
    _P.v = (((op1 ^ res) & (op2 ^ res) & 0x80) > 0);
}

}