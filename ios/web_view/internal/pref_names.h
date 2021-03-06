// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_WEB_VIEW_INTERNAL_PREF_NAMES_H_
#define IOS_WEB_VIEW_INTERNAL_PREF_NAMES_H_

namespace prefs {

// The value to use for Accept-Languages HTTP header when making an HTTP
// request. Currently only used for Translate related requests.
extern const char kAcceptLanguages[];

// Boolean controlling whether history saving is disabled.
extern const char kSavingBrowserHistoryDisabled[];

}  // namespace prefs

#endif  // IOS_WEB_VIEW_INTERNAL_PREF_NAMES_H_
