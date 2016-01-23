// RUN: clang %s -S -emit-llvm -o %t.ll
// RUN: opt -load %bindir/lib/LLVMSCAT${MOD_EXT} -scatter %t.ll -S -o %t0.ll
// RUN: FileCheck %s < %t0.ll
// RUN: clang %t0.ll -o %t0
// RUN: %t0
#include <stdio.h>

int main()
{
    // CHECK: ret
    return 0;
}
