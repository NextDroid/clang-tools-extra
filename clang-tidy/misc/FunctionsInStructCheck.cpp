//===--- FunctionsInStructCheck.cpp - clang-tidy---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "FunctionsInStructCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void FunctionsInStructCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl(unless(isImplicit()),hasAncestor(cxxRecordDecl(isStruct()))).bind("method"), this);
}

void FunctionsInStructCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("method");
  diag(MatchedDecl->getLocation(), "structs should not provide member functions or methods");
}

} // namespace misc
} // namespace tidy
} // namespace clang
