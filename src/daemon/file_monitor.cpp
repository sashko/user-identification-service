// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "daemon/file_monitor.h"

#include <glib-unix.h>
#include <glib.h>
#include <glibmm.h>

#include <cassert>
#include <csignal>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>

#define FILE_NAME "/home/sashko/pelux-user-id"

namespace UserIdentificationDBusService::FileMonitor
{
    void FileMonitor::on_file_changed(const Glib::RefPtr<Gio::File> &file,
                                      const Glib::RefPtr<Gio::File> &other_file,
                                      Gio::FileMonitorEvent event_type)
    {
        (void)file;
        (void)other_file;

        int uid;

        if (event_type == Gio::FILE_MONITOR_EVENT_CHANGED) {
            g_info("File changed");

            std::ifstream uid_file(FILE_NAME);
            if (!uid_file) {
                g_error("Could not open uid.file");

                return;
            }

            uid_file >> uid;
            g_info("ID: %d", uid);

            uid_file.close();
        }
    }

    int FileMonitor::run()
    {
        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(FILE_NAME);
        Glib::RefPtr<Gio::FileMonitor> monitor = file->monitor_file(Gio::FILE_MONITOR_NONE);

        g_info("Monitoring file...");
        monitor->signal_changed().connect(sigc::ptr_fun(on_file_changed));

        return EXIT_SUCCESS;
    }
}
