/*
 * Copyright (c) 2016, Egor Pugin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder nor the names of
 *        its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "common.h"

#include <functional>
#include <memory>

struct sqlite3;
class SqliteDatabase;

sqlite3 *load_from_file_to_memory(const String &fn);
void save_from_memory_to_file(const String &fn, sqlite3 *db);

class SqliteDatabase
{
    typedef int(*Sqlite3Callback)(void*, int, char**, char**);
    typedef std::function<int(int, char**, char**)> DatabaseCallback;

public:
    SqliteDatabase();
    SqliteDatabase(sqlite3 *db);
    SqliteDatabase(const String &dbname);
    ~SqliteDatabase();

    void loadDatabase(const String &dbname);
    void save(const path &fn) const;

    bool isLoaded() const;
    sqlite3 *getDb() const;

    String getName() const;
    String getFullName() const;

    bool execute(const String &sql, void *object, Sqlite3Callback callback, bool nothrow = false, String *errmsg = 0) const;
    bool execute(const String &sql, DatabaseCallback callback = DatabaseCallback(), bool nothrow = false, String *errmsg = 0) const;

private:
    sqlite3 *db = nullptr;
    String name;
    String fullName;
};
