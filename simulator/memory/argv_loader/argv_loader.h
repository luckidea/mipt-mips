/**
 * argv_loader.h: loader of arguments to guest memory
 * @author Rustem Yunusov <yunusov.rr@phystech.edu>
 * Copyright 2019 MIPT-MIPS iLab project
 */

#ifndef ARGV_LOADER_H
#define ARGV_LOADER_H

#include <infra/argv.h>
#include <infra/types.h>
#include <memory/memory.h>

template <typename T, std::endian endian>
class ArgvLoader
{
public:
    ArgvLoader( const char* const* argv, const char* const* envp);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init, hicpp-member-init) https://github.com/llvm/llvm-project/issues/37250
    explicit ArgvLoader( const char* const* argv) : ArgvLoader( argv, nullptr) { }

    size_t load_to( const std::shared_ptr<FuncMemory>& mem, Addr addr);
private:
    const int argc;
    const char* const* argv;
    const char* const* envp;
    Addr offset;

    static const constexpr size_t GUEST_WORD_SIZE = bytewidth<T>;

    void place_nullptr( const std::shared_ptr<FuncMemory>& mem, Addr addr)
    {
        mem->write<T, endian>( T{}, addr);
    }

    void place_nullterminator( const std::shared_ptr<FuncMemory>& mem, Addr addr)
    {
        mem->write<uint8, endian>( uint8{}, addr);
    }

    void load_argv_contents( const std::shared_ptr<FuncMemory>& mem, Addr addr);
    void load_envp_contents( const std::shared_ptr<FuncMemory>& mem, Addr addr);
};

#endif // ARGV_LOADER_H
