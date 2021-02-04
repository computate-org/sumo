/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2021 German Aerospace Center (DLR) and others.
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
/// @file    GNESelectorFrame.h
/// @author  Jakob Erdmann
/// @date    Mar 2011
///
// The Widget for modifying selections of network-elements
// (some elements adapted from GUIDialog_GLChosenEditor)
/****************************************************************************/
#pragma once
#include <config.h>

#include <netedit/frames/GNEFrame.h>
#include <netedit/GNEViewNetHelper.h>

// ===========================================================================
// class declaration
// ===========================================================================

class GNEElementSet;
class GNEMatchAttribute;
class GNEMatchGenericDataAttribute;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNESelectorFrame
 * The Widget for modifying selections of network-elements
 */
class GNESelectorFrame : public GNEFrame {

public:
    
    // @brief friend class
    friend class GNEElementSet;
    friend class GNEMatchAttribute;
    friend class GNEMatchGenericDataAttribute;


    // ===========================================================================
    // class LockGLObjectTypes
    // ===========================================================================

    class LockGLObjectTypes : protected FXGroupBox {

    public:
        /// @brief class for object types entries
        class ObjectTypeEntry : protected FXObject {
            /// @brief FOX-declaration
            FXDECLARE(GNESelectorFrame::LockGLObjectTypes::ObjectTypeEntry)

        public:
            /// @brief constructor
            ObjectTypeEntry(FXMatrix* matrixParent, const Supermode supermode, const std::string& label);

            /// @brief get supermode associated to this ObjectTypeEntry
            Supermode getSupermode() const;

            /// @brief show ObjectTypeEntry
            void showObjectTypeEntry();

            /// @brief hide ObjectTypeEntry
            void hideObjectTypeEntry();

            /// @brief up count
            void counterUp();

            /// @brief down count
            void counterDown();

            /// @brief check if current GLType is blocked
            bool isGLTypeLocked() const;

            /// @name FOX-callbacks
            /// @{

            /// @brief called when user change the CheckBox
            long onCmdSetCheckBox(FXObject*, FXSelector, void*);

            /// @}

        protected:
            ObjectTypeEntry();

        private:
            /// @brief supermode associated to this ObjectTypeEntry
            const Supermode mySupermode;

            /// @brief label counter
            FXLabel* myLabelCounter;

            /// @brief label type nane
            FXLabel* myLabelTypeName;

            /// @brief check box to check if GLObject type is blocked
            FXCheckButton* myCheckBoxLocked;

            /// @brief counter
            int myCounter;

        private:
            /// @brief Invalidated assignment operator.
            ObjectTypeEntry& operator=(const ObjectTypeEntry&) = delete;

        };

        /// @brief constructor
        LockGLObjectTypes(GNESelectorFrame* selectorFrameParent);

        /// @brief destructor
        ~LockGLObjectTypes();

        /// @brief set object selected
        void addedLockedObject(const GUIGlObjectType type);

        /// @brief set object unselected
        void removeLockedObject(const GUIGlObjectType type);

        /// @brief check if an object is locked
        bool IsObjectTypeLocked(const GUIGlObjectType type) const;

        /// @brief show type Entries (depending if we're in Network or demand supermode)
        void showTypeEntries();

    private:
        /// @brief pointer to Selector Frame Parent
        GNESelectorFrame* mySelectorFrameParent;

        /// @brief check boxes for type-based selection locking and selected object counts
        std::map<GUIGlObjectType, ObjectTypeEntry*> myTypeEntries;

        /// @brief Invalidated copy constructor.
        LockGLObjectTypes(const LockGLObjectTypes&) = delete;

        /// @brief Invalidated assignment operator.
        LockGLObjectTypes& operator=(const LockGLObjectTypes&) = delete;
    };

    // ===========================================================================
    // class ModificationMode
    // ===========================================================================

