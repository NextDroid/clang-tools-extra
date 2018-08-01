//===--- VirtualShadowingCheck.cpp - clang-tidy----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "VirtualShadowingCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nextdroid {

void VirtualShadowingCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl(isVirtual()).bind("method"), this);
}
//namespace
//{
//bool CandidatePred(const CXXRecordDecl *BaseDefinition, void *UserData) {
//  // get the original method from UserData
//  const auto method = reinterpret_cast<const CXXMethodDecl *>(UserData);
//
//  // get a string ref to the original method's name
//  const auto name = method->getName();
//
//  // check all the methods in the base class
//  for (const auto &base_method : BaseDefinition->methods()) {
//    if (name == base_method->getName()) {
//      // if we found a method with the same name check if it's virtual:
//      //   * if it is not virtual the original method was problematic
//      //   * if the base's method was virtual the original method was OK
//      //     (but the base's method could be problematic and would be checked
//      //     in a different analyzer run)
//      return not base_method->isVirtual();
//    }
//  }
//
//  // we found no collisions with this base's methods, now check the base's
//  // bases for collisions with the original method
//  return BaseDefinition->forallBases(CandidatePred, UserData);
//}
//} // namespace

void VirtualShadowingCheck::check(const MatchFinder::MatchResult &Result) {
	const auto method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
	const auto cl_decl = method->getParent();
	if (cl_decl->getNumBases() == 0)
	{
		return;
	}
	std::function<bool(const CXXRecordDecl*)> CandidatePred;
	CandidatePred = [method, &CandidatePred](const CXXRecordDecl* BaseDefinition){  // get the original method from UserData

  		  // get a string ref to the original method's name
  		  const auto name = method->getName();

  		  // check all the methods in the base class
		  for (const auto &base_method : BaseDefinition->methods()) {
		    if (name == base_method->getName()) {
		      // if we found a method with the same name check if it's virtual:
		      //   * if it is not virtual the original method was problematic
		      //   * if the base's method was virtual the original method was OK
		      //     (but the base's method could be problematic and would be checked
		      //     in a different analyzer run)
		      return not base_method->isVirtual();
		    }
		  }
		  return BaseDefinition->forallBases(CandidatePred);
	};

	if (not cl_decl->forallBases(CandidatePred ))
	{
		return;
	}
	diag(method->getLocStart(),
			"method hides non-virtual method from a base class");

}

} // namespace nextdroid
} // namespace tidy
} // namespace clang
