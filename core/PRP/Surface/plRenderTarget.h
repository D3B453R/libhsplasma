/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLRENDERTARGET_H
#define _PLRENDERTARGET_H

#include "plBitmap.h"
#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plRenderTarget : public virtual plBitmap {
    CREATABLE(plRenderTarget, kRenderTarget, plBitmap)

protected:
    unsigned short fWidth, fHeight;
    union {
        struct {
            unsigned short fLeft, fTop, fRight, fBottom;
        } fAbsolute;
        struct {
            float fLeft, fTop, fRight, fBottom;
        } fProportional;
    } fViewport;
    bool fProportionalViewport;
    unsigned char fZDepth, fStencilDepth;

public:
    plRenderTarget() : fWidth(0), fHeight(0), fProportionalViewport(false),
                       fZDepth(0), fStencilDepth(0) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    void readData(hsStream* S);
    void writeData(hsStream* S);

protected:
    void IRead(hsStream* S);
    void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned short getWidth() const { return fWidth; }
    unsigned short getHeight() const { return fHeight; }
    bool getProportionalViewport() const { return fProportionalViewport; }
    unsigned char getZDepth() const { return fZDepth; }
    unsigned char getStencilDepth() const { return fStencilDepth; }

    float getProportionalViewportLeft() const { return fViewport.fProportional.fLeft; }
    float getProportionalViewportTop() const { return fViewport.fProportional.fTop; }
    float getProportionalViewportRight() const { return fViewport.fProportional.fRight; }
    float getProportionalViewportBottom() const { return fViewport.fProportional.fBottom; }

    unsigned short getAbsoluteViewportLeft() const { return fViewport.fAbsolute.fLeft; }
    unsigned short getAbsoluteViewportTop() const { return fViewport.fAbsolute.fTop; }
    unsigned short getAbsoluteViewportRight() const { return fViewport.fAbsolute.fRight; }
    unsigned short getAbsoluteViewportBottom() const { return fViewport.fAbsolute.fBottom; }

    void setWidth(unsigned short value) { fWidth = value; }
    void setHeight(unsigned short value) { fHeight = value; }
    void setProportionalViewport(bool value) { fProportionalViewport = value; }
    void setZDepth(unsigned char value) { fZDepth = value; }
    void setStencilDepth(unsigned char value) { fStencilDepth = value; }

    void setProportionalViewportLeft(float value) { fViewport.fProportional.fLeft = value; }
    void setProportionalViewportTop(float value) { fViewport.fProportional.fTop = value; }
    void setProportionalViewportRight(float value) { fViewport.fProportional.fRight = value; }
    void setProportionalViewportBottom(float value) { fViewport.fProportional.fBottom = value; }

    void setAbsoluteViewportLeft(float value) { fViewport.fAbsolute.fLeft = value; }
    void setAbsoluteViewportTop(float value) { fViewport.fAbsolute.fTop = value; }
    void setAbsoluteViewportRight(float value) { fViewport.fAbsolute.fRight = value; }
    void setAbsoluteViewportBottom(float value) { fViewport.fAbsolute.fBottom = value; }
};


class PLASMA_DLL plCubicRenderTarget : public virtual plRenderTarget {
    CREATABLE(plCubicRenderTarget, kCubicRenderTarget, plRenderTarget)

public:
    enum Faces {
        kLeftFace, kRightFace, kFrontFace, kBackFace, kTopFace, kBottomFace
    };

protected:
    plRenderTarget fFaces[6];

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plRenderTarget* getFace(size_t which) { return &fFaces[which]; }
};

#endif
