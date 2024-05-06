#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "hello"

namespace {
struct Hello : public FunctionPass {
  static char ID;
  Hello() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    // Option 1: Using Twine::str()
    // std::string Filename = F.getName().str() + ".dot";

    // Option 2: Temporary string for concatenation
    std::string FunctionName = F.getName().str();
    std::string Filename = FunctionName + ".dot";

    std::error_code EC;
    // Replace with the appropriate flag for your LLVM version (e.g., Write, RW)
    raw_fd_ostream File(Filename, EC, sys::fs::OpenFlags::OF_Text); // Use ReadWrite


    if (!EC) {
      File << "digraph " << F.getName() << " {\n";
      File << "\n";

      for (auto &BB : F) {
        for (auto &I : BB) {
          for (auto &U : I.operands()) {
            Value *V = U.get();
            if (dyn_cast<Instruction>(V)) {
              File << "\"" << I << "\"" << " -> " << "\"" << *V << "\"" << ";\n";
            } else if (V->getName() != "") {
              File << "\"" << V->getName() << "\"" << " -> " << "\"" << I << "\"" << ";\n";
              File << "\"" << V->getName() << "\"" << " [ color = red ]\n";
            }
          }
        }
      }

      File << "\n}\n";
    } else {
      errs() << "Error creating .dot file: " << EC.message() << "\n";
    }

    return false;
  }
};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("pdg", "PDG Pass");
