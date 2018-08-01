//===--- ClassInheritFromStructCheck.cpp - clang-tidy----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ClassInheritFromStructCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ClassInheritFromStructCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(cxxRecordDecl(isClass(),unless(isImplicit()),isDerivedFrom(cxxRecordDecl(isStruct()))).bind("class"), this);
}

void ClassInheritFromStructCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("class");
  diag(MatchedDecl->getLocation(), "classes should not inherit from structs");
}

} // namespace misc
} // namespace tidy
} // namespace clang
