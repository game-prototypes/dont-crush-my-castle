//TITLE: Debug Log
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.5
//DESCRIPTION: Logs for warnings and errors

#include "debug_log.h"

//report an error
void debug_log::report(const string &error,log_type type,bool write,bool show,bool assert) {
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
//easy-to-use report
void debug_log::report(const string &error,log_type type) {
    report(error,type,false,true,false);
}