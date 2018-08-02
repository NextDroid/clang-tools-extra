//===--- VirtualFunctionDeclarationCheck.cpp - clang-tidy------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "VirtualFunctionDeclarationCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <cstdio>
#include <sstream>
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void VirtualFunctionDeclarationCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl(isVirtual()).bind("method"), this);
}

void VirtualFunctionDeclarationCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXMethodDecl>("method");

  int number_of_modifiers = 0;
  if (MatchedDecl->isVirtualAsWritten())
  {
     number_of_modifiers++;
  }
  for( auto it: MatchedDecl->attrs())
  {
      if (it->getKind() ==  attr::Final)
      {
        number_of_modifiers++;
      }
      if (it->getKind() == attr::Override)
      {
        number_of_modifiers++;
      }
  }
  if (number_of_modifiers != 1)
  {
    diag(MatchedDecl->getLocation(), "virtual functions should be declared with exactly one of \"virtual\", \"override\", or \"final\" ");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
