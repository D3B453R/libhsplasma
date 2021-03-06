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

#include "plShadowMaster.h"

/* plShadowMaster */
void plShadowMaster::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fAttenDist = S->readFloat();
    fMaxDist = S->readFloat();
    fMinDist = S->readFloat();
    fMaxSize = S->readInt();
    fMinSize = S->readInt();
    fPower = S->readFloat();
}

void plShadowMaster::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeFloat(fAttenDist);
    S->writeFloat(fMaxDist);
    S->writeFloat(fMinDist);
    S->writeInt(fMaxSize);
    S->writeInt(fMinSize);
    S->writeFloat(fPower);
}

void plShadowMaster::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->startTag("ShadowParams");
    prc->writeParam("AttenDist", fAttenDist);
    prc->writeParam("MaxDist", fMaxDist);
    prc->writeParam("MinDist", fMinDist);
    prc->writeParam("MaxSize", fMaxSize);
    prc->writeParam("MinSize", fMinSize);
    prc->writeParam("Power", fPower);
    prc->endTag(true);
}

void plShadowMaster::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ShadowParams") {
        fAttenDist = tag->getParam("AttenDist", "0").to_float();
        fMaxDist = tag->getParam("MaxDist", "0").to_float();
        fMinDist = tag->getParam("MinDist", "0").to_float();
        fMaxSize = tag->getParam("MaxSize", "0").to_uint();
        fMinSize = tag->getParam("MinSize", "0").to_uint();
        fPower = tag->getParam("Power", "0").to_float();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
