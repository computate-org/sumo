/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2022 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    MFXTextFieldTooltip.cpp
/// @author  Pablo Alvarez Lopez
/// @date    2022-07-22
///
// TextField similar to FXTextField but with the possibility of showing tooltips
/****************************************************************************/
#include <config.h>

#include "MFXTextFieldTooltip.h"


FXDEFMAP(MFXTextFieldTooltip) MFXTextFieldTooltipMap[] = {
    FXMAPFUNC(SEL_ENTER,    0,  MFXTextFieldTooltip::onEnter),
    FXMAPFUNC(SEL_LEAVE,    0,  MFXTextFieldTooltip::onLeave),
};

// Object implementation
FXIMPLEMENT(MFXTextFieldTooltip, FXTextField, MFXTextFieldTooltipMap, ARRAYNUMBER(MFXTextFieldTooltipMap))


MFXTextFieldTooltip::MFXTextFieldTooltip(FXComposite* p, FXint ncols, FXObject* tgt, FXSelector sel,
        FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb) :
    FXTextField(p, ncols, tgt, sel, opts, x, y, w, h, pl, pr, pt, pb) {
}


MFXTextFieldTooltip::~MFXTextFieldTooltip() {}


void 
MFXTextFieldTooltip::setToolTipText(const FXString &toolTip) {
    myToolTipText = toolTip;
}


long
MFXTextFieldTooltip::onEnter(FXObject* sender, FXSelector sel, void* ptr) {
    // create on first enter
    if (myStaticToolTip == nullptr) {
        myStaticToolTip = new MFXStaticToolTip(getApp());
        myStaticToolTip->create();
    }
    // check if show toolTip text
    if (!myToolTipText.empty()) {
        // show toolTip text
        setTipText(myToolTipText);
        // show tip show
        myStaticToolTip->onTipShow(sender, sel, ptr);
    } else if (font->getTextWidth(contents.text(), contents.length()) > getWidth()) {
        // only show tip Text if contents is bigger than textField width
        setTipText(contents);
        // show tip show
        myStaticToolTip->onTipShow(sender, sel, ptr);
    }
    // always show help text
    setHelpText(contents);
    // continue with FXTextField function
    return FXTextField::onEnter(sender, sel, ptr);
}


long
MFXTextFieldTooltip::onLeave(FXObject* sender, FXSelector sel, void* ptr) {
    // hide tip show
    myStaticToolTip->onTipHide(sender, sel, this);
    // continue with FXTextField function
    return FXTextField::onLeave(sender, sel, ptr);
}


/****************************************************************************/
