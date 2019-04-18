// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#ifndef USER_IDENTIFICATION_SERVICE_FILE_MONITOR_H
#define USER_IDENTIFICATION_SERVICE_FILE_MONITOR_H

#include <glibmm.h>
#include <giomm/file.h>
#include <giomm/filemonitor.h>

#include <memory>
#include <string>

namespace UserIdentificationDBusService::FileMonitor
{
    class FileMonitor
    {
    public:
        FileMonitor() = default;
        ~FileMonitor() = default;

        int run();

    private:
        static void on_file_changed(const Glib::RefPtr<Gio::File> &old_file,
                             const Glib::RefPtr<Gio::File> &new_file,
                             Gio::FileMonitorEvent monitorEvent);
    };
}

#endif // USER_IDENTIFICATION_SERVICE_FILE_MONITOR_H
