/*
 * Copyright (C) 2017 Red Hat, Inc.
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.`
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef LIBDNF_MODULE_FORM_PY_H
#define LIBDNF_MODULE_FORM_PY_H

#include "hy-module-form.hpp"

extern PyTypeObject module_form_Type;

libdnf::ModuleForm * moduleFormFromPyObject(PyObject *o);
PyObject *moduleFormToPyObject(libdnf::ModuleForm * module_form);
int module_form_converter(PyObject *o, libdnf::ModuleForm ** module_form_ptr);

#endif //LIBDNF_MODULE_FORM_PY_H
