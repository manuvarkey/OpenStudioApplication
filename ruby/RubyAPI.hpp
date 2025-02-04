/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) OpenStudio Coalition and other contributors.
*  See also https://openstudiocoalition.org/about/software_license/
***********************************************************************************************************************/

#ifndef RUBYAPI_HPP
#define RUBYAPI_HPP

#if (_WIN32 || _MSC_VER)
#  ifdef openstudio_rb_EXPORTS
#    define RUBY_API __declspec(dllexport)
#  elif defined openstudio_modeleditor_rb_EXPORTS
#    define RUBY_API __declspec(dllexport)
#  else
#    define RUBY_API __declspec(dllimport)
#  endif
#else
#  define RUBY_API
#endif

#endif
