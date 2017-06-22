#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status {
 public:
 	Status() {
 		_ok = true;
 		_msg = "";
 	}

 	Status(bool ok, std::string& msg) {
 		_ok = ok;
 		_msg = msg;
 	}
 	
 	bool ok() {
 		return _ok;
 	}

 	std::string msg() {
 		return _msg;
 	}

 	void set_ok(bool ok) {
 		_ok = ok;
 	}

 	void set_msg(std::string msg) {
 		_msg = msg;
 	}
 private:
 	bool _ok;
 	std::string _msg;
};

#endif