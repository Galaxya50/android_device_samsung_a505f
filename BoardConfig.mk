#
# Copyright (C) 2020-2021 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

## Inherit from the common tree
include device/samsung/universal9610-common/BoardConfigCommon.mk

## Inherit from the proprietary configuration
include vendor/samsung/a50/BoardConfigVendor.mk

DEVICE_PATH := device/samsung/a50

TARGET_OTA_ASSERT_DEVICE := a50

## APEX image
DEXPREOPT_GENERATE_APEX_IMAGE := true

# Init
TARGET_INIT_VENDOR_LIB := //$(DEVICE_PATH):libinit_a50

## Manifest
DEVICE_MANIFEST_FILE += $(DEVICE_PATH)/device_manifest.xml

## Properties
TARGET_VENDOR_PROP += $(DEVICE_PATH)/vendor.prop
