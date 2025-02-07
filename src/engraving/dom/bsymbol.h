/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __BSYMBOL_H__
#define __BSYMBOL_H__

#include <vector>

#include "engravingitem.h"

namespace mu::engraving {
//---------------------------------------------------------
//   @@ BSymbol
///    base class for Symbol and Image
//---------------------------------------------------------

class BSymbol : public EngravingItem
{
    OBJECT_ALLOCATOR(engraving, BSymbol)
public:

    Segment* segment() const { return (Segment*)explicitParent(); }

    // Score Tree functions
    EngravingObject* scanParent() const override;
    EngravingObjectList scanChildren() const override;
    void scanElements(void* data, void (* func)(void*, EngravingItem*), bool all=true) override;

    BSymbol& operator=(const BSymbol&) = delete;

    void add(EngravingItem*) override;
    void remove(EngravingItem*) override;
    bool acceptDrop(EditData&) const override;
    EngravingItem* drop(EditData&) override;
    mu::RectF drag(EditData&) override;

    Align align() const { return m_align; }
    void setAlign(Align a) { m_align = a; }

    const std::vector<EngravingItem*>& leafs() const { return m_leafs; }
    std::vector<EngravingItem*>& leafs() { return m_leafs; }
    mu::PointF pagePos() const override;
    mu::PointF canvasPos() const override;
    std::vector<mu::LineF> dragAnchorLines() const override;

protected:
    BSymbol(const ElementType& type, EngravingItem* parent, ElementFlags f = ElementFlag::NOTHING);
    BSymbol(const BSymbol&);

private:

    std::vector<EngravingItem*> m_leafs;
    Align m_align = { AlignH::LEFT, AlignV::BASELINE };
};
} // namespace mu::engraving
#endif
