/*
 * Copyright (C) 2017-2018 Red Hat, Inc.
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
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

#include "hy-module-form.h"
#include "hy-module-form.hpp"

#include <regex/regex.hpp>

namespace libdnf {

#define MODULE_NAME "([-a-zA-Z0-9\\._]+)"
#define MODULE_STREAM MODULE_NAME
#define MODULE_VERSION "([0-9]+)"
#define MODULE_CONTEXT "([0-9a-f]+)"
#define MODULE_ARCH MODULE_NAME
#define MODULE_PROFILE MODULE_NAME

constexpr const char * module_form_regex[] = {
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION ":" MODULE_CONTEXT "::?" MODULE_ARCH "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION ":" MODULE_CONTEXT "::?" MODULE_ARCH "\\/?" "()"           "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION     "()"           "::"  MODULE_ARCH "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION     "()"           "::"  MODULE_ARCH "\\/?" "()"           "$",
    "^" MODULE_NAME ":" MODULE_STREAM     "()"               "()"           "::"  MODULE_ARCH "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM     "()"               "()"           "::"  MODULE_ARCH "\\/?" "()"           "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION ":" MODULE_CONTEXT       "()"        "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION     "()"                 "()"        "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION ":" MODULE_CONTEXT       "()"        "\\/?" "()"           "$",
    "^" MODULE_NAME ":" MODULE_STREAM ":" MODULE_VERSION     "()"                 "()"        "\\/?" "()"           "$",
    "^" MODULE_NAME ":" MODULE_STREAM     "()"               "()"                 "()"        "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME ":" MODULE_STREAM     "()"               "()"                 "()"        "\\/?" "()"           "$",
    "^" MODULE_NAME     "()"              "()"               "()"           "::"  MODULE_ARCH "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME     "()"              "()"               "()"           "::"  MODULE_ARCH "\\/?" "()"           "$",
    "^" MODULE_NAME     "()"              "()"               "()"                 "()"        "\\/"  MODULE_PROFILE "$",
    "^" MODULE_NAME     "()"              "()"               "()"                 "()"        "\\/?" "()"           "$"
};

bool ModuleForm::parse(const char *moduleFormStr, HyModuleFormEnum form)
{
    enum { NAME = 1, STREAM = 2, VERSION = 3, CONTEXT = 4, ARCH = 5, PROFILE = 6, _LAST_ };
    Regex reg(module_form_regex[form - 1], REG_EXTENDED);
    auto matchResult = reg.match(moduleFormStr, false, _LAST_);
    if (!matchResult.isMatched() || matchResult.getMatchedLen(NAME) == 0)
        return false;
    name = matchResult.getMatchedString(NAME);
    if (matchResult.getMatchedLen(VERSION) > 0)
        version = atoll(matchResult.getMatchedString(VERSION).c_str());
    else
        version = -1;
    stream = matchResult.getMatchedString(STREAM);
    context = matchResult.getMatchedString(CONTEXT);
    arch = matchResult.getMatchedString(ARCH);
    profile = matchResult.getMatchedString(PROFILE);
    return true;
}

void
ModuleForm::clear()
{
    name.clear();
    stream.clear();
    version = -1;
    context.clear();
    arch.clear();
    profile.clear();
}

}

HyModuleForm
hy_module_form_create()
{
    return new libdnf::ModuleForm;
}

void
hy_module_form_free(HyModuleForm module_form)
{
    delete module_form;
}

HyModuleForm
hy_module_form_clone(HyModuleForm module_form)
{
    return new libdnf::ModuleForm(*module_form);
}

const char *
hy_module_form_get_string(HyModuleForm module_form, int which)
{
    switch (which) {
        case HY_MODULE_FORM_NAME:
            return module_form->getName().empty() ? nullptr : module_form->getName().c_str();
        case HY_MODULE_FORM_STREAM:
            return module_form->getStream().empty() ? nullptr : module_form->getStream().c_str();
        case HY_MODULE_FORM_CONTEXT:
            return module_form->getContext().empty() ? nullptr : module_form->getContext().c_str();
        case HY_MODULE_FORM_ARCH:
            return module_form->getArch().empty() ? nullptr : module_form->getArch().c_str();
        case HY_MODULE_FORM_PROFILE:
            return module_form->getProfile().empty() ? nullptr : module_form->getProfile().c_str();
        default:
            return nullptr;
    }
}

void
hy_module_form_set_string(HyModuleForm module_form, int which, const char* str_val)
{
    auto tmp = str_val ? str_val : "";
    switch (which) {
        case HY_MODULE_FORM_NAME:
            module_form->setName(tmp);
            break;
        case HY_MODULE_FORM_STREAM:
            module_form->setStream(tmp);
            break;
        case HY_MODULE_FORM_CONTEXT:
            module_form->setContext(tmp);
            break;
        case HY_MODULE_FORM_ARCH:
            module_form->setArch(tmp);
            break;
        case HY_MODULE_FORM_PROFILE:
            module_form->setProfile(tmp);
        default:;
    }
}

long long
hy_module_form_get_version(HyModuleForm module_form)
{
    return module_form->getVersion();
}

void
hy_module_form_set_version(HyModuleForm module_form, long long version)
{
    module_form->setVersion(version);
}
