/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 */

#include <Python.h>
#include <string>
#include "TextParser.h"
#include "TextParser_python_api.h"

static PyMethodDef TextParser_method[] = {
    {"getInstanceSingleton", TextParser_getInstanceSingleton, METH_VARARGS, "return TextParser's singleton instance"},
    {"createInstance", TextParser_createInstance, METH_VARARGS, "return TextParser's instance"},
    {"deleteInstance", TextParser_deleteInstance, METH_VARARGS, "delete TextParser's instance"},
    {"read", TextParser_read, METH_VARARGS, "wrapper method for TextParser::read()"},
    {"write", TextParser_write, METH_VARARGS, "wrapper method for TextParser::write()"},
    {"remove", TextParser_remove, METH_VARARGS, "wrapper method for TextParser::remove()"},
    {"getAllLabels", TextParser_getAllLabels, METH_VARARGS, "wrapper method for TextParser::getAllLabels()"},
    {"getType", TextParser_getType, METH_VARARGS, "wrapper method for TextParser::getType()"},
    {"getValue", TextParser_getValue, METH_VARARGS, "wrapper method for TextParser::getValue()"},
    {"currentNode", TextParser_currentNode, METH_VARARGS, "wrapper method for TextParser::currentNode()"},
    {"getNodes", TextParser_getNodes, METH_VARARGS, "wrapper method for TextParser::getNodes()"},
    {"getLabels", TextParser_getLabels, METH_VARARGS, "wrapper method for TextParser::getLabels()"},
    {"changeNode", TextParser_changeNode, METH_VARARGS, "wrapper method for TextParser::changeNode()"},
    {"updateValue", TextParser_updateValue, METH_VARARGS, "wrapper method for TextParser::updateValue()"},
    {"deleteLeaf", TextParser_deleteLeaf, METH_VARARGS, "wrapper method for TextParser::deleteLeaf()"},
    {"createLeaf", TextParser_createLeaf, METH_VARARGS, "wrapper method for TextParser::createLeaf()"},
    {"getVersionInfo", TextParser_getVersionInfo, METH_VARARGS, "wrapper method for TextParser::getVersionInfo()"},
    {"splitRange", TextParser_splitRange, METH_VARARGS, "wrapper method for TextParser::splitRange()"},
    {"expandRange", TextParser_expandRange, METH_VARARGS, "wrapper method for TextParser::expandRange()"},
    {"splitList", TextParser_splitList, METH_VARARGS, "wrapper method for TextParser::splitList()"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initTextParser(void)
{
    (void)Py_InitModule("TextParser", TextParser_method);
}

static PyObject* TextParser_getInstanceSingleton(PyObject* self, PyObject* args)
{
    PyObject* ret = PyCObject_FromVoidPtr(static_cast<void*>(TextParser::get_instance_singleton()), NULL);
    return Py_BuildValue("O", ret);
}

static PyObject* TextParser_createInstance(PyObject* self, PyObject* args)
{
    PyObject* ret = PyCObject_FromVoidPtr(static_cast<void*>(new TextParser), NULL);
    return Py_BuildValue("O", ret);
}

static PyObject* TextParser_deleteInstance(PyObject* self, PyObject* args)
{
    PyObject* handle;
    if(!PyArg_ParseTuple(args, "O", &handle))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));
    tp->remove();
    delete tp;
    int         ret = 0;
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_read(PyObject* self, PyObject* args)
{
    // 引数の解析
    const char* filename;
    PyObject*   handle;
    if(!PyArg_ParseTuple(args, "Os", &handle, &filename))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->read(filename);
    if(ret != 0)
    {
        std::cerr<<"MetaData read failed!! ("<<filename<<")"<<std::endl;
    }

    //戻り値を設定
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_write(PyObject* self, PyObject* args)
{
    const char* filename;
    PyObject*   handle;
    if(!PyArg_ParseTuple(args, "Os", &handle, &filename))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->write(filename);
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_remove(PyObject* self, PyObject* args)
{
    PyObject* handle;
    if(!PyArg_ParseTuple(args, "O", &handle))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->remove();
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_getAllLabels(PyObject* self, PyObject* args)
{
    PyObject* handle;
    if(!PyArg_ParseTuple(args, "O", &handle))
    {
        return NULL;
    }
    TextParser*              tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::vector<std::string> labels;
    int                      ret       = tp->getAllLabels(labels);
    PyObject*                py_labels = PyList_New(labels.size());
    int                      i         = 0;
    for(std::vector<std::string>::iterator it = labels.begin(); it != labels.end(); ++it)
    {
        PyList_SetItem(py_labels, i++, Py_BuildValue("s", (*it).c_str()));
    }
    return Py_BuildValue("iO", ret, py_labels);
}

static PyObject* TextParser_getType(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    if(!PyArg_ParseTuple(args, "Os", &handle, &label))
    {
        return NULL;
    }
    TextParser*         tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int                 ierr;
    TextParserValueType ret = tp->getType(label, &ierr);
    return Py_BuildValue("ii", ierr, ret);
}

static PyObject* TextParser_getValue(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    if(!PyArg_ParseTuple(args, "Os", &handle, &label))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::string value;
    int         ret = tp->getValue(label, value);
    return Py_BuildValue("is", ret, value.c_str());
}

static PyObject* TextParser_currentNode(PyObject* self, PyObject* args)
{
    PyObject* handle;
    if(!PyArg_ParseTuple(args, "O", &handle))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::string value;
    int         ret = tp->currentNode(value);
    return Py_BuildValue("is", ret, value.c_str());
}

static PyObject* TextParser_getNodes(PyObject* self, PyObject* args)
{
    PyObject* handle;
    int oswitch=0;
    if(!PyArg_ParseTuple(args, "O|i", &handle, &oswitch))
    {
        return NULL;
    }
    TextParser*              tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::vector<std::string> labels;
    int                      ret       = tp->getNodes(labels, oswitch);
    PyObject*                py_labels = PyList_New(labels.size());
    int                      i         = 0;
    for(std::vector<std::string>::iterator it = labels.begin(); it != labels.end(); ++it)
    {
        PyList_SetItem(py_labels, i++, Py_BuildValue("s", (*it).c_str()));
    }
    return Py_BuildValue("iO", ret, py_labels);
}

static PyObject* TextParser_getLabels(PyObject* self, PyObject* args)
{
    PyObject* handle;
    int oswitch=0;
    if(!PyArg_ParseTuple(args, "O|i", &handle, &oswitch))
    {
        return NULL;
    }
    TextParser*              tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::vector<std::string> labels;
    int                      ret       = tp->getLabels(labels, oswitch);
    PyObject*                py_labels = PyList_New(labels.size());
    int                      i         = 0;
    for(std::vector<std::string>::iterator it = labels.begin(); it != labels.end(); ++it)
    {
        PyList_SetItem(py_labels, i++, Py_BuildValue("s", (*it).c_str()));
    }
    return Py_BuildValue("iO", ret, py_labels);
}

static PyObject* TextParser_changeNode(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    if(!PyArg_ParseTuple(args, "Os", &handle, &label))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->changeNode(label);
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_updateValue(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    const char* value;
    if(!PyArg_ParseTuple(args, "Oss", &handle, &label, &value))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->updateValue(label, value);
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_deleteLeaf(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    if(!PyArg_ParseTuple(args, "Os", &handle, &label))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->deleteLeaf(label);
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_createLeaf(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* label;
    const char* value;
    if(!PyArg_ParseTuple(args, "Oss", &handle, &label, &value))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    int         ret = tp->createLeaf(label, value);
    return Py_BuildValue("i", ret);
}

static PyObject* TextParser_splitRange(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* value;
    if(!PyArg_ParseTuple(args, "Os", &handle, &value))
    {
        return NULL;
    }
    TextParser* tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    double      from;
    double      to;
    double      step;
    int         ret = tp->splitRange(value, &from, &to, &step);

    return Py_BuildValue("iddd", ret, from, to, step);
}

static PyObject* TextParser_expandRange(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* value;
    if(!PyArg_ParseTuple(args, "Os", &handle, &value))
    {
        return NULL;
    }
    TextParser*         tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));

    std::vector<double> expanded;
    int                 ret         = tp->expandRange(value, expanded);
    PyObject*           py_expanded = PyList_New(expanded.size());
    int                 i           = 0;
    for(std::vector<double>::iterator it = expanded.begin(); it != expanded.end(); ++it)
    {
        PyList_SetItem(py_expanded, i++, Py_BuildValue("d", *it));
    }
    return Py_BuildValue("iO", ret, py_expanded);
}

static PyObject* TextParser_splitList(PyObject* self, PyObject* args)
{
    PyObject*   handle;
    const char* value;
    if(!PyArg_ParseTuple(args, "Os", &handle, &value))
    {
        return NULL;
    }
    TextParser*         tp = static_cast<TextParser*>(PyCObject_AsVoidPtr(handle));
    std::vector<double> list;
    TextParserSortOrder order = TP_SORT_NONE;
    int                 ret     = tp->splitList(value, list, order);
    PyObject*           py_list = PyList_New(list.size());
    int                 i       = 0;
    for(std::vector<double>::iterator it = list.begin(); it != list.end(); ++it)
    {
        PyList_SetItem(py_list, i++, Py_BuildValue("d", *it));
    }
    return Py_BuildValue("iO", ret, py_list);
}

static PyObject* TextParser_getVersionInfo(PyObject* self, PyObject* args)
{
    return Py_BuildValue("s", TP_VERSION_NO);
}
