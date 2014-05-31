/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 */

#ifndef PYTP_H
#define PYTP_H
#include <Python.h>

extern "C"
{
    PyMODINIT_FUNC initTextParser(void);
    static PyObject* TextParser_getInstanceSingleton(PyObject* self, PyObject* args);
    static PyObject* TextParser_createInstance(PyObject* self, PyObject* args);
    static PyObject* TextParser_deleteInstance(PyObject* self, PyObject* args);
    static PyObject* TextParser_read(PyObject* self, PyObject* args);
    static PyObject* TextParser_write(PyObject* self, PyObject* args);
    static PyObject* TextParser_remove(PyObject* self, PyObject* args);
    static PyObject* TextParser_getAllLabels(PyObject* self, PyObject* args);
    static PyObject* TextParser_getType(PyObject* self, PyObject* args);
    static PyObject* TextParser_getValue(PyObject* self, PyObject* args);
    static PyObject* TextParser_currentNode(PyObject* self, PyObject* args);
    static PyObject* TextParser_getNodes(PyObject* self, PyObject* args);
    static PyObject* TextParser_getLabels(PyObject* self, PyObject* args);
    static PyObject* TextParser_changeNode(PyObject* self, PyObject* args);
    static PyObject* TextParser_updateValue(PyObject* self, PyObject* args);
    static PyObject* TextParser_deleteLeaf(PyObject* self, PyObject* args);
    static PyObject* TextParser_createLeaf(PyObject* self, PyObject* args);
    static PyObject* TextParser_splitRange(PyObject* self, PyObject* args);
    static PyObject* TextParser_expandRange(PyObject* self, PyObject* args);
    static PyObject* TextParser_splitList(PyObject* self, PyObject* args);
    static PyObject* TextParser_getVersionInfo(PyObject* self, PyObject* args);
}
#endif
