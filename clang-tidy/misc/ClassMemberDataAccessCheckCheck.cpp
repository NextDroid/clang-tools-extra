//===--- ClassMemberDataAccessCheckCheck.cpp - clang-tidy------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ClassMemberDataAccessCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ClassMemberDataAccessCheckCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(fieldDecl(hasAncestor(cxxRecordDecl(isClass()))).bind("field"), this);
}

void ClassMemberDataAccessCheckCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("field");
  AccessSpecifier okay = AS_private;
  if (MatchedDecl->getAccess() == okay)
  {
    return;
  }
  if (static_cast<const CXXRecordDecl*>(MatchedDecl->getParent())->isPOD())
  {
    return; 
  }
  diag(MatchedDecl->getLocation(), "non-POD class member data should be private");
}

} // namespace misc
} // namespace tidy
} // namespace clang
