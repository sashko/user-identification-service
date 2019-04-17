// Copyright (C) 2019 Luxoft Sweden AB
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#ifndef USER_IDENTIFICATION_SERVICE_DAEMON_DBUS_SERVICE_H
#define USER_IDENTIFICATION_SERVICE_DAEMON_DBUS_SERVICE_H

#include <glibmm.h>

#include "generated/dbus/user_identification_common.h"
#include "generated/dbus/user_identification_stub.h"

namespace UserIdentificationDBusService::Daemon
{
    class DBusService
    {
    public:
        explicit DBusService(const Glib::RefPtr<Glib::MainLoop> &main_loop);
        ~DBusService();

        DBusService(const DBusService &other) = delete;
        DBusService(DBusService &&other) = delete;
        DBusService &operator=(const DBusService &other) = delete;
        DBusService &operator=(DBusService &&other) = delete;

        void own_name();
        void unown_name();

    private:
        class UserIdentification : public com::luxoft::UserIdentificationStub
        {
        public:
            void RemoveMeFoo(guint32 number, MethodInvocation &invocation) override;

            bool RemoveMeBaz_setHandler(bool value) override;
            bool RemoveMeBaz_get() override;

        private:
            bool remove_me_baz_ = false;
        };

        void bus_acquired(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                          const Glib::ustring &name);
        void name_acquired(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                           const Glib::ustring &name);
        void name_lost(const Glib::RefPtr<Gio::DBus::Connection> &connection,
                       const Glib::ustring &name);

        Glib::RefPtr<Glib::MainLoop> main_loop_;
        guint connection_id_ = 0;

        UserIdentification user_identification_;
    };
}

#endif // USER_IDENTIFICATION_SERVICE_DAEMON_DBUS_SERVICE_H
