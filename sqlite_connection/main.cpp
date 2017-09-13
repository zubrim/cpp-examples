/*!
This program is an example of steps to allow embedded database connectivity to a C++ program.
A database containing simple notes with logging function was implemented.
*/
#include <iostream>
#include <map>
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "note.h"

using namespace Poco::Data::Keywords;
using namespace Poco::Data;
using Poco::Data::Session;
using Poco::Data::Statement;

int main(int argc, char* argv[]) {

	/// register connector and create a session
	/// sqlite3.db is a default database file
	Poco::Data::SQLite::Connector::registerConnector();
	Session session("SQLite", "assets/sqlite3.db");
	/// turn on FOREIGN KEYS support
	session << "PRAGMA foreign_keys = ON", now;
	/// create tables (Notes and Logs)
	session << "DROP TABLE IF EXISTS notes", now;
	session << "CREATE TABLE notes("
		"uid INTEGER PRIMARY KEY AUTOINCREMENT,"
		"title TEXT)",
		now;
	session << "DROP TABLE IF EXISTS logs", now;
	session << "CREATE TABLE logs("
		"note_uid INTEGER,"
		"timestamp INTEGER,"
		"action INTEGER,"
		"CONSTRAINT note_action UNIQUE (note_uid,timestamp,action),"
		"FOREIGN KEY (note_uid) REFERENCES notes(uid) ON DELETE CASCADE)",
		now;

	/// insert a note
	std::string title = "This is the first note in the database";
	session << "INSERT INTO notes(title) VALUES (?)", use(title), now;
	/// insert corresponding log record
	Poco::UInt64 note_uid;
	Poco::UInt8 action = 0; /// i.e. note creation
	session << "SELECT last_insert_rowid()", into(note_uid), now;
	Poco::Timestamp timestamp;
	timestamp.update();
	Poco::UInt64 timestamp_value = timestamp.epochMicroseconds();
	session << "INSERT INTO logs VALUES(?,?,?)",
		use(note_uid),
		use(timestamp_value),
		use(action),
		now;

	/// update the note
	title = "This is the first note UPDATED";
	session << "UPDATE notes SET title = (?) WHERE uid = (?)",
		use(title),
		use(note_uid),
		now;
	/// log this update
	action = 1; /// i.e. update
	timestamp.update();
	timestamp_value = timestamp.epochMicroseconds();
	session << "INSERT INTO logs VALUES(?,?,?)",
		use(note_uid),
		use(timestamp_value),
		use(action),
		now;

	/// get notes from the database to Note objects with STL
	std::vector<Note> notes;
	session << "SELECT uid, title FROM notes", into(notes), now;
	/// let's work with the first row
	Note note = notes.at(0);
	Log logs;
	note.setlog_ptr(logs);
	note_uid = note.getuid();
	/// get all logs for note with uid = 1 
	session << "SELECT * FROM logs WHERE note_uid = (?)", into(logs), use(note_uid), now;
	note.print_log();

	system("pause");
}