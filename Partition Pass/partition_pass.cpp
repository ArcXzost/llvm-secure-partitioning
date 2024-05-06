#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/Support/raw_ostream.h"
#include <queue>
#include <set>
#include <unordered_map>

using namespace llvm;

namespace
{
  struct CallGraphPass : public ModulePass
  {
    static char ID;
    std::unordered_map<Function *, int> functionIDs;
    std::unordered_map<int, Function *> idToFunction;
    std::unordered_map<Function *, std::set<Function *>> callGraph;
    std::set<Function *> secureFunctions;
    std::set<Function *> nonSecureFunctions;

    CallGraphPass() : ModulePass(ID) {}

    void buildFunctionIDs(Module &M)
    {
      int id = 0;
      for (auto &F : M)
      {
        functionIDs[&F] = id;
        idToFunction[id] = &F;
        id++;
      }
    }

    void buildCallGraph(Module &M)
    {
      for (auto &F : M)
      {
        for (auto &BB : F)
        {
          for (auto &I : BB)
          {
            if (auto *callInst = dyn_cast<CallInst>(&I))
            {
              Function *calledFunc = callInst->getCalledFunction();
              if (calledFunc && !calledFunc->isDeclaration())
              {
                callGraph[&F].insert(calledFunc);
              }
            }
          }
        }
      }
    }

    void markSecureFunctions(Module &M)
    {
      for (auto &F : M)
      {
        if (F.hasSection())
        {
          if (F.getSection() == "secure")
          {
            markSecure(&F);
          }
        }
      }

      for (auto &G : M.globals())
      {
        if (G.hasSection())
        {
          if (G.getSection() == "secure_var")
          {
            for (User *U : G.users())
            {
              if (auto *I = dyn_cast<Instruction>(U))
              {
                if (auto *F = I->getFunction())
                {
                  markSecure(F);
                }
              }
            }
          }
        }
      }
    }

    void markSecure(Function *func)
    {
      if (secureFunctions.count(func))
      {
        return;
      }

      secureFunctions.insert(func);

      for (auto *callee : callGraph[func])
      {
        markSecure(callee);
      }
    }

    void printCallGraphBFS()
    {
      std::set<Function *> visited;
      std::queue<Function *> q;

      for (auto &[caller, callees] : callGraph)
      {
        q.push(caller);
        visited.insert(caller);
        while (!q.empty())
        {
          Function *currFunc = q.front();
          q.pop();
          errs() << "Function ID: " << functionIDs[currFunc] << ", Name: " << currFunc->getName() << "\n";
          for (auto *callee : callGraph[currFunc])
          {
            errs() << "\tCalled Function ID: " << functionIDs[callee] << ", Name: " << callee->getName() << "\n";
            if (!visited.count(callee))
            {
              q.push(callee);
              visited.insert(callee);
            }
          }
        }
      }
    }

    void printFunctionSets()
    {
      errs() << "=== Secure Functions ===\n";
      for (auto *func : secureFunctions)
      {
        errs() << "ID: " << functionIDs[func] << ", Name: " << func->getName() << "\n";
      }

      errs() << "\n=== Non-Secure Functions ===\n";
      for (auto &F : idToFunction)
      {
        if (!secureFunctions.count(F.second))
        {
          errs() << "ID: " << F.first << ", Name: " << F.second->getName() << "\n";
        }
      }
    }

    bool runOnModule(Module &M) override
    {
      buildFunctionIDs(M);
      buildCallGraph(M);
      markSecureFunctions(M);

      errs() << "\n\t=== Dependence Graph(Calls) ===\n\n";
      printCallGraphBFS();

      errs() << "\n\t=== Function Partitions ===\n\n";
      printFunctionSets();

      return false;
    }
  };
}

char CallGraphPass::ID = 0;
static RegisterPass<CallGraphPass> X("call-graph", "Call Graph Pass");
