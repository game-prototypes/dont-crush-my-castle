//TITLE: Debug Log
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.2
//DESCRIPTION: Logs for warnings and errors
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum log_type {comment,warning,err,fatal_error};

namespace debug_log {

     const string version="V0.1";
     const string log_file="dcmc.log";
     const bool show_contact=false;
     const string contact_info="Please, contact support";

     const bool hide_assert=false;
     const bool hide_write=false;
     const bool hide_show=false; //true to hide errors

     const bool force_assert=false;
     const bool force_write=false;
     const bool force_show=false; //true to force errors

     //report an error
     void report(string error,log_type type,bool write,bool show,bool assert=false) {
        string error_msg=version+"::Log - ";
        switch(type) {
        case comment:
            error_msg+="Comment";
            break;
        case warning:
            error_msg+="Warning";
            break;
        case err:
            error_msg+="Error";
            break;
        case fatal_error:
            error_msg+="FATAL ERROR";
        }
        if((write==true && hide_write==false) || force_write==true) { //Write
            ofstream out;
            out.open(log_file.c_str(),ios::app);
            out<<error_msg<<endl<<error;
            if(assert==true) out<<" (asserted)";
            out<<endl<<"------------"<<endl;
            out.close();
        }
        if((show==true && hide_show==false) || force_show==true) {//Show
            cout<<"----";
            cout<<endl<<error_msg<<endl<<error;
            if(assert==true) cout<<" (asserted)";
            if(show_contact==true) cout<<endl<<contact_info<<endl;
            cout<<endl<<"----"<<endl;
        }
        if((assert==true && hide_assert==false) || force_assert==true) {//asert
            exit(EXIT_FAILURE);
        }
    }
    
    //easy-yo-use report
    void report(string error,log_type type=comment) {
        report(error,type,false,true,false);
    }
};
