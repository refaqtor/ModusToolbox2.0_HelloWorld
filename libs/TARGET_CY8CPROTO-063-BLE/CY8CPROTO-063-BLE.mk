################################################################################
# \file CY8CPROTO-063-BLE.mk
# \version 1.0
#
# \brief
# Define the CY8CPROTO-063-BLE target.
#
################################################################################
# \copyright
# Copyright 2018-2019 Cypress Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

ifeq ($(WHICHFILE),true)
$(info Processing $(lastword $(MAKEFILE_LIST)))
endif

# MCU device selection
DEVICE:=CYBLE-416045-02

# Additional components supported by the target
COMPONENTS+=CM0P_SLEEP BSP_DESIGN_MODUS

# Use CyHAL
DEFINES+=CY_USING_HAL
