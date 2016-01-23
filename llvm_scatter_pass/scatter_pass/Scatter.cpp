#define DEBUG_TYPE "scatter"
#include "llvm/Support/Debug.h"

#include "llvm/ADT/Statistic.h"
STATISTIC(XORCount, "The # of substituted instructions");

#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace {

    class Scatter : public BasicBlockPass {

        public:
            static char ID;
            Scatter() : BasicBlockPass(ID) {}

            bool doInitialization(Module &M) override {

                ArrayType* ArrayTy_0 = ArrayType::get(IntegerType::get(M.getContext(), 32), 4);
                PointerType* PointerTy_1 = PointerType::get(ArrayTy_0, 0);

                PointerType* PointerTy_2 = PointerType::get(IntegerType::get(M.getContext(), 32), 0);
                ArrayType* ArrayTy_3 = ArrayType::get(PointerTy_2, 2);

                GlobalVariable* gvar_int32_access_counter = new GlobalVariable(/*Module=*/M,
                        /*Type=*/IntegerType::get(M.getContext(), 32),
                        /*isConstant=*/false,
                        /*Linkage=*/GlobalValue::CommonLinkage,
                        /*Initializer=*/0, // has initializer, specified below
                        /*Name=*/"access_counter");
                gvar_int32_access_counter->setAlignment(4);

                GlobalVariable* gvar_array_access_array = new GlobalVariable(/*Module=*/M,
                        /*Type=*/ArrayTy_0,
                        /*isConstant=*/false,
                        /*Linkage=*/GlobalValue::ExternalLinkage,
                        /*Initializer=*/0, // has initializer, specified below
                        /*Name=*/"access_array");
                gvar_array_access_array->setAlignment(16);

                GlobalVariable* gvar_array_address_array = new GlobalVariable(/*Module=*/M,
                        /*Type=*/ArrayTy_3,
                        /*isConstant=*/false,
                        /*Linkage=*/GlobalValue::CommonLinkage,
                        /*Initializer=*/0, // has initializer, specified below
                        /*Name=*/"address_array");
                gvar_array_address_array->setAlignment(16);

                // Constant Definitions
                std::vector<Constant*> const_array_8_elems;
                ConstantInt* const_int32_9 = ConstantInt::get(M.getContext(), APInt(32, StringRef("0"), 10));
                const_array_8_elems.push_back(const_int32_9);
                ConstantInt* const_int32_10 = ConstantInt::get(M.getContext(), APInt(32, StringRef("1"), 10));
                const_array_8_elems.push_back(const_int32_10);
                const_array_8_elems.push_back(const_int32_9);
                const_array_8_elems.push_back(const_int32_10);
                Constant* const_array_8 = ConstantArray::get(ArrayTy_0, const_array_8_elems);
                ConstantAggregateZero* const_array_11 = ConstantAggregateZero::get(ArrayTy_3);
                ConstantInt* const_int32_12 = ConstantInt::get(M.getContext(), APInt(32, StringRef("2147483647"), 10));

                // Global Variable Definitions
                gvar_array_access_array->setInitializer(const_array_8);
                gvar_int32_access_counter->setInitializer(const_int32_9);
                gvar_array_address_array->setInitializer(const_array_11);


                return true;
            }

            bool runOnBasicBlock(BasicBlock &BB) override {

            }

        private:

    };
}

char Scatter::ID = 0;
static RegisterPass<Scatter>
X(  "scatter",  // the option name -> -scatter
    "Data scatter pass", // option description
    true, // true as we don't modify the CFG
    false // true if we're writing an analysis
 );

// clang pass registration (optional)
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

static void
registerClangPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new Scatter());
}

// Note the registration point, clang offers several insertion points where you
// can insert your pass.
static RegisterStandardPasses RegisterClangPass
(PassManagerBuilder::EP_EarlyAsPossible, registerClangPass);
