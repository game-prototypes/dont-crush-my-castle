//TITLE: Debug Log
//PROJECT: DON´T CRUSH MY CASTLE
//AUTHOR: Andrés Ortiz
//VERSION: 0.1
//DESCRIPTION: Logs for warnings and errors

enum log_type{comment,warning,error,fatal_error}



class debug_log{
      private:
static const string version="V0.1"; 
static const string log_file="dcmc.log";     
static const bool show_contact=true;           
              
static const bool hide_assert=false;
static const bool hide_write=false;
static const bool hide_show=false; //true to hide errors

static const bool force_assert=false;
static const bool force_write=false;
static const bool force_show=false; //true to force errors


   public:      
    static void report(string error,log_type=comment){
           report(error,log_type,false,true,false);       
           }
    static void report(string error,log_type,bool write,bool show,bool assert=false){
                string error_msg="Log:"
                switch(log_type){
                                 case comment: 
                                      error_msg+="Comment";
                                 break;
                                 case warning: 
                                 error_msg+="Warning";
                                 break;
                                 case error:
                                 error_msg+="Error";
                                 break;
                                 case fatal_error:
                                 error_msg+="FATAL ERROR"; 
                                 }
                error_msg+="::"+version;
                if((write==true && hide_write==false) || force_write==true){//Write
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
                cout<<endl<<"----"<<endl;
                }
                if((assert==true && hide_assert==false) || force_assert==true) {//asert
        exit(EXIT_FAILURE);
    }
                
    }
