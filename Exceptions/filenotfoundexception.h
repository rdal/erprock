#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <QObject>
#include <stdexcept> // stdexcept header file contains runtime_error
using std::runtime_error; // Standard C++ library class runtime_error

//!  Exception launched when file is not found
/*!
  \author Rafael Donato <rafaeldonato@gmail.com>

  This class is an exception that is launched when file is not found.
*/
class FileNotFoundException : public runtime_error
{
public:
    //! Default constructor.
    /*!
    * Create a new instance of FileNotFoundException.
    */
    FileNotFoundException();
};

#endif // FILENOTFOUNDEXCEPTION_H
