

#include "SQLiteCommand.h"

#include "../../sqlcipher/inc/sqlite3.h"

SQLiteCommand::SQLiteCommand() : stmt_(NULL) {}

SQLiteCommand::~SQLiteCommand() {
  Clear();
}

void SQLiteCommand::Clear() {
  if (stmt_) {
    sqlite3_finalize(stmt_);
    stmt_ = NULL;
  }
}

bool SQLiteCommand::Prepare(const std::string &query) {
#ifdef UNICODE
  int rc = sqlite3_prepare16_v2(database_, query.c_str(), -1, &stmt_, NULL);
#else
  int rc = sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt_, NULL);
#endif
  return rc == SQLITE_OK;
}

bool SQLiteCommand::Execute() {
  sqlite3_step(stmt_);
  return sqlite3_reset(stmt_) == SQLITE_OK;
}

bool SQLiteCommand::BindParam(int index, const unsigned char *blob_buf) {
  int rc = sqlite3_bind_blob(stmt_, index, blob_buf, sizeof(blob_buf), NULL);
  return rc == SQLITE_OK;
}

bool SQLiteCommand::BindParam(int index, const int value) {
  int rc = sqlite3_bind_int(stmt_, index, value);
  return rc == SQLITE_OK;
}

bool SQLiteCommand::BindParam(int index, const double value) {
  int rc = sqlite3_bind_double(stmt_, index, value);
  return rc == SQLITE_OK;
}

bool SQLiteCommand::BindParam(int index, const char *value) {
#ifdef  UNICODE
  int rc = sqlite3_bind_text16(stmt_, index, value, -1, SQLITE_TRANSIENT);
#else
  int rc = sqlite3_bind_text(stmt_, index, value, -1, SQLITE_TRANSIENT);
#endif
  return rc == SQLITE_OK;
}
