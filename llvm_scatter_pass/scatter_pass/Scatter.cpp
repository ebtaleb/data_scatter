#define DEBUG_TYPE "scatter"
#include "llvm/Support/Debug.h"

#include "llvm/ADT/Statistic.h"
STATISTIC(XORCount, "The # of substituted instructions");

#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {

    class Scatter : public BasicBlockPass {

        public:
            static char ID;
            Scatter() : BasicBlockPass(ID) {}

            bool doInitialization(Module &M) override {
                return false;
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
