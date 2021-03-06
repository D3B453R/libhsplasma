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

#include "pyAGChannel.h"

#include <PRP/Avatar/plScalarChannel.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ScalarControllerCacheChannel, plScalarControllerCacheChannel)

PY_PLASMA_TYPE(ScalarControllerCacheChannel, plScalarControllerCacheChannel,
               "plScalarControllerCacheChannel wrapper")

PY_PLASMA_TYPE_INIT(ScalarControllerCacheChannel) {
    pyScalarControllerCacheChannel_Type.tp_new = pyScalarControllerCacheChannel_new;
    pyScalarControllerCacheChannel_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_CheckAndReady(&pyScalarControllerCacheChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarControllerCacheChannel_Type);
    return (PyObject*)&pyScalarControllerCacheChannel_Type;
}

PY_PLASMA_IFC_METHODS(ScalarControllerCacheChannel, plScalarControllerCacheChannel)
