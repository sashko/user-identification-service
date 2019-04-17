// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include <giomm.h>
#include <glibmm.h>

#include <clocale>
#include <cstdlib>
#include <iostream>

#include "common/version.h"
#include "config.h"
#include "daemon/arguments.h"
#include "daemon/daemon.h"

int main(int argc, char *argv[])
{
    std::setlocale(LC_ALL, "");

    Glib::init();
    Gio::init();

    auto arguments = UserIdentificationDBusService::Daemon::Arguments::parse(argc, argv, std::cout);
    if (!arguments)
        return EXIT_FAILURE;

    if (arguments->print_version_and_exit) {
        std::cout << Glib::get_prgname() << " " << UserIdentificationDBusService::Common::VERSION << '\n';
        return EXIT_SUCCESS;
    }

    UserIdentificationDBusService::Daemon::Daemon daemon;

    return daemon.run();
}