    class ModificationMode : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNESelectorFrame::ModificationMode)

    public:
        /// @brief operations of selector
        enum class Operation {
            ADD,
            SUB,
            RESTRICT,
            REPLACE,
            DEFAULT
        };

        /// @brief constructor
        ModificationMode(GNESelectorFrame* selectorFrameParent);

        /// @brief destructor
        ~ModificationMode();

        /// @brief get current modification mode
        Operation getModificationMode() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief called when user change type of selction operation
        long onCmdSelectModificationMode(FXObject*, FXSelector, void*);

        /// @}

    protected:
        /// @brief FOX need this
        FOX_CONSTRUCTOR(ModificationMode)

    private:
        /// @brief add radio button
        FXRadioButton* myAddRadioButton;

        /// @brief remove radio button
        FXRadioButton* myRemoveRadioButton;

        /// @brief keep button
        FXRadioButton* myKeepRadioButton;

        /// @brief replace radio button
        FXRadioButton* myReplaceRadioButton;

        /// @brief how to modify selection
        Operation myModificationModeType;

        /// @brief Invalidated copy constructor.
        ModificationMode(const ModificationMode&) = delete;

        /// @brief Invalidated assignment operator.
        ModificationMode& operator=(const ModificationMode&) = delete;
    };

    // ===========================================================================
    // class VisualScaling
    // ===========================================================================

    class VisualScaling : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNESelectorFrame::VisualScaling)

    public:
        /// @brief constructor
        VisualScaling(GNESelectorFrame* selectorFrameParent);

        /// @brief destructor
        ~VisualScaling();

        /// @name FOX-callbacks
        /// @{

        /// @brief Called when the user changes visual scaling
        long onCmdScaleSelection(FXObject*, FXSelector, void*);

        /// @}

    protected:
        /// @brief FOX need this
        FOX_CONSTRUCTOR(VisualScaling)

    private:
        /// @brief pointer to Selector Frame Parent
        GNESelectorFrame* mySelectorFrameParent;

        /// @brief Spinner for selection scaling
        FXRealSpinner* mySelectionScaling;

        /// @brief Invalidated copy constructor.
        VisualScaling(const VisualScaling&) = delete;

        /// @brief Invalidated assignment operator.
        VisualScaling& operator=(const VisualScaling&) = delete;
    };

    // ===========================================================================
    // class SelectionOperation
    // ===========================================================================

    class SelectionOperation : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNESelectorFrame::SelectionOperation)

    public:
        /// @brief constructor
        SelectionOperation(GNESelectorFrame* selectorFrameParent);

        /// @brief destructor
        ~SelectionOperation();

        /// @name FOX-callbacks
        /// @{

        /**@brief Called when the user presses the Load-button
         * @note Opens a file dialog and forces the parent to load the list of selected
         * objects when a file was chosen. Rebuilds the list, then, and redraws itself.
         */
        long onCmdLoad(FXObject*, FXSelector, void*);

        /** @brief Called when the user presses the Save-button
         * @note Opens a file dialog and forces the selection container to save the list
           of selected objects when a file was chosen. If the saveing failed, a message window is shown.
         */
        long onCmdSave(FXObject*, FXSelector, void*);

        /**@brief Called when the user presses the Clear-button
         * @note Clear the internal list and calls GUISelectedStorage::clear and repaints itself
         */
        long onCmdClear(FXObject*, FXSelector, void*);

        /**@brief Called when the user presses the Invert-button
         * @note invert the selection and repaints itself
         */
        long onCmdInvert(FXObject*, FXSelector, void*);

        /// @}

    protected:
        /// @brief FOX need this
        FOX_CONSTRUCTOR(SelectionOperation)

    private:
        /// @brief pointer to Selector Frame Parent
        GNESelectorFrame* mySelectorFrameParent;

        /// @brief Invalidated copy constructor.
        SelectionOperation(const SelectionOperation&) = delete;

        /// @brief Invalidated assignment operator.
        SelectionOperation& operator=(const SelectionOperation&) = delete;
    };

    /**@brief Constructor
     * @brief parent FXHorizontalFrame in which this GNEFrame is placed
     * @brief viewNet viewNet that uses this GNEFrame
     */
    GNESelectorFrame(FXHorizontalFrame* horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNESelectorFrame();

    /// @brief show Frame
    void show();

    /// @brief hide Frame
    void hide();

    /// @brief clear current selection with possibility of undo/redo
    void clearCurrentSelection() const;

    /**@brief apply list of ids to the current selection according to Operation,
     * @note if setop==DEFAULT than the currently set mode (myOperation) is used
     */
    void handleIDs(const std::vector<GNEAttributeCarrier*>& ACs, const ModificationMode::Operation setop = ModificationMode::Operation::DEFAULT);

    /// @brief get selected items Modul
    LockGLObjectTypes* getLockGLObjectTypes() const;

    /// @brief get modification mode modul
    ModificationMode* getModificationModeModul() const;

private:
    /// @brief modul for lock selected items
    LockGLObjectTypes* myLockGLObjectTypes;

    /// @brief modul for change modification mode
    ModificationMode* myModificationMode;

    /// @brief moduls for select element set
    GNEElementSet* myNetworkElementSet, *myDemandElementSet, *myDataElementSet;

    /// @brief modul for match generic data attribute
    GNEMatchGenericDataAttribute* myMatchGenericDataAttribute;

    /// @brief modul for visual scaling
    VisualScaling* myVisualScaling;

    /// @brief modul for selection operations
    SelectionOperation* mySelectionOperation;

    /// @brief check if there is ACs to select/unselect
    bool ACsToSelected() const;

    /**@brief return ACs of the given type with matching attrs
     * @param[in] ACTag XML Tag of AttributeCarrier
     * @param[in] ACAttr XML Attribute of AttributeCarrier
     * @param[in] compOp One of {<,>,=} for matching against val or '@' for matching against expr
     */
    std::vector<GNEAttributeCarrier*> getMatches(const SumoXMLTag ACTag, const SumoXMLAttr ACAttr, const char compOp, const double val, const std::string& expr);

    /**@brief return GenericDatas of the given type with matching attrs
     * @param[in] genericDatas list of filter generic datas
     * @param[in] attr XML Attribute used to filter
     * @param[in] compOp One of {<,>,=} for matching against val or '@' for matching against expr
     */
    std::vector<GNEAttributeCarrier*> getGenericMatches(const std::vector<GNEGenericData*>& genericDatas, const std::string& attr, const char compOp, const double val, const std::string& expr);

    /// @brief Invalidated copy constructor.
    GNESelectorFrame(const GNESelectorFrame&) = delete;

    /// @brief Invalidated assignment operator.
    GNESelectorFrame& operator=(const GNESelectorFrame&) = delete;
};
