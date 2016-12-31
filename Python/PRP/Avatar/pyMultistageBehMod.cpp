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

#include "pyMultistageBehMod.h"

#include <PRP/Avatar/plMultistageBehMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(MultistageBehMod, plMultistageBehMod)

static PyObject* pyMultistageBehMod_addStage(pyMultistageBehMod* self, PyObject* args) {
    pyAnimStage* anim;
    if (!PyArg_ParseTuple(args, "O", &anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    if (!pyAnimStage_Check((PyObject*)anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    self->fThis->addStage(anim->fThis);
    anim->fPyOwned = false;
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_delStage(pyMultistageBehMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delStage expects an int");
        return NULL;
    }
    self->fThis->delStage(idx);
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_clearStages(pyMultistageBehMod* self) {
    self->fThis->clearStages();
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_addReceiver(pyMultistageBehMod* self, PyObject* args) {
    pyKey* rcvr;
    if (!PyArg_ParseTuple(args, "O", &rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    self->fThis->addReceiver(*rcvr->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_delReceiver(pyMultistageBehMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }
    self->fThis->delReceiver(idx);
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_clearReceivers(pyMultistageBehMod* self) {
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_getStages(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStages().size());
    for (size_t i=0; i<self->fThis->getStages().size(); i++)
        PyList_SET_ITEM(list, i, ICreate(self->fThis->getStages()[i]));
    return list;
}

static PyObject* pyMultistageBehMod_getReceivers(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getReceivers().size());
    for (size_t i=0; i<self->fThis->getReceivers().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

static int pyMultistageBehMod_setStages(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add stages, use addStage()");
    return -1;
}

static int pyMultistageBehMod_setReceivers(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver()");
    return -1;
}

static PyMethodDef pyMultistageBehMod_Methods[] = {
    { "addStage", (PyCFunction)pyMultistageBehMod_addStage, METH_VARARGS,
      "Params: stage\n"
      "Add a plAnimStage to the behavior mod" },
    { "delStage", (PyCFunction)pyMultistageBehMod_delStage, METH_VARARGS,
      "Params: idx\n"
      "Remove a stage from the behavior mod" },
    { "clearStages", (PyCFunction)pyMultistageBehMod_clearStages, METH_NOARGS,
      "Remove all stages from the behavior mod" },
    { "addReceiver", (PyCFunction)pyMultistageBehMod_addReceiver, METH_VARARGS,
      "Params: key\n"
      "Add a receiver key to the behavior mod" },
    { "delReceiver", (PyCFunction)pyMultistageBehMod_delReceiver, METH_VARARGS,
      "Params: idx\n"
      "Remove a receiver from the behavior mod" },
    { "clearReceivers", (PyCFunction)pyMultistageBehMod_clearReceivers, METH_NOARGS,
      "Remove all receivers from the behavior mod" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(bool, MultistageBehMod, freezePhys, getFreezePhys, setFreezePhys)
PY_PROPERTY(bool, MultistageBehMod, smartSeek, getSmartSeek, setSmartSeek)
PY_PROPERTY(bool, MultistageBehMod, reverseFBControlsOnRelease,
            getReverseFBControlsOnRelease, setReverseFBControlsOnRelease)

static PyGetSetDef pyMultistageBehMod_GetSet[] = {
    { _pycs("stages"), (getter)pyMultistageBehMod_getStages,
        (setter)pyMultistageBehMod_setStages, NULL, NULL },
    { _pycs("receivers"), (getter)pyMultistageBehMod_getReceivers,
        (setter)pyMultistageBehMod_setReceivers, NULL, NULL },
    pyMultistageBehMod_freezePhys_getset,
    pyMultistageBehMod_smartSeek_getset,
    pyMultistageBehMod_reverseFBControlsOnRelease_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyMultistageBehMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plMultistageBehMod",    /* tp_name */
    sizeof(pyMultistageBehMod),         /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plMultistageBehMod wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMultistageBehMod_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyMultistageBehMod_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMultistageBehMod_new,             /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyMultistageBehMod_Type() {
    pyMultistageBehMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyMultistageBehMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyMultistageBehMod_Type);
    return (PyObject*)&pyMultistageBehMod_Type;
}

PY_PLASMA_IFC_METHODS(MultistageBehMod, plMultistageBehMod)

}
