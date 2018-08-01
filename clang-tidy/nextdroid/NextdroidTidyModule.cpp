//===--- CppCoreGuidelinesModule.cpp - clang-tidy -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "VirtualShadowingCheck.h"
#include "../hicpp/MultiwayPathsCoveredCheck.h"

namespace clang {
namespace tidy {
namespace nextdroid {

/// A module containing checks of the Nextdroid guidelines
class NextdroidModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<VirtualShadowingCheck>(
        "nextdroid-virtual-shadowing");
    CheckFactories.registerCheck<hicpp::MultiwayPathsCoveredCheck>(
        "M6-4-2-terminating-else-clause");
  }
	
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<NextdroidModule>
    X("nextdroid-module", "Adds checks for the Nextdroid Guidelines.");

} // namespace nextdroid

// This anchor is used to force the linker to link in the generated object file
// and thus register the NextdroidModule.
volatile int NextdroidModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
