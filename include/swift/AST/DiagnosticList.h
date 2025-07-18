//===--- DiagnosticList.h - Diagnostic Definitions --------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2025 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
//  This file defines all of the diagnostics emitted by Swift.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_DIAGNOSTICLIST_H
#define SWIFT_DIAGNOSTICLIST_H

/// `DiagnosticList.h` is imported into Swift. Be *very* careful with what you
/// include here and keep these includes minimal!
///
/// See include guidelines and caveats in `BasicBridging.h`.
#include "swift/Basic/SwiftBridging.h"
#include <stdint.h>

namespace swift {

/// Enumeration describing all of possible diagnostics.
///
/// Each of the diagnostics described in Diagnostics.def has an entry in
/// this enumeration type that uniquely identifies it.
enum class ENUM_EXTENSIBILITY_ATTR(open) DiagID : uint32_t {
#define DIAG(KIND, ID, Group, Options, Text, Signature) ID,
#include "swift/AST/DiagnosticsAll.def"
  NumDiagsHandle
};
static_assert(static_cast<uint32_t>(swift::DiagID::invalid_diagnostic) == 0,
              "0 is not the invalid diagnostic ID");

constexpr auto NumDiagIDs = static_cast<uint32_t>(DiagID::NumDiagsHandle);

enum class ENUM_EXTENSIBILITY_ATTR(open) FixItID : uint32_t {
#define DIAG(KIND, ID, Group, Options, Text, Signature)
#define FIXIT(ID, Text, Signature) ID,
#include "swift/AST/DiagnosticsAll.def"
};

} // end namespace swift

#endif /* SWIFT_DIAGNOSTICLIST_H */
