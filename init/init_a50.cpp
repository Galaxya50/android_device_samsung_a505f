/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
*/

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <android-base/properties.h>
#include <android-base/logging.h>
#include <vector>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<string> ro_props_default_source_order = {
    "",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor.",
};

void property_override(string prop, string value) {
    auto pi = (prop_info*) __system_property_find(prop.c_str());

    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void set_ro_build_prop(const string &prop, const string &value, bool product = true) {
    string prop_name;

    for (const auto &source : ro_props_default_source_order) {
        if (product)
            prop_name = "ro.product." + source + prop;
        else
            prop_name = "ro." + source + "build." + prop;

        property_override(prop_name.c_str(), value.c_str());
    }
}

void set_build_fingerprint(string device, string name, string build) {
    string build_fingerprint;

    build_fingerprint = "samsung/" + name + "/" + device + ":11/RP1A.200720.012/" + build + ":user/release-keys";
    set_ro_build_prop("fingerprint", build_fingerprint, false);
    property_override("ro.bootimage.build.fingerprint", build_fingerprint);

    set_ro_build_prop("name", name);
    set_ro_build_prop("name", name, false);
    set_ro_build_prop("device", device);
    set_ro_build_prop("device", device, false);
}

void vendor_load_properties() {
    string model;

    model = GetProperty("ro.boot.product.model", "");
    if(model.empty()){
        model = GetProperty("ro.boot.em.model", "");
    }

    if (model == "SM-A505F") {
        set_build_fingerprint("a50", "a50dd", "A505FDDS9CUK1");
    } else if (model == "SM-A505FN") {
        set_build_fingerprint("a50", "a50xx", "A505FNXXS9CUJ1");
    } else if (model == "SM-A505G") {
        set_build_fingerprint("a50", "a50ub", "A505GUBS9CVA3");
    } else if (model == "SM-A505GN") {
        set_build_fingerprint("a50", "a50xtc", "A505GNDXS9CVA1");
    } else {
        LOG(ERROR) << __func__ << ": Coudn't indentify model!";
    }

    set_ro_build_prop("model", model);
    set_ro_build_prop("product", model, false);
}