#pragma once
#include <vector>
#include <string>
#include "Poco/Timestamp.h"
#include "Poco/Data/TypeHandler.h"


class Log_Entry;
typedef std::vector<Log_Entry> Log;

/// note in the database
class Note {
private:
	Poco::UInt64 uid;
	std::string title;
	Log *log_ptr = nullptr;
public:
	Poco::UInt64 getuid() const;
	std::string gettitle() const;
	Log *getlog_ptr() const;
	void setuid(Poco::UInt64 uid);
	void settitle(std::string text);
	void setlog_ptr(Log& log);
	void print_log();
};

/// log entry for the note in the database
class Log_Entry {
private:
	Poco::UInt64 noteuid;
	Poco::Timestamp timestamp;
	Poco::UInt8 action; /// action 0 - creation, 1 - update
public:
	Poco::UInt64 getnoteuid() const;
	Poco::Timestamp gettimestamp() const;
	Poco::UInt8 getaction() const;
	void setnoteuid(Poco::UInt64);
	void settimestamp(Poco::Timestamp);
	void setaction(Poco::UInt8);

};

/// Definitions for template type handler for class Note and Log_Entry
/// This is according to the User Guide on how to bind objects to the database data types
namespace Poco {
	namespace Data {
		template <>
		class TypeHandler<class Note> {
		public:
			/// the table is defined as Notes (uid INTEGER, title TEXT)
			static void bind(std::size_t pos, const Note& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir) {
				TypeHandler<Poco::UInt64>::bind(pos++, obj.getuid(), pBinder, dir);
				TypeHandler<std::string>::bind(pos++, obj.gettitle(), pBinder, dir);
			};
			static std::size_t size() {
				return 2; // two column table
			};
			static void prepare(std::size_t pos, const Note& obj, AbstractPreparator::Ptr pPrepare) {
				TypeHandler<Poco::UInt64>::prepare(pos++, obj.getuid(), pPrepare);
				TypeHandler<std::string>::prepare(pos++, obj.gettitle(), pPrepare);
			};
			static void extract(std::size_t pos, Note& obj, const Note& defVal, AbstractExtractor::Ptr pExt) {
				Poco::UInt64 uid;
				std::string title;
				TypeHandler<Poco::UInt64>::extract(pos++, uid, defVal.getuid(), pExt);
				TypeHandler<std::string>::extract(pos++, title, defVal.gettitle(), pExt);
				obj.setuid(uid);
				obj.settitle(title);
			};
		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};

		template <>
		class TypeHandler<class Log_Entry> {
		public:
			/// the table is defined as Logs (note_uid INTEGER, timestamp INTEGER, action INTEGER)
			static void bind(std::size_t pos, const Log_Entry& obj, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir) {
				TypeHandler<Poco::UInt64>::bind(pos++, obj.getnoteuid(), pBinder, dir);
				TypeHandler<Poco::UInt64>::bind(pos++, obj.gettimestamp().epochMicroseconds(), pBinder, dir);
				TypeHandler<Poco::UInt8>::bind(pos++, obj.getaction(), pBinder, dir);
			};
			static std::size_t size() {
				return 3; // three column table
			};
			static void prepare(std::size_t pos, const Log_Entry& obj, AbstractPreparator::Ptr pPrepare) {
				TypeHandler<Poco::UInt64>::prepare(pos++, obj.getnoteuid(), pPrepare);
				TypeHandler<Poco::UInt64>::prepare(pos++, obj.gettimestamp().epochMicroseconds(), pPrepare);
				TypeHandler<Poco::UInt8>::prepare(pos++, obj.getaction(), pPrepare);
			};
			static void extract(std::size_t pos, Log_Entry& obj, const Log_Entry& defVal, AbstractExtractor::Ptr pExt) {
				Poco::UInt64 noteuid;
				Poco::UInt64 timestamp_value;
				Poco::UInt8 action;
				TypeHandler<Poco::UInt64>::extract(pos++, noteuid, defVal.getnoteuid(), pExt);
				TypeHandler<Poco::UInt64>::extract(pos++, timestamp_value, defVal.gettimestamp().epochMicroseconds(), pExt);
				TypeHandler<Poco::UInt8>::extract(pos++, action, defVal.getaction(), pExt);
				obj.setnoteuid(noteuid);
				Poco::Timestamp timestamp(timestamp_value);
				obj.settimestamp(timestamp);
				obj.setaction(action);
			};
		private:
			TypeHandler();
			~TypeHandler();
			TypeHandler(const TypeHandler&);
			TypeHandler& operator=(const TypeHandler&);
		};
	}
}