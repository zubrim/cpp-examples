#include "note.h"

/// Note's member functions implementation
Poco::UInt64 Note::getuid() const {
	return uid;
};
std::string Note::gettitle() const {
	return title;
};
Log *Note::getlog_ptr() const {
	return log_ptr;
};
void Note::setuid(Poco::UInt64 uid) {
	this->uid = uid;
};
void Note::settitle(std::string text) {
	this->title = text;
};
void Note::setlog_ptr(Log& log) {
	this->log_ptr = &log;
};
void Note::print_log() {
	for (auto it = log_ptr->begin(); it < log_ptr->end(); ++it) {
		std::cout << it->gettimestamp().epochMicroseconds() << std::endl;
	}
}

/// Log_Entry's member functions implementation
Poco::UInt64 Log_Entry::getnoteuid() const {
	return noteuid;
};
Poco::Timestamp Log_Entry::gettimestamp() const {
	return timestamp;
};
Poco::UInt8 Log_Entry::getaction() const {
	return action;
};
void Log_Entry::setnoteuid(Poco::UInt64 noteuid) {
	this->noteuid = noteuid;
};
void Log_Entry::settimestamp(Poco::Timestamp timestamp) {
	this->timestamp = timestamp;
};
void Log_Entry::setaction(Poco::UInt8) {
	this->action = action;
};