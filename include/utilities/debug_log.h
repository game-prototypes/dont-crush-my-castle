//TITLE: Debug Log
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.6
//DESCRIPTION: Logs for warnings and errors
#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <iostream>
//#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

enum log_type {comment,warning,err,fatal_error};

namespace debug_log {
const string version="V0.4.4";
const string log_file="dcmc.log";
const bool show_contact=false;
const string contact_info="Please, contact support";

const bool hide_assert=true;
const bool hide_write=true;
const bool hide_show=true; //true to hide errors

const bool force_assert=false;
const bool force_write=false;
const bool force_show=false; //true to force errors

//report an error
void report(const string &error,log_type type,bool write,bool show,bool assert=false);

//easy-to-use report
void report(const string &error,log_type type=comment);
};
#endif
