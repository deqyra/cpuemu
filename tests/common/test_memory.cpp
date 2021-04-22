#include <catch2/catch2.hpp>

#include <cpuemu/common/memory.hpp>

#define TAGS "[common][memory]"

namespace emu
{

TEST_CASE("Memory", TAGS)
{
    constexpr uint64_t Length = 65536;
    Memory<Length> mem;

    SECTION("memory has the proper size")
    {
        using std::size;
        REQUIRE(size(mem.data) == Length);
    }

    SECTION("memory is all zeros at instantiation")
    {
        bool allZeroed = true;
        for (uint64_t i = 0; i < Length; i++)
        {
            if (mem.data[i] != 0)
            {
                allZeroed = false;
                break;
            }
        }

        REQUIRE(allZeroed);
    }

    SECTION("memory can be assigned to with a vector of bytes")
    {
        std::vector<Byte> bytes = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
        mem = bytes;

        bool sameAsVector = true;
        for (uint64_t i = 0; i < bytes.size(); i++)
        {
            if (mem.data[i] != bytes[i])
            {
                sameAsVector = false;
                break;
            }
        }

        bool zeroEverywhereElse = true;
        for (uint64_t i = bytes.size(); i < Length; i++)
        {
            if (mem.data[i] != 0)
            {
                zeroEverywhereElse = false;
                break;
            }
        }

        CHECK(sameAsVector);
        CHECK(zeroEverywhereElse);
    }

    SECTION("Memory<Size>::_cell")
    {
        SECTION("operator[] return a properly constructed _cell proxy object")
        {
            auto i = GENERATE(0, 512, 65535);

            auto cell = mem[i];
            REQUIRE(cell.data == mem.data);
            REQUIRE(cell.where == i);
        }

        SECTION("_cell proxy object allows reading from memory")
        {
            auto i = GENERATE(0, 512, 65535);

            mem.data[i] = 0xAB;
            auto cell = mem[i];
            REQUIRE((Byte)(cell) == 0xAB);

            //mem.data[i] = 0xCD;
            //REQUIRE(mem[i] == 0xCD);
        }

        SECTION("_cell proxy object allows writing to memory")
        {
            auto i = GENERATE(0, 512, 65535);

            auto cell = mem[i];
            cell = 0xAC;
            REQUIRE(mem.data[i] == 0xAC);

            mem[i] = 0xBD;
            REQUIRE(mem.data[i] == 0xBD);
        }

        SECTION("_cell proxy object allows writing to a range of memory")
        {
            std::vector<Byte> bytes = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

            auto cell = mem[0x23];
            cell = bytes;
            bool properlyCopied = true;
            for (uint64_t i = 0; i < bytes.size(); i++)
            {
                if (mem.data[0x23 + i] != bytes[i])
                {
                    properlyCopied = false;
                    break;
                }
            }
            CHECK(properlyCopied);

            mem[0xA3D5] = bytes;
            properlyCopied = true;
            for (uint64_t i = 0; i < bytes.size(); i++)
            {
                if (mem.data[0xA3D5 + i] != bytes[i])
                {
                    properlyCopied = false;
                    break;
                }
            }
            CHECK(properlyCopied);
        }
    }
}

}