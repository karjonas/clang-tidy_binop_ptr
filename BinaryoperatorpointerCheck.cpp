//===--- BinaryoperatorpointerCheck.cpp - clang-tidy-----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "BinaryoperatorpointerCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void BinaryoperatorpointerCheck::registerMatchers(MatchFinder *Finder) {
  if (!getLangOpts().CPlusPlus)
    return;

  // Flag all operators +, -, +=, -=, ++, -- that result in a pointer
  Finder->addMatcher(
      binaryOperator(
          anyOf(hasOperatorName("<"), hasOperatorName(">"),
                hasOperatorName("<="), hasOperatorName(">=")),
	  hasLHS(hasType(pointerType())),
	  hasRHS(hasType(pointerType())),
          anything())
          .bind("expr"),
      this);
}

void BinaryoperatorpointerCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedExpr = Result.Nodes.getNodeAs<Expr>("expr");
  diag(MatchedExpr->getExprLoc(), "Do not sort by pointers (╯°□°)╯︵ ┻━┻");
}

} // namespace misc
} // namespace tidy
} // namespace clang
