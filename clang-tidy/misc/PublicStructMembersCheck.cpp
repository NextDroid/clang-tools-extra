//===--- PublicStructMembersCheck.cpp - clang-tidy-------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "PublicStructMembersCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PublicStructMembersCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(decl(fieldDecl(hasAncestor(cxxRecordDecl(isStruct())))).bind("struct_field"), this);
}

void PublicStructMembersCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("struct_field");
  AccessSpecifier okay = AS_public;
  if (MatchedDecl->getAccess() == okay)
    return;
  diag(MatchedDecl->getLocation(), "struct contains non-public data member");
}

} // namespace misc
} // namespace tidy
} // namespace clang
