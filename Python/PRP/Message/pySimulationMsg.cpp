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

#include "pySimulationMsg.h"
#include "pyMessage.h"

#include <PRP/Message/plSimulationMsg.h>

PY_PLASMA_NEW(SimulationMsg, plSimulationMsg)

PY_PLASMA_TYPE(SimulationMsg, plSimulationMsg, "plSimulationMsg wrapper")

PY_PLASMA_TYPE_INIT(SimulationMsg) {
    pySimulationMsg_Type.tp_new = pySimulationMsg_new;
    pySimulationMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pySimulationMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pySimulationMsg_Type);
    return (PyObject*)&pySimulationMsg_Type;
}

PY_PLASMA_IFC_METHODS(SimulationMsg, plSimulationMsg)
