#include "filenotfoundexception.h"

FileNotFoundException::FileNotFoundException() : runtime_error( "File not found! Verify its path and try again.")
{
}
